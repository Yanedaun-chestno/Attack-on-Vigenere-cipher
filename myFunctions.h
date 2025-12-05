#pragma once
#include <string>
#include <vector>
#include <map>

//cracking.cpp
double xSquared(const std::string&, int);
int FindBestShift(std::string&);
std::vector<std::string> PossibleKeywords(); //might need to fix
int VigenereDecryption(std::string, std::vector<std::string>);

//kasiski.cpp
std::vector<int> kasiskiExamination(); //need fix

//project_vshe.cpp
static std::map<char, int> asciiBuild(int, int);
static std::string vigenereEncrypt(); //need fix
