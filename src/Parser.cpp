#include "Parser.hpp"
#include "EnglishConstants.hpp"

#include <iostream>

namespace StealthNLP {
    namespace {
        inline void addSyllable(std::vector<std::string>& syllables, std::string::const_iterator& syllableBegin,
            const std::string::const_iterator& syllableEnd, int& syllableCount) noexcept {
            if (syllableBegin < syllableEnd) {
                syllables.emplace_back(syllableBegin, syllableEnd);
                ++syllableCount;
                syllableBegin = syllableEnd;
            }
        }

        inline bool findConsonantExtent(std::string::const_iterator& letter, const std::string::const_iterator& wordEnd) {
            bool validExtent = false;
            while (isConsonant(*++letter) && letter < wordEnd) {
                validExtent = true;
            }
            return validExtent;
        }

        inline bool shouldSplitCharacters(char first, char second) noexcept {
            // Either it is a strong succeeding consonant or a double letter
            return isDoubleConsonant(first, second)
                && (!isWeakSucceedingConsonant(second) || isDoubleLetter(first, second));
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
        for (std::string::const_iterator letter = word.cbegin(); letter < word.cend(); ++letter) {
            // Grab lettersLeo
            previousLetter = currentLetter;
            currentLetter = *letter;
            // Remember whether the previous letter was a vowel and check if this letter is a vowel.
            prevVowelFound = vowelFound;
            actingConsonantFound = isActingConsonantPair(previousLetter, currentLetter);
            vowelFound = isVowel(currentLetter) && !actingConsonantFound;
            // If this letter is a consonant (or acting consonant) but the last letter was a vowel, end the syllable.
            if (actingConsonantFound) {
                addSyllable(syllables, syllableBegin, letter, syllableCount);
                // Scan until the next vowel
                vowelFound = findConsonantExtent(letter, word.cend());
                if (vowelFound)  addSyllable(syllables, syllableBegin, letter, syllableCount);
            } else if (prevVowelFound && !vowelFound) {
                if (syllableCount != 0 && shouldSplitCharacters(*syllableBegin, *(syllableBegin + 1))) {
                    // Strong consonants and double consonants should be split
                    syllables.back() += *syllableBegin++;
                }
                addSyllable(syllables, syllableBegin, letter, syllableCount);
            }
        }
        // Handle last letter
        if (actingConsonantFound || isConsonant(word.back()) || endsOnSilentE(word)) {
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
