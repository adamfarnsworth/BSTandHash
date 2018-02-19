/*
 * BinarySearchTree.cpp
 *
 *  Created on: Jan 27, 2018
 *      Author: Adam
 */

#include "BinarySearchTree.h"
#include <string.h>

BinarySearchTree::BinarySearchTree() {
	root = NULL;
	rootTemp = NULL;
	occured = false;
	nodeCount = 0;
}
BinarySearchTree::~BinarySearchTree() {

}

void BinarySearchTree::insertNode(string data) {
	if (root == NULL) { 		//adding new node for first value
		nodeCount++;
		root = new node();
		root->left = NULL;
		root->right = NULL;
		root->word = data;
		root->counter++;
		rootTemp = root;
	} else {
		insertNode(data, root);
	}
}

void BinarySearchTree::insertNode(string data, node* leaf) {

//checking if data is GREATER than word of leaf && checking if a node exists
	occured = false;

	while (!occured) {

		if (data.compare(leaf->word) == 0) { //checking if data is = word of leaf
			leaf->counter++;
			occured = true;
		}

		else if (data.compare(leaf->word) < 0) { //checking if data is LESS than word of leaf

			if (leaf->left != NULL) {			//checking if a node exists
				leaf = leaf->left;
				occured = false;
			} else {

				nodeCount++;
				node *temp = new node();
				occured = true;
				leaf->left = temp;
				temp->word = data;
				temp->left = NULL;
				temp->right = NULL;
				temp->counter++;

			}
		}

		else if ((data.compare(leaf->word) > 0)) { //checking if data is GREATER word of leaf

			if (leaf->right != NULL) {			//checking if a node exists
				occured = false;
				leaf = leaf->right;
			} else {

				nodeCount++;
				node *temp = new node();
				occured = true;
				leaf->right = temp;
				temp->word = data;
				temp->left = NULL;
				temp->right = NULL;
				temp->counter++;

			}
		}

	}

}

void BinarySearchTree::sort() {

	if (root == NULL) {
		return;
	} else {
		sort(root);

	}
}

void BinarySearchTree::sort(node* leaf) {

	if (leaf != NULL) {
		sort(leaf->left);
		myfile << leaf->word << "\n";
		sort(leaf->right);

	} else
		return;
}

bool BinarySearchTree::searchTree(string data) {

	if (root == NULL)
		return false;
	else
		return searchTree(data, root);

}

bool BinarySearchTree::searchTree(string data, node* leaf) {

	if (leaf == NULL)					//base case on a empty tree
		return false;

	leaf = traverseTree(data, leaf);	//traversing tree to find node

	if (leaf == NULL)					//the word dosent exist
		return false;
	if (leaf->word == data)				//the word does exist
		return true;

	return false;
//******************************************
//recursion
//******************************************
//	if(leaf == NULL)
//		return false;
//
//	// Base Cases: root is null or key is present at root
//	if (leaf->word == data)
//		return true;
//
//	// Key is greater than root's key
//	else if (leaf->word < data)
//		return searchTree(data, leaf->right);
//
//	// Key is smaller than root's key
//	return searchTree(data, leaf->left);
//******************************************
//******************************************

}

node* BinarySearchTree::traverseTree(string data, node* leaf) {

	while (leaf != NULL) {

		if (leaf->word == data)
			break;

		// Key is greater than root's key
		if (leaf->word < data)
			leaf = leaf->right;

		// Key is smaller than root's key
		else if ((leaf->word > data))
			leaf = leaf->left;
	}

	return leaf;
}

void BinarySearchTree::deleteNode(string data) {

	if (root == NULL)	//base case of the tree being empty
		return;
	else {
		deleteNode(data, root);
	}
}

void BinarySearchTree::deleteNode(string data, node* leaf) {
	node*parent = new node();
	parent = leaf;

	while (leaf != NULL) {		//tree traversal

		if (leaf->word == data)	//word is found
			break;

		if (leaf->word < data) {		// Key is greater than root's key
			parent = leaf;
			leaf = leaf->right;
		}

		else if ((leaf->word > data)) {		// Key is smaller than root's key
			parent = leaf;
			leaf = leaf->left;
		}
	}
	if (leaf == NULL) {		//word does not exist

		return;
	}

	if ((leaf->right == NULL) && (leaf->left == NULL)) {//*****if the current node has ZERO children *****
		if (leaf->counter > 1) {		//decrementing node
			leaf->counter--;
		} else {	//deleting node
			if (parent == leaf) {	//the word is root

				delete parent;
				parent = NULL;

				delete leaf;
				leaf = NULL;

				delete root;
				root = NULL;

			}

			else if (parent->right == leaf) {//checking which node the parent is deleting
				delete leaf;
				leaf = NULL;
				parent->right = NULL;
			} else {
				delete leaf;
				leaf = NULL;
				parent->left = NULL;
			}

		}

	}

	else if ((leaf->right == NULL) || (leaf->left == NULL)) { //***** if the current node has ONE child *****
		if ((leaf->right == NULL)) {		//right child is empty
			if (leaf->counter > 1) {		//checking count in node
				leaf->counter--;
			} else {

				if (parent == leaf) {	//the word is root
					root = root->left;
					delete leaf;
					leaf = NULL;
					delete parent;
					parent = NULL;
				}

				else if (parent->right == leaf) {//checking which node the parent is deleting
					parent->right = leaf->left;
					delete leaf;
					leaf = NULL;
				} else {
					parent->left = leaf->left;
					delete leaf;
					leaf = NULL;
				}

			}

		} else if ((leaf->left == NULL)) {		//left child is empty
			if (leaf->counter > 1) {		//checking count in node
				leaf->counter--;
			} else {

				if (parent == leaf) {	//the word is root
					root = root->right;
					delete leaf;
					delete parent;
					leaf = NULL;
					parent = NULL;
				}

				else if (parent->right == leaf) {//checking which node the parent is deleting
					parent->right = leaf->right;
					delete leaf;
					leaf = NULL;

				} else {
					parent->left = leaf->right;
					delete leaf;
					leaf = NULL;

				}
			}
		}

	}

	else {		//***** if the current node has TWO children *****
		if (leaf->counter > 1) {		//checking count in node
			leaf->counter--;
		} else {

			if (leaf == root) { //the word is root
				leaf = leaf->right;		//setting up to traverse right subtree
				node*temp = new node();
				temp = leaf;
				while (leaf->left != NULL) {		//getting smallest value
					temp = leaf;
					leaf = leaf->left;
				}

				root->word = leaf->word;
				root->counter = leaf->counter;	//Swapping values and deleting

				if (root->right == leaf) {//if what's being deleted right node is = the node being swapped
					parent->right = NULL;
				}

				delete leaf;
				leaf = NULL;
				temp->left = NULL;
				delete temp;

			} else {	// if the word is root ENDED, and ELSE is its not root

				parent = leaf;
				leaf = leaf->right;		//setting up to traverse right subtree

				node*temp = new node();
				temp = leaf;
				while (leaf->left != NULL) {		//getting smallest value
					temp = leaf;
					leaf = leaf->left;
				}


//				parent->word = leaf->word;
//				parent->counter = leaf->counter;//Swapping values and deleting

				if (parent->right == leaf) {//if what's being deleted right node is = the node being swapped
					parent->right = NULL;
				} else {	//just added this else
					parent->word = leaf->word;
					parent->counter = leaf->counter;//Swapping values and deleting

					delete leaf;
					leaf = NULL;
					temp->left = NULL;

					delete temp;
				}
			}
		}
	}
}

void BinarySearchTree::rangeSortTree(string a, string b) {
	if (root == NULL)
		return;
	else
		rangeSortTree(a, b, root);

}

void BinarySearchTree::rangeSortTree(string a, string b, node* leaf) {

	if (leaf == NULL) // if tree is empty
		return;

	if (a < leaf->word)	//traverse LEFT subtree
		rangeSortTree(a, b, leaf->left);

	if (a <= leaf->word && b >= leaf->word)	//printing if value is in our range
		cout << leaf->word << endl;

	if (b > leaf->word)	//traverse RIGHT subtree
		rangeSortTree(a, b, leaf->right);

}

void BinarySearchTree::createHashTable(HashTable &HashT, int size) {

	HashT.setSize(size);

	if (root == NULL) {
		return;
	} else {
		insertHashValue(root, HashT);

	}

}

void BinarySearchTree::insertHashValue(node* leaf, HashTable &HashT) {
	if (leaf != NULL) {
		insertHashValue(leaf->left, HashT);
		HashT.insert(leaf->word);
		HashT.fixCount(leaf->word, leaf->counter);
		insertHashValue(leaf->right, HashT);

	} else
		return;

}

