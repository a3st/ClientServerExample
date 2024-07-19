#include "precompiled.h"
#include "server.h"

using namespace example;

int32_t main(int32_t const argc, char** argv)
{
    if (argc < 2)
    {
        std::cout << "usage: server [port]" << std::endl;
        return EXIT_SUCCESS;
    }
    int16_t const port = std::stoi(argv[1]);

    try
    {
        Server server("log.txt");
        server.run("127.0.0.1", port);
        return EXIT_SUCCESS;
    }
    catch (std::runtime_error e)
    {
        std::cerr << e.what() << std::endl;
        return EXIT_FAILURE;
    }
}