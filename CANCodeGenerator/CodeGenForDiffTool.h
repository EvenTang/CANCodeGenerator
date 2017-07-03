#pragma once

#include <vector>
#include <string>

#include "DBCAnalyzer.h"
#include "CommonlibsForCodeGen.h"


//  @brief A generator for the following senario
//
//  BO_ 1620 CAN_Message_1: 8 BCM
//    SG_ SIG_12_05 : 55 | 16@0+ (0.001, 0)[0 | 5] "V"  ECU, BCM
//    SG_ SIG_05 : 39 | 16@0+ (0.001, 0)[0 | 5] "V"  ECU, BCM
//    SG_ SIG_06 : 23 | 16@0+ (0.001, 0)[0 | 5] "V"  ECU, BCM
//    SG_ SIG_07 : 7 | 16@0+ (0.001, 0)[0 | 5] "V"  ECU, BCM
//  
//  	||
//  	||
//  	\/
//  
//  m_message_pool[1620] = Message("CAN_Message_1", std::vector<Signal>{
//  	Signal("SIG_12_05", 55, 16, true),
//  	Signal("SIG_05",    39, 16, true),
//  	Signal("SIG_06",    23, 16, true),
//  	Signal("SIG_07",    7, 16, true),
//  });
//
class CodeGenForDiffTool
{
public:
	CodeGenForDiffTool(std::string const & _map_name);
	~CodeGenForDiffTool();

public:
	std::vector<std::string> GenerateCode(DBCFileDescriptor const & _file_descriptor);

private:
	std::vector<std::string> GetMessageInitalCode(Message const & _msg);

private:
	std::string m_map_name;

};

