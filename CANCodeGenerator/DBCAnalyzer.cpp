#include "DBCAnalyzer.h"

#include <regex>


DBCAnalyzer::DBCAnalyzer()
{
}


DBCAnalyzer::~DBCAnalyzer()
{
}

DBCFileDescriptor DBCAnalyzer::Analyze(std::string const & _file_name)
{
	DBCFileDescriptor file_descriptor;
		
	//AnalyzerDBCByLines();

	return std::move(file_descriptor);
}

void DBCAnalyzer::AnalyzerDBCByLines(std::vector<std::string> const & _lines)
{
	DBCFileDescriptor file_descriptor;
	for (auto iter = _lines.begin(); iter != _lines.end(); ++iter) {
		if (MessageRecognizer(*iter, file_descriptor))
		{
			auto & msg = file_descriptor.Messages().back();
			++iter;
			while (SignalRecognizer(*iter, msg)) {
				++iter;
			}
			--iter;
		}
	}
}

bool DBCAnalyzer::MessageRecognizer(std::string const & _line, DBCFileDescriptor & _file_descriptor)
{
	// message = BO_ message_id message_name ':' message_size transmitter{ signal };
	std::regex message_definition(R"(BO_\s+(\d+)\s+(\w+)\s+:.*)");
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
	signal.SetBitInfo(
		static_cast<uint8_t>(std::stoul(m[2].str())), 
		static_cast<uint8_t>(std::stoul(m[3].str())));
	signal.SetIsBigEndian(m[4].str() == "1");
	signal.SetIsUnsigned(m[5].str() == "+");

	_msg.AddSignal(signal);
	
	return true;
}
