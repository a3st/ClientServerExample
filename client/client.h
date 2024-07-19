#pragma once

namespace example
{
    class Client
    {
      public:
        Client(std::string const& userName);

        ~Client();

        void setConnectionTime(uint64_t const seconds);

        void run(std::string const& server, uint32_t const port);

      private:
        int32_t clientSocket;
        std::string userName;
        uint64_t seconds;

        std::string getTime() const;
    };
} // namespace example