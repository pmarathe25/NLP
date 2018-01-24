#ifndef STEALTHNLP_PARSER_H
#define STEALTHNLP_PARSER_H
#include <vector>
#include <string>

namespace StealthNLP {
    int parseSyllables(const std::string& word, std::vector<std::string>& syllables) noexcept;

    std::vector<std::string> parseSyllables(const std::string& word) noexcept;
} /* StealthNLP */

#endif /* end of include guard: STEALTHNLP_PARSER_H */
