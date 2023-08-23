/*linkedlist.h*/

#pragma once

#include <iostream>

using namespace std;


class linkedlist
{
private:
    struct NODE
    {
        int Data;
        NODE* Next;
    };
    
    NODE* Head;  // first node in list (or nullptr)
    NODE* Tail;  // last node in list (or nullptr)
    int    Size;        // # of elements (i.e. nodes) in list
    
public:
    //
    // default constructor
    //
    // Creates an empty list.
    //
    linkedlist()
    {
        Head = nullptr;
        Tail = nullptr;
        Size = 0;
    }
    
    //
    // size
    //
    // Returns the # of elements in the list.
    //
    int size()
    {
        return Size;
    }
    
    //
    // push_back
    //
    // Pushes value onto the end of the list.
    //
    void push_back(int value)
    {
        NODE* newNode = new NODE();
        newNode->Data = value;
        newNode->Next = nullptr;
        
        if (Head == nullptr)  // list is empty, so update Head/Tail:
        {
            Head = newNode;
            Tail = newNode;
        }
        else  // list is non-empty:
        {
            Tail->Next = newNode;  // append to tail
            Tail = newNode;
        }
        
        Size++;
    }
    
    //
    // insert
    //
    // Inserts the given value in the list *after* the key.  If
    // the key cannot be found, nothing happens; if the key occurs
    // multiple times, value will be inserted after the first
    // instance.
    //
    void insert(int value, int key)
    {
        // allocate a new node to hold the value:
        NODE* newNode = new NODE();
        newNode->Data = value;
        newNode->Next = nullptr;
        
        //
        // 1. traverse and find the key:
        
        //
        NODE* curNode = Head;
        
        while (curNode != nullptr)
        {
            if (curNode->Data == key)
                break;
            
            curNode = curNode->Next;
        }
        
        // 2. did we find it?  if not, return now:
        if (curNode == nullptr)
        {
            delete newNode;  // give the memory back since we didn't insert:
            return;
        }
        
        // 3. found it, so insert after curnode:
        //
        // NOTE: there's no way to insert at the head of the list,
        // since value has to follow the key.  So that case is
        // eliminated.
        //
        if (curNode == Tail)  // insert at the tail:
        {
            Tail->Next = newNode;
            Tail = newNode;
        }
        else // insert after curNode:
        {
            newNode->Next = curNode->Next;  // what follows me is what follows curNode:
            curNode->Next = newNode;  // now new node follows curNode:
        }
        
        Size++;
    }
    
    //
    // remove
    //
    // Removes the first instance of value from the list; if
    // the value cannot be found, nothing happens.
    //
    void remove(int value)
    {
        //
        // 1. traverse and find the value:
        //
        // NOTE: current node will trail one behind
        // the successor node.  The goal is to delete
        // the successor node, and we'll do that by
        // updating current node to point around it.
        //
        NODE* curNode = nullptr;  // no current to start
        NODE* sucNode = Head;  // successor node is 1st node
        
        while (sucNode != nullptr)  // traverse list:
        {
            if (sucNode->Data == value)  // found node to delete!
                break;
            
            curNode = sucNode;  // otherwise advance to next node:
            sucNode = sucNode->Next;
        }
        
        // 2. did we find it?  if not, nothing to do so return:
        if (sucNode == nullptr)
        {
            return;
        }
        
        //
        // 3. found it, so unlink sucNode from the list:
        //
        if (Head == sucNode)  // removing first node:
        {
            Head = sucNode->Next;  // update Head pointer to 2nd node:
            
            if (Head == nullptr)  // is list now empty?  if so, update Tail as well
                Tail = nullptr;
            
            delete sucNode;  // free the node we just unlinked:
        }
        else  // we are not removing the first node, so unlink:
        {
            curNode->Next = sucNode->Next;
            
            if (Tail == sucNode)  // did we delete tail node?
                Tail = curNode;  // if so, curNode is now the tail
            
            delete sucNode;  // free the node we just unlinked:
        }
        
        Size--;
    }
    
    //
    // output
    //
    // Outputs the size, followed by the elements one by one on
    // the same line.
    //
    void output()
    {
        cout << "Size: " << Size << endl;
        cout << "Elements: ";

        NODE* curNode = Head;
        
        while (curNode != nullptr)
        {
            cout << curNode->Data << " ";
            curNode = curNode->Next;
        }
        
        cout << endl;
    }
    
  int countDuplicates() const {
        //vector for a list of duplicates
        vector<int> duplicates;
        //current node
        NODE* curNode = Head;
        //next node
        NODE* nextNode = Head->Next;
        //counter for duplicates


    return -1;
  }
    
};