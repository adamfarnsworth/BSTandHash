/*
 * HashTable.cpp
 *
 *  Created on: Feb 4, 2018
 *      Author: Adam
 */

#include "HashTable.h"
#include "BinarySearchTree.h"


HashTable::HashTable() {
	tableSize = 0;
	table = NULL;
}

HashTable::~HashTable() {

}
void HashTable::setSize(int x) {
	tableSize = x;
	table = new value*[tableSize];

	for (int i = 0; i < tableSize; i++) { //creating table
		table[i] = new value;
		table[i]->word = "";
		table[i]->count = 0;
		table[i]->next = NULL;
	}
}
int HashTable::indexCount(int index) {
	int count = 0;
	value*ptr = table[index];
	while (ptr->next != NULL) {
		count++;
		ptr = ptr->next;
	}
	return count;

}

void HashTable::insert(string data) {

	int index;
	index = hash(data);

	if (table[index]->word == "") {	//index is empty, base case

		table[index]->word = data;
		table[index]->count++;
	} else {							//there exists an item at this index

		if (table[index]->word == data) {	// word is base case, count++

			table[index]->count++;
		} else {							//the data need to make its own spot

			value* ptr = table[index];
			while (ptr->next != NULL) {		//finding the end
				ptr = ptr->next;
				if (ptr->word == data)		//word found
					break;
			}

			if (ptr->word == data) {		//if the data is the word, count++
				ptr->count++;
			} else {
				value* temp = new value();	//creating new value
				temp->word = data;
				temp->count++;
				temp->next = NULL;

				ptr->next = temp;		//linking the values

			}

		}
	}

}

void HashTable::printTable() {
	int buckets = 0;
	int reuse = 0;
	int total = 0;
	int largest = 0;
	int largestCount = 0;
	value*ptr;


	for (int i = 0; i < tableSize; i++) {		//Iterate through whole table
		if (table[i]->count != 0) {
			buckets++;
			cout << table[i]->word << " " << table[i]->count << endl;
			total++;
			ptr = table[i];
			largestCount = 0;
		}
		for (int j = 0; j < indexCount(i); j++) {//Iterate through entire bucket
			largestCount++;
			reuse++;
			total++;
			//cout << "_________________" << endl;
			ptr = ptr->next;

			cout << ptr->word << " " << ptr->count << endl;
			if (largestCount > largest)
				largest = largestCount;

		}
	}
	cout << "buckets = " << buckets << "  from " << tableSize << endl;
	cout << "total bucket reuse = " << reuse << endl;
	cout << "total words inserted = " << total << endl;
	cout << "sectionSize = " << tableSize - ((25) * tableSize) / 26 - 1 << endl;
	cout << "deepest node has a length of " << largest << endl;

}
void HashTable::deleteValue(string data) {

	int index;
	index = hash(data);

	if (table[index]->word == "") {					//index is empty, base case
		return;
	} else {							//there are other items at this index
		value*ptr = table[index];
		value*parent = table[index];
		while (ptr->next != NULL) {						//Iterating through list
			if (ptr->word == data)
				break;
			parent = ptr;						//keeping track of parent node
			ptr = ptr->next;
		}

		if (ptr->word == data) {						//the data is found
			if (ptr->count > 1) {						//if there is more than
				table[index]->count--;
			} else {
				if (parent->next == NULL) {			// only node at this index
					parent->word = "";
					parent->count = 0;
				} else {			// there is more than 1 node at this index
					if (ptr == parent) { 				// Deleting root
						if (ptr->next != NULL) {
							ptr->word = ptr->next->word;
							ptr->count = ptr->next->count;
							ptr->next = ptr->next->next;
							delete ptr->next;
							ptr->next = NULL;
						} else {
							ptr->word = "";
							ptr->count = 0;
							ptr->next = NULL;
						}
					} else if (ptr->next != NULL) {		//not deleting root
						parent->next = ptr->next;
						delete ptr;
						ptr = NULL;
					} else {
						parent->next = NULL;
						delete ptr;
						ptr = NULL;
					}
				}

			}
		} else {
			return;
		}

	}

}
int HashTable::hash(string word) {
	//************
	//version1
	//************
	int sectionSize = tableSize - ((25) * tableSize) / 26 - 1;
	int index = tableSize - (123 - word[0]) * tableSize / 26;
	int baseLetter = index;
//cout<<sectionSize<<endl;
//cout<<tableSize<<endl;
//system("pause");
	for (int i = 1; i < word.length(); i++)
		if ((word[i] != '-') && (word[i] != '\''))
			index = index + (baseLetter + sectionSize - index) / (123 - word[i] + (i));

	return index;

//	//************
//	//version2
//	//************
//	unsigned int hash = 7;
//
//	for (unsigned int i = 0; i < word.length(); i++) {
//		hash = hash * 31 + word[i];
//	}
//
//	hash = hash % tableSize;
//
//	return hash;

//	//************
//	//version3
//	//************
//	int index;
//		for (int i = 0; i < word.size(); i++) {
//		index += (int) word[i];
//	}
//	index = (index % tableSize);
//
//	return index;

}

bool HashTable::search(string data) {
	int index;
	index = hash(data);
	value*ptr = table[index];
	while (ptr->next != NULL) {	//Iterating through list
		if (ptr->word == data)
			break;
		ptr = ptr->next;
	}

	if (ptr->word == data) {

		return true;
	} else {

		return false;
	}
}

void HashTable::rangeSort(string a, string b) {
	value*ptr;
	for (int i = 0; i < tableSize; i++) {		//Iterate through whole table
		if (table[i]->count != 0) {
			ptr = table[i];
			if ((table[i]->word >= a) && (table[i]->word <= b))
				cout << table[i]->word << endl;
		}
		for (int j = 0; j < indexCount(i); j++) {//Iterate through entire bucket

			ptr = ptr->next;
			if ((ptr->word > a) && (ptr->word < b))
				cout << ptr->word << endl;
		}
	}

}

void HashTable::sortHash() {
	BinarySearchTree tempTree;
	value*ptr;
	for (int i = 0; i < tableSize; i++) {		//Iterate through whole table
		if (table[i]->count != 0) {
			ptr = table[i];
			tempTree.insertNode(table[i]->word);
		}
		for (int j = 0; j < indexCount(i); j++) {//Iterate through entire bucket

			ptr = ptr->next;
			tempTree.insertNode(ptr->word);
		}
	}
	tempTree.sort();

}

void HashTable::fixCount(string data, int x) {
	int index = hash(data);

	value*ptr = table[index];
	while (ptr->next != NULL) {	//Iterating through list
		if (ptr->word == data)
			break;
		ptr = ptr->next;
	}

	if (ptr->word == data)
		table[index]->count = x;

}
