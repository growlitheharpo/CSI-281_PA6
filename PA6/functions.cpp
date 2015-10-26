#include "header.h"
#include <string>
#include <fstream>
#include <iomanip>
#include "timerSystem.h"

double encryptFile(AlphabetTree &treeRoot, const string &source, const string &target)
{
	ifstream fin(source);
	ofstream fout(target);
	string tmp = "";
	char *returnedValue;

	double time;
	TimerSystem timer;

	if (!fin.good() || !fout.good())
		return -1.0;

	timer.startClock();
	fin >> tmp;
	do
	{
		//turns out, converting to c_string is significantly faster
		returnedValue = treeRoot.doSearch(tmp.c_str(), 0, tmp.length()); 

		fout << returnedValue << " ";
		fin >> tmp;

	} while (!fin.eof());

	time = timer.getTime();

	fin.close();
	fout.close();

	return time;
}

double loadData(AlphabetTree & rootNode)
{
	string tmpWord;
	string tmpCode;
	TimerSystem timer;
	double time;

	ifstream fin;
	fin.open(CODES_FILE);

	if (!fin.good())
	{
		fin.close();
		return -1.0;
	}

	timer.startClock();

	fin >> tmpWord >> tmpCode;
	while (!fin.eof())
	{
		rootNode.addWord(tmpWord, tmpCode);
		fin >> tmpWord >> tmpCode;
	}

	time = timer.getTime();

	fin.close();

	return time;
}

void mainMenu()
{
	bool shutdown = false;
	string source, target;
	double time;
	AlphabetTree treeRoot;

	time = loadData(treeRoot);
	if (time < 0)
	{
		cout << "The code file could not be loaded!" << endl;
		return;
	}
	
	cout << fixed << showpoint << setprecision(4)
		 << "\tLoading time: " << time << " seconds" << endl << endl;

	cout << setprecision(8);

	while (shutdown == false)
	{
		cout << "\tEnter source filename: ";
		getline(cin, source);
		
		if (source == EXIT_KEYWORD)
		{
			shutdown = true;
		}
		else
		{
			cout << "\tEnter target filename: ";
			getline(cin, target);

			if (source == target)
			{
				cout << "Target cannot equal source!" << endl;
			}
			else
			{
				time = encryptFile(treeRoot, source, target);
				cout << "\n\t\tEncryption complete!\n\t\t\tTime: " << time << endl << endl;
			}
		}
	}
}