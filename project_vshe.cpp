#include <iostream>
#include <string>
#include <algorithm>
#include <cctype>
#include <vector>
#include <map>

//global variables
std::map<char, int> asciiTable;

//functions
static std::map<char, int> asciiBuild(int chStart, int chEnd) {
	for (int ch = chStart; ch < chEnd; ++ch) {
		asciiTable.insert({ static_cast<char>(ch), ch }); //i can use emplace instead of insert
	}
	return asciiTable;
}

static std::string vigenereEncrypt() {
	//asciiBuild(65, 91);
	asciiBuild(97, 123);
	for (const auto [k, num] : asciiTable) {
		std::cout << "[" << k << "] = " << num << std::endl;
	}
	std::string userText;
	std::getline(std::cin, userText);

	std::string userKey;
	std::getline(std::cin, userKey);
	std::transform(userKey.begin(), userKey.end(), userKey.begin(), ::tolower);
	userKey.erase(remove_if(userKey.begin(), userKey.end(), isspace));
	std::vector<int> shifts;
	for (char m : userKey) {
		shifts.push_back(asciiTable[m] - 97);
	}

	std::string encryptedText;
	int counter = 0;
	for (char el : userText) {
		if (el == ' ') {
			encryptedText += ' ';
			continue;
		}

		int asciiPos;
		if (isupper(el)) {
			asciiPos = asciiTable[tolower(el)] + shifts[counter % userKey.length()];
		}
		else {
			asciiPos = asciiTable[tolower(el)] + shifts[counter % userKey.length()];
		}

		if (asciiPos > 122) {
			asciiPos = 97 + (asciiPos - 123);
		}

		char newEl;
		if (isupper(el)) {
			newEl = toupper(static_cast<char>(asciiPos));
		}
		else {
			newEl = static_cast<char>(asciiPos);
		}
		counter += 1;
		encryptedText += newEl;
	}

	return encryptedText;
}

//main process
int main() {
	std::cout << vigenereEncrypt() << std::endl;
	return 0;
}