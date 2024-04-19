#include "pch.h"
#include"../example/examString.cpp"
#include<vector>
//googleµ¥Ôª²âÊÔ Á·Ï°
using namespace std;

class SolutionTest :public testing::Test {
protected:
	Solution _s1;
	 
};

TEST_F(SolutionTest, testRemoveDuplicates) { 
	vector<int>nums;
	nums = { 1, 1, 1, 2, 2, 3 };
	EXPECT_EQ(5,_s1.removeDuplicates(nums)); 

	nums = { 0, 1, 1, 1, 1, 2, 3 };
	EXPECT_EQ(7,_s1.removeDuplicates(nums));
	EXPECT_TRUE(true);
}
 

TEST_F(SolutionTest, testMaxSubArray) {
	vector<int>nums;
	nums = { -2,1,-3,4,-1,2,1,-5,4 };
	EXPECT_EQ(6, _s1.removeDuplicates(nums));

}


TEST_F(SolutionTest, maxProfit) {
	vector<int>nums;
	nums = { 7,1,5,3,6,4 };
	EXPECT_EQ(5, _s1.maxProfit(nums));
	nums = { 7,6,4,3,1 };
	EXPECT_EQ(0, _s1.maxProfit(nums));
}


int main(int argc, char** argv) {
	testing::InitGoogleTest(&argc, argv); 
	return RUN_ALL_TESTS();
}