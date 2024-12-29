#include "array_double.hpp"
#include <fstream>

void getIgnoreWords(const char *ignoreWordFileName, string ignoreWords[]){
    ifstream ignoreFile(ignoreWordFileName);
    if(ignoreFile.fail()){
        cout << "Failed to open " << ignoreWordFileName << endl;
    }

    string line;
    int i = 0;
    while(getline(ignoreFile, line)){
        ignoreWords[i] = line;
        i++;
    }
}


bool isIgnoreWord(string word, string ignoreWords[], int length){
    for(int i = 0; i < length; i++){
        if(word == ignoreWords[i]){
            return true;
        }
    }
    return false;
}


int getTotalNumberNonIgnoreWords(wordRecord distinctWords[], int length){
    int total = 0;
    for(int i = 0; i < length; i++){
        total += distinctWords[i].count;
    }
    return total;
}


void sortArray(wordRecord distinctWords[], int length){
    wordRecord temp;
    for(int j = 0; j < length - 1; j++){
        for(int i = 0; i < length - 1; i++){
            if(distinctWords[i].count < distinctWords[i + 1].count){
                temp = distinctWords[i];
                distinctWords[i] = distinctWords[i + 1];
                distinctWords[i + 1] = temp;
            }else if(distinctWords[i].count == distinctWords[i + 1].count && distinctWords[i].word > distinctWords[i + 1].word){
                temp = distinctWords[i];
                distinctWords[i] = distinctWords[i + 1];
                distinctWords[i + 1] = temp;
            }
        }
    }
}


void printTenFromN(wordRecord distinctWords[], int N, int totalNumWords){
    float prob;
    for(int i = N; i < N + 10; i++){
        prob = (float) distinctWords[i].count / totalNumWords;
        cout << fixed << setprecision(5) << prob << " - " << distinctWords[i].word << endl;
    }
}

