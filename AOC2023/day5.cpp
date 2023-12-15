#include "day5.h"

namespace day5 {
	using ll = long long;
	using utils::convertToLl;
	using utils::split;
	using utils::print;
	ll part1(const string& filename) {
		vector<string> lines = utils::getLines(filename);
		print(lines);
		vector<ll> seedNumbers = convertToLl(split(split(lines[0], ':')[1]));
		print(seedNumbers);

		constexpr ll numberOfMaps = 7;
		vector<map<ll, ll>> maps(numberOfMaps);

		ll mapCounter = -1;
		for (const auto& line : lines) {
			if (line == "" || line.find("seeds:") != -1)
				continue;
			if (line[line.size() - 1] == ':') {
				++mapCounter;
				cout << mapCounter << "\n";
				continue;
			}

			vector<ll> nums = convertToLl(split(line));
			ll sourceRangeStart = nums[1];
			ll rangeLength = nums[2];
			ll destinationRangeStart = nums[0];

			// find the mapping
			for (ll i = sourceRangeStart; i < sourceRangeStart + rangeLength; ++i) {
				maps[mapCounter][i] = i - sourceRangeStart + destinationRangeStart;
			}
		}

		ll closestLocation = std::numeric_limits<ll>::max();
		for (ll num : seedNumbers) {
			ll current = num;
			cout << num << " ";
			for (ll i = 0; i < numberOfMaps; ++i) {
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
		cout << sizeof(ll) << "\n";
		ll answer = part1("day5.txt");
		cout << answer << " " << (answer == 35 ? "PASS" : "FAIL") << "\n";
	}
}