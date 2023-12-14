#include "day4.h"
#include "utils.h"
namespace day4 {

	using utils::split;
	using utils::convertToInts;
	int part1(const string& filename) {
		vector<string> lines = utils::getLines(filename);
		int totalPoints{};
		for (const auto& line : lines) {
			auto gameNumberAndData = split(line, ':');
			string gameNumber = split(gameNumberAndData[0])[1];
			string data = gameNumberAndData[1];
			auto Numbers = split(data, '|');
			vector<int> winningNumbers = convertToInts(split(Numbers[0]));
			vector<int> myNumbers = convertToInts(split(Numbers[1]));

			// set of winning numbers.
			std::set<int> setOfWinners;


			cout << line << "\n";
			cout << gameNumber << "\n";
			for (auto c : winningNumbers) {
				cout << c << " ";
				setOfWinners.insert(c);
			}
			cout << "\n";

			int winningNumberCount{};
			for (auto c : myNumbers) {
				cout << c << " ";
				if (setOfWinners.find(c) != setOfWinners.end())
					++winningNumberCount;

			}
			cout << "\n";
			totalPoints += static_cast<int>(std::pow(2, winningNumberCount - 1));
		}

		return totalPoints;
	}
	int part2(const string&) {
		return 0;
	}
	void main() {
		int answer = part1("day4test.txt");
		cout << answer << "\n";
		cout <<( (answer == 13) ? "PASS" : "FAIL") << "\n";
		cout << part1("day4.txt") << "\n";
		
		// part2
		int answer = part2("day4test.txt");
		cout << answer << "\n";
		cout <<( (answer == 30) ? "PASS" : "FAIL") << "\n";
	}
}
