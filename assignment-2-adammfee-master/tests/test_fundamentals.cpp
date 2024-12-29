// If you change anything in this file, your changes will be ignored 
// in your homework submission.
// Chekout TEST_F functions bellow to learn what is being tested.
#include <gtest/gtest.h>
#include "../code_1/array_double.hpp"

#include <fstream>
#include <iostream>
#include <string>
#include <cmath>
#include <array>
#include <vector>

using namespace std;

class test_arrayDouble : public ::testing::Test {
protected:
	// This function runs only once before any TEST_F function
	static void SetUpTestCase(){
		std::ofstream outgrade("./total_grade.txt");
		if(outgrade.is_open()){
			outgrade.clear();
			outgrade << (int)0;
			outgrade.close();
		}
	}

	// This function runs after all TEST_F functions have been executed
	static void TearDownTestCase(){
		std::ofstream outgrade("./total_grade.txt");
		if(outgrade.is_open()){
			outgrade.clear();
			outgrade << (int)std::ceil(100*total_grade/max_grade);
			outgrade.close();
			std::cout << "Total Grade is : " << (int)std::ceil(100*total_grade/max_grade) << std::endl;
		}
	}

	void add_points_to_grade(double points){
		if(!::testing::Test::HasFailure()){
			total_grade += points;
		}
	}

	// this function runs before every TEST_F function
	void SetUp() override {}

	// this function runs after every TEST_F function
	void TearDown() override {
		std::ofstream outgrade("./total_grade.txt");
		if(outgrade.is_open()){
			outgrade.clear();
			outgrade << (int)std::ceil(100*total_grade/max_grade);
			outgrade.close();
		}
	}
	
	static double total_grade;
	static double max_grade;
};

double test_arrayDouble::total_grade = 0;
double test_arrayDouble::max_grade = 100;

/////////////////////////////////////////
// Test Helper Functions
/////////////////////////////////////////

bool compare_arrays(string a[], string b[], int size){
  bool pass = true;
  for(int i = 0; i<size; ++i){
    if(a[i] != b[i])
      pass = false;
  }
  return pass;
}

void compare_arrays_structs(wordRecord a[], wordRecord b[], int size){
  for(int i = 0; i<size; ++i){
	  ASSERT_EQ(a[i].count, b[i].count) << "Array differs at index i=" << i;
	  ASSERT_EQ(a[i].word, b[i].word) << "Array differs at index i=" << i;
  }
  return;
}

std::string exec(const char* cmd) {
    std::array<char, 128> buffer;
    std::string result;
    std::unique_ptr<FILE, decltype(&pclose)> pipe(popen(cmd, "r"), pclose);
    if (!pipe) {
        throw std::runtime_error("popen() failed!");
    }
    while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr) {
        result += buffer.data();
    }
    return result;
}

void genStructArray(wordRecord structArray[], string stringArray[], int counts[], int l){
	for(int i = 0; i<l; i++){
		structArray[i].word = stringArray[i];
		structArray[i].count = counts[i];
	}
}

std::string readFileIntoString(std::string fileName){
	std::string line, out;
  	ifstream A;
  	A.open(fileName);
  	if(!A){throw std::runtime_error("could not open file: " + fileName);}
	while(getline(A,line)){
		out = out+line+"\n";
	}
	return out;
}

/////////////////////////////////////////
// Tests start here
/////////////////////////////////////////

// Test arrays
string array_A[] = {"the","be", "to", "of", "and", "a", "in", "that", "have", "i"}; 
string array_B[] = {"with", "he", "as", "you", "do", "at", "this", "but", "his", "by", "from", "they","we"}; 
int testArrLength_A = 10;
int testArrLength_B = 13;
int array_A_counts[] = {7, 9, 3, 8, 0, 2, 4, 8, 3, 9};
int array_B_counts[] = {0, 5, 2, 2, 7, 3, 7, 9, 0, 2, 3, 9, 9};
string array_A_sorted[] = {"be", "i", "of", "that", "the", "in", "have", "to", "a", "and"};
string array_B_sorted[] = {"but", "they", "we", "do", "this", "he", "at", "from", "as", "by", "you", "his", "with"};
int array_A_counts_sorted[] = {9, 9, 8, 8, 7, 4, 3, 3, 2, 0};
int array_B_counts_sorted[] = {9, 9, 9, 7, 7, 5, 3, 3, 2, 2, 2, 0, 0};
string array_A_print = "0.90000 - be\n0.90000 - i\n0.80000 - of\n0.80000 - that\n0.70000 - the\n0.40000 - in\n0.30000 - have\n0.30000 - to\n0.20000 - a\n0.00000 - and\n";
string array_B_print = "0.53846 - do\n0.53846 - this\n0.38462 - he\n0.23077 - at\n0.23077 - from\n0.15385 - as\n0.15385 - by\n0.15385 - you\n0.00000 - his\n0.00000 - with\n";

// Test the getIgnoreWords() function [10 POINTS]
TEST_F(test_arrayDouble, TestGetIgnoreWords){

	int arr_size = 10;
	string ignoreWordsA[arr_size]; // array for storing ignore words from file

	getIgnoreWords((char *)"../tests/ignoreWordsA.txt", ignoreWordsA);

	ASSERT_EQ(sizeof(array_A), sizeof(ignoreWordsA)) << "Array has incorrect length";
	for (int i = 0; i < arr_size; i++) {
		ASSERT_EQ(array_A[i], ignoreWordsA[i]) << "Array differs at index i=" << i;
	}
	add_points_to_grade(5);

	arr_size = 13;
	string ignoreWordsB[arr_size]; // array for storing ignore words from file

	getIgnoreWords((char *)"../tests/ignoreWordsB.txt", ignoreWordsB);

	ASSERT_EQ(sizeof(array_B), sizeof(ignoreWordsB)) << "Array has incorrect length";
	for (int i = 0; i < arr_size; i++) {
		ASSERT_EQ(array_B[i], ignoreWordsB[i]) << "Array differs at index i=" << i;
	}
	add_points_to_grade(5);

}

// Test the isIgnoreWord() function [10 POINTS]
TEST_F(test_arrayDouble, TestIsIgnoreWord){
	bool isIgnore;
	isIgnore = isIgnoreWord("thunder", array_A, 10);
	ASSERT_EQ(false, isIgnore);
	add_points_to_grade(2);

	isIgnore = isIgnoreWord("the", array_A, 10);
	ASSERT_EQ(true, isIgnore);
	add_points_to_grade(2);

	isIgnore = isIgnoreWord("his", array_B, 13);
	ASSERT_EQ(true, isIgnore);
	add_points_to_grade(2);

	isIgnore = isIgnoreWord("we", array_B, 13);
	ASSERT_EQ(true, isIgnore);
	add_points_to_grade(2);

	isIgnore = isIgnoreWord("his", array_A, 10);
	ASSERT_EQ(false, isIgnore);
	add_points_to_grade(2);
}

// Test the getTotalNumberOfIgnoreWords() function [10 POINTS]
// Is this getTotalNumberOfIgnoreWords or getTotalNumberNonIgnoreWords
TEST_F(test_arrayDouble, TestGetTotalNumberOfIgnoreWords){
	// Generate an array of structs
	wordRecord testArr_A[testArrLength_A];
	genStructArray(testArr_A, array_A, array_A_counts, testArrLength_A);
	// Test the function:
	int testA = getTotalNumberNonIgnoreWords(testArr_A, testArrLength_A);
	ASSERT_EQ(testA, 53);
	add_points_to_grade(5);

	// Generate an array of structs
	wordRecord testArr_B[testArrLength_B];
	genStructArray(testArr_B, array_B, array_B_counts, testArrLength_B);
	// Test the function:
	int testB = getTotalNumberNonIgnoreWords(testArr_B, testArrLength_B);
	ASSERT_EQ(testB, 58);
	add_points_to_grade(5);
}

// Test the sortArray() function [10 POINTS]
TEST_F(test_arrayDouble, TestSortArray){
	// Generate an unsorted array of structs:
	wordRecord testArr_A[testArrLength_A];
	genStructArray(testArr_A, array_A, array_A_counts, testArrLength_A);
	// Sort the array to test if sortArray() is working
	sortArray(testArr_A,testArrLength_A);
	// Generate the correctly sorted array of structs:
	wordRecord sortedArrayOfStructs_A[testArrLength_A];
	genStructArray(sortedArrayOfStructs_A, array_A_sorted, array_A_counts_sorted, testArrLength_A);
	// Compare the two arrays:
	ASSERT_EQ(sizeof(testArr_A), sizeof(sortedArrayOfStructs_A)) << "Array has incorrect length";
	compare_arrays_structs(testArr_A, sortedArrayOfStructs_A, testArrLength_A);
	add_points_to_grade(5);

	// Generate an unsorted array of structs:
	wordRecord testArr_B[testArrLength_B];
	genStructArray(testArr_B, array_B, array_B_counts, testArrLength_B);
	// Sort the array to test if sortArray() is working
	sortArray(testArr_B,testArrLength_B);		
	// Generate the correctly sorted array of structs:
	wordRecord sortedArrayOfStructs_B[testArrLength_B];
	genStructArray(sortedArrayOfStructs_B, array_B_sorted, array_B_counts_sorted, testArrLength_B);
	// Compare the two arrays:
	ASSERT_EQ(sizeof(testArr_B), sizeof(sortedArrayOfStructs_B)) << "Array has incorrect length";
	compare_arrays_structs(testArr_B, sortedArrayOfStructs_B, testArrLength_B);
	add_points_to_grade(5);
}

// Test the printeTenFromN() function [10 POINTS]
TEST_F(test_arrayDouble, TestPrintTenFromN){
	// Generate the correctly sorted array of structs:
	wordRecord sortedArrayOfStructs_A[testArrLength_A];
	genStructArray(sortedArrayOfStructs_A, array_A_sorted, array_A_counts_sorted, testArrLength_A);
	// Use the following to redirect the standard output
	testing::internal::CaptureStdout();
	// Call the function
	printTenFromN(sortedArrayOfStructs_A, 0, testArrLength_A);
	// Record the functions std output to a string variable
	string output = testing::internal::GetCapturedStdout();
	ASSERT_EQ(output, array_A_print);
	add_points_to_grade(5);

	// Generate the correctly sorted array of structs:
	wordRecord sortedArrayOfStructs_B[testArrLength_B];
	genStructArray(sortedArrayOfStructs_B, array_B_sorted, array_B_counts_sorted, testArrLength_B);
	// Use the following to redirect the standard output
	testing::internal::CaptureStdout();
	// Call the function
	printTenFromN(sortedArrayOfStructs_B, 3, testArrLength_B);
	// Record the functions std output to a string variable
	output = testing::internal::GetCapturedStdout();
	ASSERT_EQ(output, array_B_print);
	add_points_to_grade(5);
	
}

// Test the entire program [50 POINTS]
TEST_F(test_arrayDouble, TestApp_1){
	string desired = readFileIntoString("../tests/expected_1_1.txt");
	string resp = exec("./run_app_1 25 ../tests/mobyshort.txt ../tests/ignoreWords.txt");
	ASSERT_EQ(desired, resp);
  	add_points_to_grade(12.5);

	desired = readFileIntoString("../tests/expected_1_2.txt");
	resp = exec("./run_app_1 0 ../tests/mobyshort.txt ../tests/ignoreWords.txt");
	ASSERT_EQ(desired, resp);
  	add_points_to_grade(12.5);

	desired = readFileIntoString("../tests/expected_1_3.txt");
	resp = exec("./run_app_1 0 ../tests/hunger_games_short.txt ../tests/ignoreWords.txt");
	ASSERT_EQ(desired, resp);
  	add_points_to_grade(12.5);

	desired = readFileIntoString("../tests/expected_1_4.txt");
	resp = exec("./run_app_1 5 ../tests/mobydick.txt ../tests/ignoreWords.txt");
	ASSERT_EQ(desired, resp);
  	add_points_to_grade(12.5);
}
