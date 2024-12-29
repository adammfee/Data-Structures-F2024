#include <iostream>
#include "WordDecoder.hpp"
#include <vector>

using namespace std;


WordDecoder::WordDecoder()
{
    // TODO. Initialize all variables required
    stackHead = nullptr;
}

WordDecoder::~WordDecoder()
{
    //TODO. Free up to avoid memory leaks
    Letter* toDelete = nullptr;
    Letter* temp = stackHead;
    while (temp != nullptr) {
        toDelete = temp;
        temp = temp->next;
        delete toDelete;
    }
}

bool WordDecoder::isEmpty()
{
    // TODO. Checking if stack is empty
    if (stackHead != nullptr) {
        return false;
    }
    return true;
}

void WordDecoder::push(string letter)
{
    //TODO Perform push operation stack
    Letter* temp = new Letter();
    temp->letter = letter;

    temp->next = stackHead;
    stackHead = temp;
}

void WordDecoder::pop()
{
    //TODO Perform pop operation stack
    if (stackHead == nullptr) {
        cout << "Stack empty, cannot pop a letter." << endl;
        return;
    } else {
        Letter* temp = stackHead;
        stackHead = stackHead->next;
        delete temp;
    }
}

Letter* WordDecoder::peek()
{
    //TODO Perform peek operation stack
    if (stackHead == nullptr) {
        cout << "Stack empty, cannot pop a letter." << endl;
        return nullptr;
    } else {
        return stackHead;
    }
    return nullptr;
}

void WordDecoder::evaluate(string* s, int size)
{
    /* TODO:
    1. Push to stack if letter in string not a ")"
    2. If ")" comes, then pop until "(", store somewhere. Put letters back to the stack in reverse order of pop.
    3. Finally, the elements are stored in reverse, so print in reverse order. */
    cout << "The decoded word: ";

    for (int i = 0; i < size; i++) {
        if (s[i] != ")") {
            push(s[i]);
        } else {
            string tempWord = "";
            while (!isEmpty() && peek()->letter != "(") {
                tempWord += peek()->letter;
                pop();
            }

            if (!isEmpty() && peek()->letter == "(") {
                pop();
            }

            for (int j = 0; j < tempWord.size(); j++) {
                string str(1, tempWord[j]);
                push(str);
            }
        }
    }

    string decodedWord = "";
    while (!isEmpty()) {
        decodedWord = peek()->letter + decodedWord;
        pop();
    }

    cout << decodedWord << endl;
}