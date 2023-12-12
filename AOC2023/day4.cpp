#include "day4.h"
namespace day4 {

	void part1() {
		


	}
	void part2(){}
	void main() {
		part1();
		part2();
	}
}

namespace utils {
	vector<string> split(const string& s, char sep) {
		vector<string> splitStrings;
		string current{ "" };
		for (const char c : s) {
			if (c != sep) {
				current += c;
			}
			else if (c == sep && current != "") {
				splitStrings.push_back(current);
				current = "";
			}

		}
		if (current != "")
			splitStrings.push_back(current);
		return splitStrings;
	}
}