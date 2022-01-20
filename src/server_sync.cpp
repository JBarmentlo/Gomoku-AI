//
// Copyright (c) 2016-2019 Vinnie Falco (vinnie dot falco at gmail dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// Official repository: https://github.com/boostorg/beast
//

//------------------------------------------------------------------------------
//
// Example: WebSocket server, synchronous
//
//------------------------------------------------------------------------------

#include <boost/beast/core.hpp>
#include <boost/beast/websocket.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <cstdlib>
#include <functional>
#include <iostream>
#include <string>
#include <thread>

#include "state.hpp"
#include "minimax.hpp"
#include "json.hpp"

using json = nlohmann::json;

// #include <boost/json.hpp>

namespace beast = boost::beast;         // from <boost/beast.hpp>
namespace http = beast::http;           // from <boost/beast/http.hpp>
namespace websocket = beast::websocket; // from <boost/beast/websocket.hpp>
namespace net = boost::asio;            // from <boost/asio.hpp>
using tcp = boost::asio::ip::tcp;       // from <boost/asio/ip/tcp.hpp>



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

#define MSGLEN 2048
#define PRINT_STATE_ON_MOVE true

class game_handler
{
private:
	int 	sockfd;
	State	s;
	bool 	cpu;
	bool	game_over = false;
	int		depth;

public:
	game_handler();
	~game_handler();

	std::string	handle_message(std::string msg);
	std::string	handle_message_start(json json_msg);
	std::string	handle_message_move(json json_msg);
};


game_handler::game_handler()
{
	this->s = State();
	this->s.coord_evaluation_function = eval_surround_square;
}


game_handler::~game_handler()
{
}


std::string game_handler::handle_message_start(json json_msg)
{
	this->s = State();
	this->s.coord_evaluation_function = eval_surround_square;


	this->cpu           = json_msg["cpu"];
	this->depth         = json_msg["depth"];

	json response;
	response["type"]	= "game_start";
	response["cpu"]		= this->cpu;
	response["depth"]	= this->depth;

	// std::cout << "Sending" << response.dump() << std::endl;
	// send(this->sockfd, response.dump().c_str(), response.dump().length(), 0);
    return (response.dump().c_str());
}


std::string	game_handler::handle_message_move(json json_msg)
{
	json response;
	response["type"]	= "game_state";
	response["illegal"] = false;

	State tmp;
	tmp = this->s;

	std::cout << "Recieved Move: " << json_msg["move"] << std::endl;
	if (PRINT_STATE_ON_MOVE)
        this->s.print();
	this->s = this->s.make_baby_from_coord(json_msg["move"]);
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
            if (PRINT_STATE_ON_MOVE)
                this->s.print();
		}
		else
		{
			response["suggested_move"] = minimax(s, this->depth);
		}
	}

	add_game_state_to_json(response, this->s);
	response["cpu"] = this->cpu;

	// std::cout << "Sending" << response.dump() << std::endl;
	// send(this->sockfd, response.dump().c_str(), response.dump().length(), 0);
    return (response.dump().c_str());
}


std::string	game_handler::handle_message(std::string msg)
{
	json json_msg = json::parse(msg);

	if (json_msg["type"] == "start")
	{
		return (this->handle_message_start(json_msg));
	}
	else if (json_msg["type"] == "move")
	{
		return (this->handle_message_move(json_msg));
	}
    return ("Please send a valid JSON");
}

//------------------------------------------------------------------------------

// Echoes back all received WebSocket messages
void
do_session(tcp::socket socket)
{
    try
    {
        // Construct the stream by moving in the socket
        websocket::stream<tcp::socket> ws{std::move(socket)};

        // Set a decorator to change the Server of the handshake
        ws.set_option(websocket::stream_base::decorator(
            [](websocket::response_type& res)
            {
                res.set(http::field::server,
                    std::string(BOOST_BEAST_VERSION_STRING) +
                        " websocket-server-sync");
            }));

        // Accept the websocket handshake
        ws.accept();
		std::cout << "Websocket Connection accepted" << std::endl;
        game_handler game = game_handler();
        for(;;)
        {
            // This buffer will hold the incoming message
            beast::flat_buffer buffer;
            beast::flat_buffer reply_buffer;

            std::string msg;
            std::string response;

            // Read a message
            ws.read(buffer);

            // Echo the message back
            ws.text(ws.got_text());

            msg = beast::buffers_to_string(buffer.data());
            std::cout << "Recieved message:\n ------------\n" << msg << "\n------------" << std::endl;
            response = game.handle_message(msg);
            ostream(reply_buffer) << response;
            ws.write(reply_buffer.data());
            // ws.write(response);
        }
    }
    catch(beast::system_error const& se)
    {
        // This indicates that the session was closed
        if(se.code() != websocket::error::closed)
            std::cerr << "Error: " << se.code().message() << std::endl;
		std::cout << "Websocket Connection closed" << std::endl;
    }
    catch(std::exception const& e)
    {
        std::cerr << "Error: " << e.what() << std::endl;
    }
}

//------------------------------------------------------------------------------

int run_websocket_server(std::string adress, int porto)
{
    try
    {
        // Check command line arguments.
        // if (argc != 3)
        // {
        //     std::cerr <<
        //         "Usage: websocket-server-sync <address> <port>\n" <<
        //         "Example:\n" <<
        //         "    websocket-server-sync 0.0.0.0 8080\n";
        //     return EXIT_FAILURE;
        // }
        std::cout << "porto: " << porto << std::endl;
        auto const address = net::ip::make_address(adress);
        unsigned short const port = static_cast<unsigned short>(porto);
        std::cout << "Starting WebSocket Server on adrress: " << address << ":" << port << std::endl;

        // The io_context is required for all I/O
        net::io_context ioc{1};
        // The acceptor receives incoming connections
        tcp::acceptor acceptor{ioc, {address, port}};
        for(;;)
        {
            // This will receive the new connection
            tcp::socket socket{ioc};

            // Block until we get a connection
            acceptor.accept(socket);
		    std::cout << "Websocket Connection attempt from: " << socket.remote_endpoint() << " to: " << socket.local_endpoint() << std::endl;
            

            // Launch the session, transferring ownership of the socket
            std::thread(
                &do_session,
                std::move(socket)).detach();
        }
    }
    catch (const std::exception& e)
    {
        std::cerr << "Error: " << e.what() << std::endl;
        return EXIT_FAILURE;
    }
}