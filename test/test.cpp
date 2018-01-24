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
    std::string testWord = "Gattaca Attic Furniture Stuff Heimola";

    StealthNLP::parseSyllables(testWord, syllables);
    displaySyllables(syllables);
}
