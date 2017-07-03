#include "DBCAnalyzer.h"

#include <regex>
#include <fstream>


DBCAnalyzer::DBCAnalyzer()
{
}


DBCAnalyzer::~DBCAnalyzer()
{
}

DBCFileDescriptor DBCAnalyzer::Analyze(std::string const & _file_name)
{
	DBCFileDescriptor file_descriptor;
		
	std::ifstream in_file(_file_name);
	std::vector<std::string> file_lines;
	std::string line;
	while (std::getline(in_file, line)) {
		file_lines.push_back(line);
	}
	AnalyzerDBCByLines(file_lines, file_descriptor);

	return std::move(file_descriptor);
}

void DBCAnalyzer::AnalyzerDBCByLines(std::vector<std::string> const & _lines, DBCFileDescriptor & _file_descriptor)
{
	for (auto iter = _lines.begin(); iter != _lines.end(); ++iter) {
		if (MessageRecognizer(*iter, _file_descriptor))
		{
			auto & msg = _file_descriptor.Messages().back();
			++iter;
			while (iter != _lines.end() && SignalRecognizer(*iter, msg)) {
				++iter;
			}
			--iter;
		}
	}
}

bool DBCAnalyzer::MessageRecognizer(std::string const & _line, DBCFileDescriptor & _file_descriptor)
{
	// message = BO_ message_id message_name ':' message_size transmitter{ signal };
	std::regex message_definition(R"(BO_\s+(\d+)\s+(\w+)\s*:.*)");
	std::smatch m;
	if (!std::regex_match(_line, m, message_definition)) {
		return false;
	}
	
	Message msg;
	msg.SetMessageName(m[2].str());
	msg.SetMsgID(std::stol(m[1].str()));

	_file_descriptor.AddMessage(msg);

	return true;
}

bool DBCAnalyzer::SignalRecognizer(std::string const & _line, Message & _msg)
{
	//signal = 'SG_' signal_name multiplexer_indicator ':' start_bit '|'
	//	signal_size '@' byte_order value_type '(' factor ',' offset ')'
	//	'[' minimum '|' maximum ']' unit receiver{ ',' receiver };
	std::regex signal_definition(R"(\s*SG_\s+(\w+)\s+:\s+(\d+)\|(\d+)@(\d)(\+|-).*)");
	std::smatch m;
	if (!std::regex_match(_line, m, signal_definition)) {
		return false;
	}

	Signal signal;
	signal.SetName(m[1].str());

	// 1 - little endian (Intel)
    // 0 - big endian (Motorola)
	// @attention : this is different from DBC-File-Format-Documentation.pdf
	//              chapter 8.1 Signal Definition
	//              But matches the real behavior of CANdb++
	signal.SetIsBigEndian(m[4].str() == "0");

	uint8_t start_bit = static_cast<uint8_t>(std::stoul(m[2].str()));   // Attention! start_bit should be : LSB position
	uint8_t signal_size = static_cast<uint8_t>(std::stoul(m[3].str())); 
	if (signal.IsBigEndian()) {
		start_bit = ChangMotorolaOrderMSBT2LSB(start_bit, signal_size);
	}

	signal.SetBitInfo(start_bit, signal_size);
	
	signal.SetIsUnsigned(m[5].str() == "+");

	_msg.AddSignal(signal);
	
	return true;
}

uint8_t DBCAnalyzer::ChangMotorolaOrderMSBT2LSB(uint8_t start_bit, uint8_t signal_size) {
	while (--signal_size) {
		if (0 == (start_bit % 8)) {
			start_bit += 15;
		}
		else {
			start_bit--;
		}
	}
	return start_bit;
}