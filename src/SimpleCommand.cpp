#include <iostream>
#include "SimpleCommand.h"
#include <unistd.h>
#include <cstring>
#include <pwd.h>
#include <fcntl.h>
#include <wait.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string>
#include <fstream>
#include <sstream>

inline bool file_exists (const std::string& name) {
    struct stat buffer;
    return (stat (name.c_str(), &buffer) == 0);
}

char * get_home_directory () {
    char *home = getenv("HOME");

    if (home == nullptr){
        home = getpwuid(getuid())->pw_dir;
    }
    return home;
}

std::vector<std::string> get_path_folders() {
	std::stringstream ss(getenv("PATH"));
	std::vector<std::string> result;

	while( ss.good() )
	{
		std::string substr;
		getline( ss, substr, ':' );
		result.push_back( substr );
	}
	return result;
}

void SimpleCommand::execute() {
	if (command == "exit"){
		executeExit();
	} else if (command == "cd"){
		executeCD();
	}
	else {
		executeRunProgramm();
	}
}

void SimpleCommand::handleRedirections() {
	//	redirections
	for (auto &redirect : redirects){
		int newDescr = -1;
		if (redirect.getType() == IORedirect::OUTPUT){
			newDescr = open(redirect.getNewFile().c_str(), O_CREAT | O_WRONLY);
		} else if (redirect.getType() == IORedirect::APPEND){
			newDescr = open(redirect.getNewFile().c_str(), O_CREAT | O_WRONLY | O_APPEND);
		} else if (redirect.getType() == IORedirect::INPUT){
			newDescr = open(redirect.getNewFile().c_str(), O_RDONLY);
		}

		if (newDescr < 0) {
			std::cerr << "Error opening the file" << std::endl;
			return;
		}

		dup2(newDescr, redirect.getOldFileDescriptor());
		close(newDescr);
	}
}

char *const*SimpleCommand::argumentsForProgramm() {
	std::vector<std::string> allArgs (arguments);
	allArgs.insert(allArgs.begin(), command);
	return vectorToCharArr(allArgs);
}

char *const*SimpleCommand::vectorToCharArr(const std::vector<std::string> &cppStrings) {
	std::vector<const char*> cStrings;
	for(int i = 0; i < cppStrings.size(); ++i)
	{
		cStrings.push_back(cppStrings[i].c_str());
	}
	cStrings.push_back(nullptr);

	return const_cast<char *const *>(&cStrings[0]);
}

void SimpleCommand::executeExit() {
	exit(0);
}

void SimpleCommand::executeCD() {
	char *toDir;

	if (arguments.empty()){
		toDir = get_home_directory();
	} else if (arguments.size() == 1){
		toDir = const_cast<char *>(arguments[0].c_str());
	} else{
		std::cerr << "Incorrect command!" << std::endl;
		return;
	}
	chdir(toDir);
	return;
}

void SimpleCommand::executeRunProgramm() {
	std::string program_path = getProgramPath();
	if(program_path.empty()) {
		return;
	}

    // then this is the new child process
    handleRedirections();
    execvp(const_cast<char *>(program_path.c_str()), argumentsForProgramm());

}

std::string SimpleCommand::getProgramPath() {
	// if file does not exist, try to look in the PATH folders
	std::string program_path = "";
	if(file_exists(command)) {
		program_path = command;
	}
	else {
		// get folders from PATH
		std::vector<std::string> folders = get_path_folders();
		for(const auto &folder: folders) {
			// if the command exists in this folders, break form the loop and execute it
			if (file_exists(folder + separator() + command)) {
				program_path = folder + separator() + command;
				break;
			}
		}
	}

	//if it didn't find the file, show an error
	if(program_path.empty()) {
		std::cerr << "Command not found!" << std::endl;
	}

	return program_path;
}

bool SimpleCommand::canBeForked() {
    return command != "cd" && command != "exit";
}
