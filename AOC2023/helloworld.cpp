#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <algorithm>
#include <map>


using std::string;
using std::cout;
using std::cin;
using std::vector;

namespace day1q1 {
    void main(const string& filename) {
        // open file
        string line{};
        std::ifstream myfile(filename);
        // read one line each
        //  
        [[maybe_unused]] int total_calibration{};
        while (std::getline(myfile, line)) {
            vector<int> nums{};
            for (char c : line) {
                if (isdigit(c)) {
                    nums.push_back(c - '0');
                }
            }
            int calibrationValue = nums[0] * 10 + nums[nums.size() - 1];
            //cout << calibrationValue << "\n";
            total_calibration += calibrationValue;
        }
        cout << total_calibration;
        
    }
}
namespace day1q2 {
    std::pair<int, int> findFirstAndLastInt(const string& s) {
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

    void main(const string& filename) {
        const std::map<string, int> words = { {"one", 1}, {"two", 2}, {"three", 3}, {"four", 4}, {"five", 5}, {"six", 6}, {"seven",7}, {"eight",8}, {"nine",9} };

        // open file
        string line{};
        std::ifstream myfile(filename);
        [[maybe_unused]] int total_calibration{};

        while (std::getline(myfile, line)) {
            [[maybe_unused]] int first{};
            [[maybe_unused]] int last{};
            [[maybe_unused]] int first_index{};
            [[maybe_unused]] int last_index{};

            auto [a, b] = findFirstAndLastInt(line);
			first_index = a;
			last_index = b;
			first = line[first_index] - '0';
			last = line[last_index] - '0';

            for (const auto& [key, num] : words) {
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
        cout << total_calibration;
    }
}

int main()
{
    string filename = "day1q1.txt";
    //string filename = "test.txt";
    day1q1::main(filename);
    cout << " ";
    day1q2::main(filename);

    string teststring = "6shgbprkpbksnfourfivemvncvg2eight";
    std::pair<int, int> a = day1q2::findFirstAndLastInt(teststring);
    cout << " " << a.first << " " << a.second;
}

