#include "lywCodeRuntime.h"

#include <regex>



using namespace std;

lywCodeRuntime::lywCodeRuntime()
{
}


lywCodeRuntime::~lywCodeRuntime()
{
}


SourceCode lywCodeRuntime::ExcuteCodeBlock(CodeLineConstPointer & _iter_to_line, CodeLineConstPointer _end_of_file)
{
	if (_iter_to_line->find("%%")) {
		regex re_for_start(R"(.*%%\s*for.*%%)");
		if (std::regex_match(*_iter_to_line, re_for_start)) {
			auto temp = _iter_to_line;
			ForStatement<int> for_block; // todo: int should be MessageProxy/SignalProxy/DBCProxy
			for_block.start = temp;
			regex re_for_end(R"(.*%%\s*endfor.*%%)");

			uint8_t nest_count = 0;
			do {
				if (regex_match(*_iter_to_line, re_for_start)) {
					nest_count++;
				}
				if (regex_match(*temp, re_for_end)) {
					nest_count--;
					if (nest_count == 0) {
						for_block.end = temp;
					}
					break;
				}
				temp++;
			} while (temp != _end_of_file);
			_iter_to_line = temp;

			return for_block.Execute();
			
		}
	}

	return SourceCode();
}



