#include<iostream>
#include<cmath>
#include<iomanip>
#include "../code_1/WordDecoder.hpp"

using namespace std;



int main(int argc, char* argv[])
{
    // DO NOT MODIFY THIS.
    if(argc>1)
    {
         freopen(argv[1],"r",stdin);
    }

    /* TODO- 
              1. cout #>
              2. get the user input
              3. store them in an array
              4. If the array is empty then print "Nothing to evaluate"
                 else call the evaluate function
    */
    WordDecoder func;
    string input;

    cout << "Enter the encoded word separated by '(' and ')'" << endl << "#>";
    getline(cin, input);

    if (input.empty()) {
        cout << "Nothing to evaluate";
        return 0;
    }

    int size = input.size();
    string* inputArr = new string[size];

    for (int i = 0; i < size; i++) {
        inputArr[i] = string(1, input[i]);
    }

    func.evaluate(inputArr, size);

    delete[] inputArr;

    return 0;
}