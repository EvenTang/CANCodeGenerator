#pragma once

#include <vector>
#include <string>
#include <map>
#include <functional>

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
				auto executed_code = ExpandStatement(code_pointer);
				generated_code.push_back(executed_code);
			}
		}

		return generated_code;
	}


	std::string ExpandStatement(CodeLineConstPointer code_pointer) {
		// find the embedded lyw code

		// evaluate the embedded lyw code 

		// replace the embedded lyw code with evaluated string.

		return "";
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

