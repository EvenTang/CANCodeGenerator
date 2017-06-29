# CANCode Generator 

## what is it?

Hand writing code for parsing CAN data frames is a boring work, and it is esay to make mistake.

This tool is used to generate CAN data frame processing code from a DBC file.

# Sample

For V0.1

Given a simple .dbc file like :

```
BO_ 1620 CAN_Message_1: 8 BCM
 SG_ SIG1205 : 55|16@0+ (0.001,0) [0|5] "V"  ECU,BCM
 SG_ SIG_05 : 39|16@0+ (0.001,0) [0|5] "V"  ECU,BCM
 SG_ SIG_05 : 23|16@0+ (0.001,0) [0|5] "V"  ECU,BCM
 SG_ SIG_05 : 7|16@0+ (0.001,0) [0|5] "V"  ECU,BCM

BO_ 1604 CAN_Message_1: 8 BCM
 SG_ SIG1204 : 55|16@0+ (0.001,0) [0|5] "V"  ECU,BCM
 SG_ SIG1104 : 39|16@0+ (0.001,0) [0|5] "V"  ECU,BCM
 SG_ SIG1004 : 23|16@0+ (0.001,0) [0|5] "V"  ECU,BCM
 SG_ SIG0904 : 7|16@0+ (0.001,0) [0|5] "V"  ECU,BCM

BO_ 1588 CAN_Message_3: 8 BCM
 SG_ SIG1203 : 55|16@0+ (0.001,0) [0|5] "V"  ECU,BCM
 SG_ SIG1103 : 39|16@0+ (0.001,0) [0|5] "V"  ECU,BCM
 SG_ SIG1003 : 23|16@0+ (0.001,0) [0|5] "V"  ECU,BCM
 SG_ SIG0903 : 7|16@0+ (0.001,0) [0|5] "V"  ECU,BCM

```

The tool will generate the following C++ code for processing CAN messages defined in the above DBC file:

```C++
class CAN_Message_1 {
public:
    static const uint32_t message_id = 1620;
    static std::string const message_name;
public:
    CAN_Message_1(void):
        SIG_12_05("SIG_12_05"),
        SIG_05("SIG_05"),
        SIG_05("SIG_05"),
        SIG_05("SIG_05")
    {
        ;
    }
    void UpdateSignalsByMessagePayload(std::array<uint8_t, 8> const & _buffer) {
        SIG_12_05.m_signal_value = ExractSignalFromMessage<uint16_t>(_buffer,55, 16);
        SIG_05.m_signal_value = ExractSignalFromMessage<uint16_t>(_buffer,39, 16);
        SIG_05.m_signal_value = ExractSignalFromMessage<uint16_t>(_buffer,23, 16);
        SIG_05.m_signal_value = ExractSignalFromMessage<uint16_t>(_buffer,7, 16);
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
    CAN_Message_1(void):
        SIG_12_04("SIG_12_04"),
        SIG_11_04("SIG_11_04"),
        SIG_10_04("SIG_10_04"),
        SIG_09_04("SIG_09_04")
    {
        ;
    }
    void UpdateSignalsByMessagePayload(std::array<uint8_t, 8> const & _buffer) {
        SIG_12_04.m_signal_value = ExractSignalFromMessage<uint16_t>(_buffer,55, 16);
        SIG_11_04.m_signal_value = ExractSignalFromMessage<uint16_t>(_buffer,39, 16);
        SIG_10_04.m_signal_value = ExractSignalFromMessage<uint16_t>(_buffer,23, 16);
        SIG_09_04.m_signal_value = ExractSignalFromMessage<uint16_t>(_buffer,7, 16);
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
    CAN_Message_3(void):
        SIG_12_03("SIG_12_03"),
        SIG_11_03("SIG_11_03"),
        SIG_10_03("SIG_10_03"),
        SIG_09_03("SIG_09_03")
    {
        ;
    }
    void UpdateSignalsByMessagePayload(std::array<uint8_t, 8> const & _buffer) {
        SIG_12_03.m_signal_value = ExractSignalFromMessage<uint16_t>(_buffer,55, 16);
        SIG_11_03.m_signal_value = ExractSignalFromMessage<uint16_t>(_buffer,39, 16);
        SIG_10_03.m_signal_value = ExractSignalFromMessage<uint16_t>(_buffer,23, 16);
        SIG_09_03.m_signal_value = ExractSignalFromMessage<uint16_t>(_buffer,7, 16);
    }
public:
    Signal<uint16_t>  SIG_12_03;
    Signal<uint16_t>  SIG_11_03;
    Signal<uint16_t>  SIG_10_03;
    Signal<uint16_t>  SIG_09_03;
};
```

Alone with the fix code like:

```C++
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
	return T(); // todo need to be implemented.
}
```

It can work in very simple project now.

To be updated. (functionality of the tool~)
