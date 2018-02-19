/*
 * BinarySearchTree.h
 *
 *  Created on: Jan 27, 2018
 *      Author: Adam
 */

#ifndef SRC_BINARYSEARCHTREE_H_
#define SRC_BINARYSEARCHTREE_H_
#include "HashTable.h"
#include <fstream>
#include "main.h"

struct node {
	string word;
	int counter = 0;
	node* left;
	node* right;

};



class BinarySearchTree {
public:
	int nodeCount;
	BinarySearchTree();
	~BinarySearchTree();
	void sort();
	void insertNode(string data);
	void createHashTable(HashTable &HashT, int size);
	bool searchTree(string data);
	void deleteNode(string data);
	void rangeSortTree(string a, string b);
private:
	node* root = new node();
	node* rootTemp;
	void insertNode(string data, node* leaf);
	void deleteNode(string data, node* leaf);
	bool searchTree(string data, node* leaf);
	void sort(node* leaf);
	node* traverseTree(string data, node* leaf);
	void rangeSortTree(string a, string b, node* leaf);
	void insertHashValue(node* leaf, HashTable &HashT);
	bool occured;
};

#endif /* SRC_BINARYSEARCHTREE_H_ */
