#include <iostream>
#include <fstream>
#include <string>
#include "../code_1/array_double.hpp"

using namespace std;

int main(int argc, char* argv[])
{
    // your code here
    if(argc != 4){
        cout << "Usage: Assignment2Solution <number of words> <inputfilename.txt> <ignoreWordsfilename.txt>" << endl;
        return 1;
    }

    int N = atoi(argv[1]);
    ifstream textFile(argv[2]);

    if(textFile.fail()){
        cout << "Error, failed to open: " << argv[2] << endl;
    }

    string ignoreWords[50];
    getIgnoreWords(argv[3], ignoreWords);

    const int initialSize = 100;
    int capacity = initialSize;
    int loop = 0;
    int doubleCount = 0;
    int distinctWords = 0;
    int nonCommonWords = 0;
    wordRecord* wordsArray = new wordRecord[initialSize];
    string word;
    bool found;

    while(textFile >> word){
        found = false;
        if(isIgnoreWord(word, ignoreWords, 50)){
            continue;
        }else{
            for(int i = 0; i < loop; i++){
                if(wordsArray[i].word == word){
                    wordsArray[i].count++;
                    found = true;
                    break;
                }
            }

            if(!found){
                if(loop >= capacity){
                    const int newSize = 2 * capacity;
                    wordRecord* newArray = new wordRecord[newSize];

                    for(int i = 0; i < capacity; i++){
                        newArray[i] = wordsArray[i];
                    }

                    delete[] wordsArray;
                    wordsArray = newArray;
                    capacity = newSize;
                    doubleCount++;
                }
                wordsArray[loop].word = word;
                wordsArray[loop].count = 1;
                distinctWords++;
                loop++;
            }
        }
    }

    for(int i = 0; i < loop; i++){
        nonCommonWords += wordsArray[i].count;
    }

    sortArray(wordsArray, loop);

    cout << "Array doubled: " << doubleCount << endl;
    cout << "Distinct non-common words: " << distinctWords << endl;
    cout << "Total non-common words: " << nonCommonWords << endl;
    cout << "Probability of next 10 words from rank " << N << endl;
    cout << "---------------------------------------" << endl;

    printTenFromN(wordsArray, N, nonCommonWords);
    
    return 0;
}