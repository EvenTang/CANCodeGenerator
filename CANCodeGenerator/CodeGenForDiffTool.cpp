#include "CodeGenForDiffTool.h"



CodeGenForDiffTool::CodeGenForDiffTool()
{
}


CodeGenForDiffTool::~CodeGenForDiffTool()
{
}

std::vector<std::string> CodeGenForDiffTool::GenerateCode(DBCFileDescriptor const & _file_descriptor)
{
	auto source_code = std::vector<std::string>();

	for (auto message : _file_descriptor.Messages()) {
		source_code += GetMessageInitalCode(message);
	}

	return source_code;
}

std::vector<std::string> CodeGenForDiffTool::GetMessageInitalCode(Message const & _msg)
{
	auto source_code = std::vector<std::string>();

	//  
	//  m_message_pool[1620] = Message("CAN_Message_1", std::vector<Signal>{
	//  	Signal("SIG_12_05", 55, 16, true),
	//  	Signal("SIG_05",    39, 16, true),
	//  	Signal("SIG_06",    23, 16, true),
	//  	Signal("SIG_07",    7, 16, true),
	//  });
	//
	source_code.push_back("m_message_pool[" + std::to_string(_msg.ID()) + "] = Message(\"" + _msg.Name() + "\", std::vector<Signal>{");
	for (auto signal : _msg.Signals()) {
		auto init_signal = "    Signal(\"" + 
			signal.Name() + 
			"\", " +
			std::to_string(signal.StartBit()) + 
			", " + 
			std::to_string(signal.SignalSize()) + 
			", " + 
			(signal.IsBigEndian() ? "true" : "false") +
			"),";

		source_code.push_back(init_signal);
	}
	source_code.push_back("});");

	return source_code;
}

