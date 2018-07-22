#include "tokenizer.hpp"

using namespace std;

StringTokenizer::StringTokenizer(string data, string delimiters){
    _pos = 0;
    _data = data;
    _delimiters = delimiters;
    string::size_type lastPos = data.find_first_not_of(delimiters, 0);
    string::size_type pos = data.find_first_of(delimiters, lastPos);

    while(string::npos != pos || string::npos != lastPos){
        _tokens.push_back(data.substr(lastPos, pos - lastPos));
        lastPos = data.find_first_not_of(delimiters, pos);
        pos = data.find_first_of(delimiters, lastPos);
    }
}

StringTokenizer::~StringTokenizer(){
    _tokens.clear();
}

int StringTokenizer::countTokens(){
    return _tokens.size();
}

string StringTokenizer::nextToken(){
    return _tokens[_pos++];
}

bool StringTokenizer::hasMoreTokens(){
    return _pos < _tokens.size();
}
