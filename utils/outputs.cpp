#include <iostream>
#include <unistd.h>

/**
 * Test program that prints some lines to both stdout and stderr,
 * so that we can test I/O redirection.
 */
int main()
{
    std::cout << "O: Input comes from " << (isatty(STDIN_FILENO) ? "the terminal" : "somewhere else") << std::endl;
    std::cerr << "E: Ouput goes to " << (isatty(STDOUT_FILENO) ? "the terminal" : "somewhere else") << std::endl;
    std::cout << "O: Errors go to " << (isatty(STDERR_FILENO) ? "the terminal" : "somewhere else") << std::endl;

    std::cout << "O: Lorem ipsum dolor sit amet, consectetur adipiscing elit." << std::endl;
    std::cerr << "E: Morbi blandit posuere eros, vel ornare mauris." << std::endl;
    std::cout << "O: Vestibulum ante ipsum primis in faucibus orci luctus et ultrices posuere cubilia." << std::endl;
    std::cerr << "E: Aenan ultrices dolor id nisl mollis, eu tempor eros tincidunt." << std::endl;
    std::cout << "O: Cras diam risus, elementum sit amet lectus id, feugiat condimentum enim." << std::endl;
}
