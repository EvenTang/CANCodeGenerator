#include "CommonlibsForCodeGen.h"

std::vector<std::string> AddIndent(std::vector<std::string> const & _source)
{
	auto new_code = std::vector<std::string>();
	for (auto const & line : _source) {
		new_code.push_back("    " + line);
	}

	return new_code;
}