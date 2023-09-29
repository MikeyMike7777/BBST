/*
Author: Michael Mathews
Assignment Title: Assignment 6.1
Assignment Description: Find the nth element (SELECT) in a created BBST
Due Date: 10/7/22
Date Created: 10/7/22
Date Last Modified: 10/7/22
*/

#ifndef BBST_hpp
#define BBST_hpp

#include <iostream>
#include <vector>

using namespace std;

class BBST;

class Node {
    public:
        friend class BBST;
    /*
    precondition: Node is not created
    postcondition: Nodes is created and initialized
    return type: none (this is a default constructor)
    description: Node is created wtih given values and
     sets left and right nodes along with proper height
    */
        Node(const int d = 0, Node *l = NULL, Node *r = NULL, int h = 0):
    data(d),left(l), right(r), height(h) {}
    /*
    precondition: Nodes are not deallocated
    postcondition: Nodes are deleted
    return type: none (this is a destructor)
    description: Nodes are recursively deleted
    */
        ~Node();

        const Node *getLeft() const { return left; }
        const Node *getRight() const { return right; }
        const int &getData() const { return data; }

    protected:
        int data;
        Node *left, *right;
        int height;

    /*
    precondition: BBST not rotated for a Left case
    postcondition: BBST properly rotated
    return type: Node pointer to new top node
    description: rotates BBST once left
    */
        Node *singleRotateLeft();
    /*
    precondition: BBST not rotated for a Right case
    postcondition: BBST properly rotated
    return type: Node pointer to new top node
    description: rotates BBST once right
    */
        Node *singleRotateRight();
    /*
    precondition: BBST not rotated for a Left Right case
    postcondition: BBST properly rotated
    return type: Node pointer to new top node
    description: rotates BBST once left then once right
    */
        Node *doubleRotateLeftRight();
    /*
    precondition: BBST not rotated for a Right Left case
    postcondition: BBST properly rotated
    return type: Node pointer to new top node
    description: rotates BBST once right then once left
    */
        Node *doubleRotateRightLeft();

        static int getHeight(Node const *n) { return n ? n->height : -1; }
        void updateHeight() {
            int lh = getHeight(left), rh = getHeight(right);
            height = (lh > rh ? lh : rh) + 1;
        }
};

class BBST {
    public:
        BBST() : root(NULL) {}
        Node* getRoot(){return root;}
        virtual ~BBST() { delete root; }
    /*
    precondition: value not in BBST
    postcondition: value inserted in correct location of BBST
    return type: none
    description: correctly inserts value into a BBST
    */
        void insert(const int &item);
    /*
    precondition: BBST inorder representation is not known
    postcondition: vector is updated with inorder representation of BBST
    return type: none
    description: stores inorder representation of current BBST
    */
        void printInOrder(Node*, vector<int>*);

    protected:
    /*
    precondition: BBST not correctly balanced
    postcondition: BBST rebalanced
    return type: none
    description: rebalances BBST from bottom to top (with use of rotations)
    */
        void rebalancePathToRoot(vector<Node*> const &path);
        Node *root;
};

#endif /* BBST_h */
