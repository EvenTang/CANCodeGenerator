#pragma once

#include <string>
#include <vector>
#include <map>


#include "lywCodeRuntime.h"

#include "CommonlibsForCodeGen.h"


class lywGenCodeTempParser
{
public:
	lywGenCodeTempParser();
	~lywGenCodeTempParser();

public:
	SourceCode GenerateCode(void) const;

private:

	bool Is_AnylywCode(std::string iter_to_line) const;
	
private:
	SourceCode m_original_file;
	mutable lywCodeRuntime m_interpretor;
};

