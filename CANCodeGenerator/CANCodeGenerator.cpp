#include "CANCodeGenerator.h"

#include <array>

#include "CommonlibsForCodeGen.h"


CANCodeGenerator::CANCodeGenerator()
{
}


CANCodeGenerator::~CANCodeGenerator()
{
}

std::vector<std::string> CANCodeGenerator::GenerateCode(DBCFileDescriptor const & _file_descriptor)
{
	auto CCode = std::vector<std::string>();
	for (auto const & message : _file_descriptor.Messages()) {
		auto message_class_definition = GenerateMessageClassDefinition(message);
		CCode += message_class_definition;
		CCode.push_back("");
	}

	return CCode;
}

std::vector<std::string> CANCodeGenerator::GenerateMessageClassDefinition(Message const & _message)
{
	auto message_class_definition = std::vector<std::string>();

	message_class_definition += GenerateMessageClassHeader(_message);
	message_class_definition += AddIndent(GenerateMessageClassConstructor(_message));
	message_class_definition += AddIndent(GenerateMessageClassUpdateSignalMethod(_message));
	message_class_definition += GenerateMessageClassDataMemberDefinition(_message);
	message_class_definition.push_back("};");

	return message_class_definition;
}

std::vector<std::string> CANCodeGenerator::GenerateMessageClassHeader(Message const & _message)
{
	return std::vector<std::string>({
		"class " + _message.Name() + " {",
		"public:",
		"    static const uint32_t message_id = " + std::to_string(_message.ID()) + ";",
		"    static std::string const message_name;",
		"public:",
	});
}

std::vector<std::string> CANCodeGenerator::GenerateMessageClassConstructor(Message const & _message)
{
	auto message_constructor = std::vector<std::string>();

	message_constructor.push_back(_message.Name() + "(void):");
	auto iter = _message.Signals().begin();
	while(iter != _message.Signals().end()) {
		auto signal_initialization = "    " + iter->Name() + "(\"" + iter->Name() + "\")";
		++iter;
		if (iter != _message.Signals().end()) {
			signal_initialization += ",";
		}
		message_constructor.push_back(signal_initialization);
	}
	message_constructor += std::vector<std::string>({
		"{",
		"    ;",
		"}"
	});
	
	return message_constructor;
}


std::vector<std::string> CANCodeGenerator::GenerateMessageClassUpdateSignalMethod(Message const & _message)
{
#if 0
	void UpdateSignalsByMessagePayload(std::array<uint8_t, 8> const & _buffer) {
		a.m_signal_value = ExractSignalFromMessage<uint8_t>(_buffer, 2, 3);
		b.m_signal_value = ExractSignalFromMessage<uint16_t>(_buffer, 2, 3);
	}	
#endif
	//                               bypte : 1   2   3   4   5   6   7   8
	const std::array<uint8_t, 8> type_map = {8, 16, 16, 32, 32, 32, 32, 64};

	auto message_constructor = std::vector<std::string>();

	message_constructor.push_back("void UpdateSignalsByMessagePayload(std::array<uint8_t, 8> const & _buffer) {");
	for (auto const & signal_descriptor : _message.Signals()) {
		// todo : it is better to have a format method like : str.format("{signal_name}.m_signal_value = 
		//  ExractSignalFromMessage<{signale_value_type}>(_buffer, {signal_start_bit}, {signal_size});", XXX,XXX,XXX,XXX);
		auto signal_value_assignment = "    " +
			signal_descriptor.Name() +
			".m_signal_value = ExractSignalFromMessage<uint" +
			std::to_string(type_map.at((signal_descriptor.SignalSize() - 1 ) / 8)) +
			"_t>(_buffer," +
			std::to_string(signal_descriptor.StartBit()) +
			", " +
			std::to_string(signal_descriptor.SignalSize()) +
			");";
		message_constructor.push_back(signal_value_assignment);
		
	}
	message_constructor.push_back("}");

	return message_constructor;
}

std::vector<std::string> CANCodeGenerator::GenerateMessageClassDataMemberDefinition(Message const & _message)
{
#if 0
	Signal<uint8_t>  a;
	Signal<uint16_t> b;
#endif
	//                               bypte : 1   2   3   4   5   6   7   8
	const std::array<uint8_t, 8> type_map = { 8, 16, 16, 32, 32, 32, 32, 64 };

	auto message_constructor = std::vector<std::string>();

	message_constructor.push_back("public:");
	for (auto const & signal_descriptor : _message.Signals()) {
		// todo : it is better to have a format method like : str.format("{signal_name}.m_signal_value = 
		//  ExractSignalFromMessage<{signale_value_type}>(_buffer, {signal_start_bit}, {signal_size});", XXX,XXX,XXX,XXX);
		auto signal_declaration = "    Signal<uint" +
			std::to_string(type_map.at((signal_descriptor.SignalSize() - 1) / 8)) +
			"_t>  " +
			signal_descriptor.Name() +
			";";
		message_constructor.push_back(signal_declaration);

	}

	return message_constructor;
}


