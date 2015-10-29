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
#ifndef HEADER_H
#define HEADER_H

#include "AlphabetTree.h"

const string CODES_FILE = "codes.txt",
			 EXIT_KEYWORD = "exit";

double encryptFile(AlphabetTree &treeRoot, const string &source, const string &target);
bool getFileNames(string &input, string &output);
double loadData(AlphabetTree &rootNode);
void mainMenu();

#endif
