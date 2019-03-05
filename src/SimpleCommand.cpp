#include <iostream>
#include "SimpleCommand.h"
#include <unistd.h>
#include <cstring>
#include <pwd.h>
#include <fcntl.h>
#include <wait.h>



void SimpleCommand::execute() {
    unsigned long arg = arguments.size() + 1;
    char *argument[arg + 1];

    argument[0] = const_cast<char *>(command.c_str());
    int index = 1;

    for (auto &argu : arguments){
        argument[index] = const_cast<char *>(argu.c_str());
        ++index;
    }
    argument[index] = nullptr;


	if (command == "exit"){
		exit(0);
	} else if (strcmp(argument[0], "cd") == 0){
	    char *toDir;

	    if (arg == 1){
	        char *home = getenv("HOME");

	        if (home == nullptr){
	            home = getpwuid(getuid())->pw_dir;
	        }
	        toDir = home;
	    } else if (arg == 2){
	        toDir = argument[1];
	    } else{
	        std::cerr << "Incorrect command!" << std::endl;
            return;
	    }
	    chdir(toDir);
        return;
	}

	for (auto &redirect : redirects){
	    int replacing = redirect.getOldFileDescriptor();
	    int newDescr;
	    if (redirect.getType() == IORedirect::OUTPUT){
	        newDescr = open(redirect.getNewFile().c_str(), O_CREAT| O_WRONLY | S_IRWXU);
	    } else if (redirect.getType() == IORedirect::APPEND){
	        newDescr = open(redirect.getNewFile().c_str(), O_CREAT | O_WRONLY | O_APPEND | S_IRWXU);
	    } else if (redirect.getType() == IORedirect::INPUT){
	        newDescr = open(redirect.getNewFile().c_str(), O_RDONLY);
	    }
	    dup2(newDescr, replacing);
	    close(newDescr);
	}

	execvp(argument[0], argument);
}
