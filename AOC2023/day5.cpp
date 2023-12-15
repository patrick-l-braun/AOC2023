#include "day5.h"

namespace day5 {
	using ll = long long;
	using utils::convertToLl;
	using utils::split;
	using utils::print;
	constexpr int numberOfMaps = 7;

	struct Mapping {
		ll destinationRangeStart{};
		ll sourceRangeStart{};
		ll rangeLength{};
	};
	class ConvertMapping {
	public:
		ConvertMapping(){
			maps = vector<vector<Mapping>>(numberOfMaps);
		}

		// turns each line into a mapping (uses aggregate initialiser)
		void addLine(int mappingNumber, const string& line) {
			vector<ll> nums = convertToLl(split(line));
			maps[mappingNumber].push_back({ nums[0], nums[1], nums[2] });
		}
		
		// Converts a number based on a mapping
		ll convert(int mappingNumber, ll number) {
			for (const Mapping& map : maps[mappingNumber]) {
				// check if the mapping applies
				if (number > map.sourceRangeStart && number < map.sourceRangeStart + map.rangeLength)
					//convert
					return number - map.sourceRangeStart + map.destinationRangeStart;
			}
			return number;
		}
	private:
		vector<vector<Mapping>> maps;
	};

	ll part1(const string& filename) {
		vector<string> lines = utils::getLines(filename);
		print(lines);
		vector<ll> seedNumbers = convertToLl(split(split(lines[0], ':')[1]));
		print(seedNumbers);

		ConvertMapping converter;

		int mapCounter = -1;
		for (const auto& line : lines) {
			if (line == "" || line.find("seeds:") != -1)
				continue;
			if (line[line.size() - 1] == ':') {
				++mapCounter;
				cout << mapCounter << "\n";
				continue;
			}
			converter.addLine(mapCounter, line);
		}

		ll closestLocation = std::numeric_limits<ll>::max();
		for (ll num : seedNumbers) {
			ll current = num;
			cout << num << " ";
			for (int i = 0; i < numberOfMaps; ++i) {
				current = converter.convert(i, current);
				cout << " -> " << current;
			}
			cout << "\n";
			closestLocation = std::min(closestLocation, current);
		}
		return closestLocation;
	}
	void main() {
		ll answer = part1("day5test.txt");
		cout << answer << " " << (answer == 35 ? "PASS" : "FAIL") << "\n";

		ll answerForMain = part1("day5.txt");
		cout << answerForMain << "\n";
	}
}