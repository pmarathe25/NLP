#include "Parser.hpp"
#include <vector>
#include <string>
#include <iostream>

void displaySyllables(const std::vector<std::string> syllables) noexcept {
    for (const std::string& syllable : syllables) {
        std::cout << "'" <<  syllable << "'" << '\n';
    }
}

int main() {
    std::vector<std::string> syllables{};
    // std::string testWord = "Gattaca Attic Furniture Stuff Heimola";
    std::string testWord = "Stuff";
    // std::string testWord = "Furniture";
    // std::string testWord = "Labrador";
    // std::string testWord = "Syllable";
    // std::string testWord = "Meteorite";

    std::cout << "Syllable Count: " << StealthNLP::parseSyllables(testWord, syllables) << '\n';
    displaySyllables(syllables);
}
