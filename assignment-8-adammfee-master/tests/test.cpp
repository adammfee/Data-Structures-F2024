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
#include "../code_1/Graph.hpp"

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

TEST_F(test_x, AddVertex){
    string result;
    string expected;
    
    string names[] = {"ATLS", "EC", "AERO", "CHEM", "DUAN", "FLMG"};
    int len = 6;
    result = test_addVertex(names,len);
    expected = "[GRADER] Adding:ATLS\n[GRADER] Adding:EC\n[GRADER] Adding:AERO\n[GRADER] Adding:CHEM\n[GRADER] Adding:DUAN\n[GRADER] Adding:FLMG\nadded vertices are:\nATLS\nEC\nAERO\nCHEM\nDUAN\nFLMG\n";
    ASSERT_EQ(expected, result);
    add_points_to_grade(3);
    
    
    string names1[] = {"ATLS", "EC", "AERO", "CHEM", "DUAN", "FLMG", "AERO", "CHEM"};
    int len1 = 8;
    result = test_addVertex(names1,len1);
    expected = "[GRADER] Adding:ATLS\n[GRADER] Adding:EC\n[GRADER] Adding:AERO\n[GRADER] Adding:CHEM\n[GRADER] Adding:DUAN\n[GRADER] Adding:FLMG\n[GRADER] Adding:AERO\nAERO found.\n[GRADER] Adding:CHEM\nCHEM found.\nadded vertices are:\nATLS\nEC\nAERO\nCHEM\nDUAN\nFLMG\n";
    ASSERT_EQ(expected, result);
    add_points_to_grade(3);
    
    string names2[] = {};
    int len2 = 0;
    result = test_addVertex(names2,len2);
    expected = "added vertices are:\n";
    ASSERT_EQ(expected, result);
    add_points_to_grade(3);
    
    string names3[] = {"CHEM"};
    int len3 = 1;
    result = test_addVertex(names3,len3);
    expected =  "[GRADER] Adding:CHEM\nadded vertices are:\nCHEM\n";
    ASSERT_EQ(expected, result);
    add_points_to_grade(1);
}



TEST_F(test_x, AddShowEdge){
    string result;
    string expected;
    
    string names[] = {"ATLS", "EC", "AERO", "CHEM", "DUAN", "FLMG"};
    int len = 6;
    string edges[] = {"ATLS-->EC", "ATLS-->AERO", "CHEM-->DUAN" };
    int elen = 3;
    result = test_addShowEdge(names,len, edges, elen);
    expected = "[GRADER] Adding Vertex:ATLS\n[GRADER] Adding Vertex:EC\n[GRADER] Adding Vertex:AERO\n[GRADER] Adding Vertex:CHEM\n[GRADER] Adding Vertex:DUAN\n[GRADER] Adding Vertex:FLMG\n[GRADER] Adding edge between: ATLS   EC\n[GRADER] Adding edge between: ATLS   AERO\n[GRADER] Adding edge between: CHEM   DUAN\nATLS --> EC AERO \nEC --> ATLS \nAERO --> ATLS \nCHEM --> DUAN \nDUAN --> CHEM \nFLMG --> \n";
    ASSERT_EQ(expected, result);
    add_points_to_grade(5);
    
    
    string names1[] = {"ATLS", "EC", "AERO", "CHEM", "DUAN", "FLMG"};
    int len1 = 6;
    string edges1[] = {"ATLS-->EC", "ATLS-->ENG", "ENG-->DUAN" };
    int elen1 = 3;
    result = test_addShowEdge(names1,len1, edges1, elen1);
    expected = "[GRADER] Adding Vertex:ATLS\n[GRADER] Adding Vertex:EC\n[GRADER] Adding Vertex:AERO\n[GRADER] Adding Vertex:CHEM\n[GRADER] Adding Vertex:DUAN\n[GRADER] Adding Vertex:FLMG\n[GRADER] Adding edge between: ATLS   EC\n[GRADER] Adding edge between: ATLS   ENG\n[GRADER] Adding edge between: ENG   DUAN\nATLS --> EC \nEC --> ATLS \nAERO --> \nCHEM --> \nDUAN --> \nFLMG --> \n";
    ASSERT_EQ(expected, result);
    add_points_to_grade(5);
    
    string names2[] = {"ATLS", "EC", "AERO", "CHEM", "DUAN", "FLMG"};
    int len2 = 6;
    string edges2[] = {"ATLS-->ATLS", "EC-->EC", "FLMG-->DUAN" };
    int elen2 = 3;
    result = test_addShowEdge(names2,len2, edges2, elen2);
    expected ="[GRADER] Adding Vertex:ATLS\n[GRADER] Adding Vertex:EC\n[GRADER] Adding Vertex:AERO\n[GRADER] Adding Vertex:CHEM\n[GRADER] Adding Vertex:DUAN\n[GRADER] Adding Vertex:FLMG\n[GRADER] Adding edge between: ATLS   ATLS\n[GRADER] Adding edge between: EC   EC\n[GRADER] Adding edge between: FLMG   DUAN\nATLS --> \nEC --> \nAERO --> \nCHEM --> \nDUAN --> FLMG \nFLMG --> DUAN \n";
    ASSERT_EQ(expected, result);
    add_points_to_grade(5);
    
    
    string names3[] = {"ATLS", "EC", "AERO", "CHEM", "DUAN", "FLMG", "HLMS", "UMC", "REC"};
    int len3 = 9;
    string edges3[] = {"ATLS-->AERO", "EC-->AERO", "FLMG-->DUAN", "ATLS-->DUAN", "EC-->FLMG", "HLMS-->UMC", "UMC-->REC"};
    int elen3 = 7;
    result = test_addShowEdge(names3,len3, edges3, elen3);
    expected ="[GRADER] Adding Vertex:ATLS\n[GRADER] Adding Vertex:EC\n[GRADER] Adding Vertex:AERO\n[GRADER] Adding Vertex:CHEM\n[GRADER] Adding Vertex:DUAN\n[GRADER] Adding Vertex:FLMG\n[GRADER] Adding Vertex:HLMS\n[GRADER] Adding Vertex:UMC\n[GRADER] Adding Vertex:REC\n[GRADER] Adding edge between: ATLS   AERO\n[GRADER] Adding edge between: EC   AERO\n[GRADER] Adding edge between: FLMG   DUAN\n[GRADER] Adding edge between: ATLS   DUAN\n[GRADER] Adding edge between: EC   FLMG\n[GRADER] Adding edge between: HLMS   UMC\n[GRADER] Adding edge between: UMC   REC\nATLS --> AERO DUAN \nEC --> AERO FLMG \nAERO --> ATLS EC \nCHEM --> \nDUAN --> FLMG ATLS \nFLMG --> DUAN EC \nHLMS --> UMC \nUMC --> HLMS REC \nREC --> UMC \n";
    ASSERT_EQ(expected, result);
    add_points_to_grade(5);
}



TEST_F(test_x, test_bfs){
    string result;
    string expected;
    
    string names[] = {"ATLS", "EC", "AERO", "CHEM", "DUAN", "FLMG"};
    int len = 6;
    string edges[] = {"ATLS-->EC", "ATLS-->AERO", "CHEM-->DUAN", "AERO-->CHEM"};
    int elen = 4;
    result = test_bfs(names,len, edges, elen, "ATLS");
    expected = "[GRADER] Adding Vertex:ATLS\n[GRADER] Adding Vertex:EC\n[GRADER] Adding Vertex:AERO\n[GRADER] Adding Vertex:CHEM\n[GRADER] Adding Vertex:DUAN\n[GRADER] Adding Vertex:FLMG\n[GRADER] Adding edge between: ATLS   EC\n[GRADER] Adding edge between: ATLS   AERO\n[GRADER] Adding edge between: CHEM   DUAN\n[GRADER] Adding edge between: AERO   CHEM\nATLS --> EC AERO \nEC --> ATLS \nAERO --> ATLS CHEM \nCHEM --> DUAN AERO \nDUAN --> CHEM \nFLMG --> \nStarting vertex (root): ATLS-> EC(1) AERO(1) CHEM(2) DUAN(3) \n\n";
    ASSERT_EQ(expected, result);
    add_points_to_grade(10);
    
    
    result = test_bfs(names,len, edges, elen, "AERO");
    expected = "[GRADER] Adding Vertex:ATLS\n[GRADER] Adding Vertex:EC\n[GRADER] Adding Vertex:AERO\n[GRADER] Adding Vertex:CHEM\n[GRADER] Adding Vertex:DUAN\n[GRADER] Adding Vertex:FLMG\n[GRADER] Adding edge between: ATLS   EC\n[GRADER] Adding edge between: ATLS   AERO\n[GRADER] Adding edge between: CHEM   DUAN\n[GRADER] Adding edge between: AERO   CHEM\nATLS --> EC AERO \nEC --> ATLS \nAERO --> ATLS CHEM \nCHEM --> DUAN AERO \nDUAN --> CHEM \nFLMG --> \nStarting vertex (root): AERO-> ATLS(1) CHEM(1) EC(2) DUAN(2) \n\n";
    ASSERT_EQ(expected, result);
    add_points_to_grade(10);
    
    result = test_bfs(names,len, edges, elen, "FLMG");
    expected = "[GRADER] Adding Vertex:ATLS\n[GRADER] Adding Vertex:EC\n[GRADER] Adding Vertex:AERO\n[GRADER] Adding Vertex:CHEM\n[GRADER] Adding Vertex:DUAN\n[GRADER] Adding Vertex:FLMG\n[GRADER] Adding edge between: ATLS   EC\n[GRADER] Adding edge between: ATLS   AERO\n[GRADER] Adding edge between: CHEM   DUAN\n[GRADER] Adding edge between: AERO   CHEM\nATLS --> EC AERO \nEC --> ATLS \nAERO --> ATLS CHEM \nCHEM --> DUAN AERO \nDUAN --> CHEM \nFLMG --> \nStarting vertex (root): FLMG-> \n\n";
    ASSERT_EQ(expected, result);
    add_points_to_grade(5);
    
    
    
    string names1[] = {"ATLS", "EC", "AERO", "CHEM", "DUAN", "FLMG"};
    int len1 = 6;
    string edges1[] = {"ATLS-->EC", "ATLS-->AERO", "CHEM-->DUAN", "FLMG-->CHEM"};
    int elen1 = 4;
    result = test_bfs(names1,len1, edges1, elen1, "DUAN");
    expected = "[GRADER] Adding Vertex:ATLS\n[GRADER] Adding Vertex:EC\n[GRADER] Adding Vertex:AERO\n[GRADER] Adding Vertex:CHEM\n[GRADER] Adding Vertex:DUAN\n[GRADER] Adding Vertex:FLMG\n[GRADER] Adding edge between: ATLS   EC\n[GRADER] Adding edge between: ATLS   AERO\n[GRADER] Adding edge between: CHEM   DUAN\n[GRADER] Adding edge between: FLMG   CHEM\nATLS --> EC AERO \nEC --> ATLS \nAERO --> ATLS \nCHEM --> DUAN FLMG \nDUAN --> CHEM \nFLMG --> CHEM \nStarting vertex (root): DUAN-> CHEM(1) FLMG(2) \n\n";
    ASSERT_EQ(expected, result);
    add_points_to_grade(10);
}


TEST_F(test_x, test_shortestpath){
    string result;
    string expected;
    
    string names[] = {"ATLS", "EC", "AERO", "CHEM", "DUAN", "FLMG"};
    int len = 6;
    string edges[] = {"ATLS-->EC", "ATLS-->AERO", "CHEM-->DUAN", "AERO-->CHEM"};
    int elen = 4;
    string source = "ATLS";
    string dest = "DUAN";
    result = test_shortestpath(names,len, edges, elen, source, dest);
    expected = "[GRADER] Adding Vertex:ATLS\n[GRADER] Adding Vertex:EC\n[GRADER] Adding Vertex:AERO\n[GRADER] Adding Vertex:CHEM\n[GRADER] Adding Vertex:DUAN\n[GRADER] Adding Vertex:FLMG\n[GRADER] Adding edge between: ATLS   EC\n[GRADER] Adding edge between: ATLS   AERO\n[GRADER] Adding edge between: CHEM   DUAN\n[GRADER] Adding edge between: AERO   CHEM\nATLS --> EC AERO \nEC --> ATLS \nAERO --> ATLS CHEM \nCHEM --> DUAN AERO \nDUAN --> CHEM \nFLMG --> \nDUAN\nCHEM\nAERO\nATLS\nShortest Path Distance: 3\n";
    ASSERT_EQ(expected, result);
    add_points_to_grade(10);
    
    
    string names1[] = {"ATLS", "EC", "AERO", "CHEM", "DUAN", "FLMG"};
    int len1 = 6;
    string edges1[] = {"ATLS-->EC", "ATLS-->AERO", "CHEM-->DUAN", "AERO-->CHEM", "CHEM-->FLMG", "ATLS-->FLMG"};
    int elen1 = 6;
    string source1 = "EC";
    string dest1 = "CHEM";
    result = test_shortestpath(names1,len1, edges1, elen1, source1, dest1);
    expected ="[GRADER] Adding Vertex:ATLS\n[GRADER] Adding Vertex:EC\n[GRADER] Adding Vertex:AERO\n[GRADER] Adding Vertex:CHEM\n[GRADER] Adding Vertex:DUAN\n[GRADER] Adding Vertex:FLMG\n[GRADER] Adding edge between: ATLS   EC\n[GRADER] Adding edge between: ATLS   AERO\n[GRADER] Adding edge between: CHEM   DUAN\n[GRADER] Adding edge between: AERO   CHEM\n[GRADER] Adding edge between: CHEM   FLMG\n[GRADER] Adding edge between: ATLS   FLMG\nATLS --> EC AERO FLMG \nEC --> ATLS \nAERO --> ATLS CHEM \nCHEM --> DUAN AERO FLMG \nDUAN --> CHEM \nFLMG --> CHEM ATLS \nCHEM\nAERO\nATLS\nEC\nShortest Path Distance: 3\n";
    ASSERT_EQ(expected, result);
    add_points_to_grade(10);
    
    
    
    string names3[] = {"ATLS", "EC", "AERO", "CHEM", "DUAN", "FLMG", "HLMS", "UMC", "REC"};
    int len3 = 9;
    string edges3[] = {"ATLS-->AERO", "EC-->AERO", "ATLS-->DUAN", "HLMS-->UMC", "UMC-->REC", "HLMS-->EC"};
    int elen3 = 6;
    string source3 = "REC";
    string dest3 = "ATLS";
    result = test_shortestpath(names3,len3, edges3, elen3, source3, dest3);
    expected = "[GRADER] Adding Vertex:ATLS\n[GRADER] Adding Vertex:EC\n[GRADER] Adding Vertex:AERO\n[GRADER] Adding Vertex:CHEM\n[GRADER] Adding Vertex:DUAN\n[GRADER] Adding Vertex:FLMG\n[GRADER] Adding Vertex:HLMS\n[GRADER] Adding Vertex:UMC\n[GRADER] Adding Vertex:REC\n[GRADER] Adding edge between: ATLS   AERO\n[GRADER] Adding edge between: EC   AERO\n[GRADER] Adding edge between: ATLS   DUAN\n[GRADER] Adding edge between: HLMS   UMC\n[GRADER] Adding edge between: UMC   REC\n[GRADER] Adding edge between: HLMS   EC\nATLS --> AERO DUAN \nEC --> AERO HLMS \nAERO --> ATLS EC \nCHEM --> \nDUAN --> ATLS \nFLMG --> \nHLMS --> UMC EC \nUMC --> HLMS REC \nREC --> UMC \nATLS\nAERO\nEC\nHLMS\nUMC\nREC\nShortest Path Distance: 5\n";
    ASSERT_EQ(expected, result);
    add_points_to_grade(15);
}