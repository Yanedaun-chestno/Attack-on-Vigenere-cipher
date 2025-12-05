#include <iostream>
#include <string>
#include <map>
#include <algorithm>
#include <vector>
#include <cmath>
#include <set>
//Ji fw hz bbj ns tx bvnj cw lam ehumxahv Kuunlwk bwf difdxz wa jbi ebvr ge myxymf Gxy wdbvuf qhh skzcji ij gnbfnwysml ncejorw Hz hb juow tzaf qaeagah n iye gy bfbkvpwl Ibq rs shiwgvda ifw bvrc Ns vbm hb ifiwi Vc zeli sgl pl q mpwxx hb iuc ox mbq Jbi zxifgqwlw tvr gxy xzhcgndx rsmcfnb mlgvsg Gxux xemgu ym lwbz hb jcw s vwbfkgqsmqca Tyzgnbzl ji fw pqguux Xg wqs ge mpwxx Hb ifiwi xsesbefvm hb tlisfim gxyvwl bvr hof Xhz wa jbel ltsrf ij vxihu mbel wzsncm qsr kczu Qlwg es uqpi kactsbyh gyn huym qgkboy simd Fcgg wczw na dnkmi lamfr ym xzx zsffygl Mpog cuowl koyqgmlr wt fe fsfz twsu

std::vector<int> kasiskiExamination() {
    //input
    std::string encryptedText;
    getline(std::cin, encryptedText);
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
    int lettersSum = textNoSpaces.length();
    std::cout << lettersSum << std::endl;

    //divisors for string
    std::vector<int> divisors;
    for (int i = 1; i <= sqrt(lettersSum); ++i) {
        if (lettersSum % i == 0) {
            divisors.push_back(i);
            if (i * i != lettersSum) {
                divisors.push_back(lettersSum / i);
            }
        }
    }

    //finding good part length for analysis
    int partLen;
    for (int el : divisors) {
        std::cout << el << ' ';
        if (el == 3) {
            partLen = el;
        }
    }
    std::cout << "\n";

    //parts
    int parts = lettersSum / partLen;
    std::vector<std::string> textParts;
    for (int i = 0; i < parts; ++i) {
        textParts.push_back(textNoSpaces.substr(i * partLen, partLen));
        std::cout << textParts[i] << ' ';
    }
    std::cout << "\n";

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
        for (int num : vectors) {
            std::cout << "Element: " << key << ", Index: " << num << std::endl;
        }
        indexDiffV.push_back(vectors[1] - vectors[0]);
    }

    //checking the distance and outputting
    std::cout << "Distances: ";
    for (int el : indexDiffV) {
        std::cout << el << ", ";
    }
    std::cout << '\n';

    //divisors of distances
    std::map<int, int> commonDivisors;
    for (int el : indexDiffV) {
        for (int i = 2; i <= sqrt(el); ++i) {
            if (el % i == 0) {
                commonDivisors[i]++;
                if (i * i != el) {
                    commonDivisors[el / i]++;
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
        if (freq == maxFreq) {
            std::cout << "Possible key length: " << divisor << std::endl;
            possibleLen.push_back(divisor);
        }
    }

    return possibleLen;
}