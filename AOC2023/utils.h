#pragma once
#include "include.h"

namespace utils {
	vector<string> split(const string& s, char sep = ' ');
	vector<string> getLines(const string& filename);
	vector<int> convertToInts(const vector<string>& a);
}
