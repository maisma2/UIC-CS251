//
// Threaded BST unit tests based
//
/*
#include <iostream>
#include <fstream>
#include <string>
#include <random>
#include <vector>
#include <algorithm>

#include "bstt.h"

#include <gtest/gtest.h>

using namespace std;

struct SYMBOL0
{
    int x;
    double y;
    string z;

    SYMBOL0(int a=-1, double b=-2, string c="-3")
    {
        x = a;
        y = b;
        z = c;
    }
};

ostream& operator<<(ostream& os, const SYMBOL0& s)
{
    os << s.x << "," << s.y << "," << s.z;
    return os;
}

TEST(bstt,basic)
//"(0) basic test of all functionality")
{
bstt<int, int>      tree1;
bstt<string, int>   tree2;
bstt<char, SYMBOL0>  tree3;

EXPECT_TRUE(tree1.size() == 0);
EXPECT_TRUE(tree2.size() == 0);
EXPECT_TRUE(tree3.size() == 0);

tree1.insert(100, -100);
tree1.insert(50, -50);
tree1.insert(25, -25);
tree1.insert(75, -75);
tree1.insert(12, -12);
tree1.insert(33, -33);
tree1.insert(62, -62);
tree1.insert(87, -87);

tree2.insert("mother", 456);
tree2.insert("uncle", 123);
tree2.insert("father", 789);
tree2.insert("apple", 999);

int value;

EXPECT_TRUE(tree2.search("apple", value));
EXPECT_TRUE(value == 999);
EXPECT_TRUE(tree2.search("mother", value));
EXPECT_TRUE(value == 456);
EXPECT_TRUE(tree2.search("uncle", value));
EXPECT_TRUE(value == 123);
EXPECT_TRUE(tree2.search("father", value));
EXPECT_TRUE(value == 789);

EXPECT_TRUE(!(tree2.search("pizza", value)));
EXPECT_TRUE(!(tree2.search("zizza", value)));

EXPECT_TRUE(tree2["apple"] == 999);
EXPECT_TRUE(tree2["mother"] == 456);
EXPECT_TRUE(tree2["uncle"] == 123);
EXPECT_TRUE(tree2["father"] == 789);

EXPECT_TRUE(tree2["pizza"] == 0);
EXPECT_TRUE(tree2["zizza"] == 0);

EXPECT_TRUE(tree2("pizza") == "");
EXPECT_TRUE(tree2("zizza") == "");

EXPECT_TRUE(tree2("apple") == "father");
EXPECT_TRUE(tree2("mother") == "uncle");
EXPECT_TRUE(tree2("father") == "mother");
EXPECT_TRUE(tree2("uncle") == "");

SYMBOL0  sym1(1, 2, "3");
SYMBOL0  sym2;
SYMBOL0  sym3(4, 5, "6");

tree3.insert('a', sym1);
tree3.insert('b', sym2);
tree3.insert('c', sym3);

SYMBOL0  sym;
EXPECT_TRUE(tree3.search('a', sym));
EXPECT_TRUE(sym.x == 1);
EXPECT_TRUE(sym.z == "3");
EXPECT_TRUE(!(tree3.search('z', sym)));

EXPECT_TRUE(tree3('a') == 'b');
EXPECT_TRUE(tree3('b') == 'c');

EXPECT_TRUE(tree1.size() == 8);
EXPECT_TRUE(tree2.size() == 4);
EXPECT_TRUE(tree3.size() == 3);

//
// let's insert some random numbers into tree1 to make it bigger:
//
int N = 1000;
vector<int> keys = { 100, 50, 25, 75, 12, 33, 62, 87 };

for (int key : keys)
{
tree1.insert(key, key);  // these should *not* overwrite:
}

for (int key : keys)
{
int value;

EXPECT_TRUE(tree1.search(key, value));
EXPECT_TRUE(value == -key);
}

std::random_device random_device;
std::uniform_int_distribution<int> distributionAgent1(1000, 100000);

while (tree1.size() != N)
{
int key = distributionAgent1(random_device);

//
// just in case we generate a duplicate, don't insert again:
//
if (std::find(keys.begin(), keys.end(), key) == keys.end())
{
//
// not in vector, so new key:
//
tree1.insert(key, -key);
keys.push_back(key);
}
}

EXPECT_TRUE(tree1.size() == N);
EXPECT_TRUE(keys.size() == N);

//
// each key should be in the tree:
//
for (int key : keys)
{
int value;

EXPECT_TRUE(tree1.search(key, value));
EXPECT_TRUE(value == -key);
}

EXPECT_TRUE(!(tree1.search(0, value)));
EXPECT_TRUE(!(tree1.search(999, value)));
EXPECT_TRUE(!(tree1.search(999999, value)));

//
// [] and ():
//
for (int key : keys)
{
EXPECT_TRUE(tree1[key] == -key);
}

EXPECT_TRUE(tree1[0] == 0);
EXPECT_TRUE(tree1[1] == 0);
EXPECT_TRUE(tree1[-1] == 0);
EXPECT_TRUE(tree1[999] == 0);
EXPECT_TRUE(tree1[999999] == 0);

EXPECT_TRUE(tree1(0) == 0);
EXPECT_TRUE(tree1(1) == 0);
EXPECT_TRUE(tree1(-1) == 0);
EXPECT_TRUE(tree1(999) == 0);
EXPECT_TRUE(tree1(999999) == 0);

EXPECT_TRUE(tree1(75) == 87);
EXPECT_TRUE(tree1(12) == 25);
EXPECT_TRUE(tree1(33) == 50);
EXPECT_TRUE(tree1(25) == 33);
EXPECT_TRUE(tree1(87) == 100);
EXPECT_TRUE(tree1(50) == 75);
EXPECT_TRUE(tree1(62) == 75);
EXPECT_TRUE(tree1(100) != 0);

//
// test copy constructor:
//
bstt<int, int>  tree1_cc = tree1;

tree1.insert(1, -1);

EXPECT_TRUE(tree1.size() == (N + 1));
EXPECT_TRUE(tree1_cc.size() == N);
EXPECT_TRUE(tree2.size() == 4);
EXPECT_TRUE(tree3.size() == 3);

tree1_cc.insert(2, -2);

for (int key : keys)
{
int value;

EXPECT_TRUE(tree1.search(key, value));
EXPECT_TRUE(value == -key);
}

for (int key : keys)
{
int value;

EXPECT_TRUE(tree1_cc.search(key, value));
EXPECT_TRUE(value == -key);
}

EXPECT_TRUE(tree1.search(1, value));
EXPECT_TRUE(value == -1);
EXPECT_TRUE(!(tree1.search(2, value)));

EXPECT_TRUE(tree1_cc.search(2, value));
EXPECT_TRUE(value == -2);
EXPECT_TRUE(!(tree1_cc.search(1, value)));

bstt<string, int>  tree2_cc = tree2;

EXPECT_TRUE(tree2_cc.search("apple", value));
EXPECT_TRUE(value == 999);
EXPECT_TRUE(tree2_cc.search("mother", value));
EXPECT_TRUE(value == 456);
EXPECT_TRUE(tree2_cc.search("uncle", value));
EXPECT_TRUE(value == 123);
EXPECT_TRUE(tree2_cc.search("father", value));
EXPECT_TRUE(value == 789);

EXPECT_TRUE(!(tree2_cc.search("pizza", value)));
EXPECT_TRUE(!(tree2_cc.search("zizza", value)));

EXPECT_TRUE(tree2_cc["apple"] == 999);
EXPECT_TRUE(tree2_cc["mother"] == 456);
EXPECT_TRUE(tree2_cc["uncle"] == 123);
EXPECT_TRUE(tree2_cc["father"] == 789);

EXPECT_TRUE(tree2_cc["pizza"] == 0);
EXPECT_TRUE(tree2_cc["zizza"] == 0);

EXPECT_TRUE(tree2_cc("pizza") == "");
EXPECT_TRUE(tree2_cc("zizza") == "");

EXPECT_TRUE(tree2_cc("apple") == "father");
EXPECT_TRUE(tree2_cc("mother") == "uncle");
EXPECT_TRUE(tree2_cc("father") == "mother");
EXPECT_TRUE(tree2_cc("uncle") == "");

//
// now operator=
//
bstt<string, int>  tree2_c;

tree2_c.insert("pizza", 123);
tree2_c.insert("zizza", 456);

tree2_c = tree2;  // copy:

EXPECT_TRUE(tree2_c.search("apple", value));
EXPECT_TRUE(value == 999);
EXPECT_TRUE(tree2_c.search("mother", value));
EXPECT_TRUE(value == 456);
EXPECT_TRUE(tree2_c.search("uncle", value));
EXPECT_TRUE(value == 123);
EXPECT_TRUE(tree2_c.search("father", value));
EXPECT_TRUE(value == 789);

EXPECT_TRUE(!(tree2_c.search("pizza", value)));
EXPECT_TRUE(!(tree2_c.search("zizza", value)));

EXPECT_TRUE(tree2_c["apple"] == 999);
EXPECT_TRUE(tree2_c["mother"] == 456);
EXPECT_TRUE(tree2_c["uncle"] == 123);
EXPECT_TRUE(tree2_c["father"] == 789);

EXPECT_TRUE(tree2_c["pizza"] == 0);
EXPECT_TRUE(tree2_c["zizza"] == 0);

EXPECT_TRUE(tree2_c("pizza") == "");
EXPECT_TRUE(tree2_c("zizza") == "");

EXPECT_TRUE(tree2_c("apple") == "father");
EXPECT_TRUE(tree2_c("mother") == "uncle");
EXPECT_TRUE(tree2_c("father") == "mother");
EXPECT_TRUE(tree2_c("uncle") == "");

bstt<int, int>  tree1_c;
tree1_c.insert(5, -5);
tree1_c.insert(3, -3);
tree1_c.insert(7, -7);
tree1_c.insert(1, -1);
tree1_c.insert(2, -2);
tree1_c.insert(6, -6);

EXPECT_TRUE(tree1_c.size() == 6);

EXPECT_TRUE(tree1_c.search(5, value));
EXPECT_TRUE(value == -5);
EXPECT_TRUE(tree1_c.search(6, value));
EXPECT_TRUE(value == -6);
EXPECT_TRUE(tree1_c.search(1, value));
EXPECT_TRUE(value == -1);

tree1_c = tree1;  // clear and copy:

EXPECT_TRUE(tree1.size() == (N + 1));
EXPECT_TRUE(tree1_c.size() == (N+1));

tree1_c.insert(2, -2);

tree1.insert(-999, 999);

for (int key : keys)
{
int value;

EXPECT_TRUE(tree1.search(key, value));
EXPECT_TRUE(value == -key);
}

for (int key : keys)
{
int value;

EXPECT_TRUE(tree1_c.search(key, value));
EXPECT_TRUE(value == -key);
}

EXPECT_TRUE(tree1.search(-999, value));
EXPECT_TRUE(value == 999);
EXPECT_TRUE(!(tree1.search(2, value)));

EXPECT_TRUE(tree1_c.search(2, value));
EXPECT_TRUE(value == -2);
EXPECT_TRUE(!(tree1_c.search(-999, value)));

//
// clear();
//
tree1_cc.clear();

EXPECT_TRUE(tree1_cc.size() == 0);

vector<int> keys2 = { 101, 51, 149, 24, 23, 22, 21, 20, 140, 141, 142, 143, 144, 146, 145 };

for (int key : keys2)
{
tree1_cc.insert(key, key + 1);
}

EXPECT_TRUE(tree1_cc.size() == keys2.size());

tree1_c.clear();

EXPECT_TRUE(tree1_c.size() == 0);

tree1_c.insert(12345, 1);

EXPECT_TRUE(tree1_c.size() == 1);

for (int key : keys2)
{
int value;

EXPECT_TRUE(tree1_cc.search(key, value));
EXPECT_TRUE(value == key + 1);
}

EXPECT_TRUE(tree1_c.search(12345, value));
EXPECT_TRUE(value == 1);

for (int key : keys)
{
int value;

EXPECT_TRUE(!(tree1_c.search(key, value)));
EXPECT_TRUE(!(tree1_cc.search(key, value)));
}

//
// begin()
// next()
//
keys.push_back(-999);
keys.push_back(1);

std::sort(keys.begin(), keys.end());

int key;
int i = 0;
int iterations = 0;

tree1.begin();
while (tree1.next(key))
{
EXPECT_TRUE(key == keys[i]);
++i;
++iterations;

key = -1;  // clear key in case next() is looking at it:
}

EXPECT_TRUE(iterations == keys.size());

vector<string> keys3 = { "apple", "father", "mother", "uncle" };

i = 0;
iterations = 0;

string key3;

tree2.begin();
while (tree2.next(key3))
{
EXPECT_TRUE(key3 == keys3[i]);
++i;
++iterations;

key3 = "";  // clear key in case next() is looking at it:
}

EXPECT_TRUE(iterations == keys3.size());

//
// done
//
}
*/