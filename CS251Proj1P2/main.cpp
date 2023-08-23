/*
 * File: textGenerator.cpp
 * Name: Abeer Ismail
 * Date: 6/23/2023
 * Purpose: Taking sample text and using a N grams map to generate random text at the end, uses myrandom.h as the random number generator for the text
 * Notes: Clion was the IDE used with periodic pasting back into zybooks for live edit history, zybooks timeout led to me changing my code from vector<strings> to implementing a map otherwise it worked fine at the 8:00 PM
 *          submissions
 */

#include <cctype>
#include <iostream>
#include <vector>
#include <fstream>
#include <queue>
#include <algorithm>
#include <sstream>
#include <iterator>
#include <map>
#include "myrandom.h"


using namespace std;

//Opens the input file and creates and returns an object
ifstream openMessage(string &fName){
    //We return a ifstream object, and a filename as reference to be used in build map
    //Get file name, error checking for bad name, open file, return ifstream object and edit the filename variable

    ifstream textFile;
    string fileName;
    bool validFile = false;
    cout << "Input file name?  ";
    while (!validFile) {

        cin >> fileName;
        textFile.open(fileName);
        if (textFile.fail()) {
            cout << "Invalid file, try again: " << endl;
        } else {
            validFile = true;
            fName = fileName;
        }
    }
    return textFile;

}

//Builds a map by importing a text file
void buildMap(ifstream &textFile,  int n, map<vector<string>, vector<string>>& nGramMap, string const &fNameHolder){
    //4 Steps
    //1. Read in the file
    //2. Build the map, key is a vector of strings, value is a vector of strings, check for keys to add in values rather than a new key
    //3. Loops through the map and print out the key and values for higher than word count N values
    //4. Sorting is done because it's a map. This was not the case earlier submissions

    cout << "...Building map: " << fNameHolder << "..." <<  endl << endl;
    n -= 1;
    vector<string> words;
    string word;
    while (textFile >> word) {
        words.push_back(word);
    }

    int totalWords = words.size();

    for (int i = 0; i < totalWords; ++i) {
        vector<string> key(n);
        for (int j = 0; j < n; ++j) {
            key[j] = words[(i + j) % totalWords];
        }

        string nextWord = words[(i + n) % totalWords];

        nGramMap[key].push_back(nextWord);
    }

}

//Simple printing of a map
void printMap(const map<vector<string>, vector<string>>& nGramMap){
    //Basic formatting checks using zybooks as a reference
    //Changed to mapping rather than vectors and size_t to find object size rather than int for safety

    for (auto const& pair: nGramMap) {
        cout << "{";
        for (size_t i = 0; i < pair.first.size(); ++i) {
            cout << pair.first[i];
            if (i != pair.first.size() - 1) // If it's not the last element
                cout << " ";
        }
        cout << "} -> {";
        for (size_t i = 0; i < pair.second.size(); ++i) {
            cout << pair.second[i];
            if (i != pair.second.size() - 1) // If it's not the last element
                cout << " ";
        }
        cout << "}" << endl;
    }
}

//Generates a text of words based on the map and using random number selections from myrandom.h
void generateRandomText(map<vector<string>, vector<string>>& nMap, int n, int wordCount) {
    //First it error checks for building a map
    //Second getting random integers for both the key to start and the values, then using that picks out the values
    //It prints out words until we hit the wordGen count, advance() is used to move the iterator to the next key
    //it prints the words out, increases the counter, then deletes the prefix we found and reruns

    cout << "...";
    if(nMap.empty()){ //error checking just in case
        cout << "Please build the map first" << endl;
        return;
    }

    // Choose a random prefix to start, it stands for iterator and advance() is increasing it
    int prefixIndex = randomInteger(0, nMap.size() - 1);
    auto it = nMap.begin();
    advance(it, prefixIndex);
    vector<string> prefix = it->first;

    for (string word : prefix)
        cout << word << " ";

    int wordsPrinted = n - 1;

    while (wordsPrinted < wordCount) {
        vector<string> suffixes = nMap[prefix];
        int suffixIndex = randomInteger(0, suffixes.size() - 1);
        string nextWord = suffixes[suffixIndex];
        //checks for last word spacing
        if (wordsPrinted == wordCount - 1) {
            cout << nextWord;
        }
        else{
            cout << nextWord << " ";
        }
        wordsPrinted++;

        prefix.erase(prefix.begin());
        prefix.push_back(nextWord);
    }

    cout << "..." << endl;
}

int main() {

    while (true) {
        cout << "Welcome to the Text Generator." << endl << "This program makes random text based on a document."<< endl;
        string fNameHolder;
        ifstream textFile = openMessage(fNameHolder);
        map<vector<string>, vector<string>> nGramMap;
        char userChoice;
        bool mapBuilt = false;

        int inputN;
        int wordsToGen;

        cout << "Value of N?  ";
        cin >> inputN;
        while (inputN <= 1) {
            cout << "N must be > 1, try again:  ";
            cin >> inputN;
        }
        cout << "Total words you'd like to generate?  ";
        cin >> wordsToGen;
        while (wordsToGen < inputN) {
            cout << "Total words must be at least N, try again:  ";
            cin >> wordsToGen;
        }

        char genChoice;
        while (true) {
            cout <<  "Type b-build map, p-print map, g-generate text, s-start over, x-to exit: " << endl;
            cin >> genChoice;
            genChoice = tolower(genChoice);
            if (genChoice == 'b') {
                nGramMap.clear();
                buildMap(textFile, inputN, nGramMap, fNameHolder);
            }
            else if (genChoice == 'p') {
                printMap(nGramMap);
            }
            else if (genChoice == 'g') {
                generateRandomText(nGramMap, inputN, wordsToGen);
            }
            else if (genChoice == 's') {
                //goes to int main()
                cout << endl;
                break;
            }
            else if (genChoice == 'x') {
                return 0; // Exit the program
            }
            else {
                cout << "Invalid choice, try again:  ";
                cin >> genChoice;
                genChoice = tolower(genChoice);
            }
        }

        textFile.close();
    }
}
