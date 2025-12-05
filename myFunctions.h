#pragma once
#include <string>
#include <vector>
#include <map>

//cracking.cpp
double xSquared(const std::string&, int);
int FindBestShift(std::string&);
std::vector<std::string> PossibleKeywords(std::string&);
int VigenereDecryption(std::string, std::vector<std::string>);

//kasiski.cpp
std::vector<int> kasiskiExamination(std::string);

//project_vshe.cpp
static std::map<char, int> asciiBuild(int, int);
static std::string vigenereEncrypt(std::string, std::string);
