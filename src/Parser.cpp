#include "Parser.hpp"
#include "EnglishConstants.hpp"

#include <iostream>

namespace StealthNLP {
    namespace {
        inline void addSyllable(std::vector<std::string>& syllables, std::string::const_iterator& syllableBegin,
            const std::string::const_iterator& syllableEnd, int& syllableCount) noexcept {
            syllables.emplace_back(syllableBegin, syllableEnd);
            ++syllableCount;
            syllableBegin = syllableEnd;
            // DEBUG
            // std::cout << "Added syllable: " << syllables.back() << '\n';
            // END DEBUG
        }
    }

    // Use supplied buffer
    int parseSyllables(const std::string& word, std::vector<std::string>& syllables) noexcept {
        int syllableCount = 0;
        char currentLetter = '\0', previousLetter = '\0';
        bool vowelFound = false, actingConsonantFound = false, prevVowelFound = false;
        // Maintain endpoints for syllables
        std::string::const_iterator syllableBegin = word.cbegin();
        // GO!
        for (std::string::const_iterator letter = word.cbegin(); letter != word.cend(); ++letter) {
            previousLetter = currentLetter;
            currentLetter = std::tolower(*letter);
            // Remember whether the previous letter was a vowel and check if this letter is a vowel.
            prevVowelFound = vowelFound;
            // Check if this vowel is going to act like a consonant.
            actingConsonantFound = VOWEL_PAIRS.count(currentLetter) && VOWEL_PAIRS.at(currentLetter).count(previousLetter);
            vowelFound = VOWELS.count(currentLetter) && !actingConsonantFound;

            // DEBUG
            // if (actingConsonantFound) std::cout << "Acting consonant found at: " << currentLetter << '\n';
            // else if (vowelFound) std::cout << "Vowel found at: " << currentLetter << '\n';
            // else std::cout << "Consonant found at: " << currentLetter << '\n';
            // END DEBUG

            // If this letter is a consonant (or acting consonant) but the last letter was a vowel, end the syllable.
            if (actingConsonantFound) {
                addSyllable(syllables, syllableBegin, letter, syllableCount);
                // Scan until the next vowel
                prevVowelFound = true;
                while (!vowelFound) {
                    vowelFound = VOWELS.count(*++letter);
                }
                addSyllable(syllables, syllableBegin, letter, syllableCount);
            } else if (prevVowelFound && !vowelFound ) {
                if (!VOWELS.count(*syllableBegin) && !VOWELS.count(*(syllableBegin + 1)) && syllableCount != 0
                    && (!WEAK_SUCCEEDING_CONSONANTS.count(*(syllableBegin + 1)) || *syllableBegin == *(syllableBegin + 1))) {
                    // Strong consonants and double consonants will always be split
                    syllables.back() += *syllableBegin++;
                    // DEBUG
                    // std::cout << "Found double consonant: " << *syllableBegin << *(syllableBegin + 1) << '\n';
                    // END DEBUG
                }
                addSyllable(syllables, syllableBegin, letter, syllableCount);
            }
        }
        // Handle last letter
        if (!VOWELS.count(word.back()) || (VOWELS.count(word[word.size() - 3]) && word.back() == 'e')) {
            // If we end on a consonant (or 'e' in special cases), add it to the previous syllable.
            syllables.back() += std::string(syllableBegin, word.cend());
        } else {
            // Otherwise add the syllable remaining in the buffer
            addSyllable(syllables, syllableBegin, word.cend(), syllableCount);
        }
        return syllableCount;
    }

    // Allocate a new buffer
    std::vector<std::string> parseSyllables(const std::string& word) noexcept {
        std::vector<std::string> syllables;
        parseSyllables(word, syllables);
        return syllables;
    }

} /* StealthNLP */
