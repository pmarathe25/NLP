#include "Parser.hpp"
#include "EnglishConstants.hpp"

namespace StealthNLP {
    namespace {
        inline void appendToPreviousSyllable(std::vector<std::string>& syllables, std::string::const_iterator& syllableBegin,
            const std::string::const_iterator& syllableEnd) noexcept {
            if (syllableBegin < syllableEnd) {
                syllables.back().append(syllableBegin, syllableEnd);
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

        inline bool shouldSplitCharacters(unsigned char first, unsigned char second) noexcept {
            // Either it is a strong succeeding consonant or a double letter
            return isDoubleConsonant(first, second)
                && (!isWeakSucceedingConsonantPair(first, second) || isDoubleLetter(first, second));
        }

        inline void removeDuplicateConsonants(std::vector<std::string>& syllables, std::string::const_iterator& begin,
            const std::string::const_iterator& end) {
            // Strong consonants and double consonants should be split as long as they are within bounds
            while (begin + 1 < end && shouldSplitCharacters(*begin, *(begin + 1))) {
                syllables.back() += *begin++;
            }
        }

        inline void addSyllable(std::vector<std::string>& syllables, std::string::const_iterator& syllableBegin,
            const std::string::const_iterator& syllableEnd, const std::string::const_iterator& wordBegin,
            const std::string::const_iterator& wordEnd, int& syllableCount) noexcept {
            // Remove duplicate consonants from this syllable if this is not the first syllable.
            if (syllableCount > 0) removeDuplicateConsonants(syllables, syllableBegin, wordEnd);
            // If the previous vowel was a silent E, merge into the previous syllable
            if (isSilentE(syllableEnd - 1, wordBegin, wordEnd)) {
                appendToPreviousSyllable(syllables, syllableBegin, syllableEnd);
            } else if (syllableBegin < syllableEnd) {
                // Otherwise add the syllable (if valid)
                syllables.emplace_back(syllableBegin, syllableEnd);
                syllableBegin = syllableEnd;
                ++syllableCount;
            }
        }
    }

    // Use supplied buffer
    int parseSyllables(const std::string& word, std::vector<std::string>& syllables) noexcept {
        // How many syllables in this word?
        int syllableCount = 0;
        // Always cache 2 letters at a time
        unsigned char currentLetter = '\0', previousLetter = '\0';
        bool vowelFound = false, prevVowelFound = false;
        // Maintain endpoints for syllables
        std::string::const_iterator syllableBegin = word.cbegin();
        // GO!
        for (std::string::const_iterator letter = word.cbegin(); letter < word.cend(); ++letter) {
            // Grab letters
            previousLetter = currentLetter;
            currentLetter = *letter;
            // Remember whether the previous letter was a vowel and check if this letter is a vowel.
            prevVowelFound = vowelFound;
            vowelFound = isVowel(currentLetter);
            // If this letter is a consonant (or acting consonant) but the last letter was a vowel, end the syllable.
            if (prevVowelFound && (!vowelFound || isActingConsonantPair(letter, word.cbegin(), word.cend()))) {
                addSyllable(syllables, syllableBegin, letter, word.cbegin(), word.cend(), syllableCount);
            }
        }
        // Handle last letter. If we end on a consonant (or 'e' in special cases)...
        if (isConsonant(word.back()) || isSilentE(word.cend() - 1, word.cbegin(), word.cend())) {
            // ...add it to the previous syllable if there is one.
            if (syllableCount != 0) appendToPreviousSyllable(syllables, syllableBegin, word.cend());
        } else {
            // Otherwise add the syllable remaining in the buffer
            addSyllable(syllables, syllableBegin, word.cend(), word.cbegin(), word.cend(), syllableCount);
        }
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
