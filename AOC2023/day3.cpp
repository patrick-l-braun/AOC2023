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
	void main() {
		string input = "day3.txt";
		vector<vector<char>> arr = get2DArray(input);

		cout << "501 763 331 161 683 980\n";
		cout << "948 633 990\n";

		int totalSum{};

		for (int i = 0; i < arr.size(); ++i) {
			int startOfNum = -1;
			int endOfNum{};
			int num{};
			for (int j = 0; j < arr[0].size(); ++j) {
				if (isdigit(arr[i][j])){
					if (startOfNum == -1) {
						startOfNum = j;
						endOfNum = j;
						num = arr[i][j] - '0';
					}
					else
					{
						endOfNum = j;
						num = num * 10 + (arr[i][j] - '0');
					}
				}
				if (ispunct(arr[i][j]) || (j == arr[0].size() - 1)) {
					if (startOfNum == -1)
						continue;
					if (hasPunctAround(arr, i, startOfNum, endOfNum)) {
						totalSum += num; 
						cout << num << " ";
					}
					startOfNum = -1;
					endOfNum = -1;
					num = 0;
					
				}

			}
			cout << "\n";

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

	}
}