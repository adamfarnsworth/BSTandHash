# BSTandHash

## Implement Binary Search Tree and Hash Table classes.  
Each node in the BST or row in the Hash Table is a pair of (word,counter) where counter shows the number of occurrence of the word in the dataset.  
Each class should have at least the following functions:
* A constructor and a destructor.
* A function for searching a word in the BST/Hash Table (the word may or may not exist).
* A function for inserting a new word into the BST/Hash Table or increment the counter
if the word is already inserted.
* A function for deleting a word from the BST/Hash Table if the counter reaches zero or
decrement the counter by one. Deletion of already deleted word should be ignored.
* A function to sort all the words lexicographically.
* A function for doing a range search. The function takes as input two words. Given two
words, the function should find all the words in between. The resulting words need not
be sorted.  

You are expected to find 3 pairs of such words which have 10, 100, and 1000 words in
between them and measure the running time for performing range query.  

## Input
Implement a simple text-based (cin, cout) user interface for your code. It should allow you to:
* Search a given word, show whether the word exist in the dataset, and show the required
time to search a word in BST vs. Hash Table
* Insert a new word and show the required time to insert a word into BST vs. Hash Table
* Delete a word and show the required time to delete a word from BST vs. Hash Table
* Sort all the words alphabetically and write them in a separate file and show the required
time to sort all the words in BST vs. Hash Table
* Do a range search and show the required time to do range search in BST vs. Hash Table  

## Program Output Details:
Your code should compile into a single binary by running make. Call this binary ”main”. Once
you run main, your code should build a BST and a Hash Table out of the dataset. Then your
code should prompt the user to enter 1, 2, 3, 4, or 5 to search, insert, delete, sort, or range
search, respectively.
Then, for search, insert, and delete, you should prompt the user for an argument. For sort,
you will not prompt for an argument. For range search, you will prompt for two arguments,
separated by a newline.
Your program should loop forever unless given a kill signal (CTRL-C); a user should be able
to enter consecutive commands (insert, delete, insert, etc.) without restarting the program.  

### Examples
> make  
> . / main  
> 1  
> wordThatDoesExist  
true  
BST: 0. 1 0 s  
Hash : 0. 0 0 1 s  
> . / main  
> 1  
> wordThatDoesNotExist  
f a l s e  
BST: 0. 2 s  
Hash : 1. 0 s  
> . / main  
> 2  
> wo rdTo Inse r t  
BST: 0. 1 0 s  
Hash : 0. 0 0 1 s  
> . / main  
> 3  
> wordToDelete  
BST: 0. 1 0 s  
Hash : 0. 0 0 1 s  
2  
> . / main  
> 4  
/ path / t o / output . t x t  
BST: 0. 1 0 s  
Hash : 0. 0 0 1 s  
> . / main  
> 5  
> startWord  
> endWord  
startWord  
. . .  
endWord  
. . .  
po s siblyO the rW o rd s  
BST: 0. 1 0 s  
Hash : 0. 0 0 1 s  
