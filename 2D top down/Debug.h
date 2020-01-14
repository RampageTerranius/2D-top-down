#pragma once

#include <string>
#include <vector>
#include <iostream>

class DebugMessage
{
private:
	std::string fileName;
	std::string functionName;
	std::string coderMessage;
	std::string programMessage;
public:
	DebugMessage(std::string fileName, std::string functionName, std::string coderMessage, std::string programMessage);
	std::string FileName() { return fileName; }
	std::string FunctionName() { return functionName; }
	std::string CoderMessage() { return coderMessage; }
	std::string ProgramMessage() { return programMessage; }
};

class Debug
{
public:
	Debug();
	bool showMessagesOnConsole;
	void LogError(std::string fileName, std::string functionName, std::string coderMessage, std::string programMessage);

private:
	std::vector<DebugMessage> msg;
};
