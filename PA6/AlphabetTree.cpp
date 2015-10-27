#include "AlphabetTree.h"

AlphabetTree::AlphabetTree()
{
	myLetter = 0;
	myCode = NULL;

	for (int i = 0; i < NUMBER_OF_LETTERS_IN_ENGLISH; i++)
		myChildren[i] = NULL;
}

AlphabetTree::AlphabetTree(char l)
{
	myLetter = l;
	myCode = NULL;

	for (int i = 0; i < NUMBER_OF_LETTERS_IN_ENGLISH; i++)
		myChildren[i] = NULL;
}

AlphabetTree::~AlphabetTree()
{
	if (myCode != NULL)
		delete myCode;

	for (int i = 0; i < NUMBER_OF_LETTERS_IN_ENGLISH; i++)
	{
		if (myChildren[i] != NULL)
			delete myChildren[i];
	}
}


char* AlphabetTree::doSearch(const string &word, int currentIndex)
{
	if (currentIndex == word.length())
	{
		if (myCode == NULL)
			return const_cast<char *>(word.c_str());

		return myCode;
	}
	else if (myChildren[word[currentIndex] - LOWEST_CHARACTER_VALUE] == NULL)
	{
		return const_cast<char *>(word.c_str());
	}
	else
	{
		return myChildren[word[currentIndex] - LOWEST_CHARACTER_VALUE]->doSearch(word, currentIndex + 1);
	}
}


char* AlphabetTree::doSearch(const char* word, int currentIndex, int length)
{
	if (currentIndex == length)
	{
		if (myCode == NULL)
			return const_cast<char *>(word);

		return myCode;
	}
	else if (word[currentIndex] - LOWEST_CHARACTER_VALUE < 0 || myChildren[word[currentIndex] - LOWEST_CHARACTER_VALUE] == NULL)
	{
		return const_cast<char *>(word);
	}
	else
	{
		return myChildren[word[currentIndex] - LOWEST_CHARACTER_VALUE]->doSearch(word, currentIndex + 1, length);
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
		int letterIndex = newWord[0] - LOWEST_CHARACTER_VALUE;

		if (myChildren[letterIndex] == NULL)
		{
			myChildren[letterIndex] = new AlphabetTree(newWord[0]);
		}

		newWord.erase(0, 1);
		myChildren[letterIndex]->addWord(newWord, wordCode);
	}
}