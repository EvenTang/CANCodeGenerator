#pragma once

#include <string>
#include <vector>
#include <cstdint>


class Signal {
public:
	void SetName(std::string const _name) {
		m_signal_name = _name;
	}
	std::string const & Name(void) const { return m_signal_name; }

	void SetBitInfo(uint8_t _start, uint8_t _size) {
		m_start_bit = _start;
		m_signal_size = _size;
	}
	uint8_t StartBit(void) const { return m_start_bit; }
	uint8_t SignalSize(void) const { return m_signal_size; }

	void SetIsBigEndian(bool _is_big_endian) {
		m_is_big_endian = _is_big_endian;
	}
	void SetIsUnsigned(bool _is_unsigned) {
		m_is_unsigned = _is_unsigned;
	}

private:
	std::string m_signal_name;
	uint8_t m_start_bit;
	uint8_t m_signal_size;
	bool    m_is_big_endian;
	bool    m_is_unsigned;
};

class Message {

public:

	std::string const & Name() const { return m_message_name; }
	void SetMessageName(std::string const & _name) {
		m_message_name = _name;
	}

	uint32_t ID(void) const { return m_msg_id; }
	void SetMsgID(uint32_t _msg_id) { m_msg_id = _msg_id; }

	void AddSignal(Signal const & _signal) {
		m_signals.push_back(_signal);
	}

	std::vector<Signal> & Signals(void) { 
		return m_signals; 
	}
	std::vector<Signal> const & Signals(void) const {
		return m_signals;
	}
private:
	std::string         m_message_name;
	uint32_t            m_msg_id;
	std::vector<Signal> m_signals;
};

class DBCFileDescriptor {
public:
	void AddMessage(Message const & _msg) {
		m_messages.push_back(_msg);
	}
	std::vector<Message> & Messages(void) {
		return m_messages;
	}

	std::vector<Message> const & Messages(void) const {
		return m_messages;
	}

private:

	std::vector<Message> m_messages;
};


// @brief input a dbc file, output a DBCFileDescriptor for DBC
//        DBC Ref to : <DBC-File-Format-Documentation.pdf>
//        Analyzer file by Regular Expression.
//
class DBCAnalyzer
{
public:
	DBCAnalyzer();
	~DBCAnalyzer();


public:
	DBCFileDescriptor Analyze(std::string const & _file_name);


private:
	void AnalyzerDBCByLines(std::vector<std::string> const & _lines, DBCFileDescriptor & _file_descriptor);

	bool MessageRecognizer(std::string const & _line, DBCFileDescriptor & _file_descriptor);
	bool SignalRecognizer(std::string const & _line, Message & _msg);
};

