#ifndef TOKENIZER_HPP
#define TOKENIZER_HPP

#include <string>
#include <vector>
#include <algorithm>

class StringTokenizer
{
public:
    StringTokenizer(std::string data, std::string delimiters);
    ~StringTokenizer();
    int countTokens();
    std::string nextToken();
    bool hasMoreTokens();

private:
    std::string _data;
    std::string _delimiters;
    unsigned int _pos;
    std::vector<std::string> _tokens;
};

#endif // TOKENIZER_HPP
