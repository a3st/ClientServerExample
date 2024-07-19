#pragma once

#include "thread_pool.h"

namespace example
{
    class Server
    {
      public:
        Server(std::string const& logPath);

        ~Server();

        void run(std::string const& server, uint16_t const port);

      private:
        int32_t serverSocket;
        std::ofstream log;
        ThreadPool threadPool;
        std::mutex mutex;
    };
} // namespace example