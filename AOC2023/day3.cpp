#include "day3.h"

namespace day3 {
	vector<vector<char>> get2DArray(const string& filename) {
		std::ifstream file(filename);
		if (!file.is_open())
			throw std::runtime_error("File did not open");
		string line;
		vector<vector<char>> completeArray;
		while (std::getline(file, line)) {
			vector<char> charsInLine;
			for (char c : line) {
				charsInLine.push_back(c);
			}
			completeArray.push_back(charsInLine);
		}
		return completeArray;
	}
	bool isIndexValidAndPunct(const vector<vector<char>>& arr, int lineNumber, int charNumber) {
		if (lineNumber < 0 || lineNumber >= arr.size())
			return false;
		if (charNumber < 0 || charNumber >= arr[0].size())
			return false;
		char val = arr[lineNumber][charNumber];
		return ispunct(val) && (val != '.');
	}
	bool hasPunctAround(const vector<vector<char>>& arr, int lineNum, int numStart, int numEnd) {
		// test above
		for (int i = numStart - 1; i <= numEnd + 1; ++i) {
			if (isIndexValidAndPunct(arr, lineNum - 1, i))
				return true;
		}

		// test left
		if (isIndexValidAndPunct(arr, lineNum, numStart - 1))
			return true;

		// test right
		if (isIndexValidAndPunct(arr, lineNum, numEnd + 1))
			return true;

		// testBelow 
		for (int i = numStart - 1; i <= numEnd + 1; ++i) {
			if (isIndexValidAndPunct(arr, lineNum + 1, i))
				return true;
		}
		return false;
	}
	int part1impl(string input) {
		vector<vector<char>> arr = get2DArray(input);

		int totalSum{};

		// iterate over each line
		for (int i = 0; i < arr.size(); ++i) {
			int startOfNum = -1;
			int endOfNum{};
			int num{};
			// find the numbers in the line
			for (int j = 0; j < arr[0].size(); ++j) {
				if (isdigit(arr[i][j])){
					if (startOfNum == -1) {
						startOfNum = j;
						endOfNum = j; // this accounts for single digits
						num = arr[i][j] - '0';
					}
					else
					{
						endOfNum = j;
						num = num * 10 + (arr[i][j] - '0');
					}
				}
				// need to process number at end of line as well
				if (ispunct(arr[i][j]) || (j == arr[0].size() - 1)) {
					if (startOfNum == -1)
						continue;
					// check if the number has punctuation around
					if (hasPunctAround(arr, i, startOfNum, endOfNum)) {
						totalSum += num; 
					}
					startOfNum = -1;
					endOfNum = -1;
					num = 0;
					
				}

			}

		}
		
		if (input == "day3test.txt") {
			for (const auto& line : arr) {
				for (const auto& char_ : line) {
					cout << char_ << " ";
				}
				cout << "\n";
			}
			cout << isIndexValidAndPunct(arr, -1, 0) << " should be false\n";
			cout << isIndexValidAndPunct(arr, 0, -1) << " should be false\n";
			cout << isIndexValidAndPunct(arr, 10, 0) << " should be false\n";
			cout << isIndexValidAndPunct(arr, 0, 10) << " should be false\n";
			cout << isIndexValidAndPunct(arr, 1, 3) << " should be true\n";
			cout << isIndexValidAndPunct(arr, 0, 3) << " should be false\n\n";

			cout << hasPunctAround(arr, 0, 0, 2) << " should be true\n";
			cout << hasPunctAround(arr, 0, 5, 7) << " should be false\n";
		}
		cout << "\n" << totalSum << "\n";
		return totalSum;
	}
	void part1() {
		part1impl("day3.txt");

		part1impl("day3test.txt");
	}
	bool isIndexValid(const vector<vector<char>>& arr, int lineNumber, int charNumber) {
		if (lineNumber < 0 || lineNumber >= arr.size())
			return false;
		if (charNumber < 0 || charNumber >= arr[0].size())
			return false;
		return true;
	}


	
	void findGears(const vector<vector<char>>& arr, int lineNum, int numStart, int numEnd, int num, map<std::pair<int, int>, vector<int>>& gearsToNumsAround) {
		// test above
		for (int i = numStart - 1; i <= numEnd + 1; ++i) {
			if (isIndexValid(arr, lineNum - 1, i) && arr[lineNum - 1][i] == '*')
				gearsToNumsAround[std::pair(lineNum - 1, i)].push_back(num);
		}

		// test left
		if (isIndexValid(arr, lineNum, numStart - 1) && arr[lineNum][numStart -1] == '*')
			gearsToNumsAround[std::pair(lineNum, numStart -1)].push_back(num);


		// test right
		if (isIndexValid(arr, lineNum, numEnd + 1) && arr[lineNum][numEnd + 1] == '*')
			gearsToNumsAround[std::pair(lineNum, numEnd + 1)].push_back(num);

		// testBelow 
		for (int i = numStart - 1; i <= numEnd + 1; ++i) {
			if (isIndexValid(arr, lineNum + 1, i) && arr[lineNum + 1][i] == '*')
				gearsToNumsAround[std::pair(lineNum + 1, i)].push_back(num);
		}
	}
	int part2impl(string input) {
		vector<vector<char>> arr = get2DArray(input);
		map<std::pair<int, int>, vector<int>> gearsToNumsAround{};

		long totalSum{};

		// iterate over each line
		for (int i = 0; i < arr.size(); ++i) {
			int startOfNum = -1;
			int endOfNum{};
			int num{};
			// find the numbers in the line
			for (int j = 0; j < arr[0].size(); ++j) {
				if (isdigit(arr[i][j])) {
					if (startOfNum == -1) {
						startOfNum = j;
						endOfNum = j; // this accounts for single digits
						num = arr[i][j] - '0';
					}
					else
					{
						endOfNum = j;
						num = num * 10 + (arr[i][j] - '0');
					}
				}
				// need to process number at end of line as well
				if (ispunct(arr[i][j]) || (j == arr[0].size() - 1)) {
					if (startOfNum == -1)
						continue;
					
					// find all the gears around that number so that we can check if a gear has two neighbours
					findGears(arr, i, startOfNum, endOfNum, num, gearsToNumsAround); 
					startOfNum = -1;
					endOfNum = -1;
					num = 0;

				}

			}

		}

		
		for (const auto& [location, intsAroundGear] : gearsToNumsAround) {
			if (intsAroundGear.size() == 2) {
				totalSum += intsAroundGear[0] * intsAroundGear[1];
			}
		}
		return totalSum;
	}
	void part2() {

		int result = part2impl("day3test.txt");
		cout << (result == 467835 ? "PASS" : "FAIL") << "\n";

		cout << part2impl("day3.txt") << "\n";

	}
	void main() {
		part1();
		part2();
	}
}