#ifndef READFILE_H__
#define READFILE_H__

#include <string>
#include <iostream>
#include <fstream>
#include <iomanip>

using namespace std;

struct wordRecord {
	string word;
	int count;
};

// TODO add detailed explanation on what the function should do
void getIgnoreWords(const char *ignoreWordFileName, string ignoreWords[]);
bool isIgnoreWord(string word, string ignoreWords[], int length);
int getTotalNumberNonIgnoreWords(wordRecord distinctWords[], int length);
void sortArray(wordRecord distinctWords[], int length);
void printTenFromN(wordRecord distinctWords[], int N, int totalNumWords);

#endif // READFILE_H__