#include "lywGenCodeTempParser.h"

#include "CommonlibsForCodeGen.h"

using namespace std;

lywGenCodeTempParser::lywGenCodeTempParser()
{
}


lywGenCodeTempParser::~lywGenCodeTempParser()
{
}

SourceCode lywGenCodeTempParser::GenerateCode(void) const
{
	vector<string> generated_file;
	
	for (auto iter_to_line = m_original_file.begin(); iter_to_line != m_original_file.end(); ++iter_to_line) {
	    if (!Is_AnylywCode(*iter_to_line)) {
			generated_file.push_back(*iter_to_line);
	    }
		else {
			generated_file += m_interpretor.ExcuteCodeBlock(m_original_file, iter_to_line);
		}
	}

	return generated_file;
}


bool lywGenCodeTempParser::Is_AnylywCode(std::string iter_to_line) const
{
	throw std::logic_error("The method or operation is not implemented.");
}
