#pragma once

#include <vector>
#include <string>
#include <map>
#include <functional>
#include <regex>

#include "CommonlibsForCodeGen.h"


class MsgProxy
{
public:
	MsgProxy() {}
	~MsgProxy() {}
//
//	std::string EvaluateProperty(std::string const & _property_name) {
//		return m_property_map[_property_name]();
//	}

private:
//	std::map<std::string, std::function<std::string()>> const m_property_map = {
// 		{ "Name", [this]() {return ""; } },
// 		{ "ID", [this]() {return ""; } },
// 	};
};

class SignalProxy
{
public:
	SignalProxy() {}
	~SignalProxy() {}
#if 0
	inline std::string EvaluateProperty(std::string const & _property_name) {
		return m_property_map[_property_name]();
	}

private:
	std::map<std::string, std::function<std::string()>> const m_property_map = {
		{ "Name", [this]() {return ""; } },
		{ "ID", [this]() {return ""; } },
	};
#endif


};



// %% for @sth in @DBC.All [if @sth.Name == X] %%
template <typename T>
class ForStatement {

public:
	/**
	 * @brief  Expand C/C++ Source code.
	 *
	 * @return SourceCode																									
	 * @retval NONE
	 *
	 * @note   NONE
	 * @see    NONE
	 */
	SourceCode Execute()
	{
		SourceCode generated_code;

		for (auto loog_var : m_for_rang) {
			for (auto code_pointer = start + 1; code_pointer != end; ++code_pointer) {
				auto executed_code = ExpandStatement(code_pointer, loog_var);
				generated_code.push_back(executed_code);
			}
		}

		return generated_code;
	}


	std::string ExpandStatement(CodeLineConstPointer code_pointer, T _cur_loop_var) {
		
		std::string source_line = *code_pointer;
		
		// find the embedded lyw code
		std::regex re(R"((.*)@([^@])\.([^@])@)(.*)");
		std::smatch m;
		while (std::regex_match(source_line, m, re)) {
			// evaluate the embedded lyw code 
			if (m.str(2) != m_loop_variable_name) {
				//return "";
				throw std::logic_error("lyw Code is not right~! Unknown variable ~!");
			}
			source_line = m.str(1) + _cur_loop_var.EvaluateProperty(m.str(3)) + m.str(4);
		}

		return source_line;
	}


public:
	CodeLineConstPointer start;
	CodeLineConstPointer end;

	std::string m_loop_variable_name;
	std::vector<T> m_for_rang;
};



class lywCodeRuntime
{
public:
	lywCodeRuntime();
	~lywCodeRuntime();


	SourceCode ExcuteCodeBlock(CodeLineConstPointer & _iter_to_line, CodeLineConstPointer _end_of_file);
};

