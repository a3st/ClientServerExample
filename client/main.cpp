#include "client.h"
#include "precompiled.h"

using namespace example;

int32_t main(int32_t const argc, char** argv)
{
    if (argc < 2)
    {
        std::cout << "usage: client [userName] [port] [time]" << std::endl;
        return EXIT_SUCCESS;
    }
    std::string const userName = argv[1];

    if (argc < 3)
    {
        std::cout << "usage: client [userName] [port] [time]" << std::endl;
        return EXIT_SUCCESS;
    }
    int16_t const port = std::stoi(argv[2]);

    if (argc < 4)
    {
        std::cout << "usage: client [userName] [port] [time]" << std::endl;
        return EXIT_SUCCESS;
    }
    uint64_t const time = std::stoi(argv[3]);

    try
    {
        Client client(userName);
        client.setConnectionTime(time);
        client.run("127.0.0.1", port);
        return EXIT_SUCCESS;
    }
    catch (std::runtime_error e)
    {
        std::cerr << e.what() << std::endl;
        return EXIT_FAILURE;
    }
}