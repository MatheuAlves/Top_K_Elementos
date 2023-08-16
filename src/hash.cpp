#include "hash.hpp"
#define k 20

HashTable::HashTable() {}

struct greaters{
    bool operator()(const pair<string, int>& a,const pair<string, int>& b) const{
        return a.second>b.second;
    }
};

string HashTable::removeSpecialCharacters(string& word) {
    string cleanedWord = word;
    cleanedWord.erase(remove_if(cleanedWord.begin(), cleanedWord.end(), ::ispunct), cleanedWord.end());
    transform(cleanedWord.begin(), cleanedWord.end(), cleanedWord.begin(), ::tolower);
    return cleanedWord;
}


void HashTable::insertWord(string& word) {
    string cleanedWord = removeSpecialCharacters(word);

    if (!cleanedWord.empty()) {
        if (table.find(cleanedWord) == table.end()) {
            table[cleanedWord] = 1;
        } else {
            table[cleanedWord]++;
        }
    }
}

void HashTable::printOccurrences(){
    for (const auto& entry : table) {
        cout << entry.first << ": " << entry.second << " ocorrências" << endl;
    }
}

void HashTable::printTopWords(){
    vector<pair<string, int>> sortedWords;
    
    int contador=0;
    for(auto entry = table.begin(); entry != table.end();) {
        sortedWords.emplace_back(entry->first, entry->second);
        auto aux=entry;
        entry++;
        table.erase(aux);
        if (contador==k-1) break;
        else contador++;
    }
    
    make_heap(sortedWords.begin(),sortedWords.end(), greaters());

    for (auto &entry : table)
    {
        if (entry.second>=sortedWords.front().second)
        {
            pop_heap(sortedWords.begin(),sortedWords.end(), greaters());
            sortedWords.pop_back();
            sortedWords.push_back(entry);
            push_heap(sortedWords.begin(),sortedWords.end(), greaters());
        }
    }

    cout << "\n\nTop " << k << " Palavras não ordenadas:\n" << endl;
    for (size_t i = 0; i < sortedWords.size(); ++i) {
        cout << i+1 << "\t"<< sortedWords[i].first << ":\t" << sortedWords[i].second << " ocorrências" << endl;
    }

    sort(sortedWords.begin(), sortedWords.end(), [](const auto& a, const auto& b) {
        return a.second > b.second;
    });

    cout << "\n\nTop " << k << " Palavras ordenadas:\n" << endl;
    for (size_t i = 0; i < sortedWords.size(); ++i) {
        cout << i+1 << "\t"<< sortedWords[i].first << ":\t" << sortedWords[i].second << " ocorrências" << endl;
    }
}

void HashTable::separastopwords() {
    ifstream arq("dataset/stopwords.txt");
    string stopword;

    if (arq.is_open()) {
        while (getline(arq, stopword)) {
            stopword.erase(remove(stopword.begin(), stopword.end(), '\r'), stopword.end());
            pacote.push_back(stopword);
        }
        arq.close();
    } else {
        cout << "Não foi possível abrir o arquivo." << endl;
    }
}

bool HashTable::stopwords(string& word)
{
    transform(word.begin(), word.end(), word.begin(), ::tolower);
    for (int i = 0; i < int(pacote.size()); ++i)
    {
        if (pacote[i] == word || "—" == word)
        {
            return true;
        }
    }
    return false;
}
