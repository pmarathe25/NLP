#include "Parser.hpp"
#include "EnglishConstants.hpp"

namespace StealthNLP {
    namespace {
        inline bool addSyllable(std::vector<std::string>& syllables, std::string::const_iterator& syllableBegin,
            const std::string::const_iterator& syllableEnd) noexcept {
            if (syllableBegin < syllableEnd) {
                syllables.emplace_back(syllableBegin, syllableEnd);
                syllableBegin = syllableEnd;
                return true;
            }
            return false;
        }

        inline bool findConsonantExtent(std::string::const_iterator& letter, const std::string::const_iterator& wordEnd) {
            bool validExtent = false;
            while (isConsonant(*++letter) && letter < wordEnd) {
                validExtent = true;
            }
            return validExtent;
        }

        inline bool shouldSplitCharacters(unsigned char first, unsigned char second) noexcept {
            // Either it is a strong succeeding consonant or a double letter
            return isDoubleConsonant(first, second)
                && (!isWeakSucceedingConsonant(second) || isDoubleLetter(first, second));
        }
    }

    // Use supplied buffer
    int parseSyllables(const std::string& word, std::vector<std::string>& syllables) noexcept {
        int syllableCount = 0;
        unsigned char currentLetter = '\0', previousLetter = '\0';
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
            if (prevVowelFound && !vowelFound) {
                if (syllableCount != 0 && shouldSplitCharacters(*syllableBegin, *(syllableBegin + 1))) {
                    // Strong consonants and double consonants should be split
                    syllables.back() += *syllableBegin++;
                }
                syllableCount += addSyllable(syllables, syllableBegin, letter);
                // Change the acting consonant to a vowel now.
                vowelFound = actingConsonantFound;
            }
        }
        // If we end on a consonant (or 'e' in special cases), add it to the previous syllable.
        if (isConsonant(word.back()) || endsOnSilentE(word)) syllables.back() += std::string(syllableBegin, word.cend());
        // Otherwise add the syllable remaining in the buffer
        else syllableCount += addSyllable(syllables, syllableBegin, word.cend());
        // Done!
        return syllableCount;
    }

    // Allocate a new buffer
    std::vector<std::string> parseSyllables(const std::string& word) noexcept {
        std::vector<std::string> syllables;
        parseSyllables(word, syllables);
        return syllables;
    }

} /* StealthNLP */
