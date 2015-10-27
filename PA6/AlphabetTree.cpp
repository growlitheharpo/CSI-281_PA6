#include "AlphabetTree.h"

void AlphabetTree::shiftMyChildren(char newLow)
{
	AlphabetTree **newChildren;
	int i;

	newChildren = new AlphabetTree*[HIGHEST_USED_ASCII_VALUE - newLow];

	for (i = 0; i < (myLowestBranch - newLow); i++)
		newChildren[i] = NULL;

	for (i = 0; i < myArraySize; i++)
		newChildren[myLowestBranch - newLow + i] = myChildren[i];

	delete[] myChildren;
	myChildren = newChildren;

	myLowestBranch = newLow;
	myArraySize = HIGHEST_USED_ASCII_VALUE - newLow;
}

AlphabetTree::AlphabetTree()
{
	myLetter = 0;
	myCode = NULL;
	myArraySize = 26;
	myLowestBranch = 'a';

	myChildren = new AlphabetTree*[myArraySize];

	for (int i = 0; i < myArraySize; i++)
		myChildren[i] = NULL;
}

AlphabetTree::AlphabetTree(char l)
{
	myLetter = l;
	myCode = NULL;

	myLowestBranch = l;
	myArraySize = HIGHEST_USED_ASCII_VALUE - l; //123 instead of 128 b/c the last 5 ASCII characters won't be used

	myChildren = new AlphabetTree*[myArraySize];

	for (int i = 0; i < myArraySize; i++)
		myChildren[i] = NULL;
}

AlphabetTree::~AlphabetTree()
{
	if (myCode != NULL)
		delete myCode;

	for (int i = 0; i < myArraySize; i++)
	{
		if (myChildren[i] != NULL)
			delete myChildren[i];
	}

	delete[] myChildren;
}


char* AlphabetTree::doSearch(const string &word, int currentIndex)
{
	if (currentIndex == word.length())
	{
		if (myCode == NULL)
			return const_cast<char *>(word.c_str());

		return myCode;
	}
	else if (word[currentIndex] - myLowestBranch < 0 || myChildren[word[currentIndex] - myLowestBranch] == NULL)
	{
		return const_cast<char *>(word.c_str());
	}
	else
	{
		return myChildren[word[currentIndex] - myLowestBranch]->doSearch(word, currentIndex + 1);
	}
}


char* AlphabetTree::doSearch(const char* word, int currentIndex, int length)
{
	if (currentIndex == length)
	{
		return myCode;
	}
	else if (myChildren[word[currentIndex] - myLowestBranch] == NULL)
	{
		return const_cast<char *>(word);
	}
	else
	{
		return myChildren[word[currentIndex] - myLowestBranch]->doSearch(word, currentIndex + 1, length);
	}
}

void AlphabetTree::addWord(string &newWord, const string &wordCode)
{
	if (newWord.length() == 0)
	{
		//this->myCode = wordCode; //when myCode was a string, we could use this
		if (this->myCode != NULL)
			delete myCode;

		this->myCode = new char[wordCode.size() + 1];
		this->myCode[wordCode.size()] = 0;	//null terminator
		memcpy(this->myCode, wordCode.c_str(), wordCode.size());
	}
	else
	{
		int letterIndex = newWord[0] - myLowestBranch;

		if (letterIndex < 0)
		{
			shiftMyChildren(newWord[0]);
			letterIndex = 0;
		}

		if (myChildren[letterIndex] == NULL)
		{
			myChildren[letterIndex] = new AlphabetTree(newWord[0]);
		}

		newWord.erase(0, 1);
		myChildren[letterIndex]->addWord(newWord, wordCode);
	}
}