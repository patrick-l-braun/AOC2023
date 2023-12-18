#include "day5.h"

namespace day5 {
	using ll = long long;
	using utils::convertToLl;
	using utils::split;
	using utils::print;
	constexpr int numberOfMaps = 7;

	struct Range {
		ll start{};
		ll length{};
	};
	struct Mapping {
		ll destinationRangeStart{};
		ll sourceRangeStart{};
		ll rangeLength{};

		Range getIntersection(Range otherRange) const {
			Range intersection;
			if (otherRange.start < sourceRangeStart)
				intersection.start = sourceRangeStart;
			else
				intersection.start = otherRange.start;
			
			ll otherRangeEnd = otherRange.start + otherRange.length;
			ll mappingRangeEnd = sourceRangeStart + rangeLength;
			if (otherRangeEnd < mappingRangeEnd) {
				intersection.length = otherRangeEnd - intersection.start;
			}
			else {
				intersection.length = mappingRangeEnd - intersection.start;
			}
			return intersection;
		}

		Range convert(Range range) const {
			Range intersection = getIntersection(range);

			ll diff = sourceRangeStart - destinationRangeStart;
			intersection.start = intersection.start - diff;
			return intersection;

		}
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
				if (number >= map.sourceRangeStart && number < map.sourceRangeStart + map.rangeLength)
					//convert
					return number - map.sourceRangeStart + map.destinationRangeStart;
			}
			return number;
		}

		vector<Range> convertRanges(int mappingNumber, vector<Range>& ranges) {
			vector<Range> outputs;
			for (const Range& range : ranges) {
				for (const Mapping& map : maps[mappingNumber]) {
					Range r = map.convert(range);
					if (r.length > 0) {
						outputs.push_back(r);
					}
					else {
						//outputs.push_back(range);
					}
				}
			}
			return outputs;
		}
	private:
		vector<vector<Mapping>> maps;
	};

	ll part1(const string& filename, int mode) {
		vector<string> lines = utils::getLines(filename);
		print(lines);
		vector<ll> seedNumbers = convertToLl(split(split(lines[0], ':')[1]));
		vector<Range> seedRanges;
		if (mode == 2) {
			for (int i = 0; i < seedNumbers.size(); i+=2){
				seedRanges.push_back({ seedNumbers[i], seedNumbers[i + 1] });
			}
		}
		cout << seedNumbers.size() << "\n";

		ConvertMapping converter;

		int mapCounter = -1;
		for (const auto& line : lines) {
			if (line == "" || line.find("seeds:") != -1)
				continue;
			if (line[line.size() - 1] == ':') {
				++mapCounter;
				continue;
			}
			converter.addLine(mapCounter, line);
		}

		ll closestLocation = std::numeric_limits<ll>::max();
		int j = 0;
		if (mode == 1) {
			for (ll num : seedNumbers) {
				cout << j << " / " << seedNumbers.size() << " | ";
				ll current = num;
				cout << num << " ";
				for (int i = 0; i < numberOfMaps; ++i) {
					current = converter.convert(i, current);
					cout << " -> " << current;
				}
				cout << "\n";
				closestLocation = std::min(closestLocation, current);
				j++;
			}
		}
		if (mode == 2) {
			vector<Range> ranges = seedRanges;
			for (Range range : ranges) {
				vector<Range> current = { range };
				for (int i = 0; i < numberOfMaps; ++i) {
					current = converter.convertRanges(i, current);
				}
				for (auto r : current) {
					closestLocation = std::min(closestLocation, r.start);
				}

			}
		}
		return closestLocation;
	}
	void main() {
		//ll answer = part1("day5test.txt", 1);
		//cout << answer << " " << (answer == 35 ? "PASS" : "FAIL") << "\n";

		//ll answerForMain = part1("day5.txt", 1);
		//cout << answerForMain << "\n";

		ll answer2 = part1("day5test.txt", 2);
		cout << answer2 << " " << (answer2 == 46 ? "PASS" : "FAIL") << "\n";
		//ll answerForMain2 = part1("day5.txt", 2);
		//cout << answerForMain2 << "\n";

		Range r = { 74, 14 };
		
		Mapping m = { 45, 77, 23 };
		Range i = m.getIntersection(r);
		cout << i.start << " " << i.length << "\n";
		i = m.convert(r);
		cout << i.start << " " << i.length << "\n";


		Mapping otherM = { 68, 64, 13 };
		Range otherI = otherM.getIntersection(r);
		cout << otherI.start << " " << otherI.length << "\n";
		otherI = otherM.convert(r);
		cout << otherI.start << " " << otherI.length << "\n";


		Mapping irrelaventM = { 81, 45, 19 };
		otherI = irrelaventM.getIntersection(r);
		cout << otherI.start << " " << otherI.length << "\n";
		otherI = irrelaventM.convert(r);
		cout << otherI.start << " " << otherI.length << "\n";


	}
}