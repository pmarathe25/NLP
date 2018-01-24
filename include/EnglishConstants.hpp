#ifndef STEALTHNLP_ENGLISH_CONSTANTS_H
#define STEALTHNLP_ENGLISH_CONSTANTS_H
#include <unordered_set>
#include <unordered_map>

namespace StealthNLP {
    static const std::unordered_set<char> VOWELS = {'a', 'e', 'i', 'o', 'u', 'y'};

    // Consonants that cannot be separated from the consonant before them
    static const std::unordered_set<char> WEAK_SUCCEEDING_CONSONANTS = {'l', 'r'};

    // A vowel that acts like a consonant when preceding by any of the following vowels
    static const std::unordered_map<char, std::unordered_set<char>> VOWEL_PAIRS = {
        {'o', {'e'}},
    };
} /* StealthNLP */

#endif /* end of include guard: STEALTHNLP_ENGLISH_CONSTANTS_H */
