#include <iostream>
#include <string> // incluedes find and rfind
#include <fstream>
#include <vector>
#include <map>


using std::string;
using std::cout;    
using std::cin;
using std::vector;

namespace day1 {
    int findTotal(const string& filename) {
        // open file using ifstream
        string line{};
        std::ifstream myfile(filename);

        // sums the total for each line
        int total_calibration{};

        // read one line each
        while (std::getline(myfile, line)) {
            // find all the nums in the string
            vector<int> nums{};
            for (char c : line) {
                if (isdigit(c)) {
                    // converts char to int value
                    nums.push_back(c - '0');
                }
            }
            // get the first and last value
            int calibrationValue = nums[0] * 10 + nums[nums.size() - 1];
            total_calibration += calibrationValue;
        }
        return total_calibration;
    }

    std::pair<int, int> findIndexOfFirstAndLastInt(const string& s) {
        int first{};
        int last{};
        for (int i = 0; i < s.size(); i++) {
            if (isdigit(s[i])) {
                first = i;
                break;
            }
                
        }
        for (int i = static_cast<int>(s.size() - 1); i >= 0; --i){
            if (isdigit(s[i])) {
                last = i;
                break;
            }
        }
        return std::make_pair(first, last);
    }

    int findTotalWithWords(const string& filename) {
        const std::map<string, int> wordsToInt = { {"one", 1}, {"two", 2}, {"three", 3}, {"four", 4}, {"five", 5}, {"six", 6}, {"seven",7}, {"eight",8}, {"nine",9} };

        // open file
        string line{};
        std::ifstream myfile(filename);
        int total_calibration{};

        while (std::getline(myfile, line)) {
            int first{};
            int last{};
            int first_index{};
            int last_index{};

            auto [a, b] = findIndexOfFirstAndLastInt(line);
			first_index = a;
			last_index = b;
			first = line[first_index] - '0';
			last = line[last_index] - '0';

            for (const auto& [key, num] : wordsToInt) {
                int index = static_cast<int>(line.find(key));
                if (index < 0) { continue; }
                if (index < first_index) {
                    first_index = index;
                    first = num;
                }
                int rIndex = static_cast<int>(line.rfind(key));
                if (rIndex < 0) { continue; }
                if (rIndex > last_index) {
                    last_index = rIndex;
                    last = num;
                }
            }
            total_calibration += first * 10 + last;

        }
        return total_calibration;
    }
    void main() {
		string filename = "day1q1.txt";
		//string filename = "test.txt";

		cout << findTotal(filename);
		cout << " ";
		cout << findTotalWithWords(filename);
        // 53921 54676

    }
}

int main()
{
    day1::main();
}

