#ifndef STEALTHNLP_ENGLISH_CONSTANTS_H
#define STEALTHNLP_ENGLISH_CONSTANTS_H
#include <unordered_set>
#include <unordered_map>
#include <vector>

namespace StealthNLP {
    const std::unordered_set<unsigned char> VOWELS = {'a', 'e', 'i', 'o', 'u', 'y'};

    // Consonants that cannot be separated from the consonant before them. Includes exceptions to the rule
    const std::unordered_map<unsigned char, std::unordered_set<unsigned char>> WEAK_SUCCEEDING_CONSONANTS = {
        {'l', {'d', 'p'}},
        {'r', {}},
        {'h', {'r'}},
    };

    // Letters that remove silent E's immediately preceeding them
    const std::unordered_set<unsigned char> SILENT_E_REMOVERS = {'d', 'r', 'n', 'a', 'e', 'i', 'o', 'u', 'y'};

    // A vowel that acts like a consonant when preceding by any of the following vowels
    const std::unordered_map<unsigned char, std::unordered_set<unsigned char>> ACTING_CONSONANT_PAIR = {
        {'o', {'a', 'e', 'u', 'i'}},
        {'a', {'i'}},
        {'u', {'i'}},
    };

    // When an acting consonant is wrapped by one of these, it invalidates the acting consonant
    const std::unordered_map<unsigned char, std::vector<std::pair<std::string, std::string>>> ACTING_CONSONANT_REMOVERS = {
        {'o', {{"ti", "n"}}}
    };

    inline bool isVowel(unsigned char c) noexcept {
        c = std::tolower(c);
        return VOWELS.count(c);
    }

    inline bool isConsonant(unsigned char c) noexcept {
        return !isVowel(c);
    }

    inline bool isWeakSucceedingConsonantPair(unsigned char first, unsigned char second) noexcept {
        first = std::tolower(first);
        second = std::tolower(second);
        return WEAK_SUCCEEDING_CONSONANTS.count(second) && !WEAK_SUCCEEDING_CONSONANTS.at(second).count(first);
    }

    inline bool isSilentERemover(unsigned char c) noexcept {
        c = std::tolower(c);
        return SILENT_E_REMOVERS.count(c);
    }

    inline bool isDoubleLetter(unsigned char first, unsigned char second) noexcept {
        first = std::tolower(first);
        second = std::tolower(second);
        return first == second;
    }

    inline bool isDoubleConsonant(unsigned char first, unsigned char second) noexcept {
        return isConsonant(first) && isConsonant(second);
    }

    inline bool isActingConsonantPair(const std::string::const_iterator& letter,
        const std::string::const_iterator& begin, const std::string::const_iterator& end) noexcept {
        char first = (letter - 1 >= begin) ? std::tolower(*(letter - 1)) : '\0';
        char second = std::tolower(*letter);
        bool potentialActingConsonant = ACTING_CONSONANT_PAIR.count(second) && ACTING_CONSONANT_PAIR.at(second).count(first);
        // If there is potentially an acting consonant.
        if (potentialActingConsonant && ACTING_CONSONANT_REMOVERS.count(second)) {
            // Check for exceptions. Cache prefix and suffix.
            std::string prefix, suffix;
            std::string::const_iterator startPoint, endPoint;
            for (const auto& exceptionPair : ACTING_CONSONANT_REMOVERS.at(second)) {
                // Is this exception case possible?
                prefix = exceptionPair.first;
                suffix = exceptionPair.second;
                // Cache end points
                startPoint = letter - prefix.size();
                endPoint = letter + suffix.size() + 1;
                // Check for matches
                if (startPoint >= begin && endPoint <= end
                    && (prefix == std::string(startPoint, letter))
                    && (suffix == std::string(letter + 1, endPoint)))
                    // If there's a match, this cannot act as a consonant!
                    return false;
            }
        }
        return potentialActingConsonant;
    }

    inline bool isSilentE(const std::string::const_iterator& letter, const std::string::const_iterator& begin,
         const std::string::const_iterator& end) noexcept {
        // Rules:
            // 1. Must be in-bounds.
        return (letter >= (begin + 2) && letter < end)
            // 2. Must be an 'e'
            && std::tolower(*letter) == 'e'
            // 3. Must have a vowel 2 letters before it. e.g. "ite", "ate", "ote" etc.
            && isVowel(*(letter - 2))
            // 4. That vowel must NOT be an acting consonant pair
            && (letter - 3 >= begin && !isActingConsonantPair(letter - 2, begin, end))
            // 5. Must be followed either by nothing, or something that does not remove silent E's.
            && (letter + 1 >= end || !isSilentERemover(*(letter + 1)))
            // 6. If the vowel preceeding it is an e, it must NOT be silent
            && !isSilentE(letter - 2, begin, end);
    }
} /* StealthNLP */

#endif /* end of include guard: STEALTHNLP_ENGLISH_CONSTANTS_H */
