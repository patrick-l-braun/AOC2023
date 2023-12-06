#include "day2.h"
#include <cmath>

namespace day2 {
	constexpr int maxRed = 12;
    constexpr int maxBlue = 14;
    constexpr int maxGreen = 13;
    bool validLine(const string& line) {
		// use stringstream
		int colonIndex = static_cast<int>(line.find(":"));
		string inputs = line.substr(colonIndex + 2); // moves to first input
		std::stringstream ss(inputs);

		string colour;
		int num;
		int red{};
		int green{};
		int blue{};
		while (ss >> num >> colour) {
			switch (colour[0])
			{
			case 'r':
				red = num;
				break;
			case 'b':
				blue = num;
				break;
			case 'g':
				green = num;
				break;
			default:
				throw std::runtime_error("Invalid colour");
			}

			// check if last digit is ; 
			// if it is we need to compare this case
			if (colour[colour.size() - 1]) {
				if (red > maxRed)
					return false;
				if (blue > maxBlue)
					return false;
				if (green > maxGreen)
					return false;
			}
		}
		if (red > maxRed)
			return false;
		if (blue > maxBlue)
			return false;
		if (green > maxGreen)
			return false;



		return true;
    }
	int minPower(const string& line) {
		// use stringstream
		int colonIndex = static_cast<int>(line.find(":"));
		string inputs = line.substr(colonIndex + 2); // moves to first input
		std::stringstream ss(inputs);

		string colour;
		int num;
		
		int red = 0;
		int green = 0;
		int blue = 0;
		while (ss >> num >> colour) {
			switch (colour[0])
			{
			case 'r':
				red = std::max(red, num);
				break;
			case 'b':
				blue = std::max(blue, num);
				break;
			case 'g':
				green = std::max(green, num);
				break;
			default:
				throw std::runtime_error("Invalid colour");
			}

		}
		return red * green * blue;

	}
    int totalPower(const string& filename) {
        string line{};
        std::ifstream file(filename);

        int total{};
        while (std::getline(file, line)) {
            total += minPower(line);
        }
        return total;
    }
    int totalPossible(const string& filename) {
        string line{};
        std::ifstream file(filename);

        int total{};
        int id = 1;
        while (std::getline(file, line)) {
            total += validLine(line) ? id : 0 ;
            ++id;
        }
        return total;
    }
    void main() {
		// First puzzle 2176
        cout << totalPossible("day2.txt") << "\n";
		cout << totalPower("day2.txt") << "\n";
    }
}
