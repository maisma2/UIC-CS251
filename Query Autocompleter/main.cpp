/* Name: Abeer Ismail
*   Date: 6/30/2023
*   CS 251 Project 2
*   Purpose: Application to run Autocompletelist.h
*   Notes: Creative search finds the keywords found in all terms being searched, it uses maps to keep the final list organized and memory and time efficent
*/

#include <iostream>
#include "AutocompleteList.h"
#include <map>

using namespace std;

int main() {
    // TODO:  Write the code for the autocomplete applications.
    // TODO:  Write the code for your creative search.vb
    string fileName;
    char option;

    cout << "Enter filename: ";
    cin >> fileName;
    cout << "Enter s-search or c-creative search: " ;
    cin >> option;
    cin.ignore();
    cout << "Welcome!" << endl;

    AutocompleteList list(fileName);
    if (option == 's' || option == 'S'){
        string searchTerm;
        cout << "Type your search below, press enter for autocomplete (# to stop)." << endl;
        while (searchTerm != "#"){
            cout << "Search: " << endl;
            getline(cin, searchTerm);
            if (searchTerm == "#") return 0;
            AutocompleteList matches(list.numberOfMatches(searchTerm));
            matches = list.allMatches(searchTerm);
            matches.print();
        }
    }
    else if (option == 'c' || option == 'C'){
        cout << "In-depth search tool, this autocomplete will check entire words for your keyword not just the start or end" << endl;
        string searchTerm;
        cin >> searchTerm;

        cout << "Results: " << endl;
        for (int i = 0; i < list.getSize(); i++){
            if (list[i].query.find(searchTerm) != string::npos) cout << list[i].query << endl;
        }

        return 0;
    }
    else if (option == 'x' || option == 'x'){ //Unfinished // maybe not working hence the similar linear search was implemented
        cout << "Welcome to a multiple-keyword searching tool *UNFINISHED*" << endl;
        cout << "Enter a list of terms you would like to search up, the program will then return you the list of words that were found in each term's lookup, end the list of terms with a '#' to indicate you are done with your keywords." << endl;
        string keyTerms;
        vector<string> likeTerms;
        vector<AutocompleteList> termMatches;
        while (keyTerms != "#"){
            cin >> keyTerms;
            likeTerms.push_back(keyTerms);
        }
        for (auto i:likeTerms){
            AutocompleteList matches(list.numberOfMatches(i));
            matches = list.allMatches(i);
            termMatches.push_back(matches);
        }

        map<string, int> termFreq;
        for (const auto& AutocompleteList : termMatches){
            for (const auto& term: AutocompleteList.toVector()){
                termFreq[term]++;
            }
        }

        vector<string> commonTerms;
        int numLists = termMatches.size();
        for (const auto& [term, freq] : termFreq){
            if (freq == numLists) commonTerms.push_back(term);
        }

        if (!commonTerms.empty()){
            cout << "All similarities between keywords" << endl;
            for (const auto& term : commonTerms){
                cout << term << endl;
            }
        }
        else cout << "No terms found!" << endl;

        return 0;
    }
    else cout << "Invalid Choice" << endl;
    return 0;
}
