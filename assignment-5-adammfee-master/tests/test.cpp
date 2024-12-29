// If you change anything in this file, your changes will be ignored 
// in your homework submission.
// Chekout TEST_F functions bellow to learn what is being tested.
#include <gtest/gtest.h>
// #include "../code_1/<HEADER FILE>.hpp"

#include <fstream>
#include <iostream>
#include <string>
#include <cmath>
#include <array>
#include <vector>
#include "test_helpers.hpp"

using namespace std;

class test_x : public ::testing::Test {
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

double test_x::total_grade = 0;
double test_x::max_grade = 100;







/////////////////////////////////////////
// Tests start here
/////////////////////////////////////////
TEST_F(test_x, TestPush)
{
    string result, expected;
    string arr[6] = {"(", "a", "b", "c", "d", ")"};
    int len = 6;
    result = test_push(arr,  len);
    expected= "Print stack from top to bottom:\n)\nd\nc\nb\na\n(\n";
    ASSERT_EQ(expected, result);
    add_points_to_grade(4);
}

TEST_F(test_x, TestPop)
{
    string result, expected;
    string arr[6] = {"(", "a", "b", "c", "d", ")"};
    int len = 6;
    result = test_pop(arr,  len);
    expected= "Print stack from top to bottom:\n)\nd\nc\nb\na\n(\n";
    ASSERT_EQ(expected, result);
    add_points_to_grade(4);
}

TEST_F(test_x, TestPeek)
{
    string result, expected;
    string arr[6] = {"(", "a", "b", "c", "d", ")"};
    int len = 6;
    result = test_peek(arr,  len);
    expected= "Print stack from top to bottom:\n)\nd\nc\nb\na\n(\n";
    ASSERT_EQ(expected, result);
    add_points_to_grade(4);
}

TEST_F(test_x, TestAll)
{
    string result, expected;
    string arr[6] = {"(", "a", "b", "c", "d", ")"};
    int len = 6;
    result = test_all(arr,  len);
    expected= "push: (\npush: a\npoping thrice \nStack empty, cannot pop a letter.\npush: b\npush: c\npush: d\npush: )\nPrint stack from top to bottom:\n)\nd\nc\nb\n";
    ASSERT_EQ(expected, result);
    add_points_to_grade(3);
}


TEST_F(test_x, TestEvaluate){
    string result, expected;
    
    string s1[5] = {"(", "x", "y", "z", ")"};
    int len1 = 5;
    result = test_evaluate(s1,len1);
    expected= "The decoded word: zyx\n";
    ASSERT_EQ(expected, result);
    add_points_to_grade(4);
    
    string s2[8] = {"(","(","o","d", ")","o", "g", ")"};
    int len2 = 8;
    result = test_evaluate(s2,len2);
    expected = "The decoded word: good\n";
    ASSERT_EQ(expected, result);
    add_points_to_grade(6);
    
    string s3[13] = {"(","n","i","(","s","u", "(","a" ,"t", "s",")", ")", ")"};
    int len3 = 13;
    result = test_evaluate(s3,len3);
    expected = "The decoded word: sustain\n";
    ASSERT_EQ(expected, result);
    add_points_to_grade(6);
    
    string s4[14] = {"(","s","e","(","a","m","(","l","p",")",")","x","e",")"};
    int len4 = 14;
    result = test_evaluate(s4,len4);
    expected = "The decoded word: examples\n";
    ASSERT_EQ(expected, result);
    add_points_to_grade(6);
    
    string s5[5] = {"f","(","y","l",")"};
    int len5 = 5;
    result = test_evaluate(s5,len5);
    expected = "The decoded word: fly\n";
    ASSERT_EQ(expected, result);
    add_points_to_grade(4);

}

TEST_F(test_x, TestStackCalMain)
{
    string desired = "Enter the encoded word separated by '(' and ')'\n#>The decoded word: sustain\n";
    string resp = exec("./run_app_1 ../tests/stack_cal_main/input1.txt");
    ASSERT_EQ(desired, resp);
    add_points_to_grade(3);
    
    desired = "Enter the encoded word separated by '(' and ')'\n#>Nothing to evaluate";
    resp = exec("./run_app_1 ../tests/stack_cal_main/input2.txt");
    ASSERT_EQ(desired, resp);
    add_points_to_grade(3);
    
    desired = "Enter the encoded word separated by '(' and ')'\n#>The decoded word: examples\n";
    resp = exec("./run_app_1 ../tests/stack_cal_main/input3.txt");
    ASSERT_EQ(desired, resp);
    add_points_to_grade(3);
    
}

// queue testing
TEST_F(test_x, TestConsQ)
{
    string result, expected;
    result = test_consQ();
    expected = "Correct!\n";
    ASSERT_EQ(expected, result);
    add_points_to_grade(2);
}

TEST_F(test_x, TestEnQ)
{
    string result, expected;
    
    int len = 4;
    result = test_enQ("course",  len);
    expected= "Print queue from front to back:\ncourse0\ncourse1\ncourse2\ncourse3\n";
    ASSERT_EQ(expected, result);
    add_points_to_grade(2);
    
    len = 21;
    result = test_enQ("course",  len);
    expected= "Print queue from front to back:\ncourse0\ncourse1\ncourse2\ncourse3\ncourse4\ncourse5\ncourse6\ncourse7\ncourse8\ncourse9\ncourse10\ncourse11\ncourse12\ncourse13\ncourse14\ncourse15\ncourse16\ncourse17\ncourse18\ncourse19\ncourse20\n";
    ASSERT_EQ(expected, result);
    add_points_to_grade(2);
}

TEST_F(test_x, TestDeQ)
{
    string result, expected;
    
    int len = 4;
    result = test_deQ("course",  len, 3);
    expected= "dequeuing 3 times\nPrint queue from front to back:\ncourse3\n";
    ASSERT_EQ(expected, result);
    add_points_to_grade(2);
    
    
    len = 4;
    result = test_deQ("course", len, 5);
    expected= "dequeuing 5 times\nWaitlist is empty. Cannot dequeue.\n";
    ASSERT_EQ(expected, result);
    add_points_to_grade(2);
}

TEST_F(test_x, TestPeekQ)
{
    string result, expected;
    
    int len = 0;
    int dq = 0;
    result = test_peekQ("course",  len, dq);
    expected= "enqueuing 0 elements\ndequeuing 0 times\npeeking in the queue\n<EMPTY QUEUE>\n";
    ASSERT_EQ(expected, result);
    add_points_to_grade(2);
    
    
    len = 4;
    result = test_peekQ("course",  len, 3);
    expected= "enqueuing 4 elements\ndequeuing 3 times\npeeking in the queue\nFront of the queue: course3\n";
    ASSERT_EQ(expected, result);
    add_points_to_grade(2);
    
    len = 4;
    result = test_peekQ("course",  len, 5);
    expected= "enqueuing 4 elements\ndequeuing 5 times\nWaitlist is empty. Cannot dequeue.\npeeking in the queue\n<EMPTY QUEUE>\n";
    ASSERT_EQ(expected, result);
    add_points_to_grade(2);
}

TEST_F(test_x, TestAllQ)
{
    //enQ2 deQ2
    string result, expected;
    string seq1[] = {"E","E","D","D", "P"};
    int len1 = 5;
    result = test_allQ("course",seq1, len1);
    expected = "Enqueue(course0)\nEnqueue(course1)\nDequeue\nDequeue\nPeek\n<EMPTY QUEUE>\nQueue is full? false\nQueue is empty? true\nQueue size: 0\nQueue front index: -1\nQueue back index: -1\n";
    ASSERT_EQ(expected, result);
    add_points_to_grade(4);
    
    //enQ20 deQ10 enQ7
    string seq2[] = {"E","E","E","E","E","E","E","E","E","E","E","E","E","E","E","E","E","E","E","E","D","D","D","D","D","D","D","D","D","D","E","E","E","E","E","E","E"};
    int len2 = 37;
    result = test_allQ("course", seq2, len2);
    expected = "Enqueue(course0)\nEnqueue(course1)\nEnqueue(course2)\nEnqueue(course3)\nEnqueue(course4)\nEnqueue(course5)\nEnqueue(course6)\nEnqueue(course7)\nEnqueue(course8)\nEnqueue(course9)\nEnqueue(course10)\nEnqueue(course11)\nEnqueue(course12)\nEnqueue(course13)\nEnqueue(course14)\nEnqueue(course15)\nEnqueue(course16)\nEnqueue(course17)\nEnqueue(course18)\nEnqueue(course19)\nDequeue\nDequeue\nDequeue\nDequeue\nDequeue\nDequeue\nDequeue\nDequeue\nDequeue\nDequeue\nEnqueue(course20)\nEnqueue(course21)\nEnqueue(course22)\nEnqueue(course23)\nEnqueue(course24)\nEnqueue(course25)\nEnqueue(course26)\nQueue is full? false\nQueue is empty? false\nQueue size: 17\nQueue front index: 10\nQueue back index: 26\n";
    ASSERT_EQ(expected, result);
    add_points_to_grade(4);
    
     //enQ20 deQ10 enQ10
    string seq3[] = {"E","E","E","E","E","E","E","E","E","E","E","E","E","E","E","E","E","E","E","E","D","D","D","D","D","D","D","D","D","D","E","E","E","E","E","E","E","E","E","E"};
    int len3 = 40;
    result = test_allQ("course",seq3, len3);
    expected = "Enqueue(course0)\nEnqueue(course1)\nEnqueue(course2)\nEnqueue(course3)\nEnqueue(course4)\nEnqueue(course5)\nEnqueue(course6)\nEnqueue(course7)\nEnqueue(course8)\nEnqueue(course9)\nEnqueue(course10)\nEnqueue(course11)\nEnqueue(course12)\nEnqueue(course13)\nEnqueue(course14)\nEnqueue(course15)\nEnqueue(course16)\nEnqueue(course17)\nEnqueue(course18)\nEnqueue(course19)\nDequeue\nDequeue\nDequeue\nDequeue\nDequeue\nDequeue\nDequeue\nDequeue\nDequeue\nDequeue\nEnqueue(course20)\nEnqueue(course21)\nEnqueue(course22)\nEnqueue(course23)\nEnqueue(course24)\nEnqueue(course25)\nEnqueue(course26)\nEnqueue(course27)\nEnqueue(course28)\nEnqueue(course29)\nQueue is full? false\nQueue is empty? false\nQueue size: 20\nQueue front index: 10\nQueue back index: 29\n";
    ASSERT_EQ(expected, result);
    add_points_to_grade(4);
    
    //enQ20 deQ10 enQ10 deQ20
    string seq4[] = {"E","E","E","E","E","E","E","E","E","E","E","E","E","E","E","E","E","E","E","E","D","D","D","D","D","D","D","D","D","D","E","E","E","E","E","E","E","E","E","E","D","D","D","D","D","D","D","D","D","D","D","D","D","D","D","D","D","D","D","D"};
    int len4 = 60;
    result = test_allQ("course",seq4, len4);
    expected = "Enqueue(course0)\nEnqueue(course1)\nEnqueue(course2)\nEnqueue(course3)\nEnqueue(course4)\nEnqueue(course5)\nEnqueue(course6)\nEnqueue(course7)\nEnqueue(course8)\nEnqueue(course9)\nEnqueue(course10)\nEnqueue(course11)\nEnqueue(course12)\nEnqueue(course13)\nEnqueue(course14)\nEnqueue(course15)\nEnqueue(course16)\nEnqueue(course17)\nEnqueue(course18)\nEnqueue(course19)\nDequeue\nDequeue\nDequeue\nDequeue\nDequeue\nDequeue\nDequeue\nDequeue\nDequeue\nDequeue\nEnqueue(course20)\nEnqueue(course21)\nEnqueue(course22)\nEnqueue(course23)\nEnqueue(course24)\nEnqueue(course25)\nEnqueue(course26)\nEnqueue(course27)\nEnqueue(course28)\nEnqueue(course29)\nDequeue\nDequeue\nDequeue\nDequeue\nDequeue\nDequeue\nDequeue\nDequeue\nDequeue\nDequeue\nDequeue\nDequeue\nDequeue\nDequeue\nDequeue\nDequeue\nDequeue\nDequeue\nDequeue\nDequeue\nQueue is full? false\nQueue is empty? true\nQueue size: 0\nQueue front index: -1\nQueue back index: -1\n";
    ASSERT_EQ(expected, result);
    add_points_to_grade(4);
    
    
     //enQ20 deQ9 enQ4 deQ7
    string seq5[] = {"E","E","E","E","E","E","E","E","E","E","E","E","E","E","E","E","E","E","E","E","D","D","D","D","D","D","D","D","D","E","E","E","E","D","D","D","D","D","D","D"};
    int len5 = 40;
    result = test_allQ("course",seq5, len5);
    expected = "Enqueue(course0)\nEnqueue(course1)\nEnqueue(course2)\nEnqueue(course3)\nEnqueue(course4)\nEnqueue(course5)\nEnqueue(course6)\nEnqueue(course7)\nEnqueue(course8)\nEnqueue(course9)\nEnqueue(course10)\nEnqueue(course11)\nEnqueue(course12)\nEnqueue(course13)\nEnqueue(course14)\nEnqueue(course15)\nEnqueue(course16)\nEnqueue(course17)\nEnqueue(course18)\nEnqueue(course19)\nDequeue\nDequeue\nDequeue\nDequeue\nDequeue\nDequeue\nDequeue\nDequeue\nDequeue\nEnqueue(course20)\nEnqueue(course21)\nEnqueue(course22)\nEnqueue(course23)\nDequeue\nDequeue\nDequeue\nDequeue\nDequeue\nDequeue\nDequeue\nQueue is full? false\nQueue is empty? false\nQueue size: 8\nQueue front index: 16\nQueue back index: 23\n";
    ASSERT_EQ(expected, result);
    add_points_to_grade(3);
       
}

TEST_F(test_x, TestMainQ)
{
    string desired;
    string resp;
    desired = readFileIntoString("../tests/queue_main/output1.txt");
    resp = exec("./run_app_2 5 ../tests/queue_main/input1.txt");
    ASSERT_EQ(desired, resp);
    add_points_to_grade(3.75);
    
    desired = readFileIntoString("../tests/queue_main/output2.txt");
    resp = exec("./run_app_2 5 ../tests/queue_main/input2.txt");
    ASSERT_EQ(desired, resp);
    add_points_to_grade(3.75);
    
    desired = readFileIntoString("../tests/queue_main/output3.txt");
    resp = exec("./run_app_2 5 ../tests/queue_main/input3.txt");
    ASSERT_EQ(desired, resp);
    add_points_to_grade(3.75);
    
    desired = readFileIntoString("../tests/queue_main/output4.txt");
    resp = exec("./run_app_2 5 ../tests/queue_main/input4.txt");
    ASSERT_EQ(desired, resp);
    add_points_to_grade(3.75);
}