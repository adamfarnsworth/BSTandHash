#include "BinarySearchTree.h"
#include "HashTable.h"
#include "main.h"
#include <dirent.h>
#include <fstream>
#include <regex>
#include <stack>
#include <vector>
#include <cstring>
#include <ctime>
#include <chrono>

void buildTree(BinarySearchTree &tree, HashTable &hashT, string location,
		HashTable stopwords);
void getList(stack<string> &currStack, string location);

void buildConsole(BinarySearchTree &tree, HashTable &hashT);

ofstream myfile;

int main() {

	//_______________________________________________________________________
	string resultList[100] = { "i", "me", "my", "myself", "we", "our",
			"ours", "ourselves", "you", "your", "yours", "yourself",
			"yourselves", "he", "him", "his", "himself", "she", "her", "hers",
			"herself", "it", "its", "itself", "they", "them", "their", "theirs",
			"themselves", "what", "which", "who", "whom", "this", "that",
			"these", "those", "am", "is", "are", "was", "were", "be", "been",
			"being", "have", "has", "had", "having", "do", "does", "did",
			"doing", "a", "an", "the", "and", "but", "if", "or", "because",
			"as", "until", "while", "of", "at", "by", "for", "with", "about",
			"against", "between", "into", "through", "during", "before",
			"after", "above", "below", "to", "from", "up", "down", "in", "out",
			"on", "off", "over", "under", "again", "further", "then", "once",
			"here", "there", "when", "where", "why", "how", "all"};


	BinarySearchTree bstt;		//creating tree
	HashTable htt;				//creating hash table

bstt.createHashTable(htt, 100*3/2);

//BST INSERT
auto start = std::chrono::system_clock::now();
	for (int i = 0; i<100; i++)
		bstt.insertNode(resultList[i]);
auto end = std::chrono::system_clock::now();
std::chrono::duration<double> elapsed_seconds = end-start;
std::cout << "BST INSERT: " << elapsed_seconds.count() << "s\n";

//HASH INSERT
start = std::chrono::system_clock::now();
	for (int i = 0; i<100; i++)
		htt.insert(resultList[i]);
end = std::chrono::system_clock::now();
elapsed_seconds = end-start;
std::cout << "HASH INSERT: " << elapsed_seconds.count() << "s\n";

//BST SEARCH
start = std::chrono::system_clock::now();
	for (int i = 0; i<100; i++)
		bstt.searchTree(resultList[i]);
end = std::chrono::system_clock::now();
elapsed_seconds = end-start;
std::cout << "BST SEARCH: " << elapsed_seconds.count() << "s\n";

//HASH SEARCH
start = std::chrono::system_clock::now();
	for (int i = 0; i<100; i++)
		htt.search(resultList[i]);
end = std::chrono::system_clock::now();
elapsed_seconds = end-start;
std::cout << "HASH SEARCH: " << elapsed_seconds.count() << "s\n";

//BST DELETE
start = std::chrono::system_clock::now();
	for (int i = 0; i<100; i++){
		bstt.deleteNode(resultList[i]);
	}
end = std::chrono::system_clock::now();
elapsed_seconds = end-start;
std::cout << "BST DELETE: " << elapsed_seconds.count() << "s\n";

//HASH DELETE
start = std::chrono::system_clock::now();
	for (int i = 0; i<100; i++)
		htt.deleteValue(resultList[i]);
end = std::chrono::system_clock::now();
elapsed_seconds = end-start;
std::cout << "HASH DELETE: " << elapsed_seconds.count() << "s\n";

//_________________________________________________________________________________________
	BinarySearchTree bst;		//creating tree
	HashTable ht;				//creating hash table
	stack<string> dirStack;		//all the directories
	stack<string> fileStack;	//all the files

	string stopwordsList[127] = { "i", "me", "my", "myself", "we", "our",
			"ours", "ourselves", "you", "your", "yours", "yourself",
			"yourselves", "he", "him", "his", "himself", "she", "her", "hers",
			"herself", "it", "its", "itself", "they", "them", "their", "theirs",
			"themselves", "what", "which", "who", "whom", "this", "that",
			"these", "those", "am", "is", "are", "was", "were", "be", "been",
			"being", "have", "has", "had", "having", "do", "does", "did",
			"doing", "a", "an", "the", "and", "but", "if", "or", "because",
			"as", "until", "while", "of", "at", "by", "for", "with", "about",
			"against", "between", "into", "through", "during", "before",
			"after", "above", "below", "to", "from", "up", "down", "in", "out",
			"on", "off", "over", "under", "again", "further", "then", "once",
			"here", "there", "when", "where", "why", "how", "all", "any",
			"both", "each", "few", "more", "most", "other", "some", "such",
			"no", "nor", "not", "only", "own", "same", "so", "than", "too",
			"very", "s", "t", "can", "will", "just", "don", "should", "now" };
	HashTable stopwords;		//creating stopwords table
	stopwords.setSize(127);
	for (string word : stopwordsList)
		stopwords.insert(word);

	getList(dirStack, "");			//getting all the names of the directories

	while (!dirStack.empty()) {					//going through all directories
		getList(fileStack, "/" + dirStack.top());//going through current directory and getting all the file names
		cout << dirStack.top() << endl;
		while (!fileStack.empty()) {
			cout<<fileStack.top()<<endl;
			buildTree(bst, ht, "/" + dirStack.top() + "/" + fileStack.top(),
					stopwords);	//adding onto tree from current directory files
			fileStack.pop();
		}
		dirStack.pop();
	}

	bst.createHashTable(ht, bst.nodeCount * 3 / 2);
	//ht.printTable();
	buildConsole(bst, ht);

}	//end of main

void getList(stack<string> &currStack, string location) {
	//string temp = "./hotels" + location;
	string temp = "./hotels-small" + location;
	const char *pwd; //some stupid bs about the file having the be a const char *
	pwd = temp.c_str();

	DIR *dir;
	struct dirent *ent;
	if ((dir = opendir(pwd)) != NULL) {
		while ((ent = readdir(dir)) != NULL) { //adding directories within parent directory
			currStack.push(ent->d_name);
			if ((currStack.top() == ".") || (currStack.top() == "..")) { //erasing the current and parent directory
				currStack.pop();
			}
		}

		closedir(dir);
	}
//		 else {
//			  /* could not open directory */
//			  perror ("");
//			  return EXIT_FAILURE;
//			}

}

void buildConsole(BinarySearchTree &tree, HashTable &hashT) {

	string word;
	int i=7;

	while (i != 0) {

		cin >> i;

		while (!cin || i < 1 || i > 5) {	//making sure input is valid
			cin.clear();    // Restore input stream to working state
			cin.ignore(100, '\n'); // Get rid of any garbage that user might have entered
			cin >> i;
		}

		switch (i) {

		case 1: {	//search
			bool result;
			cin >> word;

			clock_t tStart, tEnd;

			tStart = clock();	//start timer
			result = tree.searchTree(word);
			tEnd = clock();		//end timer

			printf("BST: %fs \n",
					((double) tEnd - (double) tStart) / (CLOCKS_PER_SEC));

			if (result == 1)
				std::cout << "true" << std::endl;
			else
				cout << "false" << endl;

			tStart = clock();	//start timer
			result = hashT.search(word);
			tEnd = clock();		//end timer

			printf("BST: %fs \n",
					((double) tEnd - (double) tStart) / (CLOCKS_PER_SEC));

		}
			break;
		case 2: { 	//Insert

			cin >> word;

			clock_t tStart, tEnd;

			tStart = clock();	//start timer
			tree.insertNode(word);
			tEnd = clock();		//end timer

			printf("BST: %fs \n",
					((double) tEnd - (double) tStart) / (CLOCKS_PER_SEC));

			tStart = clock();	//start timer
			hashT.insert(word);
			tEnd = clock();		//end timer

			printf("Hash: %fs \n",
					((double) tEnd - (double) tStart) / (CLOCKS_PER_SEC));

		}
			break;
		case 3: {	//Delete
			cin >> word;
			clock_t tStart, tEnd;

			tStart = clock();	//start timer
			tree.deleteNode(word);
			tEnd = clock();		//end timer

			printf("BST: %fs \n",
					((double) tEnd - (double) tStart) / (CLOCKS_PER_SEC));

			tStart = clock();	//start timer
			hashT.deleteValue(word);
			tEnd = clock();		//end timer

			printf("Hash: %fs \n",
					((double) tEnd - (double) tStart) / (CLOCKS_PER_SEC));

		}
			break;
		case 4: {	//Sort

			myfile.open("output.txt");

			clock_t tStart, tEnd;

			tStart = clock();	//start timer
			tree.sort();
			tEnd = clock();		//end timer

			cout << "Homework1/src/output.txt" << endl;

			printf("BST: %fs\n",
					((double) tEnd - (double) tStart) / (CLOCKS_PER_SEC));

			myfile << "\n";

			tStart = clock();	//start timer
			hashT.sortHash();
			tEnd = clock();		//end timer

			printf("Hash: %fs\n",
					((double) tEnd - (double) tStart) / (CLOCKS_PER_SEC));

			myfile.close();

		}
			break;
		case 5: {	//Range Search
			string word2;

			cin >> word;
			cin >> word2;

			if (word > word2) {	//swapping inputs if word is greaterr than word2
				string temp = word;
				word = word2;
				word2 = temp;
			}
			clock_t tStart, tEnd, ts, te;

			tStart = clock();	//start timer
			tree.rangeSortTree(word, word2);
			tEnd = clock();		//end timer

			ts = clock();	//start timer
			hashT.rangeSort(word, word2);
			te = clock();		//end timer

			printf("BST: %fs\n",
					((double) tEnd - (double) tStart) / (CLOCKS_PER_SEC));
			printf("Hash: %fs\n",
					((double) te - (double) ts) / (CLOCKS_PER_SEC));
		}
			break;

		}
	}
}

void buildTree(BinarySearchTree &tree, HashTable &hashT, string location,
		HashTable stopwords) {
	//regex r(R"([^\W_0-9]+(?:['_-][^\W_]+)*)"); //reggex to remove all weird stuff
	//regex r("[A-Za-z'_-]+");
	regex r("[A-Za-z]+[A-Za-z_'-]*");

	stack<string> a;
	string line;

	string tempWord;	//this will be used to get rid of all upper case letters
	ifstream inFile;

//	inFile.open("./hotels" + location);	//Opening file
	inFile.open("./hotels-small" + location);	//Opening file
	if (!inFile) {										//checking if files open
		cerr << "Unable to open file datafile";
		exit(1);   // call system to stop
	}

	if (inFile.is_open())										//reading file
		while (getline(inFile, line))
			for (sregex_iterator i = sregex_iterator(line.begin(), line.end(),
					r); i != sregex_iterator(); ++i) {			//reggex magic
				smatch m = *i;
				tempWord = m.str();
				transform(tempWord.begin(), tempWord.end(), tempWord.begin(),
						::tolower);  //converting to lower case
				if (!stopwords.search(tempWord)) {	//removing stopwords
					tree.insertNode(tempWord);

				}
			}
	inFile.close();

}
