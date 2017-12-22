#include "stdafx.h"
#include "FileSystem.h"
#include "GlobalVariables.h"
#include <iostream>

//Constructor
FileSystem::FileSystem() :rootDirectory(new Directory("/", nullptr)), workingDirectory(nullptr)
{
	workingDirectory = rootDirectory;
}

// Destructor
FileSystem::~FileSystem()
{
	delete rootDirectory;
	rootDirectory = nullptr;
	workingDirectory = nullptr;
	
}

// Copy Constructor
FileSystem::FileSystem(const FileSystem &other) :rootDirectory(new Directory(*other.rootDirectory)), workingDirectory(new Directory(*other.workingDirectory))
{
	
}

// Move Constructor
FileSystem::FileSystem(FileSystem &&other) :rootDirectory(other.workingDirectory), workingDirectory(other.workingDirectory)
{
	other.workingDirectory = nullptr;
	other.rootDirectory = nullptr;
	
}

// Copy Assignment
FileSystem& FileSystem::operator=(const FileSystem &other)
{
	if (this != &other)
	{

		delete rootDirectory;
		FileSystem(other);

	}
	
	return *this;

}

// Move Assignment
FileSystem& FileSystem::operator=(FileSystem &&other)
{
	if (this != &other)
	{
		delete rootDirectory;
		rootDirectory = other.rootDirectory;
		workingDirectory = other.workingDirectory;
		other.rootDirectory = nullptr;
		other.workingDirectory = nullptr;
	}
	
	return *this;
}

Directory& FileSystem::getRootDirectory() // Return reference to the root directory
{
	return *rootDirectory;
}
Directory& FileSystem::getWorkingDirectory() // Return reference to the working directory
{
	return *workingDirectory;
}
void FileSystem::setWorkingDirectory(Directory *newWorkingDirectory) // Change the working directory of the file system
{
	workingDirectory = newWorkingDirectory;
}