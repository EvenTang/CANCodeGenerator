#pragma once

#include <string>
#include <vector>
#include <cstdint>


class Signal {
	std::string m_signal_name;
	uint8_t m_start_bit;
	uint8_t m_signal_size;
};

class Message {
	std::string m_message_name;
	std::vector<Signal> m_signals;
};

class DBCFileDescriptor {
	std::vector<Message> m_messages;
};


// @brief input a dbc file, output a DBCFileDescriptor for DBC
//     DBC Ref to : <DBC-File-Format-Documentation.pdf>
class DBCAnalyzer
{
public:
	DBCAnalyzer();
	~DBCAnalyzer();


public:
	DBCFileDescriptor Analyze(std::string const & _file_name);
};

