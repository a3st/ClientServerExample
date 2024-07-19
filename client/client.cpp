#include "client.h"
#include "precompiled.h"

namespace example
{
    Client::Client(std::string const& userName) : userName(userName), seconds(0)
    {
        clientSocket = ::socket(AF_INET, SOCK_STREAM, 0);
    }

    Client::~Client()
    {
        ::close(clientSocket);
    }

    void Client::setConnectionTime(uint64_t const seconds)
    {
        this->seconds = seconds;
    }

    void Client::run(std::string const& server, uint32_t const port)
    {
        sockaddr_in address{};
        address.sin_family = AF_INET;
        address.sin_port = port;
        address.sin_addr.s_addr = inet_addr(server.c_str());
        auto result = ::connect(clientSocket, reinterpret_cast<sockaddr const*>(&address), sizeof(address));
        if (result == -1)
        {
            throw std::runtime_error("An error occurred while connecting to the server");
        }

        std::string message = "[" + this->getTime() + "] " + userName;

        auto length = ::send(clientSocket, message.data(), message.size(), 0);
        if (length == -1)
        {
            throw std::runtime_error("An error occurred while sending the message");
        }

        std::this_thread::sleep_for(std::chrono::seconds(seconds));

        message = "[" + this->getTime() + "] " + userName;

        length = ::send(clientSocket, message.data(), message.size(), 0);
        if (length == -1)
        {
            throw std::runtime_error("An error occurred while sending the message");
        }
    }

    std::string Client::getTime() const
    {
        auto currentTimePoint = std::chrono::system_clock::now();
        time_t currentTime = std::chrono::system_clock::to_time_t(currentTimePoint);
        tm* localTime = std::localtime(&currentTime);
        auto milliseconds =
            std::chrono::duration_cast<std::chrono::milliseconds>(currentTimePoint.time_since_epoch()).count() % 1000;

        std::ostringstream output;
        output << std::put_time(localTime, "%F %T") << "." << std::setw(3) << std::setfill('0') << milliseconds;
        return output.str();
    }
} // namespace example