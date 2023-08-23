//
// util.h - Solution.
//
// Scott Reckinger
// U. of Illinois, Chicago
//
// This file provides the functionality for huffman encoding - stage 1: build tree.
//

#pragma once
#include <map>
#include <queue>          // std::priority_queue
#include <vector>         // std::vector
#include <functional>     // std::greater
#include <string>

using namespace std;

struct HuffmanNode {
    int character;
    int count;
    HuffmanNode* zero;
    HuffmanNode* one;
};

//
// This function builds the frequency map.
//
//
void buildFrequencyMap(string str, map<char,int> &map) {
    for (auto ch : str) {
        if (map.count(ch)>0) {
            map[ch]++;
        } else {
            map[ch] = 1;
        }
    }
}

//
// This function builds an encoding tree from the frequency map.
//
struct prioritize {
    bool operator()(HuffmanNode*& h1, HuffmanNode*& h2) {
        return h1->count > h2->count;
    }
};

/*
 *     for each of the characters in the map, generate a leaf by declaring and allocating memory for a new HuffmanNode struct, where the member variables character and count are set from the (key, value) pair of the frequency map. Since each node is a standalone leaf at this point, the zero and one path should point to NULL. Add the nodes to the priority queue as they are constructed.
    Repeatedly pop off the top two elements of the priority queue, linking them to a newly constructed HuffmanNode struct in order (i.e. the first node on the left zero path, the second node on the right one path), updating the count to be the sum of the two nodes being linked, and then pushing the new subtree back to the priority queue. Note: any new nodes constructed at this point will not have a character assigned to it; instead, assign the character member variable using the const variable NOT_A_CHAR. This process repeats until the priority queue only has a single node, which points to the encoding tree!

 */
HuffmanNode* buildEncodingTree(map<char,int> &map) {
    priority_queue<HuffmanNode*, vector<HuffmanNode*>, prioritize> pq;

    // TODO: use pq to build encoding tree
    

    //replace this return line; only here for starter code compilation
    return nullptr;
}