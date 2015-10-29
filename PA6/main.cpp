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


My Data Structure:
	My structure, AlphabetTree, is sort of a combination of an array, Linked List, and a tree. This
	structure uses a LOT of memory, but that's "okay" because speed is the only thing that matters for
	this assignment.
	Each individual instance of AlphabetTree is essentially a node. Every node is a letter,
	and the branches of the trees are paths through which letters can be combined. I.e., the A in C->A
	is a different node than the A in D->A. Every node contains an array of pointers to its children.
	I chose to use an array rather than a list for the fast random access; I take advantage of this
	by using the ASCII values of the search key as indexes.
*/
#include "header.h"

int main()
{
	mainMenu();

	system("pause");
	return 0;
}