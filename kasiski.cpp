#include "myFunctions.h"
#include <iostream>
#include <string>
#include <map>
#include <algorithm>
#include <vector>
#include <cmath>
#include <set>

std::vector<int> FindDivisors(int len) {
    //divisors for string
    std::vector<int> divisors;
    for (int i = 2; i <= sqrt(len); ++i) {
        if (len % i == 0) {
            divisors.push_back(i);
            if (i * i != len) {
                divisors.push_back(len / i);
            }
        }
    }
    return divisors;
}

std::vector<int> kasiskiExamination(std::string encryptedText) {
    //input
    std::transform(encryptedText.begin(), encryptedText.end(), encryptedText.begin(), ::tolower);

    //frequency analysis for encrypted text
    std::map <char, int> letterFrequency;
    for (char ch = 'a'; ch <= 'z'; ++ch) {
        letterFrequency[ch] = 0;
    }
    for (char el : encryptedText) {
        if (el == ' ') continue;
        letterFrequency[el] += 1;
    }

    //encrypted text without spaces and the amount of letters
    std::string textNoSpaces = encryptedText;
    textNoSpaces.erase(remove_if(textNoSpaces.begin(), textNoSpaces.end(), isspace), textNoSpaces.end());
    int lettersSum = textNoSpaces.size();






    //parts
    int partLen = 3; //trigram
    int parts = lettersSum / partLen;
    std::vector<std::string> textParts;

    for (int i = 0; i < parts; ++i) {
        textParts.push_back(textNoSpaces.substr(i * partLen, partLen));
    }

    int modulo = lettersSum % partLen;
    if (modulo != 0) {
        textParts.push_back(textNoSpaces.substr(parts * partLen, modulo));
    }

    //checking parts for repeating
    std::set<std::string> elChecked;
    std::vector<std::string> elNeeded;
    for (std::string partDom : textParts) {
        int k = 0;
        if (elChecked.contains(partDom)) continue;
        for (std::string partSub : textParts) {
            if (partDom == partSub) k += 1;
        }
        if (k >= 2) {
            elNeeded.push_back(partDom);
        }
        elChecked.insert(elChecked.begin(), partDom);
    }

    //map of repeating elements
    std::map<std::string, std::vector<int>> elIndexes;
    std::vector<int> indexStore;
    for (std::string el : elNeeded) {
        indexStore = {};
        for (int i = 0; i < textParts.size(); ++i) {
            if (textParts[i] == el) indexStore.push_back(i);
        }
        elIndexes[el] = indexStore;
    }

    //outputting map
    std::vector<int> indexDiffV;
    for (const auto& [key, vectors] : elIndexes) {
        if (vectors.size() >= 2) {
            indexDiffV.push_back(vectors[1] - vectors[0]);
            for (int num : vectors) {
            }
        }
    }

    //checking the distance and outputting
    if (indexDiffV.size() == 0) {
        std::cout << "Not enough symbols for analysis, try different text";
    }

    //divisors of distances
    std::map<int, int> commonDivisors;

    bool enough_distances = false;
    if (indexDiffV.size() <= 3) {
        for (int el : indexDiffV) {
            std::vector<int> divisor = FindDivisors(el);
            for (int num : divisor) {
                commonDivisors[num]++;
            }
        }
    }
    else {
        for (int el : indexDiffV) {
            for (int i = 2; i <= sqrt(el); ++i) {
                if (el % i == 0) {
                    commonDivisors[i]++;
                    if (i * i != el) {
                        commonDivisors[el / i]++;
                        enough_distances = true;
                    }
                }
            }
        }
    }

    //frequent divisors - possible key length
    int maxFreq = 0;
    for (const auto& [divisor, freq] : commonDivisors) {
        if (freq > maxFreq) maxFreq = freq; //might not need anymore
    }

    std::vector<int> possibleLen;
    for (const auto& [divisor, freq] : commonDivisors) {
        if ((freq >= 3) and (indexDiffV.size() > 3)) {
            possibleLen.push_back(divisor);
            if (possibleLen.size() >= 11) break; //might need to delete
            \
        }
        else if (not enough_distances) {
            possibleLen.push_back(divisor);
        }
    }

    if (possibleLen.size() <= 2) {
            for (const auto& [divisor, freq] : commonDivisors) {
                if (possibleLen.size() >= 11) break;
                possibleLen.push_back(divisor);
            }
        }

    return possibleLen;
}