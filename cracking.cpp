#include "myFunctions.h"
#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
#include <map>
//Ji fw hz bbj ns tx bvnj cw lam ehumxahv Kuunlwk bwf difdxz wa jbi ebvr ge myxymf Gxy wdbvuf qhh skzcji ij gnbfnwysml ncejorw Hz hb juow tzaf qaeagah n iye gy bfbkvpwl Ibq rs shiwgvda ifw bvrc Ns vbm hb ifiwi Vc zeli sgl pl q mpwxx hb iuc ox mbq Jbi zxifgqwlw tvr gxy xzhcgndx rsmcfnb mlgvsg Gxux xemgu ym lwbz hb jcw s vwbfkgqsmqca Tyzgnbzl ji fw pqguux Xg wqs ge mpwxx Hb ifiwi xsesbefvm hb tlisfim gxyvwl bvr hof Xhz wa jbel ltsrf ij vxihu mbel wzsncm qsr kczu Qlwg es uqpi kactsbyh gyn huym qgkboy simd Fcgg wczw na dnkmi lamfr ym xzx zsffygl Mpog cuowl koyqgmlr wt fe fsfz twsu

const double EN_FREQ[26] = {
0.08167, 0.01492, 0.02782, 0.04253, 0.12702, 0.02228,
0.02015, 0.06094, 0.06966, 0.00153, 0.00772, 0.04025,
0.02406, 0.06749, 0.07507, 0.01929, 0.00095, 0.05987,
0.06327, 0.09056, 0.02758, 0.00978, 0.02360, 0.00150,
0.01974, 0.00074
};


double xSquared(const std::string &part, int shift) {
    int freq[26] = { 0 };

    for (char ch : part) {
        if ('a' <= ch <= 'z') {
            int decrypted = (ch - 'a' - shift + 26) % 26;
            freq[decrypted]++;
        }
    }

    double xSqr = 0.0;
    for (int i = 0; i < 26; ++i) {
        double expected = EN_FREQ[i] * part.size();
        double difference = expected - freq[i];
        xSqr += (pow(difference, 2)) / expected;
    }

    return xSqr;
}


int FindBestShift(std::string& part) {
    double bestXsqr = 1e9;
    int bestShift = 0;

    for (int shift = 0; shift < 26; ++shift) {
        double xSqr = xSquared(part, shift);
        if (xSqr < bestXsqr) {
            bestXsqr = xSqr;
            bestShift = shift;
        }
    }

    return bestShift;
}


std::vector<std::string> PossibleKeywords(std::string& encryptedText) {
    getline(std::cin, encryptedText);
    std::transform(encryptedText.begin(), encryptedText.end(), encryptedText.begin(), ::tolower);

    std::string textNoSpaces = encryptedText;
    textNoSpaces.erase(remove_if(textNoSpaces.begin(), textNoSpaces.end(), std::isspace), textNoSpaces.end());
    int textLen = textNoSpaces.size();

    std::cout << textNoSpaces << std::endl;
    std::cout << textLen << std::endl;

    std::vector<int> possibleKeys = kasiskiExamination(encryptedText);
    std::vector<std::string> keywords;
    for (int key : possibleKeys) {
        std::vector<std::string> caesarList;
        std::string possibleKeyword = "";
        for (int i = 0; i < key; ++i) {
            std::string currentKey;
            for (int ch = i; ch < textLen; ch = ch + key) {
                currentKey += textNoSpaces[ch];
            }
            caesarList.push_back(currentKey);
        }
        for (std::string text : caesarList) {
            possibleKeyword += ('a' + FindBestShift(text));
        }
        std::cout << possibleKeyword << std::endl;
        keywords.push_back(possibleKeyword);
    }

    return keywords;
}


int VigenereDecryption(std::string encryptedText, std::vector<std::string> keywords) {
    std::map<std::string, std::string> textVariations;
    for (std::string key : keywords) {
        int kLen = key.size();
        int index = 0;
        std::string decryptedText;

        for (char ch : encryptedText) {
            if (ch >= 'a' && ch <= 'z') {
                int shift = key[index % kLen] - 'a';
                decryptedText += static_cast<char>(((ch - 'a' - shift + 26) % 26) + 'a');
                index++;
            }
            else {
                decryptedText += ch;
            }
        }
        textVariations[key] = decryptedText;
    }

    for (const auto& [key, text] : textVariations) {
        std::cout << std::endl << "Possible key: " << key << std::endl << "Text for key: " << text << std::endl;
    }

    return 0;
}