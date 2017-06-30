#include <iostream>


#include "DBCAnalyzer.h"
#include "CANCodeGenerator.h"

using namespace std;

int main() {
	DBCAnalyzer parser;
	auto dbc_file_descriptor = parser.Analyze("");

	CANCodeGenerator generator;
	auto source_code = generator.GenerateCode(dbc_file_descriptor);

	for (auto const & str : source_code) {
		cout << str << endl;

	}
	cout << "=> End !" << endl;
	return 0;
}
