#pragma once

#include <string>
#include <vector>
#include <map>


#include "lywCodeRuntime.h"


class lywGenCodeTempParser
{
public:
	lywGenCodeTempParser();
	~lywGenCodeTempParser();

	typedef std::vector<std::string>                 SourceCode;
	typedef std::vector<std::string>::const_iterator CodeLinePointer;

public:
	SourceCode GenerateCode(void) const;

private:

	SourceCode ExecutelywCode(CodeLinePointer & _iter_to_line) const;
	bool Is_AnylywCode(std::string iter_to_line) const;
	bool IsForBlock(CodeLinePointer & _iter_to_line) const;
	bool IsForBlockEnd(CodeLinePointer & _iter_to_line) const;
	SourceCode ExpandForBlock(SourceCode source_block) const;
private:
	SourceCode m_original_file;
	lywCodeRuntime run_time_interpretor;
};

