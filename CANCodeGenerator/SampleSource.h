#pragma once

#include <string>
#include <vector>
#include <array>
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

	void UpdateSignals(std::array<uint8_t, 8> const & _buffer) {
		a.m_signal_value = ExractSignalFromMessage<uint8_t>(_buffer, 2, 3);
		b.m_signal_value = ExractSignalFromMessage<uint16_t>(_buffer, 2, 3);
	}

	std::array<uint8_t, 8> m_message_buffer;

	Signal<uint8_t> a;
	Signal<uint16_t> b;

};



#endif
