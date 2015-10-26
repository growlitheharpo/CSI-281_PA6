#ifndef ALPHABET_TREE_H
#define ALPHABET_TREE_H

#include <iostream>

using namespace std;

class AlphabetTree
{
	private:
		char myLowestBranch, myLetter;
		char* myCode; //used if this is the termination point of a word
		int myArraySize;

		AlphabetTree **myChildren;

		void shiftMyChildren(char newLow);

	public:
		AlphabetTree();
		AlphabetTree(char l);
		~AlphabetTree();

		char* doSearch(const string& word, int currentIndex);
		char* doSearch(const char* word, int currentIndex, int length);

		void addWord(string &newWord, const string &wordCode);
};

#endif