#include "day4.h"
#include "utils.h"
namespace day4 {

	using utils::split;
	using utils::convertToInts;

	int part1(const string& filename) {
		vector<string> lines = utils::getLines(filename);
		int totalPoints{};
		for (const auto& line : lines) {
			// split on the :
			auto gameNumberAndData = split(line, ':');
			string gameNumber = split(gameNumberAndData[0])[1];
			string data = gameNumberAndData[1];

			// extract the data
			auto Numbers = split(data, '|');
			vector<int> winningNumbers = convertToInts(split(Numbers[0]));
			vector<int> myNumbers = convertToInts(split(Numbers[1]));

			// set of winning numbers.
			std::set<int> setOfWinners;

			for (auto c : winningNumbers) {
				setOfWinners.insert(c);
			}

			int winningNumberCount{};
			for (auto c : myNumbers) {
				if (setOfWinners.find(c) != setOfWinners.end())
					++winningNumberCount;

			}
			totalPoints += static_cast<int>(std::pow(2, winningNumberCount - 1));
		}

		return totalPoints;
	}
	int part2(const string& filename) {
		vector<string> lines = utils::getLines(filename);
		int totalCards{};
		vector<int> numberOfCards(lines.size(), 1);

		for (const auto& line : lines) {
			// split on the :
			auto gameNumberAndData = split(line, ':');
			// split into Game and Num. Then get Num. Convert to int and -1 for 0 indexing
			int gameIndex = stoi(split(gameNumberAndData[0])[1]) - 1;
			string data = gameNumberAndData[1];

			// extract the data
			auto Numbers = split(data, '|');
			vector<int> winningNumbers = convertToInts(split(Numbers[0]));
			vector<int> myNumbers = convertToInts(split(Numbers[1]));

			// set of winning numbers.
			std::set<int> setOfWinners;

			for (auto c : winningNumbers) {
				setOfWinners.insert(c);
			}

			int winningNumberCount{};
			for (auto c : myNumbers) {
				if (setOfWinners.find(c) != setOfWinners.end())
					++winningNumberCount;

			}

			// Get new cards based on number of winning numbers.
			for (int i = gameIndex + 1; i <= gameIndex + winningNumberCount; i++) {
				if (i < lines.size()) {
					// for each copy of current card we get more of the later cards
					numberOfCards[i] += numberOfCards[gameIndex];
				}
			}

			totalCards += numberOfCards[gameIndex];
		}
		return totalCards;
		
		
	}
	void main() {
		int answer = part1("day4test.txt");
		cout << answer << "\n";
		cout <<( (answer == 13) ? "PASS" : "FAIL") << "\n";
		cout << part1("day4.txt") << "\n";
		
		// part2
		int answer2 = part2("day4test.txt");
		cout << answer2 << "\n";
		cout <<( (answer2 == 30) ? "PASS" : "FAIL") << "\n";

		cout << part2("day4.txt") << "\n";
	}
}
