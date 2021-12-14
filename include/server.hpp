#ifndef SERVER_H
#define SERVER_H

State run_server(int portno, State s = State());
State run_server_once(int portno, State s);

#endif