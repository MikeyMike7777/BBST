/*
Author: Michael Mathews
Assignment Title: Assignment 6.1
Assignment Description: Find the nth element (SELECT) in a created BBST
Due Date: 10/7/22
Date Created: 10/7/22
Date Last Modified: 10/7/22
*/

#include <iostream>
#include <string>
#include <sstream>
#include "BBST.h"

using namespace std;

/*
Data Abstraction: a BBST is made
Input: numbers for a tree and the requested nth value
Process: creates a BBST and gives an inorder representation
 of this tree
Output: The nth smallest value in the BBST
Assumptions: the numbers are entered correctly on one line. A selection is
 given for the nth number they wish to recaieve
*/
int main() {
    int num, selection, count = 0;
    string line;
    stringstream ss;
    BBST tree;
    vector<int> nums;
    
    getline(cin, line);
    ss << line;
    while(ss >> num){
        tree.insert(num);
        count++;
    }
    
    cin >> selection;
    tree.printInOrder(tree.getRoot(), &nums);
    
    if(selection <= count){
        cout << nums[selection-1] << endl;
    }
    
    return 0;
}
