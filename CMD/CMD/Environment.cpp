#include "stdafx.h"
#include "Environment.h"
#include "stringFunction.h"
#include <iostream>
#include "GlobalVariables.h"

using namespace std;

//Constructor
Environment::Environment() :commandsHistory(), fs() {
}

// Destructor
Environment::~Environment()
{
	clear();

}

// Copy Constructor
Environment::Environment(const Environment &other) :commandsHistory(other.commandsHistory), fs(other.fs)
{
	copy(other);
	
}

// Move Constructor
Environment::Environment(Environment &&other) :commandsHistory(other.commandsHistory), fs(other.fs)//do we need to do it recursively or the changing of the first pointers are enough?
{
	unsigned int size = getHistory().size();
	for (unsigned int i = 0; i < size; i++)
	{
		commandsHistory[i] = other.commandsHistory[i];
		other.commandsHistory[i] = nullptr;
	}
	
}

// Copy Assignment
Environment& Environment::operator=(const Environment &other)
{
	if (this != &other)
	{
		clear();
		copy(other);
	}

	return *this;
	
}

// Move Assignment
Environment& Environment::operator=(Environment &&other)
{
	if (this != &other)
	{
		clear();
		unsigned int size = getHistory().size();
		for (unsigned int i = 0; i < size; i++)
		{
			commandsHistory[i] = other.commandsHistory[i];
			other.commandsHistory[i] = nullptr;
		}
	}
	
	return *this;
}

vector<BaseCommand*>& Environment::getHistory() {
	return commandsHistory;
}

BaseCommand* Environment::getCommand(string args)
{
	string com = getComString(args);


	if (com.compare("pwd") == 0)
		return new PwdCommand(args);
	else  if (com.compare("ls") == 0)
		return new LsCommand(args);
	else  if (com.compare("cd") == 0)
		return new CdCommand(args);
	else  if (com.compare("mkdir") == 0)
		return new MkdirCommand(args);
	else  if (com.compare("mkfile") == 0)
		return new MkfileCommand(args);
	else  if (com.compare("cp") == 0)
		return new CpCommand(args);
	else  if (com.compare("rename") == 0)
		return new RenameCommand(args);
	else  if (com.compare("rm") == 0)
		return new RmCommand(args);
	else  if (com.compare("mv") == 0)
		return new MvCommand(args);
	else  if (com.compare("history") == 0)
		return new HistoryCommand(args, getHistory());
	else  if (com.compare("exec") == 0)
		return new ExecCommand(args, getHistory());
	else return new ErrorCommand(com + " " + args);

}

void Environment::clear() {

	unsigned int size = commandsHistory.size();
	for (unsigned int i = 0; i < size; i++) {
		delete commandsHistory[i];
		commandsHistory[i] = nullptr;

	}
	commandsHistory.clear();

}


void Environment::copy(const Environment &other)
{
	unsigned int size = (&other)->commandsHistory.size();
	for (unsigned int i = 0; i < size; i++)
	{
		BaseCommand *bs = getCommand((&other)->commandsHistory[i]->getArgs());
		commandsHistory.push_back(bs);
	}
	fs = other.fs;
}

FileSystem& Environment::getFileSystem() {
	return fs;
}

void Environment::addToHistory(BaseCommand *command) {
	commandsHistory.push_back(command);
}

void Environment::start() {
	bool exit = false;
	string userInput = "";
	while (!exit) {
		cout << fs.getWorkingDirectory().getAbsolutePath() << ">";
		getline(cin, userInput);
		if (userInput == "exit")
		{
			exit = true;
		}
		else
		{
			BaseCommand *com = getCommand(userInput);
			com->execute(fs);
			addToHistory(com);

		}

	}
}
