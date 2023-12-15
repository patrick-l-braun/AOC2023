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

		constexpr int numberOfMaps = 7;
		vector<map<int, int>> maps(numberOfMaps);

		int mapCounter = -1;
		for (const auto& line : lines) {
			if (line == "" || line.find("seeds:") != -1)
				continue;
			if (line[line.size() - 1] == ':') {
				++mapCounter;
				continue;
			}

			vector<int> nums = convertToInts(split(line));
			int sourceRangeStart = nums[1];
			int rangeLength = nums[2];
			int destinationRangeStart = nums[0];

			// find the mapping
			for (int i = sourceRangeStart; i < sourceRangeStart + rangeLength; ++i) {
				maps[mapCounter][i] = i - sourceRangeStart + destinationRangeStart;
			}
		}

		int closestLocation = std::numeric_limits<int>::max();
		for (int num : seedNumbers) {
			int current = num;
			cout << num << " ";
			for (int i = 0; i < numberOfMaps; ++i) {
				if (maps[i].find(current) != maps[i].end())
					current = maps[i][current];
				cout << " -> " << current;
				// else we keep it unchanged
			}
			cout << "\n";
			closestLocation = std::min(closestLocation, current);
		}
		//for (auto m : maps) {
		//	print(m);
		//}




		return closestLocation;
	}
	void main() {
		int answer = part1("day5test.txt");
		cout << answer << " " << (answer == 35 ? "PASS" : "FAIL") << "\n";
	}
}