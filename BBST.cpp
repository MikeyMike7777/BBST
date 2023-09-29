/*
Author: Michael Mathews
Assignment Title: Assignment 6.1
Assignment Description: Find the nth element (SELECT) in a created BBST
Due Date: 10/7/22
Date Created: 10/7/22
Date Last Modified: 10/7/22
*/

#include "BBST.h"

Node::~Node(){
    if(this->left){
        delete this->left;
    }
    if(this->right){
        delete this->right;
    }
}

Node* Node::singleRotateLeft(){
    Node *rightChild = this->right;
    this->right = rightChild->left;
    rightChild->left = this;
    return rightChild;
}

Node* Node::singleRotateRight(){
    Node *leftChild = this->left;
    this->left = leftChild->right;
    leftChild->right = this;
    return leftChild;
}


Node* Node::doubleRotateLeftRight(){
    this->left = this->left->singleRotateLeft();
    return this->singleRotateRight();
}


Node* Node::doubleRotateRightLeft(){
    this->right = this->right->singleRotateRight();
    return this->singleRotateLeft();
}


void BBST::insert(const int &item){
    Node *ptr = this->root, *parent = this->root;
    vector<Node*> vect;
    bool found = false, first = true;

    //search for item
    while(ptr and !found){
        if(item < ptr->data){
            vect.push_back(ptr);
            parent = ptr;
            ptr = ptr->left;
        }
        else if(ptr->data < item){
            vect.push_back(ptr);
            parent = ptr;
            ptr = ptr->right;
        }
        else{
            found = true;
        }
        first = false;
    }
    
    //if first element, create first node
    if(first){
        Node *newNode = new Node(item);
        this->root = newNode;
        vect.push_back(this->root);
    }
    //if not in avl, insert
    else if(!found){
        Node *newNode = new Node(item);
        if(item < parent->data){
            parent->left = newNode;
        }
        else{
            parent->right = newNode;
        }
        //add last ptr to vector
        vect.push_back(newNode);
    }
    //update heights
    for(int i = vect.size()-1; i >= 0; i--){
        vect[i]->Node::updateHeight();
    }
    //rebalance tree
    this->rebalancePathToRoot(vect);
}

void BBST::printInOrder(Node* n, vector<int>* v){
    if (n != NULL){
        printInOrder(n->left, v);
        (*v).push_back(n->getData());
        printInOrder(n->right, v);
    }
}

void BBST::rebalancePathToRoot(vector<Node*> const &path){
    //set equal to bottom node
    int i = path.size()-1, diff;
    Node *node, *newTop;
    //rebalance up to first node
    while(i >= 0){
        //update current node
        node = path[i];
        //find if imbalance
        diff = Node::getHeight(node->left) -
               Node::getHeight(node->right);
        if(diff < -1){
            //find taller tree on right side
            diff = Node::getHeight(node->right->left) -
                   Node::getHeight(node->right->right);
            //rotate
            if(diff <= 0){
                //set parent to the correct child
                if(i < 1){
                    newTop = node->singleRotateLeft();
                    this->root = newTop;
                }
                else if(path[i-1]->right == node){
                    newTop = node->singleRotateLeft();
                    path[i-1]->right = newTop;
                }
                else{
                    newTop = node->singleRotateLeft();
                    path[i-1]->left = newTop;
                }
                //update height of old and new top node
                node->updateHeight();
                newTop->updateHeight();
            }
            else{
                //set parent to the correct child
                if(i < 1){
                    newTop = node->doubleRotateRightLeft();
                    this->root = newTop;
                }
                else if(path[i-1]->right == node){
                    newTop = node->doubleRotateRightLeft();
                    path[i-1]->right = newTop;
                }
                else{
                    newTop = node->doubleRotateRightLeft();
                    path[i-1]->left = newTop;
                }
                //update heights of new top, left, and right
                newTop->left->updateHeight();
                newTop->right->updateHeight();
                newTop->updateHeight();
            }
            //update rest of heights
            for(int j = i; j >= 0; j--){
                path[j]->updateHeight();
            }
        }
        else if(diff > 1){
            //find taller tree on left side
            diff = Node::getHeight(node->left->left) -
                   Node::getHeight(node->left->right);
            //rotate
            if(diff >= 0){
                //set parent to the correct child
                if(i < 1){
                    newTop = node->singleRotateRight();
                    this->root = newTop;
                }
                else if(path[i-1]->right == node){
                    newTop = node->singleRotateRight();
                    path[i-1]->right = newTop;
                }
                else{
                    newTop = node->singleRotateRight();
                    path[i-1]->left = newTop;
                }
                //update height of old and new top node
                node->updateHeight();
                newTop->updateHeight();
            }
            else{
                if(i < 1){
                    newTop = node->doubleRotateLeftRight();
                    this->root = newTop;
                }
                else if(path[i-1]->right == node){
                    newTop = node->doubleRotateLeftRight();
                    path[i-1]->right = newTop;
                }
                else{
                    newTop = node->doubleRotateLeftRight();
                    path[i-1]->left = newTop;
                }
                //update heights of new top, left, and right
                newTop->left->updateHeight();
                newTop->right->updateHeight();
                newTop->updateHeight();
            }
            //update new heights
            for(int j = path.size()-1; j >= 0; j--){
                path[j]->updateHeight();
            }
        }
        //go up tree one
        i--;
    }
}
