//
//  main.cpp
//  iluminoTakeHomeAsses
//
//  Created by Amin Mohtashami on 7/15/24.
//

#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <stdio.h>
#include <string.h>
#include <unordered_map>
#include <set>
using namespace std;

// starting optimized trie
class Trie {
    unordered_map<char, Trie*> mp = unordered_map<char, Trie*>();
public:
    int isWord = false;
    
    Trie* AddNextLetter(char i) {
        Trie* nt = new Trie();
        mp.insert_or_assign(tolower(i), nt);
        return nt;
    }
    
    Trie* GetNextTrie(char i) {
        return mp.count(i) ? mp[tolower(i)] : NULL;
    }
};

void GetInputFileStream(ifstream* inputfile, string filename) {
    // use pointer to open file
    inputfile->open(filename);
    if (!inputfile->is_open()) {
        cerr << "Error opening the file!" << endl;
        cout << "Please input absolute file path for " << filename << endl;
        // if file not found allow user to input absolute path for file
        string newfilename;
        cin >> newfilename;
        GetInputFileStream(inputfile, newfilename);
        return ;
    }
}

void ReadInputPredefindFile(string input_file, Trie* trie, set<string>* predefinedset ) {
    // open predefined file
    ifstream inputFile;
    GetInputFileStream(&inputFile, input_file);
    
    // add predefined words to inmemory map and set default value to 0
    Trie* head_trie = trie;
    string predefinedword;
    while (getline(inputFile, predefinedword)) {
        predefinedset->insert(predefinedword);
        for (char i : predefinedword) {
            head_trie = head_trie->AddNextLetter(i);
        }
        head_trie->isWord = true;
        head_trie = trie;
    }
}

bool MatchesPredefinedWord(string predefinedword, string line, int position_inline) {
    // if current position being checked has less characters than predefined word there can be no match.
    // if character after word match
    // we are at the begginging of the word. i.e, we are not checking subset of a word
    unsigned long space_position_after_match = position_inline + predefinedword.size();
    if (space_position_after_match >= line.size() || isalpha(line[space_position_after_match]) || (position_inline - 1 >= 0 && isalpha(line[position_inline-1]))) {
        return false;
    }
    
    // check full length of predefined word exists in line. case insensitive
    for (int i = 0; i < predefinedword.size(); i++) {
        if (tolower(predefinedword[i]) != tolower(line[position_inline + i])) {
            return false;
        }
    }
    return true;
}

void ReadInputFileAndUpdateCount(string input_file, Trie* trie, unordered_map<string, int>* mp, set<string>* predefined_set) {
    // open file we want to read
    ifstream inputFile;
    GetInputFileStream(&inputFile, input_file);
    
    // get one line at a time from file and check against predefined words
    string line;
    while (getline(inputFile, line)) {
        Trie* head_trie = trie;
        // for each value in predefined word, run find all matches in line
        for (int i = 0; i < line.size(); i++) {
            if (head_trie->GetNextTrie(tolower(line[i])) != NULL) {
                int j = i;
                cout << line[i] << ", " << line[j+1] << endl;
                while (head_trie && !head_trie->isWord ) {
                    cout << line[j] << endl;
                    head_trie = head_trie->GetNextTrie(tolower(line[j]));
                    j++;
                }
                if (head_trie && head_trie->isWord && line.size() > j && !isalpha(line[j])) {
                    string word = line.substr(i, j-1);
                    mp->insert_or_assign(word, mp->at(word)+1);
                }
                head_trie = trie;
            }
        }
        /*
        for (string word_to_match : *predefined_set) {
            
            for (int i = 0; i < line.size(); i++) {
                // case insensitive comparison with our predefined words. Increment count if match found.
                if (tolower(word_to_match[0]) == tolower(line[i]) && MatchesPredefinedWord(word_to_match, line, i)) {
                    mp->insert_or_assign(word_to_match, mp->at(word_to_match) + 1);
                }
            }
        }
         */
    }
    
}

void PrintPredefinedWordCol(string value, int column_size) {
    // console view friendly print, based on largest predefined word column size
    cout << value;
    for (unsigned long i = value.size(); i < column_size; i++) {
        cout << " ";
    }
}

int main(int argc, const char * argv[]) {
    // file names and empty map
    string predefind_filename = "PredefinedWords";
    string filename = "File";
    Trie predefined_word_trie = Trie();
    
    // console friendly print
    int space_for_predefined_word_column = 0;
    
    // read file and update in memory
    set<string> predefinedset = set<string>();
    ReadInputPredefindFile(predefind_filename, &predefined_word_trie, &predefinedset);
    
    unordered_map<string, int>predefined_word_map = unordered_map<string, int>();
    // add predefined words to set. using set as key values to update mapped results.
    for (string i : predefinedset) {
        string a = "";
        for (char j : i) {
            a += tolower(j);
        }
        predefined_word_map.insert_or_assign(a, 0);
        space_for_predefined_word_column = max(space_for_predefined_word_column, (int) i.size());
    }
    
    // read file and update match counts
    ReadInputFileAndUpdateCount(filename, &predefined_word_trie, &predefined_word_map, &predefinedset);
    
    // values for console output
    string predefined_word = "Predefined word";
    string match_count = "Match count ";
    string col_space = "\t\t";
    space_for_predefined_word_column = max(space_for_predefined_word_column, (int) predefined_word.size());
    
    //print header for console output
    PrintPredefinedWordCol(predefined_word, space_for_predefined_word_column);
    cout << col_space << match_count << endl;
    
    for (auto i : predefined_word_map) {
        // print rows for console output with file matches
        PrintPredefinedWordCol(i.first, space_for_predefined_word_column);
        cout << col_space << i.second << endl;
    }
    
    // return successful code to terminate program
    return 0;
}
