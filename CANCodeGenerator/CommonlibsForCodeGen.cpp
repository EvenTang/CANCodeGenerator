#include "CommonlibsForCodeGen.h"

SourceCode AddPrefixToAll(SourceCode const _source, std::string const & _prefix /*= " "*/)
{
	auto new_code = std::vector<std::string>();
	for (auto const & line : _source) {
		new_code.push_back(_prefix + line);
	}

	return new_code;
}

SourceCode AddIndent(SourceCode const & _source)
{
	return AddPrefixToAll(_source, "    ");
}