#include <cstdlib>
#include <iostream>
#include <unistd.h>

/**
 * Test program that counts down for a certain number of seconds.
 * You can supply the number of seconds as an argument or the default 3 seconds
 * is used.
 */
int main( int argc, char *argv[] )
{
    // Get number of seconds
    int numSeconds = 3;
    if( argc > 1 )
    {
        numSeconds = std::atoi(argv[1]);
        if( numSeconds < 1 )
            numSeconds = 3;
    }

    // Count down
    while( numSeconds > 0 )
    {
        std::cout << "Process destruction in " << numSeconds << " seconds..." << std::endl;
        sleep(1);
        numSeconds--;
    }

    return 0;
}
