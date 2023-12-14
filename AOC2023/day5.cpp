#include "day5.h"

namespace day5 {
	using utils::convertToInts;
	using utils::split;
	using utils::print;
	int part1(const string& filename) {
		vector<string> lines = utils::getLines(filename);
		print(lines);
		vector<int> seedNumbers = convertToInts(split(split(lines[0], ':')[1]));
		print(seedNumbers);


		return 0;
	}
	void main() {
		int answer = part1("day5test.txt");
		cout << answer << " " << (answer == 35 ? "PASS" : "FAIL") << "\n";
	}
}