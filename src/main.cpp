#include "hash.hpp"

int main() {

    HashTable hashTable;
    string line, word;
    int num_files = 2;

    hashTable.separastopwords();
    
    for (int i = 0; i < num_files; ++i) {
        string file_name = "txt" + to_string(i+1) + ".txt";
        ifstream file("dataset/"+file_name);
        if (!file.is_open()) {
            cerr << "Failed to open the file." << endl;
            return 1;
        }

        while (getline(file, line)) {
            istringstream iss(line);
            while (iss >> word) {
                if(hashTable.stopwords(word) != true){
                    hashTable.insertWord(word);
                }
            }
        }
    }

    //hashTable.printOccurrences();
    hashTable.printTopWords();

    return 0;
}
