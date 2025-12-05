#include "myFunctions.h"
#include <iostream>
#include <string>
#include <map>
#include <algorithm>
#include <vector>
#include <cmath>
#include <set>
//Ji fw hz bbj ns tx bvnj cw lam ehumxahv Kuunlwk bwf difdxz wa jbi ebvr ge myxymf Gxy wdbvuf qhh skzcji ij gnbfnwysml ncejorw Hz hb juow tzaf qaeagah n iye gy bfbkvpwl Ibq rs shiwgvda ifw bvrc Ns vbm hb ifiwi Vc zeli sgl pl q mpwxx hb iuc ox mbq Jbi zxifgqwlw tvr gxy xzhcgndx rsmcfnb mlgvsg Gxux xemgu ym lwbz hb jcw s vwbfkgqsmqca Tyzgnbzl ji fw pqguux Xg wqs ge mpwxx Hb ifiwi xsesbefvm hb tlisfim gxyvwl bvr hof Xhz wa jbel ltsrf ij vxihu mbel wzsncm qsr kczu Qlwg es uqpi kactsbyh gyn huym qgkboy simd Fcgg wczw na dnkmi lamfr ym xzx zsffygl Mpog cuowl koyqgmlr wt fe fsfz twsu

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
    for (const auto [k, num] : letterFrequency) {
        std::cout << "[" << k << "]" << " = " << num << std::endl;
    }

    //encrypted text without spaces and the amount of letters
    std::string textNoSpaces = encryptedText;
    textNoSpaces.erase(remove_if(textNoSpaces.begin(), textNoSpaces.end(), isspace), textNoSpaces.end());
    std::cout << "Normal length: " << textNoSpaces.size() << std::endl;
    int lettersSum = textNoSpaces.size();

    
    



    //parts
    int partLen = 3; //trigram
    int parts = lettersSum / partLen;
    std::vector<std::string> textParts;

    for (int i = 0; i < parts; ++i) {
        textParts.push_back(textNoSpaces.substr(i * partLen, partLen));
        std::cout << textParts.back() << ' ';
    }
    std::cout << "\n";
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
            std::cout << partDom << " = " << k << std::endl;
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
                std::cout << "Element: " << key << ", Index: " << num << std::endl;
            }
        }
    }

    //checking the distance and outputting
    if (indexDiffV.size() == 0) {
        std::cout << "Not enough symbols for analysis, try different text";
    }
    else {
        std::cout << "Distances: ";
        for (int el : indexDiffV) {
            std::cout << el << ", ";
        }
        std::cout << '\n';
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
        std::cout << "Divisor: " << divisor << ", frequency:" << freq << std::endl;
        if (freq > maxFreq) maxFreq = freq;
    }

    std::vector<int> possibleLen;
    for (const auto& [divisor, freq] : commonDivisors) {
        if ((freq == maxFreq) and (indexDiffV.size() > 3)) {
            std::cout << "Possible key length: " << divisor << std::endl;
            possibleLen.push_back(divisor);
        }
        else if (not enough_distances) {
            std::cout << "Possible key length: " << divisor << std::endl;
            possibleLen.push_back(divisor);
        }
    }

    return possibleLen;
}