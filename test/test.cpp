#include "Parser.hpp"
#include <vector>
#include <string>
#include <map>
#include <iostream>

std::ostream& operator<<(std::ostream& out, const std::vector<std::string> syllables) noexcept {
    for (const std::string& syllable : syllables) {
        out << "'" <<  syllable << "' ";
    }
    return out;
}

const std::map<std::string, std::vector<std::string>> SYLLABLE_TESTS = {
    {"Azkaban", {"Az", "ka", "ban"}},
    {"Meteorite", {"Me", "te", "o", "rite"}},
    {"Stuff", {"Stuff"}},
    {"Furniture", {"Fur", "ni", "ture"}},
    {"Labrador", {"La", "bra", "dor"}},
    {"Hybrid", {"Hy", "brid"}},
    {"Leo", {"Le" , "o"}},
    {"Syllable", {"Syl", "la", "ble"}},
    {"Hoplite", {"Hop", "lite"}},
    {"Applicable", {"App", "li", "ca", "ble"}},
    {"Easily", {"Ea", "si", "ly"}},
    {"Station", {"Sta", "tion"}},
    {"Communication", {"Com", "mu", "ni", "ca", "tion"}},
    {"Triad", {"Tri", "ad"}},
    {"Negotiation", {"Ne", "go", "ti", "a", "tion"}},
    {"Warhammer", {"War", "ham", "mer"}},
    {"Virtuoso", {"Vir", "tu", "o", "so"}},
    {"Mesopotamia", {"Me", "so", "po", "ta", "mi", "a"}},
    {"Airdrome", {"Air", "drome"}},
    {"Management", {"Ma", "nage", "ment"}},
    {"Mannerisms", {"Man", "ne", "risms"}},
    {"Miner", {"Mi", "ner"}},
    {"Hated", {"Ha", "ted"}},
    {"Belatedly", {"Be", "la", "ted", "ly"}},
};

int testSyllableParser() {
    int numSuccessful = 0;
    for (const auto& sylPair : SYLLABLE_TESTS) {
        auto syllables = StealthNLP::parseSyllables(sylPair.first);
        if (sylPair.second == syllables) {
            ++numSuccessful;
            std::cout << "Correctly parsed " << sylPair.first << " into: " << syllables << '\n';
        } else {
            std::cout << "*\tIncorrectly parsed " << sylPair.first << " into: " << syllables << " instead of: " << sylPair.second << '\n';
        }
    }
    return numSuccessful;
}

int main() {
    int correctlyParsed = testSyllableParser();
    std::cout << "Correctly parsed " << correctlyParsed << " of " << SYLLABLE_TESTS.size() << " words."<< "\n\n";
    std::string word;
    while (true) {
        std::cout << ">> ";
        std::cin >> word;
        std::cout << StealthNLP::parseSyllables(word) << '\n';
    }
}
