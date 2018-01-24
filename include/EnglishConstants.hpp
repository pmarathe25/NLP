#ifndef STEALTHNLP_ENGLISH_CONSTANTS_H
#define STEALTHNLP_ENGLISH_CONSTANTS_H
#include <unordered_set>
#include <unordered_map>

namespace StealthNLP {
    const std::unordered_set<unsigned char> VOWELS = {'a', 'e', 'i', 'o', 'u', 'y'};

    // Consonants that cannot be separated from the consonant before them
    const std::unordered_set<unsigned char> WEAK_SUCCEEDING_CONSONANTS = {'l', 'r'};

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

    inline bool isWeakSucceedingConsonant(unsigned char c) noexcept {
        c = std::tolower(c);
        return WEAK_SUCCEEDING_CONSONANTS.count(c);
    }

    inline bool isDoubleLetter(unsigned char first, unsigned char second) noexcept {
        first = std::tolower(first);
        second = std::tolower(second);
        return first == second;
    }

    inline bool isDoubleConsonant(unsigned char first, unsigned char second) noexcept {
        return isConsonant(first) && isConsonant(second);
    }

    inline bool endsOnSilentE(const std::string& word) noexcept {
        return (isVowel(word[word.size() - 3]) && std::tolower(word.back()) == 'e');
    }
} /* StealthNLP */

#endif /* end of include guard: STEALTHNLP_ENGLISH_CONSTANTS_H */
