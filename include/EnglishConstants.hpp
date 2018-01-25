#ifndef STEALTHNLP_ENGLISH_CONSTANTS_H
#define STEALTHNLP_ENGLISH_CONSTANTS_H
#include <unordered_set>
#include <unordered_map>

namespace StealthNLP {
    const std::unordered_set<unsigned char> VOWELS = {'a', 'e', 'i', 'o', 'u', 'y'};

    // Consonants that cannot be separated from the consonant before them. Includes exceptions to the rule
    const std::unordered_map<unsigned char, std::unordered_set<unsigned char>> WEAK_SUCCEEDING_CONSONANTS = {
        {'l', {'d', 'p'}},
        {'r', {}},
        {'h', {'r'}},
    };

    // Letters that remove silent E's immediately preceeding them
    const std::unordered_set<unsigned char> SILENT_E_REMOVERS = {'d', 'r', 'a', 'e', 'i', 'o', 'u', 'y'};

    // A vowel that acts like a consonant when preceding by any of the following vowels
    const std::unordered_map<unsigned char, std::unordered_set<unsigned char>> ACTING_CONSONANT_PAIR = {
        {'o', {'a', 'e', 'u'}},
        {'a', {'i'}},
    };

    inline bool isVowel(unsigned char c) noexcept {
        c = std::tolower(c);
        return VOWELS.count(c);
    }

    inline bool isConsonant(unsigned char c) noexcept {
        return !isVowel(c);
    }

    inline bool isActingConsonantPair(unsigned char first, unsigned char second) noexcept {
        first = std::tolower(first);
        second = std::tolower(second);
        return ACTING_CONSONANT_PAIR.count(second) && ACTING_CONSONANT_PAIR.at(second).count(first);
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

    inline bool isSilentE(const std::string::const_iterator& letter, const std::string::const_iterator& begin,
         const std::string::const_iterator& end) noexcept {
        // Rules:
            // 1. Must be in-bounds.
        return (letter >= (begin + 2) && letter < end)
            // 2. Must be an 'e'
            && std::tolower(*letter) == 'e'
            // 3. Must have a vowel 2 letters before it. e.g. "ite", "ate", "ote" etc.
            && isVowel(*(letter - 2))
            // 4. Must be followed either by nothing, or something that does not remove silent E's.
            && (letter + 1 >= end || !isSilentERemover(*(letter + 1)))
            // 5. If the vowel preceeding it is an e, it must NOT be silent
            && !isSilentE(letter - 2, begin, end);
    }
} /* StealthNLP */

#endif /* end of include guard: STEALTHNLP_ENGLISH_CONSTANTS_H */
