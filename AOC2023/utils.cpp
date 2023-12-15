#include "utils.h"
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
	vector<string> getLines(const string& filename) {
		string line;
		std::ifstream file(filename);
		if (!file.is_open())
			throw std::runtime_error("Couldn't open file");
		vector<string> lines;
		while (std::getline(file, line))
			lines.push_back(line);
		file.close();
		return lines;
	}
	vector<int> convertToInts(const vector<string>& a) {
		vector<int> vec;
		for (const auto& s : a) {
			vec.push_back(stoi(s));
		}
		return vec;
	}
	vector<long long> convertToLl(const vector<string>& a) {
		vector<long long> vec;
		for (const auto& s : a) {
			vec.push_back(stoll(s));
		}
		return vec;
	}
}
