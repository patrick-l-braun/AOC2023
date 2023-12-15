#pragma once
#include "include.h"

namespace utils {
	vector<string> split(const string& s, char sep = ' ');
	vector<string> getLines(const string& filename);
	vector<int> convertToInts(const vector<string>& a);
	vector<long long> convertToLl(const vector<string>& a);
	
	template<typename T>
	void print(const vector<T>& array, char sep = '\n', const string& message="") {
		for (const auto& item : array) {
			if (message == "")
				cout << message;
			cout << item << sep;
		}
		cout << "\n";
	}
	template<typename T, typename U>
	void print(const map<T, U>& mapToPrint, char sep = '\n', const string& message = "") {
		for (const std::pair<T,U>& item : mapToPrint) {
			if (message == "")
				cout << message;
			cout << item.first << ": " << item.second << sep;
		}
		cout << "\n";
	}
}
