#include "myFunctions.h"
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

static std::string vigenereEncrypt(std::string text, std::string key) {
	asciiTable = asciiBuild(97, 123);

	std::transform(key.begin(), key.end(), key.begin(), ::tolower);
	key.erase(remove_if(key.begin(), key.end(), isspace));
	std::vector<int> shifts;
	for (char m : key) {
		shifts.push_back(asciiTable[m] - 97);
	}

	std::string encryptedText;
	int counter = 0;
	for (char el : text) {
		if (el == ' ') {
			encryptedText += ' ';
			continue;
		}

		int asciiPos;
		if (isupper(el)) {
			asciiPos = asciiTable[tolower(el)] + shifts[counter % key.length()];
		}
		else {
			asciiPos = asciiTable[tolower(el)] + shifts[counter % key.length()];
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
	std::cout << "Notice before usage: the decrypter might not give accurate results because of the nature of Kasiski examination." << std::endl << "(the bigger the text, the better)" << std::endl;
	std::cout << "What function are you looking for?" << std::endl << "1. Encrypt" << std::endl << "2. Use Kasiski examination on encrypted text" << std::endl << "3. Decrypt text" << std::endl << "Choose choice (1-3): ";
	int choice;
	std::cin >> choice;
	if (choice == 1) {
		std::cin.ignore(1000, '\n');
		std::string userText;
		std::cout << "Write the text here: ";
		std::getline(std::cin, userText);

		std::string userKey;
		std::cout << "Write the keyword here: ";
		std::getline(std::cin, userKey);

		std::string ans1 = vigenereEncrypt(userText, userKey);
		std::cout << "Encrypted Text:" << std::endl << ans1;
	}
	else if (choice == 2) {
		std::cin.ignore(1000, '\n');
		std::string encryptedText;
		std::cout << "Enter encrypted text: ";
		std::getline(std::cin, encryptedText);
		std::vector<int> keyLengths = kasiskiExamination(encryptedText);

		std::string ans2;
		for (int len : keyLengths) ans2 += (std::to_string(len) + ", ");
		ans2.erase(ans2.size() - 2, 2);
		std::cout << "Possible key lengths: " << ans2;
	}
	else {
		std::string encText;
		std::cout << "Enter encrypted text: ";
		std::getline(std::cin, encText);

		std::vector<std::string> keywords = PossibleKeywords(encText);
		VigenereDecryption(encText, keywords); //auto-output
	}
	return 0;
}