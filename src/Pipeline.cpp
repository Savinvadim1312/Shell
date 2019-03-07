#include <iostream>
#include "Pipeline.h"
#include "SimpleCommand.h"
#include <unistd.h>
#include <wait.h>

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

    int pipeline[2];
    int prevOutputPipeline = 0;
    for (int i = 0; i < commands.size(); i++) {

        if (!commands[i]->canBeForked()) {
            commands[i]->execute();
            continue;
        }

        // for all the commands except the last one, create a pipe
        if (i != commands.size() - 1) {
            pipe( pipeline );
        }

        //create a fork and execute the command in the child process
        int cid = fork();
        if (cid == 0) {
            // for all the commands except first one, redirect the output of the previous pipe to the input
            if (i != 0) {
                dup2(prevOutputPipeline, 0);
                close(prevOutputPipeline);
            }

            // for all the commands except the last one, redirect the output to the pipe created
            if (i != commands.size() - 1) {
                close(pipeline[0]);
                dup2(pipeline[1], 1);
                close(pipeline[1]);
            }

            commands[i]->execute();
            break;
        }
        else {
            if (i >= 1) {
                close(prevOutputPipeline);
            }

            if (i != commands.size() - 1) {
                prevOutputPipeline = pipeline[0];
                close(pipeline[1]);
            }

            // we are waiting for the process to finish if it is not the last one, or if it is the last one and should be syncrounous
            if (i != commands.size() - 1 || i == commands.size() - 1 && !async) {
                int returnValue;
                waitpid( cid, &returnValue, 0 );
                std::cout << "Process X ended with status code " << returnValue << std::endl;
            }
        }
	}
}