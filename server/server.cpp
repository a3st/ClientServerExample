#include "server.h"
#include "precompiled.h"

namespace example
{
    Server::Server(std::string const& logPath) : log(logPath, std::ios::app)
    {
        serverSocket = ::socket(AF_INET, SOCK_STREAM, 0);
    }

    Server::~Server()
    {
        ::close(serverSocket);
    }

    void Server::run(std::string const& server, uint16_t const port)
    {
        sockaddr_in address{};
        address.sin_family = AF_INET;
        address.sin_port = port;
        address.sin_addr.s_addr = inet_addr(server.c_str());
        auto result = ::bind(serverSocket, reinterpret_cast<sockaddr const*>(&address), sizeof(address));
        if (result == -1)
        {
            throw std::runtime_error("An error occurred while starting the server");
        }

        std::cout << "Server is running... (IP: " << server << ", PORT: " << port << ")" << std::endl;

        result = ::listen(serverSocket, SOMAXCONN);
        if (result == -1)
        {
            throw std::runtime_error("An error occurred while starting the server");
        }

        while (true)
        {
            sockaddr_in address;
            socklen_t addressLength;
            result = ::accept(serverSocket, reinterpret_cast<sockaddr*>(&address), &addressLength);
            if (result == -1)
            {
                throw std::runtime_error("An error occurred while processing the connection");
            }

            threadPool.push_task([this, result]() {
                std::vector<char> buffer(512);
                while (true)
                {
                    auto length = ::recv(result, buffer.data(), buffer.size(), 0);
                    if (length == 0)
                    {
                        ::close(result);
                        return;
                    }
                    else if (length != -1)
                    {
                        {
                            std::unique_lock<std::mutex> lock(mutex);
                            log << std::string(buffer.data(), length) << std::endl;
                        }
                    }
                }
            });
        }
    }
} // namespace example