#include <iostream>


#include "DBCAnalyzer.h"
#include "CANCodeGenerator.h"
#include "CodeGenForDiffTool.h"
#include "CommonlibsForCodeGen.h"

using namespace std;

int main() {
	DBCAnalyzer parser;
	//auto dbc_file_descriptor = parser.Analyze("D:\\06 ProjectAsistent\\ClarionMitsubishi\\LogCompareTool\\CAN1_151215_CL_Local.dbc");
	//auto dbc_file_descriptor = parser.Analyze("D:\\06 ProjectAsistent\\ClarionMitsubishi\\LogCompareTool\\CAN2_151215_CL_Local.dbc");
	auto dbc_file_descriptor = parser.Analyze("D:\\06 ProjectAsistent\\ClarionMitsubishi\\LogCompareTool\\CAN3_151215_CL_Local.dbc");

	CodeGenForDiffTool generator;
	auto source_code = generator.GenerateCode(dbc_file_descriptor);


	for (auto const & str : source_code) {
		cout << str << endl;

	}
	cout << "=> End !" << endl;
	return 0;
}
