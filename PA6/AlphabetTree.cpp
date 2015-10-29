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
#include "AlphabetTree.h"


/*********************************************************************************************
*  Purpose: Shift the children of the array upwards so that it can hold children with
*			lower ASCII values than letters. Used to keep the amount of memory down.
*      Pre: Handed the new lowest value (generally '/', '\'' or '\"')
*	  Post: Children is shifted and the array's capacity is increased.
*********************************************************************************************/
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


/*********************************************************************************************
*  Purpose: Default constructor (generally only called for the root node)
*      Pre: None
*	  Post: Object is initialized with default values
*********************************************************************************************/
AlphabetTree::AlphabetTree()
{
	myCode = NULL;
	myLowestBranch = 'z';
	myArraySize = HIGHEST_USED_ASCII_VALUE - myLowestBranch;

	myChildren = new AlphabetTree*[myArraySize];

	for (int i = 0; i < myArraySize; i++)
		myChildren[i] = NULL;
}


/*********************************************************************************************
*  Purpose: Destructor
*      Pre: None
*	  Post: Memory is properly released
*********************************************************************************************/
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


/*********************************************************************************************
*  Purpose: Look for the given word in this tree
*      Pre: Handed the word, and 0 if being called from outside the recursion.
*	  Post: Returns the code if the word is valid, or the word passed in if it is invalid.
*
*	  NOTE:	This function is no longer used because, through testing, I determined that
*			an iterative version saved a significant amount of time. However, I am leaving
*			it in the code because it is a very good explanation of what is logically
*			occuring during a search.
*********************************************************************************************/
char* AlphabetTree::doSearchRecursive(const char* word, int currentIndex, int length)
{
	//If we're at the end of the word
	if (currentIndex == length)
	{
		//If my code doesn't exist, this is an invalid word. Return the word itself.
		if (myCode == NULL)
			return const_cast<char *>(word);

		//else, return the code
		return myCode;
	}
	else if (word[currentIndex] - myLowestBranch < 0 || myChildren[word[currentIndex] - myLowestBranch] == NULL)
	{
		//If we find a NULL branch, or we're trying to access an invalid branch,
		//the word is invalid. Return the word itself.
		return const_cast<char *>(word);
	}
	else
	{
		//Continue recursively along the branch, looking for the word's termination point
		return myChildren[word[currentIndex] - myLowestBranch]->doSearchRecursive(word, currentIndex + 1, length);
	}
}


/*********************************************************************************************
*  Purpose: Look for the given word in this tree
*      Pre: Handed the word, and the length of the word.
*	  Post: Returns the code if the word is valid, or the word passed in if it is invalid.
*********************************************************************************************/
char* AlphabetTree::doSearchIterative(const char* word, int length)
{
	AlphabetTree *currentLeaf = this;
	int arrayIndex, wordIndex = 0;

	//Traverse down the list for every character in the word
	while (wordIndex < length)
	{
		//The letter's index in this leaf's array is based on what its lowest child is.
		arrayIndex = word[wordIndex] - currentLeaf->myLowestBranch;

		//If that child doesn't exist or it would be out of range, return the word itself.
		if (arrayIndex < 0 || currentLeaf->myChildren[arrayIndex] == NULL)
			return const_cast<char *>(word);

		//Otherwise, move to the next leaf.
		currentLeaf = currentLeaf->myChildren[arrayIndex];
		wordIndex++;
	}

	//If the code doesn't exist, this is an invalid word. Return the word itself.
	if (currentLeaf->myCode == NULL)
		return const_cast<char *>(word);

	return currentLeaf->myCode;
}


/*********************************************************************************************
*  Purpose: Add a new word with its code to the tree.
*      Pre: Handed the new word, and the code.
*	  Post: The tree is succesfully updated with the new word and code.
*********************************************************************************************/
void AlphabetTree::addWord(string &newWord, const string &wordCode)
{
	if (newWord.length() == 0)
	{
		//Shouldn't ever enter this if statement, but maybe we're updating a code
		if (this->myCode != NULL)
			delete myCode;

		//Copy the code from std::string to C character buffer (faster!)
		this->myCode = new char[wordCode.size() + 1];
		this->myCode[wordCode.size()] = 0;	//null terminator
		memcpy(this->myCode, wordCode.c_str(), wordCode.size());
	}
	else
	{
		//find the index of this letter in myChildren
		int letterIndex = newWord[0] - myLowestBranch; 

		//If we're out of range, shift myChildren
		if (letterIndex < 0)
		{
			shiftMyChildren(newWord[0]);
			letterIndex = 0;
		}

		//If this branch doesn't exist yet, create it.
		if (myChildren[letterIndex] == NULL)
		{
			myChildren[letterIndex] = new AlphabetTree();
		}

		//Clear the first letter, and then recursively add that word to the correct child.
		newWord.erase(0, 1);
		myChildren[letterIndex]->addWord(newWord, wordCode);
	}
}