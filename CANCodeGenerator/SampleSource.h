#pragma once

#include <string>
#include <vector>
#include <array>
#include <cstdint>

#if 0


test.dbc
BO_ 1620 CAN_Message_1: 8 BCM
SG_ SIG_12_05 : 55 | 16@0+ (0.001, 0)[0 | 5] "V"  ECU, BCM
SG_ SIG_05 : 39 | 16@0+ (0.001, 0)[0 | 5] "V"  ECU, BCM
SG_ SIG_05 : 23 | 16@0+ (0.001, 0)[0 | 5] "V"  ECU, BCM
SG_ SIG_05 : 7 | 16@0+ (0.001, 0)[0 | 5] "V"  ECU, BCM

BO_ 1604 CAN_Message_1: 8 BCM
SG_ SIG_12_04 : 55 | 16@0+ (0.001, 0)[0 | 5] "V"  ECU, BCM
SG_ SIG_11_04 : 39 | 16@0+ (0.001, 0)[0 | 5] "V"  ECU, BCM
SG_ SIG_10_04 : 23 | 16@0+ (0.001, 0)[0 | 5] "V"  ECU, BCM
SG_ SIG_09_04 : 7 | 16@0+ (0.001, 0)[0 | 5] "V"  ECU, BCM

BO_ 1588 CAN_Message_3: 8 BCM
SG_ SIG_12_03 : 55 | 16@0+ (0.001, 0)[0 | 5] "V"  ECU, BCM
SG_ SIG_11_03 : 39 | 16@0+ (0.001, 0)[0 | 5] "V"  ECU, BCM
SG_ SIG_10_03 : 23 | 16@0+ (0.001, 0)[0 | 5] "V"  ECU, BCM
SG_ SIG_09_03 : 7 | 16@0+ (0.001, 0)[0 | 5] "V"  ECU, BCM


fixed code:

template <typename T>
struct Signal {
	std::string const m_signal_name;
	T m_signal_value;
};


uint8_t ExactBitsFromByte(uint8_t _byte, uint8_t _msb, uint8_t _lsb) {
	uint8_t rslt;
	static uint8_t const mask[] = {
		0b00000000,
		0b00000001,
		0b00000011,
		0b00000111,
		0b00001111,
		0b00011111,
		0b00111111,
		0b01111111,
		0b11111111,
	};
	rslt = (_byte >> _lsb) & mask[_msb - _lsb + 1];
	return rslt;
}

template <typename T>
T UnpackCANSignalFromMessagePayloadAlgorithm(std::array<uint8_t, 8> const & _playload, uint8_t _start, uint8_t _size, std::function<void(uint8_t&)> _byte_increase) {

	auto signal_value = T();

	uint8_t lsb_bit_pos_in_byte = _start % 8;   // find the LSB 
	uint8_t lsb_byte_idx = _start / 8;
	uint8_t existed_bits = 0;
	int16_t left_size = _size;

	while (left_size > 0) {
		auto const & byte_data = _playload.at(lsb_byte_idx);
		auto msg_pos_in_byte = lsb_bit_pos_in_byte + left_size - 1;
		if (msg_pos_in_byte > 7) {  // left bits of lsb byte is belone to the signal
			signal_value |= (ExactBitsFromByte(byte_data, 7, lsb_bit_pos_in_byte) << existed_bits);
			existed_bits += (7 - lsb_bit_pos_in_byte + 1);
			_byte_increase(lsb_byte_idx);
			left_size = _size - existed_bits;
			lsb_bit_pos_in_byte = 0;
		}
		else {
			signal_value |= (ExactBitsFromByte(byte_data, msg_pos_in_byte, lsb_bit_pos_in_byte) << existed_bits);
			break;
		}
	}

	return signal_value;
}

template <typename T>
inline T UnpackCANSignalFromMessagePayloadBE(std::array<uint8_t, 8> const & _playload, uint8_t _start, uint8_t _size) {
	return UnpackCANSignalFromMessagePayloadAlgorithm<T>(_playload, _start, _size, [](uint8_t & _byte_order) { --_byte_order; });
}

template <typename T>
inline T UnpackCANSignalFromMessagePayloadLE(std::array<uint8_t, 8> const & _playload, uint8_t _start, uint8_t _size) {
	return UnpackCANSignalFromMessagePayloadAlgorithm<T>(_playload, _start, _size, [](uint8_t & _byte_order) { ++_byte_order; });
}

// @brief About BE(big endian) and LE(little endian) in CAN data frame, ref to 
//        http://cn.mathworks.com/help/vnt/ug/canpack.html?s_tid=gn_loc_drop
//
template <typename T>
T UnpackCANSignalFromMessagePayload(std::array<uint8_t, 8> const & _playload, uint8_t _start, uint8_t _size, bool _is_big_endian) {
	if (_is_big_endian) {
		return UnpackCANSignalFromMessagePayloadBE<T>(_playload, _start, _size);
	}

	return UnpackCANSignalFromMessagePayloadLE<T>(_playload, _start, _size);
}


generated code:
class CAN_Message_1 {
public:
	static const uint32_t message_id = 1620;
	static std::string const message_name;
public:
	CAN_Message_1(void) :
		SIG_12_05("SIG_12_05"),
		SIG_05("SIG_05"),
		SIG_05("SIG_05"),
		SIG_05("SIG_05")
	{
		;
	}
	void UpdateSignalsByMessagePayload(std::array<uint8_t, 8> const & _buffer) {
		SIG_12_05.m_signal_value = ExractSignalFromMessage<uint16_t>(_buffer, 55, 16);
		SIG_05.m_signal_value = ExractSignalFromMessage<uint16_t>(_buffer, 39, 16);
		SIG_05.m_signal_value = ExractSignalFromMessage<uint16_t>(_buffer, 23, 16);
		SIG_05.m_signal_value = ExractSignalFromMessage<uint16_t>(_buffer, 7, 16);
	}
public:
	Signal<uint16_t>  SIG_12_05;
	Signal<uint16_t>  SIG_05;
	Signal<uint16_t>  SIG_05;
	Signal<uint16_t>  SIG_05;
};

class CAN_Message_1 {
public:
	static const uint32_t message_id = 1604;
	static std::string const message_name;
public:
	CAN_Message_1(void) :
		SIG_12_04("SIG_12_04"),
		SIG_11_04("SIG_11_04"),
		SIG_10_04("SIG_10_04"),
		SIG_09_04("SIG_09_04")
	{
		;
	}
	void UpdateSignalsByMessagePayload(std::array<uint8_t, 8> const & _buffer) {
		SIG_12_04.m_signal_value = ExractSignalFromMessage<uint16_t>(_buffer, 55, 16);
		SIG_11_04.m_signal_value = ExractSignalFromMessage<uint16_t>(_buffer, 39, 16);
		SIG_10_04.m_signal_value = ExractSignalFromMessage<uint16_t>(_buffer, 23, 16);
		SIG_09_04.m_signal_value = ExractSignalFromMessage<uint16_t>(_buffer, 7, 16);
	}
public:
	Signal<uint16_t>  SIG_12_04;
	Signal<uint16_t>  SIG_11_04;
	Signal<uint16_t>  SIG_10_04;
	Signal<uint16_t>  SIG_09_04;
};

class CAN_Message_3 {
public:
	static const uint32_t message_id = 1588;
	static std::string const message_name;
public:
	CAN_Message_3(void) :
		SIG_12_03("SIG_12_03"),
		SIG_11_03("SIG_11_03"),
		SIG_10_03("SIG_10_03"),
		SIG_09_03("SIG_09_03")
	{
		;
	}
	void UpdateSignalsByMessagePayload(std::array<uint8_t, 8> const & _buffer) {
		SIG_12_03.m_signal_value = ExractSignalFromMessage<uint16_t>(_buffer, 55, 16);
		SIG_11_03.m_signal_value = ExractSignalFromMessage<uint16_t>(_buffer, 39, 16);
		SIG_10_03.m_signal_value = ExractSignalFromMessage<uint16_t>(_buffer, 23, 16);
		SIG_09_03.m_signal_value = ExractSignalFromMessage<uint16_t>(_buffer, 7, 16);
	}
public:
	Signal<uint16_t>  SIG_12_03;
	Signal<uint16_t>  SIG_11_03;
	Signal<uint16_t>  SIG_10_03;
	Signal<uint16_t>  SIG_09_03;
};

#endif
