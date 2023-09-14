/*bstt.h*/
/*
Name: Abeer Ismail
CS 251 Project 3
7/9/2023
Purpose: Creating a BST where nodes are threaded for faster searching along with complementing functions like size and search.
Notes: Most functions have a helper function listed in private, mainly completed in CLion because of network issues, because isThreaded isn't working the search operators aren't either
*/
//
// Threaded binary search tree
//

#pragma once

#include <iostream>

using namespace std;

template<typename KeyT, typename ValueT>
class bstt {
private:
    struct NODE {
        KeyT   Key;
        ValueT Value;
        NODE*  Left;
        NODE*  Right;
        bool   isThreaded;

    };

    NODE* Root;  // pointer to root node of tree (nullptr if empty)
    int   Size;  // # of nodes in the tree (0 if empty)

    NODE* Current; //Used  for begin and next functions for traversal



    // This is a recursive function to help with the copy constructor
    NODE* bstCopyHelper(NODE* temp){
        if (temp == nullptr){
            return nullptr;
        }
        NODE* newNode = new NODE();
        newNode -> Key = temp -> Key;
        newNode -> Value = temp -> Value;
        newNode -> isThreaded = temp -> isThreaded;
        newNode -> Left = bstCopyHelper(temp ->Left);
        if (!temp->isThreaded){
            newNode -> Right = bstCopyHelper(temp -> Right);
        }
        return newNode;
    }

    // This is a recursive function to help with the destructor similar to the one above
    void clearHelper(NODE* cur) {
        if (cur != nullptr) {
            if (!cur->isThreaded)
                clearHelper(cur->Right);
            clearHelper(cur->Left);
            delete cur;
        }
    }

    // This is a recursive function to help with the search function
    bool searchHelper(NODE* cur, KeyT key, ValueT& value) const {
        if (cur == nullptr)
            return false;
        if (cur->Key == key) {
            value = cur->Value;
            return true;
        }
        if (key < cur->Key)
            return searchHelper(cur->Left, key, value);
        if (!cur->isThreaded)
            return searchHelper(cur->Right, key, value);
        return false;
    }

    // This is a recursive function to help with the insert function, this function does most of the logic to see what becomes
    // threaded or is left alone using the predecessor, 7/15/2023 11:00 PM threading is not functioning
    NODE* insert(NODE* node, NODE* parent, KeyT key, ValueT value){
        if(node == nullptr){
            node = new NODE;
            node->Key = key;
            node->Value = value;
            node->Left = nullptr;
            node->Right = (parent == nullptr) ? nullptr : parent; // Duplicate handler, this is what was missing
            node->isThreaded = true;
            Size++;
        }
        else if (key < node->Key){
            node->Left = insert(node->Left, node, key, value);
        }
        else if (key > node->Key){
            if (node->isThreaded){
                NODE* temp = new NODE; //Temp is created to be sent down to the right node later
                temp->Key = key;
                temp->Value = value;
                temp->Left = nullptr;
                temp->Right = node->Right;
                temp->isThreaded = true;

                node->Right = temp;
                node->isThreaded = false;

                Size++;
            }
            else {
                node->Right = insert(node->Right, parent, key, value);
            }
        }

        return node;

    }





    //Recursive function to print each node with correct left > right order
    void dumpHelper(ostream& output, NODE* cur) const {
        if (cur != nullptr) {
            dumpHelper(output, cur->Left);
            output << "(" << cur->Key << "," << cur->Value;

            if (cur->isThreaded && cur->Right != nullptr)
                output << "," << cur->Right->Key;
            output << ")\n";
            if (!cur->isThreaded)
                dumpHelper(output, cur->Right);
        }
    }

public:
    //
    // default constructor:
    //
    // Creates an empty tree.
    //
    bstt() {
        Root = nullptr;
        Size = 0;
    }

    //
    // copy constructor
    //
    bstt(const bstt& other) {
        Root = bstCopyHelper(other.Root);
        Size = other.Size;
    }

    //
    // destructor:
    //
    // Called automatically by system when tree is about to be destroyed;
    // this is our last chance to free any resources / memory used by
    // this tree.
    //
    virtual ~bstt() {
        clear(); //Uses in combination with the clearHelper function
    }

    //
    // operator=
    //
    // Clears "this" tree and then makes a copy of the "other" tree.
    //
    bstt& operator=(const bstt& other) {
        if (this != &other) {
            clear();
            Root = bstCopyHelper(other.Root);
            Size = other.Size;
        }

        return *this;
    }

    //
    // clear:
    //
    // Clears the contents of the tree, resetting the tree to empty.
    //
    void clear() {
        clearHelper(Root);
        Root = nullptr;
        Size = 0;
    }

    //
    // size:
    //
    // Returns the # of nodes in the tree, 0 if empty.
    //
    // Time complexity:  O(1)
    //
    int size() const {
        return Size;
    }

    //
    // search:
    //
    // Searches the tree for the given key, returning true if found
    // and false if not.  If the key is found, the corresponding value
    // is returned via the reference parameter.
    //
    // Time complexity:  O(lgN) on average
    //
    bool search(KeyT key, ValueT& value) const {
        return searchHelper(Root, key, value); //Recursive function also follows time complexity
    }

    //
    // insert
    //
    // Inserts the given key into the tree; if the key has already been insert then
    // the function returns without changing the tree.
    //
    // Time complexity:  O(lgN) on average
    //
    void insert(KeyT key, ValueT value) {
        Root = insert(Root, nullptr, key ,value);
    }

    //
    // []
    //
    // Returns the value for the given key; if the key is not found,
    // the default value ValueT{} is returned.
    //
    // Time complexity:  O(lgN) on average
    //
    ValueT operator[](KeyT key) const {
        ValueT value;
        if (search(key, value))
            return value;
        return ValueT{};
    }

    //
    // ()
    //
    // Finds the key in the tree, and returns the key to the "right".
    // If the right is threaded, this will be the next inorder key.
    // if the right is not threaded, it will be the key of whatever
    // node is immediately to the right.
    //
    // If no such key exists, or there is no key to the "right", the
    // default key value KeyT{} is returned.
    //
    // Time complexity:  O(lgN) on average
    //
    KeyT operator()(KeyT key) const {
        NODE* cur = Root;
        while (cur != nullptr){

            if (cur->Key == key){
                if (cur->isThreaded && cur->Right != nullptr){
                    return cur->Right->Key;
                }

                else if(!cur->isThreaded && cur->Right != nullptr){
                    return cur->Right->Key;
                }

                else {
                    return KeyT{};
                }
            }

            if (key < cur->Key){
                cur = cur->Left;
            }

            else if (!cur->isThreaded){
                cur = cur->Right;
            }
            else{
                cur = nullptr;
            }
        }

        return KeyT{};
    }


    //
    // begin
    //
    // Resets internal state for an inorder traversal.  After the
    // call to begin(), the internal state denotes the first inorder
    // key; this ensure that first call to next() function returns
    // the first inorder key.
    //
    // Space complexity: O(1)
    // Time complexity:  O(lgN) on average
    //
    // Example usage:
    //    tree.begin();
    //    while (tree.next(key))
    //      cout << key << endl;
    //
    void begin() {
        Current = Root; //Defined in private for begin and next
        while (Current != nullptr && Current->Left != nullptr){
            Current = Current->Left;
        }
    }

    //
    // next
    //
    // Uses the internal state to return the next inorder key, and
    // then advances the internal state in anticipation of future
    // calls.  If a key is in fact returned (via the reference
    // parameter), true is also returned.
    //
    // False is returned when the internal state has reached null,
    // meaning no more keys are available.  This is the end of the
    // inorder traversal.
    //
    // Space complexity: O(1)
    // Time complexity:  O(lgN) on average
    //
    // Example usage:
    //    tree.begin();
    //    while (tree.next(key))
    //      cout << key << endl;
    //
    bool next(KeyT& key) { //Not working because of isThreaded not working correctly
        if (Current == nullptr)
            return false;

        key = Current->Key;

        if (Current ->Right != nullptr && !Current->isThreaded){
            Current = Current->Right;
            while (Current->Left != nullptr){
                Current = Current->Left;
            }
        }
        else if (Current->isThreaded){
            Current = Current->Right;
        }
        return true;
    }

    //
    // dump
    //
    // Dumps the contents of the tree to the output stream, using a
    // recursive inorder traversal.
    //
    void dump(ostream& output) const {
        output << "**************************************************" << endl;
        output << "********************* BSTT ***********************" << endl;

        output << "** size: " << this->size() << endl;

        //
        // inorder traversal, with one output per line: either
        // (key,value) or (key,value,THREAD)
        //
        // (key,value) if the node is not threaded OR thread==nullptr
        // (key,value,THREAD) if the node is threaded and THREAD denotes the next inorder key
        //

        dumpHelper(output, Root); //Recursive to print

        output << "**************************************************" << endl;
    }

};

