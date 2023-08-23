/*bstt.h*/
/*
Name: Abeer Ismail
CS 251 Project 3

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

    void clearHelper(NODE* cur) {
        if (cur != nullptr) {
            if (!cur->isThreaded)
                clearHelper(cur->Right);
            clearHelper(cur->Left);
            delete cur;
        }
    }

    NODE* insert(NODE* node, NODE* parent, KeyT key, ValueT value) {
        if (node == nullptr) {
            node = new NODE;
            node->Key = key;
            node->Value = value;
            node->Left = nullptr;
            node->Right = (parent == nullptr) ? nullptr : parent; //Duplicate handler
            node->isThreaded = true;
            Size++;
        } else if (key < node->Key) {
            node->Left = insert(node->Left, node, key, value);
        } else if (key > node->Key) {
            if (node->isThreaded) {
                NODE* temp = new NODE;
                temp->Key = key;
                temp->Value = value;
                temp->Left = nullptr;
                temp->Right = node->Right;
                temp->isThreaded = true;

                node->Right = temp;
                node->isThreaded = false;

                Size++;
            } else {
                node->Right = insert(node->Right, parent, key, value);
            }
        }

        return node;
    }

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
    clear();
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
    //
    // TODO
    //

    return false;
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
    Root = insert(Root, nullptr, key, value);
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
    //
    // TODO
    //

    return ValueT{ };
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
    //
    // TODO
    //

    return KeyT{ };
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
    //
    // TODO
    //
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
  bool next(KeyT& key) {
    //
    // TODO
    //

    return false;
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

    dumpHelper(output, Root);

    output << "**************************************************" << endl;
  }

};

int main() {
    bstt<int, string> tree;

    tree.insert(50, "Apple");
    tree.insert(30, "Banana");
    tree.insert(70, "Cherry");
    tree.insert(20, "Date");
    tree.insert(40, "Elderberry");
    tree.insert(60, "Fig");
    tree.insert(80, "Grape");

    // Attempt to insert a duplicate key, should be ignored:
    tree.insert(50, "Honeydew");

    cout << "Tree size: " << tree.size() << endl;
    tree.dump(cout);

    return 0;
}
