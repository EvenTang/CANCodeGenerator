#pragma once

#include <string>
#include <vector>

#include <cstdint>

#if 1


template <typename T>
struct Signal {
	std::string const m_signal_name;
	T m_signal_value;
};

template <typename T>
T ExractSignalFromMessage(
	std::array<uint8_t, 8> const & _buffer,
	uint8_t _start_bit,
	uint8_t _signal_size) {
	return T();
}

class MessageA {
	static const uint32_t message_id = 0x33;
	static std::string const message_name;

	void UpdateSignals(uint64_t _buff) {

	}

	Signal<uint8_t> a;
	Signal<uint16_t> b;

};



#endif
