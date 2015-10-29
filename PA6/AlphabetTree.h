/*
Author:           James Keats
Class:            CSI-281-02
Assignment:       PA6
Date Assigned:    10/22/2015
Due Date:         10/29/2015 @ 9:30AM

Description:
A program for QUICKLY encrypting a given file based on a code word file.

Certification of Authenticity:
I certify that this is entirely my own work, except where I have given fully-documented references
to the work of others. I understand the definition and consequences of plagiarism and acknowledge
that the assessor of this assignment may, for the purpose of assessing this assignment:
- Reproduce this assignment and provide a copy to another member of academic staff; and/or
- Communicate a copy of this assignment to a plagiarism checking service (which may then
retain a copy of this assignment on its database for the purpose of future plagiarism checking)
*/
#ifndef ALPHABET_TREE_H
#define ALPHABET_TREE_H

#include <iostream>

using namespace std;

const int HIGHEST_USED_ASCII_VALUE = 123;

class AlphabetTree
{
	private:
		char myLowestBranch;
		char* myCode; //used if this is the termination point of a word
		int myArraySize;

		AlphabetTree **myChildren;

		void shiftMyChildren(char newLow);

	public:
		AlphabetTree();
		~AlphabetTree();

		char* doSearchRecursive(const char* word, int currentIndex, int length);
		char* doSearchIterative(const char* word, int length);
		void addWord(string &newWord, const string &wordCode);
};

#endif