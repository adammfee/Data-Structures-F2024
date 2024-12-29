r# CSCI 2270 – Data Structures - Assignment 2: Array doubling with dynamic memory

## Objectives

1. Read a file with unknown size and store its contents in a dynamic array
2. Store, search and iterate through data in an array of structs
3. Use array doubling via dynamic memory to increase the size of the array

## Instructions

Write a program to analyse the word frequency in a document. Because the number of words in the document may not be known a priori, implement a **dynamically doubling array** to store the necessary information. 

Please read all the directions *before* writing code, as this write-up contains specific
requirements for how the code should be written.

To receive credit for your code, you will need to pass the necessary test cases. Use the following steps to test your code as you work on the assignment:

 1. Open up your Linux terminal, navigate to the build directory of this assignment (e.g. `cd build`).
 2. Run the `cmake ..` command.
 3. Run the `make` command.
 4. If there are no compilation errors, two executables will be generated within the build directory: `run_app_1` and `run_tests`.
 4. If you would like to run your program including your app implementation in the `main` function, execute `run_app_1` from the terminal by typing `./run_app_1 <Required arguments>`.
 5. To run the grading tests, execute `run_tests` from the terminal by typing `./run_tests`. 

## Overview

There are two files in the main directory of your repository. One contains text to be read and analyzed by your program, and is named `Tom_Sawyer.txt`. As the name implies, this file contains the full text from *Tom Sawyer*. For your convenience, all the punctuation has been removed, all the words have been converted to lowercase, and the entire document can be read as if it were written on a single line. The other file contains the 50 most common words in the English language, which your program will ignore during analysis. It is called `ignoreWords.txt`. Additional test files are included in the `assignment-2/tests/` directory. 

Your program must take three command line arguments in the following order - a number *N*, the name of the text to be read, and the name of the text file with the words that should be ignored. It will read the text (**ignoring the words in the second file**) and store all unique words in a dynamically doubling array. It should then calculate and print the following information: 

* The number of times array doubling was required to store all the unique words
* The number of unique “non-ignore” words in the file
* The total word count of the file (excluding the ignore words)
* Starting from index N, print the 10 most frequent words along with their probability (**up to 5 decimal places**) of occurrence from the array. The array should be sorted in decreasing order based on probability of occurrence of the words.
    For example, running your program with the command:
    `./run_app_1 25 ../Tom_Sawyer.txt ../ignoreWords.txt`
    would print the next 10 words starting from index 25, i.e. your program should print the 25th-34th most frequent words, along with their respective probabilities. Keep in mind that these words should **not** be any of the words from `ignoreWords.txt`. 

The full results would be: 

```
Array doubled: 7
Distinct non-common words: 7275
Total non-common words: 42962
Probability of next 10 words from rank 25
---------------------------------------
0.00333 - little
0.00326 - more
0.00324 - into
0.00324 - see
0.00317 - over
0.00310 - joe
0.00305 - know
0.00305 - never
0.00303 - again
0.00303 - away
```

## Specifications 

### 1. Use an array of structs to store the words and their counts 
There is an unknown number of words in the file. You will store each unique word and its count (the number of times it occurs in the document). Because of this, you will need to store these words in a dynamically sized array of structs. The struct must be defined as follows: 

```
struct wordRecord { 
    string word; 
    int count; 
};
```

### 2. Use the array-doubling algorithm to increase the size of your array 

Your array will need to grow to fit the number of words in the file. **Start with an array size of 100**, and double the size whenever the array runs out of free space. You will need to allocate your array dynamically and copy values from the old array to the new array. (Array-doubling algorithm should be implemented in *main()* function). 

**Note:** Don’t use the built-in `std::vector` class. This will result in a loss of points. You’re actually writing the code that the built-in vector uses behind-the-scenes! 

### 3. Ignore the top 50 most common words that are read in from the second file 

To get useful information about word frequency, we will be ignoring the 50 most common words in the English language. These words will be read in from a file, whose name is the third command line argument. 

### 4. Take three command line arguments 

Your program must take three command line arguments - a number *N* which tells your program the starting index to print the next 10 most frequent words, the name of the text file to be read and analyzed, and the name of the text file with the words that should be ignored. 

### 5. Output the Next 10 most frequent words starting from index N 

Your program should print out the next 10 most frequent words - not including the common words - starting index *N* in the text where *N* is passed in as a command line argument. 
E.g. If N=5 then print words from index 5-14 in the array sorted in decreasing order of the probabilities of the occurrence of the words. 

*Notes on sorting:* 
* ***You are not permitted to use any library functions (i.e. `sort` from the `<algorithm>` library)***
* *One of the easiest sorting algorithms to implement is the Bubble Sort. It is also one of the slowest, but since we are not dealing with very large data files here, you can use it for your solution. See section 4.1 in your **Visualizing Data Structures** textbook for reference.*
* *Some words will have equal probabilities of occurance. Your sorting algorithm should use alphabetical (lexicographical) ordering as the tie breaker. See output example below where all ten words have probabilies of 0.00496, so they are ordered alphabetically. Your sorting algorithm can take a "second pass" through the array to resolve such ties.*

### 6. Format your final output this way:
```
Array doubled: <Number of times the array was doubled> 
# 
Unique non-common words: <Unique non-common words> 
# 
Total non-common words: <Total non-common words> 
# 
Probability of next 10 words from rank <N> 
--------------------------------------- 
<Nth highest probability> - <corresponding word> 
<N+1 th highest probability> - <corresponding word> 
... 
<N+9 th highest probability> - <corresponding word>
```

For example, using the command: 
`./run_app_1 25 ../tests/mobyshort.txt ../tests/ignoreWords.txt`

you should get the output:
```
Array doubled: 2
Distinct non-common words: 308
Total non-common words: 403
Probability of next 10 words from rank 25
---------------------------------------
0.00496 - every
0.00496 - first
0.00496 - glory
0.00496 - going
0.00496 - grow
0.00496 - healthy
0.00496 - here
0.00496 - like
0.00496 - meaning
0.00496 - miles
```

### 7. You must include the following functions (they will be tested by the autograder):

**a. In your main function in `./app_1/main_1.cpp`**

i. If the correct number of command line arguments is not passed, print the below statement and exit the program
```
std::cout << "Usage: Assignment2Solution <number of words> 
<inputfilename.txt> <ignoreWordsfilename.txt>" << std::endl;
```

ii. Get stop-words/common-words from `ignoreWords.txt` and store them in an array (Call your **getIgnoreWords** function) 

iii. Array-doubling should be done in the *main()* function 

iv. Read words from `Tom_Sawyer.txt` and store all unique words that are not ignore-words in an array of structs 

1. Create a dynamic `wordRecord` array of size 100
2. Add non-ignore words to the array (double the array size if array is full)
3. Keep track of the number of times the `wordRecord` array is doubled and the number of unique non-ignore words 

**b. In `./code_1/array_double.cpp`**
```
void getIgnoreWords(const char *ignoreWordFileName, string ignoreWords[]);
```

This function should read the words to be ignored from the file with the name stored in `ignoreWordFileName` and store them in the `ignoreWords` array. You can assume there will be exactly 50 stop words. There is no return value. 
In case the file fails to open, print an error message using the below cout statement:
```
std::cout << "Failed to open " << ignoreWordFileName << std::endl;
```

**c. In `./code_1/array_double.cpp`**
```
bool isIgnoreWord(string word, string ignoreWords[], int length);
```

This function should return whether `word` is in the `ignoreWords` array. 

**d. In `./code_1/array_double.cpp`**
```
int getTotalNumberNonIgnoreWords(wordRecord distinctWords[], int length);
```

This function should compute the total number of words in the entire document by summing up all the counts of the individual unique words. The function should return this sum. 

**e. In `./code_1/array_double.cpp`**
```
void sortArray(wordRecord distinctWords[], int length);
```

This function should sort the `distinctWords` array (which contains `length` initialized elements) by word count such that the most frequent words are sorted to the beginning. The function does not return anything. 

**f. In `./code_1/array_double.cpp`**
```
void printTenFromN(wordRecord distinctWords[], int N, int totalNumWords);
```

This function should print the next 10 words after the starting index N from **sorted** array of `distinctWords`. These 10 words should be printed with their probability of occurrence **up to 5 decimal places**. The exact format of this printing is given below . The function does not return anything. 

Probability of occurrence of a word at position *ind* in the array is computed using the formula: **(Don’t forget to cast to float!)**
```
probability-of-occurrence = (float) uniqueWords[ind].count / totalNumWords
```

Output format:
```
Probability of next 10 words from rank 25 
--------------------------------------- 
0.0033 - little 
0.0033 - more 
0.0032 - into 
0.0032 - see 
0.0032 - over 
0.0031 - joe 
0.0030 - never 
0.0030 - know 
0.0030 - away 
0.0030 - again
```

### 8. Submitting your code:
Write your code and push the changes to your private repository. Log onto Canvas and go to Assignment 2. Paste your GitHub repository link and submit.





