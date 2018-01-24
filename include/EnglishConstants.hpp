#ifndef STEALTHNLP_ENGLISH_CONSTANTS_H
#define STEALTHNLP_ENGLISH_CONSTANTS_H
#include <unordered_set>
#include <unordered_map>

namespace StealthNLP {
    static const std::unordered_set<char> VOWELS = {'a', 'e', 'i', 'o', 'u', 'y', 'A', 'E', 'I', 'O', 'U', 'Y'};

    // Consonants that cannot be separated from the consonant adjacent to them
    static const std::unordered_set<char> WEAK_CONSONANTS = {'l', 'r', 'L', 'R'};

    // A vowel that acts like a consonant when preceding by any of the following vowels
    static const std::unordered_map<char, std::unordered_set<char>> VOWEL_PAIRS = {
        {'o', {'e'}},
    };
} /* StealthNLP */

#endif /* end of include guard: STEALTHNLP_ENGLISH_CONSTANTS_H */
