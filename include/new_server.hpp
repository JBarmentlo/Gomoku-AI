#ifndef NEWSERV
#define NEWSERV

#include <sys/types.h> 
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <iostream>
#include <string.h>
#include <unistd.h>


#include "state.hpp"
#include "defines.hpp"
#include "minimax.hpp"
#include "json.hpp"
#include "utils.hpp"

using json = nlohmann::json;

#define MSGLEN 2048

void		err(const char *msg)
{
    perror(msg);
    exit(1);
}

static void	set_winner(json &response, State s)
{
	// Sets response["winner"] to "black", "white" or "no"
	if (s.game_win)
	{
		if (s.player == BLACK)
			response["winner"] = "white";
		
		if (s.player == WHITE)
			response["winner"] = "black";
	}
	else
	{
		response["winner"] = "no";
	}
}

static void	set_player(json &response, State s)
{
	// Sets response["player"] to "black", "white"

	if (s.player == BLACK)
		response["player"] = "black";
	
	if (s.player == WHITE)
		response["player"] = "white";
}


static void	add_board_to_json(json &response, State s)
{
	std::stringstream ss;
	ss << s.b_board << std::endl;
	std::string out = ss.str();
	response["black_board"] = out;
	std::stringstream sss;
	sss << s.w_board << std::endl;
	std::string out2 = sss.str();
	response["white_board"] = out2;
}


static void	add_game_state_to_json(json &response, State &s)
{
	set_winner(response, s);
	set_player(response, s);
	add_board_to_json(response, s);
	response["w_captures"] = s.w_captures;
	response["b_captures"] = s.b_captures;
}


int			get_new_connection_fd()
{
	// Creates a socket, binds it to port: PORTNO and accepts one incoming connection and closes the listening socket
	// Returns the fd for the incoming connection socket.

	int sockfd, newsockfd;
	socklen_t clilen;
	char buffer[MSGLEN];
	bzero(buffer,MSGLEN);
	struct sockaddr_in serv_addr, cli_addr;
	int n;

	sockfd =  socket(AF_INET, SOCK_STREAM, 0);
	if (sockfd < 0) 
	err("ERROR opening socket");

	bzero((char *) &serv_addr, sizeof(serv_addr));
		int enable = 1;
		if (setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &enable, sizeof(int)) < 0)
			err("setsockopt(SO_REUSEADDR) failed");

	serv_addr.sin_family		= AF_INET;  
	serv_addr.sin_addr.s_addr	= INADDR_ANY;  
	serv_addr.sin_port			= htons(PORTNO);

	if (bind(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0) 
		err("ERROR on binding");

	listen(sockfd,5);

	clilen = sizeof(cli_addr);
	newsockfd = accept(sockfd, (struct sockaddr *) &cli_addr, &clilen);
	if (newsockfd < 0)
		err("ERROR on accept");
	// n = recv(newsockfd, buffer, MSGLEN, 0);
	n = read(newsockfd, buffer, MSGLEN);
	printf("server: got connection from %s port %d\n",
	inet_ntoa(cli_addr.sin_addr), ntohs(cli_addr.sin_port));
	std::cout << "with the message:\n -------- \n" << buffer << "\n -------- \n" << std::endl;
	close(sockfd);
	return(newsockfd);
}


class play_server
{
private:
	int 	sockfd;
	State	s;
	char	buffer[MSGLEN];
	json 	msg;
	bool 	cpu;
	bool	game_over = false;
	int		depth;

public:
	play_server(int sockfd);
	~play_server();

	void	await_message(void);
	void	connection_closed(void);

	void	handle_message(void);
	void	handle_message_start(void);
	void	handle_message_move(void);

};


play_server::play_server(int sockfd)
{
	this->sockfd = sockfd;
	bzero(this->buffer,MSGLEN);
	// this->s = State();
	// this->s.coord_evaluation_function = eval_surround_square;
}


play_server::~play_server()
{
}


void	play_server::handle_message_start(void)
{
	this->s = State();
	this->s.coord_evaluation_function = eval_surround_square;
	this->cpu = this->msg["cpu"];
	this->depth = this->msg["depth"];

	json response;
	response["type"]	= "game_start";
	response["cpu"]		= this->cpu;
	response["depth"]		= this->depth;

	std::cout << "Sending" << response.dump() << std::endl;
	send(this->sockfd, response.dump().c_str(), response.dump().length(), 0);
}


void	play_server::handle_message_move(void)
{
	json response;
	response["type"]	= "game_state";
	response["illegal"] = false;

	State tmp;
	tmp = this->s;

	std::cout << "Recieved Move: " << msg["move"] << std::endl;
	
	this->s = this->s.make_baby_from_coord(msg["move"]);
	if (is_illegal(this->s))
	{
		response["illegal"] = true;
		this->s = tmp;
		std::cout << "Illegal move, reverting" << std::endl;
	}
	else
	{
		if (this->cpu)
		{
			this->s = this->s.make_baby_from_coord(minimax(s, this->depth));
		}
		else
		{
			response["suggested_move"] = minimax(s, this->depth);
		}
	}

	add_game_state_to_json(response, this->s);
	response["cpu"] = this->cpu;

	std::cout << "Sending" << response.dump() << std::endl;
	send(this->sockfd, response.dump().c_str(), response.dump().length(), 0);
	this->s.print();
}


void	play_server::handle_message(void)
{

	std::cout << "with the message:\n -------- \n" << this->buffer << "\n -------- \n" << std::endl;
	this->msg = json::parse(this->buffer);
	std::cout << this->msg << std::endl;
	bzero(this->buffer,MSGLEN);
	if (this->msg["type"] == "start")
	{
		this->handle_message_start();
	}
	else if (this->msg["type"] == "move")
	{
		this->handle_message_move();
	}
}
	

void	play_server::await_message(void)
{
	int	n;
	std::cout << "Awaiting message" << std::endl;
	bzero(this->buffer,MSGLEN);
	while(true)
	{	
		n = recv(this->sockfd, this->buffer, MSGLEN, 0);
		// recv();
		if (n > 0)
		{
			std::cout << "Recieved msg of len: " << n << std::endl;
			this->handle_message();
		}
		if (n == 0)
		{
			std::cout << "N < 0 IUUHAHGSDKJHGASDKJHGAWSDKJHG" << std::endl;
			break;
		}
	}
}


#endif // !NEWSERV
