#include "lywGenCodeTempParser.h"

#include "CommonlibsForCodeGen.h"

using namespace std;

lywGenCodeTempParser::lywGenCodeTempParser()
{
}


lywGenCodeTempParser::~lywGenCodeTempParser()
{
}

lywGenCodeTempParser::SourceCode lywGenCodeTempParser::GenerateCode(void) const
{
	vector<string> generated_file;
	
	for (auto iter_to_line = m_original_file.begin(); iter_to_line != m_original_file.end(); ++iter_to_line) {
	    if (!Is_AnylywCode(*iter_to_line)) {
			generated_file.push_back(*iter_to_line);
	    }
		else {
			generated_file += ExecutelywCode(iter_to_line);
		}
	}

	return generated_file;
}

lywGenCodeTempParser::SourceCode lywGenCodeTempParser::ExecutelywCode(CodeLinePointer & _iter_to_line) const
{
	SourceCode geneated_code;

	if (IsForBlock(_iter_to_line)) {
		SourceCode source_block;
		while (IsForBlockEnd(++_iter_to_line)) {
			source_block.push_back(*_iter_to_line);
		}
		geneated_code += ExpandForBlock(source_block);
	}

	return geneated_code;
}

bool lywGenCodeTempParser::Is_AnylywCode(std::string iter_to_line) const
{
	throw std::logic_error("The method or operation is not implemented.");
}

bool lywGenCodeTempParser::IsForBlock(CodeLinePointer & _iter_to_line) const
{
	throw std::logic_error("The method or operation is not implemented.");
}

bool lywGenCodeTempParser::IsForBlockEnd(CodeLinePointer & _iter_to_line) const
{
	throw std::logic_error("The method or operation is not implemented.");
}

lywGenCodeTempParser::SourceCode lywGenCodeTempParser::ExpandForBlock(SourceCode source_block) const
{
	throw std::logic_error("The method or operation is not implemented.");
}
