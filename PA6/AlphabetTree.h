#ifndef ALPHABET_TREE_H
#define ALPHABET_TREE_H

#include <iostream>

using namespace std;

const char LOWEST_CHARACTER_VALUE = '"';
const string INVALID_WORD = "-999";
const int NUMBER_OF_LETTERS_IN_ENGLISH = (128 - LOWEST_CHARACTER_VALUE);

class AlphabetTree
{
	private:
		char myLetter;
		char* myCode; //used if this is the termination point of a word

		AlphabetTree *myChildren[NUMBER_OF_LETTERS_IN_ENGLISH];

	public:
		AlphabetTree();
		AlphabetTree(char l);
		~AlphabetTree();

		char* doSearch(const string& word, int currentIndex);
		char* doSearch(const char* word, int currentIndex, int length);

		void addWord(string &newWord, const string &wordCode);
};

#endif