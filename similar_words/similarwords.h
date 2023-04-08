#pragma once

#include <unordered_map>
#include <unordered_set>
#include <string>

class SimilarWordsDictionary
{
public:
    void Create(const std::string& word1, const std::string& word2);

    size_t Quantity(const std::string& word) const;

    std::string CheckSimilar(const std::string& word1, const std::string& word2) const;

private:
    std::unordered_map <std::string, std::unordered_set<std::string>> synonymDictionary;
};
