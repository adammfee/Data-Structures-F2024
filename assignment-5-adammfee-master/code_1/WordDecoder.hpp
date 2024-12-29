#ifndef DECODEWORDS_H__
#define DECODEWORDS_H__
#include <iostream>


struct Letter
{
    std::string letter;
    Letter* next;
};

class WordDecoder
{
private:
  Letter* stackHead; // pointer to the top of the stack

public:
  WordDecoder();
  ~WordDecoder();
  bool isEmpty();
  void push(std::string word);
  void pop();
  Letter* peek();
  Letter* getStackHead() { return stackHead; }
  void evaluate(std::string* s, int size);
};
#endif