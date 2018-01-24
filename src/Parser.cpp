#include "Parser.hpp"
#include "EnglishConstants.hpp"

#include <iostream>

namespace StealthNLP {
    std::vector<std::string>& parseSyllables(const std::string& word, std::vector<std::string>& syllables) noexcept {
        bool vowelFound = false, prevVowelFound = false;
        // Maintain endpoints for syllables
        std::string::const_iterator syllableBegin = word.begin(), syllableEnd = word.begin();
        // GO!
        for (std::string::const_iterator letter = word.begin(); letter != word.end(); ++letter) {
            // Remember whether the previous letter was a vowel and check if this letter is a vowel.
            prevVowelFound = vowelFound;
            vowelFound = VOWELS.count(*letter);
            // If this letter is a consonant but the last letter was a vowel, end the syllable.
            if (prevVowelFound && !vowelFound) {
                // End the previous syllable
                syllableEnd = letter;
                if (*syllableBegin == *(syllableBegin + 1)) {
                    // In case of a double letter, append the first one to the previous syllable
                    syllables.back() += *syllableBegin++;
                }
                syllables.emplace_back(syllableBegin, syllableEnd);
                // Start a new syllable
                syllableBegin = letter;
            }
        }
        // Handle last letter
        if (!VOWELS.count(word.back())) {
            // If we end on a consonant, add it to the previous syllable.
            syllables.back() += std::string(syllableEnd, word.end());
        } else {
            // Otherwise add the syllable remaining in the buffer
            syllables.emplace_back(syllableEnd, word.end());
        }
        return syllables;
    }
} /* StealthNLP */
