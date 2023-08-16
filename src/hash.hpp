#ifndef HASH_HPP
#define HASH_HPP

#include <iostream>
#include <fstream>
#include <sstream>
#include <unordered_map>
#include <algorithm>

using namespace std;

class HashTable {
public:
    HashTable();
    void insertWord(string& word);
    void printOccurrences();
    void printTopWords();
    bool stopwords(string& word);
    void separastopwords();
    vector<string> pacote;

private:
    unordered_map<string, int> table;
    string removeSpecialCharacters(string& word);
};

#endif // HASH_HPP
