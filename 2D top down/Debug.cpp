#include "Debug.h"

DebugMessage::DebugMessage(std::string fileName, std::string functionName, std::string coderMessage, std::string programMessage)
{
	this->fileName = fileName;
	this->functionName = functionName;
	this->coderMessage = coderMessage;
	this->programMessage = programMessage;
}

Debug::Debug()
{
	showMessagesOnConsole = false;
}

void Debug::LogError(std::string fileName, std::string functionName, std::string coderMessage, std::string programMessage)
{
	DebugMessage newMessage(fileName, functionName, coderMessage, programMessage);

	if (showMessagesOnConsole)
		std::cout << fileName + ":" + functionName + " | " + coderMessage + ":" + programMessage;
}