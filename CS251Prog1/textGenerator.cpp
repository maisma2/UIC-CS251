/*
 * File: textGenerator.cpp
 * Name: Abeer Ismail
 * Date: 6/23/2023
 * Purpose: Taking sample text and using a map to generate random text
 */

#include <cctype>
#include <iostream>
#include <vector>
#include <fstream>
#include <map>
#include <queue>
#include <sstream>
#include <iterator>
#include "myrandom.h"


using namespace std;

void buildmap(ifstream &textFile, int n, map<vector<string>, vector<string>> &nGramMap){
    string word;
    vector<string> window;
    queue<string> windowQueue;
    while (textFile >> word){
        if (window.size() < n){
            window.push_back(word);
            windowQueue.push(word);
        }
        else {
            nGramMap[window].push_back(word);
            window.erase(window.begin());
            window.push_back(word);
            windowQueue.pop();
            windowQueue.push(word);
        }
    }
}

ifstream openMessage(){
    ifstream textFile;
    string fileName;
    bool validFile = false;
    while (!validFile) {
        cout << "Input file name?  " << endl;
        cin >> fileName;
        textFile.open(fileName);
        if (textFile.fail()) {
            cout << "Invalid file name. Please try again." << endl;
        } else {
            validFile = true;
        }
    }
    return textFile;

}

int main() {

    cout << "Welcome to the Text Generator." << endl << "This program makes random text based on a document."<< endl;
    ifstream textFile = openMessage();
    ofstream outputFile;
    map<vector<string>, vector<string>> nGramMap;
    char userChoice;
    bool mapBuilt = false;

    while (true){
        outputFile.open("output.txt");
        outputFile.clear();
        int inputN;
        int wordsToGen;
        char genChoice;
        cout << "Value of N?  ";
        cin >> inputN;
        while (inputN <= 1){
            cout << "N must be > 1, try again  ";
            cin >> inputN;
        }
        cout << "Total words you'd like to generate?  ";
        cin >> wordsToGen;
        while (wordsToGen <= inputN){
            cout << "Total words must be at least N, try again:  ";
            cin >> wordsToGen;
        }

        cout << "Type b-build map, p-print map, g-generate text, s-start over, x-to exit:" << endl;
        cin >> genChoice;
        genChoice = tolower(genChoice);
        while (genChoice != 'x'){
            if (genChoice == 'b') {
                buildmap(textFile, inputN, nGramMap); //no error handling otherwise bool would be used
                cout << "Map built! " << endl;
            }
            else  (genChoice == 'p'){
                for (auto it = nGramMap.begin(); it != nGramMap.end(); ++it){
                    cout << "Key: ";
                    for (int i = 0; i < it->first.size(); i++){
                        cout << it->first[i] << " ";
                    }
                    cout << endl;
                    cout << "Value: ";
                    for (int i = 0; i < it->second.size(); i++){
                        cout << it->second[i] << " ";
                    }
                    cout << endl;
                }
            }
            else if (genChoice == 'g') {
            }
            else if (genChoice == 's') {
                break;
            }
            else {
                cout << "Invalid choice, try again:  ";
                cin >> genChoice;
                genChoice = tolower(genChoice);
            }

        }

        textFile.close();
        return 0;
    }


}