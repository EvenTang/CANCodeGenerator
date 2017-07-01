#pragma once

#include <vector>
#include <string>

#include "DBCAnalyzer.h"


class CANCodeGenerator
{
public:
	CANCodeGenerator();
	~CANCodeGenerator();

	std::vector<std::string> GenerateCode(DBCFileDescriptor const & _file_descriptor);

private:
	std::vector<std::string> GenerateMessageClassDefinition(Message const & _message);
	std::vector<std::string> GenerateMessageClassHeader(Message const & _message);
	std::vector<std::string> GenerateMessageClassConstructor(Message const & _message);
	std::vector<std::string> GenerateMessageClassUpdateSignalMethod(Message const & _message);
	std::vector<std::string> GenerateMessageClassDataMemberDefinition(Message const & _message);

	
};

