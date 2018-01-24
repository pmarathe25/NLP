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
    {"Meteorite", {"Me", "te", "or", "ite"}},
    {"Stuff", {"Stuff"}},
    {"Furniture", {"Fur", "ni", "ture"}},
    {"Labrador", {"Lab", "ra", "dor"}},
    {"Hybrid", {"Hy", "brid"}},
    {"Leo", {"Leo"}},
};

int testSyllableParser() {
    int numSuccessful = 0;
    for (const auto& sylPair : SYLLABLE_TESTS) {
        auto syllables = StealthNLP::parseSyllables(sylPair.first);
        if (sylPair.second == syllables) {
            ++numSuccessful;
            std::cout << "Correctly parsed " << sylPair.first << " into: " << syllables << '\n';
        } else {
            std::cout << "Incorrectly parsed " << sylPair.first << " into: " << syllables << " instead of: " << sylPair.second << '\n';
        }
    }
    return numSuccessful;
}

int main() {
    std::vector<std::string> syllables;
    // std::string testWord = "Gattaca Attic Furniture Stuff Heimola";
    // std::string testWord = "Azkaban";
    // std::string testWord = "Stuff";
    // std::string testWord = "Furniture";
    // std::string testWord = "Labrador";
    // std::string testWord = "Syllable";
    // std::string testWord = "Meteorite";
    // std::cout << "Syllable Count: " << StealthNLP::parseSyllables(testWord, syllables) << '\n';
    // displaySyllables(syllables);
    int correctlyParsed = testSyllableParser();
    std::cout << "Correctly parsed " << correctlyParsed << " of " << SYLLABLE_TESTS.size() << " words."<< '\n';
}
