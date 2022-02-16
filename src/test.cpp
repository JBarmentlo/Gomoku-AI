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
// Example: WebSocket SSL server, synchronous
//
//------------------------------------------------------------------------------

#include "test.hpp"

#include <boost/beast/core.hpp>
#include <boost/beast/ssl.hpp>
#include <boost/beast/websocket.hpp>
#include <boost/beast/websocket/ssl.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <boost/asio/ssl/stream.hpp>
#include <cstdlib>
#include <functional>
#include <iostream>
#include <string>
#include <thread>

namespace beast = boost::beast;         // from <boost/beast.hpp>
namespace http = beast::http;           // from <boost/beast/http.hpp>
namespace websocket = beast::websocket; // from <boost/beast/websocket.hpp>
namespace net = boost::asio;            // from <boost/asio.hpp>
namespace ssl = boost::asio::ssl;       // from <boost/asio/ssl.hpp>
using tcp = boost::asio::ip::tcp;       // from <boost/asio/ip/tcp.hpp>

//------------------------------------------------------------------------------

// Echoes back all received WebSocket messages
void
do_session(tcp::socket socket, ssl::context& ctx)
{
    try
    {
        // Construct the websocket stream around the socket
        websocket::stream<beast::ssl_stream<tcp::socket&>> ws{socket, ctx};

        // Perform the SSL handshake
        ws.next_layer().handshake(ssl::stream_base::server);

        // Set a decorator to change the Server of the handshake
        ws.set_option(websocket::stream_base::decorator(
            [](websocket::response_type& res)
            {
                res.set(http::field::server,
                    std::string(BOOST_BEAST_VERSION_STRING) +
                        " websocket-server-sync-ssl");
            }));

        // Accept the websocket handshake
        ws.accept();

        for(;;)
        {
            // This buffer will hold the incoming message
            beast::flat_buffer buffer;

            // Read a message
            ws.read(buffer);

            // Echo the message back
            ws.text(ws.got_text());
            ws.write(buffer.data());
        }
    }
    catch(beast::system_error const& se)
    {
        // This indicates that the session was closed
        if(se.code() != websocket::error::closed)
            std::cerr << "Error: " << se.code().message() << std::endl;
    }
    catch(std::exception const& e)
    {
        std::cerr << "Error: " << e.what() << std::endl;
    }
}

//------------------------------------------------------------------------------

int runino()
{
    try
    {
        // Check command line arguments.
        auto const address = net::ip::make_address("0.0.0.0");
        auto const port = static_cast<unsigned short>(16784);

        // The io_context is required for all I/O
        net::io_context ioc{1};

        // The SSL context is required, and holds certificates
        ssl::context ctx{ssl::context::tlsv12};

        // // This holds the self-signed certificate used by the server
        // // load_server_certificate(ctx);
		// std::cout << "key" << std::endl;
        // ctx.use_private_key_file("privkey.pem", boost::asio::ssl::context::pem);
        // // ctx.use_private_key_file("/etc/letsencrypt/live/gomoku.deyaberger.fr/privkey.pem", boost::asio::ssl::context::pem);
		// std::cout << "cert" << std::endl;
		// ctx.use_certificate_chain_file("newcert.pem");
		// // ctx.use_certificate_file("/etc/letsencrypt/live/gomoku.deyaberger.fr/cert.pem", boost::asio::ssl::context::pem);
		// std::cout << "end" << std::endl;
        // // The acceptor receives incoming connections


		ctx.set_password_callback(
			[](std::size_t,
				boost::asio::ssl::context_base::password_purpose)
			{
				return "test";
			});

		ctx.set_options(
			boost::asio::ssl::context::default_workarounds |
			boost::asio::ssl::context::no_sslv2 |
			boost::asio::ssl::context::single_dh_use);

		ctx.use_certificate_chain_file("newcert.pem");

		ctx.use_private_key_file("privkey.pem",boost::asio::ssl::context::file_format::pem);

		ctx.use_tmp_dh_file("dh512.pem");








        tcp::acceptor acceptor{ioc, {address, port}};
        for(;;)
        {
            // This will receive the new connection
            tcp::socket socket{ioc};

            // Block until we get a connection
            acceptor.accept(socket);

            // Launch the session, transferring ownership of the socket
            std::thread(
                &do_session,
                std::move(socket),
                std::ref(ctx)).detach();
        }
    }
    catch (const std::exception& e)
    {
        std::cerr << "Error: " << e.what() << std::endl;
        return EXIT_FAILURE;
    }
}
