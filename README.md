# BSTandHash

1. Implement Binary Search Tree and Hash Table classes.
Each node in the BST or row in the Hash Table is a pair of (word,counter) where
counter shows the number of occurrence of the word in the dataset.
Each class should have at least the following functions:
(a) A constructor and a destructor.
(b) A function for searching a word in the BST/Hash Table (the word may or may not exist).
(c) A function for inserting a new word into the BST/Hash Table or increment the counter
if the word is already inserted.
(d) A function for deleting a word from the BST/Hash Table if the counter reaches zero or
decrement the counter by one. Deletion of already deleted word should be ignored.
(e) A function to sort all the words lexicographically.
(f) A function for doing a range search. The function takes as input two words. Given two
words, the function should find all the words in between. The resulting words need not
be sorted.
You are expected to find 3 pairs of such words which have 10, 100, and 1000 words in
between them and measure the running time for performing range query.
