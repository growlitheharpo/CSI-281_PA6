#ifndef HEADER_H
#define HEADER_H

#include "AlphabetTree.h"

const string CODES_FILE = "codes.txt",
			 EXIT_KEYWORD = "exit";

double encryptFile(AlphabetTree &treeRoot, const string &source, const string &target);
double loadData(AlphabetTree &rootNode);
void mainMenu();

#endif
