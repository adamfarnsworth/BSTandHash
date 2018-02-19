/*
 * HashTable.h
 *
 *  Created on: Feb 4, 2018
 *      Author: Adam
 */

#ifndef SRC_HASHTABLE_H_
#define SRC_HASHTABLE_H_
#include "main.h"

struct value {
	string word;
	int count;
	value* next;
};

class HashTable {
public:
	void setSize(int x);
	void insert(string data);
	void deleteValue(string data);
	void rangeSort(string a, string b);
	void fixCount(string data, int x);
	void sortHash();
	void printTable();
	bool search(string data);
	int hash(string word);
	HashTable();
	virtual ~HashTable();

private:

	int indexCount(int index);
	int tableSize;
	value**table;

};

#endif /* SRC_HASHTABLE_H_ */
