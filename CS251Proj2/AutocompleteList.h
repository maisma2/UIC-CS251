// AutocompleteList.h
/*
 * Name : Abeer Ismail
 * Date: 6/30/2023
 * CS 251 Project 2
 * Purpose: Adding in terms from a file, and using search methods to find terms that match a prefix given a time complexity requirement
 * Notes: Used CLion IDE for additional debugging where Zybooks was not enough
 */
#pragma once

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <algorithm>

using namespace std;

struct Term {
    string query;
    long long int weight;
    // need this for autograding
    bool operator==(const Term& term) const {
        return (query == term.query && weight == term.weight);
    }
};

//
// AutocompleteList
//
class AutocompleteList {
private:
    //
    // Private member variables for the abstraction.
    // This implementation uses a low-level C array, terms, to store a list of
    // Terms.  As a result, you must also keep track of the number of elements
    // stored (size).
    //
    Term* terms;  // pointer to a C-style array
    int size;  // number of elements in the array
    string sortType;  // records how list is sorted

    //
    // Private member function.
    // Returns the index of the first word in terms[] that contains the prefix,
    // or -1 if there are no words containing the prefix. This search should be
    // implemented using a variation of the binary search algorithm.
    // Performance requirement: O(logn), n is size.
    //
    int binarySearch(string prefix, int dir) const{ //dir is either first or last index of, 1 for first, -1 for last
        int l = 0;
        int r = size - 1;
        int result = -1; //index

        while (l <= r){
            int mid = l + (r - l) / 2;
            if (terms[mid].query.compare(0, prefix.size(), prefix) == 0){
                result = mid;
                if (dir == 1){
                    r = mid - 1;
                }
                else if (dir == -1){
                    l = mid + 1;
                }
            }
            else if (terms[mid].query < prefix){
                l = mid + 1;
            }
            else {
                r = mid - 1;
            }
        }
        return result;

    }

    int firstIndexOf(string prefix) {
        return binarySearch(prefix, 1);
    }



    //
    // Private member function.
    // Returns the index of the last word in terms[] that contains the prefix,
    // or -1 if there are no words containing the prefix. This search should be
    // implemented using a variation of the binary search algorithm.
    // Performance requirement: O(logn), n is size.
    //
    int lastIndexOf(string prefix) {
        return binarySearch(prefix, -1);
    }

    //
    // Private member function.
    // This function sorts the terms array by lexicographic order of the query
    // string.
    // Set sortType to "lex".
    // Performance requirement: O(nlogn), n is size.
    //
    void sortByLexOrder() {
        sortType = "lex";
        //Uses C++ library which is n log n
        sort (terms, terms+size, [](Term a, Term b){
            return a.query < b.query;
        });
    }
    //
    // Private member function.
    // This function sorts the terms array by decreasing weight order.
    // Set the sortType to "weight".
    // Performance requirement: O(nlogn), n is size.
    //
    void sortByWeightOrder() {
        // TODO: Write this function.
        sortType = "weight";
        sort(terms, terms+size, [](Term a, Term b){
            return a.weight > b.weight;
        });




    }

public:
    //
    // default constructor:
    //
    // Called automatically by C++ to create a AutocompleteList.
    // When this is called, intialize terms to a nullptr and set size to 0.
    // Set sortType to "none".
    // Performance requirement: O(1)
    //
    AutocompleteList() {
        // TODO: Write this constructor (required).
        terms = nullptr;
        size = 0;
        sortType = "none";

    }

    //
    // a second constructor:
    //
    // Parameter passed in determines size of terms.
    // When this is called, allocate memory for n Terms and
    // set size accordingly.
    // Set sortType to "none".
    // Performance requirement: O(1)
    //
    AutocompleteList(int n) {
        // TODO: Write this constructor (required).
        terms = new Term[n];
        size = n;
        sortType = "none";

    }

    string trim(const string& query){
        auto first = query.find_first_not_of(' ');
        if (first == string::npos){
            return "";
        }
        auto last = query.find_last_not_of(' ');
        return query.substr(first, last - first + 1);
    }

    //
    // a third constructor:
    //
    // Parameter passed in is name of file to read in.
    // This constructor will build Autocomplete list from file.
    // Assume file format is:
    // line 1: "<size>"
    // lines 2 thru size+1: "weight query"
    // The list should be sorted lexicographic order by the query string.
    // Set sortType to "lex".
    // Performance requirement: O(nlogn), n is size.
    //
    AutocompleteList(string filename) {
        try{
            // TODO: Write this constructor (required).
            ifstream file(filename);
            file >> size;
            terms = new Term[size];
            string line;
            int counter = 0;
            while (getline(file, line)){

                if (line == "#") break;
                if (line.empty()) continue;

                stringstream ss(line);
                string weight;
                string query;
                ss >> weight;
                //No need for stoi() since ss handles that
                getline(ss >> ws, query); // found a reference to remove whitespaces with ws()
                Term term;
                term.weight = 0; // initialize with 0
                stringstream weightStream(weight); // create a new stringstream with the weight string
                weightStream >> term.weight; // read the integer value from the stringstream
                term.query = query;
                terms[counter] = term;
                counter++;
            }
            sortType = "lex";
            sortByLexOrder();
        }
        catch (exception &e){
            cout << "Error: " << e.what() << endl;
        }
    }

    //
    // copy constructor:
    //
    // Called automatically by C++ to create an AutocompleteList that contains
    // a copy of an existing AutocompleteList.  Example: this occurs when
    // passing AutocompleteList as a parameter by value.
    // Performance requirement: O(n), n is size.
    //
    AutocompleteList(const AutocompleteList& other) {
        // TODO: Write this constructor (required).
        size = other.size;
        sortType = other.sortType;
        terms = new Term[size];
        for (int i = 0; i < size; i++){
            terms[i] = other.terms[i];
        }

    }

    //
    // copy operator=
    //
    // Called when you assign one AutocompleteList into another,
    // i.e. this = other;
    // Performance requirement: O(n), n is size.
    //
    AutocompleteList& operator=(const AutocompleteList& other) {

        //first we check if the object is the same
        if (this == &other){
            return *this;
        }
        //Get old memory back
        delete[] terms;
        //Reset object values
        size = other.size;
        sortType = other.sortType;
        //individually fill in array
        terms = new Term[size];
        for (int i = 0; i < size; i++){
            terms[i] = other.terms[i];
        }

        return  *this;

    }

    //
    // destructor:
    //
    // Called automatically by C++ to free the memory associated by the Term.
    //
    virtual ~AutocompleteList() {
        // TODO: Write this destructor (required).
        delete[] terms;

    }

    //
    // Public member function.
    // Returns the size of the AutocompleteList.
    // Performance requirement: O(1).
    //
    int getSize() {
        return size;
    }

    //
    // Public member function.
    // Returns Term element in AutocompleteList.
    // This gives public access to Terms stored in the AutocompleteList.
    // If i is out of bounds, throw an out_of_range error message:
    // "AutocompleteList: i out of bounds"
    // Note:  This public function does not necessarily fit the design of this
    // abstraction but we are having you write it for testing purposes.
    // Performance requirement: O(1).
    //
    Term& operator[](int i) {
        if (i < 0 || i >= size){
            throw out_of_range("AutocompleteList: i out of bounds");
        }
        else return terms[i];  // TODO: update
    }
    // Public member function.
    // Returns an AutocompleteList which stores a list of all Terms that
    // start with the prefix.  The AutocompleteList returned should be sorted
    // in descending order by weight.  Set the returned AutocompleteList's
    // sortType to "weight".
    // If prefix is empty string, return an empty AutocompleteList;
    // If there are no words in the list the start with the prefix, return an
    // empty AutocompleteList.
    // If *this* AutocompleteList's sortType does not equal "lex", then return
    // an empty AutocompleteList.  In other words, allMatches should only be
    // called on an AutocompleteList that is sorted in lexicographic order by
    // the query string.
    // Performance requirement: O(mlogm+logn), n is size and
    // where m is the number of matching terms.
    //
    AutocompleteList allMatches(string prefix) {
        if (sortType != "lex" || prefix.empty()){
            return AutocompleteList();
        }
        else {
            int firstIndex = firstIndexOf(prefix);
            int lastIndex = lastIndexOf(prefix);

            if (firstIndex == -1 || lastIndex == -1){
                return AutocompleteList();
            }

            AutocompleteList temp(lastIndex - firstIndex + 1);
            for (int i = firstIndex; i <= lastIndex; i++){
                temp.terms[i - firstIndex] = terms[i];
            }

            temp.sortByWeightOrder();
            temp.size = lastIndex - firstIndex + 1;
            temp.sortType = "weight";
            return temp;
        }

    }
    // Public member function.
    // Returns the number of Terms that start with the given prefix.
    // If prefix is empty, return 0.
    // If *this* AutocompleteList's sortType does not equal "lex",
    // then return 0.
    // Performance requirement: O(logn), n is size.
    //
    int numberOfMatches(string prefix) {
        if (sortType != "lex" || prefix.empty()){
            return 0;
        }
        else {
            int firstIndex = firstIndexOf(prefix);
            int lastIndex = lastIndexOf(prefix);
            if (firstIndex == -1 || lastIndex == -1){
                return 0;
            }
            return lastIndex - firstIndex + 1;
        }
    }
    //
    // Public member function.
    // Prints the AutocompleteList.
    // Pad the front of the print with 8 spaces for nicely formatted search:
    // print: "        query, weight".
    // NOTE:  This is also useful for debugging purposes.
    // Performance requirement: O(n), n is size
    //
    void print() {

        for (int i = 0; i < size; i++){
            Term& temp = terms[i];
            cout <<"        " <<temp.query <<", " << temp.weight << endl;
        }

    }
    string getSortType(){
        return sortType;
    }
    //Used in creative search to transfer queries of a list to a vector
    vector<string> toVector() const{
        vector<string> list;
        for (int i = 0; i < size; i++){
            list.push_back(terms[i].query);
        }
        return list;
    }
};
