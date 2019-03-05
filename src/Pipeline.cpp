#include <iostream>
#include <boost/process/pipe.hpp>
#include "Pipeline.h"
#include "SimpleCommand.h"

/**
 * Destructor.
 */
Pipeline::~Pipeline() {
	for( SimpleCommand *cmd : commands )
		delete cmd;
}

/**
 * Executes the commands on this pipeline.
 */
void Pipeline::execute() {
	std::cout << "FIXME: You should change Pipeline::execute()" << std::endl;

//	SimpleCommand *prevCommand = nullptr;

	for( SimpleCommand *cmd : commands ) {
		// FIXME: Probably need to set up some pipe here?
//        if(prevCommand) {
//            int pipeline[2];
//            pipe( pipeline );
//            if (fork() != 0) {
//                close( pipeline[0] ); // not needed
//                // by parent
//                // write to pipeline[1] using write()
//            }
//            else { // child process
//                close( pipeline[1] ); // not needed
//                // by child
//                // read from pipeline[0] using read()
//            }
//        }
//


       cmd->execute();
	}
}