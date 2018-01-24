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

    int parseSyllables(const std::string& word, std::vector<std::string>& syllables) noexcept {
        int syllableCount = 0;
        bool vowelFound = false, actingConsonantFound = false, prevVowelFound = false;
        // Maintain endpoints for syllables
        std::string::const_iterator syllableBegin = word.cbegin();
        // GO!
        for (std::string::const_iterator letter = word.cbegin(); letter != word.cend(); ++letter) {
            // Remember whether the previous letter was a vowel and check if this letter is a vowel.
            prevVowelFound = vowelFound;
            // Check if this vowel is going to act like a consonant.
            actingConsonantFound = VOWEL_PAIRS.count(*letter) && VOWEL_PAIRS.at(*letter).count(*(letter - 1));
            vowelFound = VOWELS.count(*letter) && !actingConsonantFound;

            // DEBUG
            // if (actingConsonantFound) std::cout << "Acting consonant found at: " << *letter << '\n';
            // else if (vowelFound) std::cout << "Vowel found at: " << *letter << '\n';
            // else std::cout << "Consonant found at: " << *letter << '\n';
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
                    && (!WEAK_CONSONANTS.count(*syllableBegin) || *syllableBegin == *(syllableBegin + 1))) {
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
} /* StealthNLP */
