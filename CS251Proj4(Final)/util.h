//
// STARTER CODE: util.h
/*
Name: Abeer Ismail
Date: 7/28/2023
Purpose: This handles the actual encoding and decoding of files, reliant on the hash map from the other file. Unit testing is done in tests.cpp and the program execution is also found in ./tests
*/
//
#include <iostream>
#include <fstream>
#include <map>
#include <queue>          // std::priority_queue
#include <vector>         // std::vector
#include <functional>     // std::greater
#include <string>
#include <sstream>
#include "bitstream.h"
#include "hashmap.h"
#pragma once


using namespace std;

struct HuffmanNode {
    int character;
    int count;
    HuffmanNode* zero;
    HuffmanNode* one;
};

//
// *This method frees the memory allocated for the Huffman tree.
//
void freeTree(HuffmanNode* node) { //Traverses, deletes, then nulls that node for the tree. It goes top to bottom
    if(node == nullptr){
        return;
    }
    freeTree(node->zero);
    freeTree(node->one);

    delete node;
    node = nullptr;
}

//
// *This function builds the frequency map.
//  If isFile is true, read from the file with name filename.
//  If isFile is false, read directly from string filename.
//
void buildFrequencyMap(string filename, bool isFile, hashmap &map) {

    istream* in; //To either go with file or filename
    ifstream file;
    istringstream str;

    if (isFile){
        file.open(filename, ios::binary); //input and output in binary mode
        if (!file.is_open()){
            throw runtime_error("Could not open file!");
        }
        in = &file; //moves to the file instead of filename and uses a pointer to access it

    }
    else{ //If there is no file, the pointer goes to the filename and sstream object
        str.str(filename);
        in = &str;
    }

    //Now it runs through each character, and adds it to the map, if there is an EOF character that is handled, if there isnt an EOF one is added
    int c;
    while((c = in->get()) != EOF){
        if (map.containsKey(c)){
            int value = map.get(c);
            map.put(c, value + 1);
        }
        else{
            map.put(c, 1);
        }
    }

    if (map.containsKey(PSEUDO_EOF)){
        int value = map.get(PSEUDO_EOF);
        map.put(PSEUDO_EOF, value + 1);
    }
    else{
        map.put(PSEUDO_EOF, 1);
    }

    if (isFile){
        file.close();
    }
}
struct GreaterCount{ //This seems redundant to line 125 but the issue of equal weighted keys and being 1 line off is somewhere
    bool operator()(HuffmanNode* a, HuffmanNode* b){
        if (a->count == b->count){
            return a->character < b->character;
        }
        return a->count > b->count;
    }
};
//
// *This function builds an encoding tree from the frequency map.
//
HuffmanNode* buildEncodingTree(hashmap &map) {

    priority_queue<HuffmanNode*, vector<HuffmanNode*>, GreaterCount> pq; //queue that weights based on which character has the higher frequency

    for (int key : map.keys()){ //This creates each node for the encoding tree, the pq handles the weighting order
        HuffmanNode* node = new HuffmanNode;
        node->character = key;
        node->count = map.get(key);
        node->zero = nullptr;
        node->one = nullptr;
        pq.push(node);
    }

    while (pq.size() > 1)  {
        HuffmanNode* first = pq.top();
        pq.pop();
        HuffmanNode* second = pq.top();
        pq.pop();

        HuffmanNode* combined = new HuffmanNode;
        combined->character = NOT_A_CHAR; //To signify a combined node to move on from
        combined->count = first->count + second->count;
        //Issue occurs when trying to balance same weighted keys, even though the output is right the line numbers they're outputted to would be wrong
        if (first->count == second->count){
            if (first->character > second->character){
                combined->one = first;
                combined->zero = second;
            }
            else{
                combined->one = second;
                combined->zero = first;
            }
        }
        else{
            combined->zero = first;
            combined->one = second;
        }

        pq.push(combined);
    }

    return pq.top();
}
//string code is how we keep track if we went left or right, this could've been done with a stack as well to keep track
void traverseTree(HuffmanNode* node, map<int, string>& encodingMap, string code = ""){
    if (!node) return;
    if (!node->zero && !node->one){
        encodingMap[node->character] = code;
    }
    else{
        traverseTree(node->zero, encodingMap, code + "0"); //left
        traverseTree(node->one, encodingMap, code + "1");
    }
}
//
// *This function builds the encoding map from an encoding tree.
//
map<int,string> buildEncodingMap(HuffmanNode* tree) {
    map<int,string> encodingMap;

    //Recursively going to go through the tree to build the map
    if (tree != nullptr){
        traverseTree(tree, encodingMap);
    }
    return encodingMap;
}

//
// *This function encodes the data in the input stream into the output stream
// using the encodingMap.  This function calculates the number of bits
// written to the output stream and sets result to the size parameter, which is
// passed by reference.  This function also returns a string representation of
// the output file, which is particularly useful for testing.
//
string encode(ifstream& input, map<int,string> &encodingMap,
              ofbitstream& output, int &size, bool makeFile) {

    string result;
    size = 0;

    char ch;
    while (input.get(ch)){//This runs through the file, for each character encodes it with the map, converts to binary 1 and 0, adds it to the end of the final result. If it's a file it uses output, else it appends result
        string code = encodingMap[ch];
        if (makeFile){
            for (char bit: code){
                if (bit == '1'){
                    output.writeBit(1);
                }
                else {
                    output.writeBit(0);
                }
            }
        }
        result += code;
        size += code.size(); //code is a string hence the method call
    }

    //Handling EOF
    string code = encodingMap[PSEUDO_EOF]; //Whatever encoded bits are for 256
    if (makeFile){
        for (char bit: code){
            if (bit == '1'){
                output.writeBit(1);
            }
            else {
                output.writeBit(0);
            }
        }
    }
    result += code;
    size += code.size();


    return result;
}

bool isLeaf(HuffmanNode* node){
    return (node->zero == nullptr && node->one == nullptr);
}


//
// *This function decodes the input stream and writes the result to the output
// stream using the encodingTree.  This function also returns a string
// representation of the output file, which is particularly useful for testing.
//
string decode(ifbitstream &input, HuffmanNode* encodingTree, ofstream &output) {

    HuffmanNode* current = encodingTree;
    string result;

    while(true){
        int bit = input.readBit(); //using ifbitstream

        if (bit == 0){
            current = current->zero;
        }
        else{
            current = current->one;
        }

        if (isLeaf(current)){
            if (current->character == PSEUDO_EOF){
                break;
            }
            else{
                output.put(current->character);
                result.push_back(current->character);
                current = encodingTree;
            }
        }
    }

    return result;
}

//
// *This function completes the entire compression process.  Given a file,
// filename, this function (1) builds a frequency map; (2) builds an encoding
// tree; (3) builds an encoding map; (4) encodes the file (don't forget to
// include the frequency map in the header of the output file).  This function
// should create a compressed file named (filename + ".huf") and should also
// return a string version of the bit pattern.
//
string compress(string filename) {

    hashmap map;

    buildFrequencyMap(filename, true, map);
    HuffmanNode* top = buildEncodingTree(map);
    std::map<int, std::string> encodingMap = buildEncodingMap(top);

    ifstream input (filename, ios::binary);
    string outputName = filename + ".huf";
    ofbitstream output(outputName.c_str()); //This creates a pointer with the .c_str()

    output << map;

    int size = 0;
    string bitPattern = encode(input, encodingMap, output, size, true);
    input.close();
    output.close();
    freeTree(top);

    return bitPattern;

}

//
// *This function completes the entire decompression process.  Given the file,
// filename (which should end with ".huf"), (1) extract the header and build
// the frequency map; (2) build an encoding tree from the frequency map; (3)
// using the encoding tree to decode the file.  This function should create a
// compressed file using the following convention.
// If filename = "example.txt.huf", then the uncompressed file should be named
// "example_unc.txt".  The function should return a string version of the
// uncompressed file.  Note: this function should reverse what the compress
// function does.
//
string decompress(string filename) {
    hashmap map;

    ifbitstream input(filename.c_str());
    input >> map; //pointer from file to hashmap

    HuffmanNode* encodingTree = buildEncodingTree(map);

    size_t periodIndex = filename.rfind('.'); //finds the last period
    string baseName = (periodIndex ==  string::npos) ? filename : filename.substr(0, periodIndex); //If there's a period in the filename it removes it so we can add unc later
    string outputName = baseName + "_unc.txt";

    ofstream output (outputName.c_str(), ios::binary);
    string result = decode(input, encodingTree, output);

    input.close();
    output.close();
    freeTree(encodingTree);

    return result;
}
