/*
* leecode题库以及c++特性
*/
#include"examString.cpp" 
#include"head.h"

void test() {

}

void testRemoveDuplicates() { 
	vector<int>nums;
	nums = { 1, 1, 1, 2, 2, 3 };
	nums = { 0, 0, 1, 1, 1, 1, 2, 3, 3 };
	Solution s1;

	int i = s1.removeDuplicates(nums);
}
void testMajorityElement() { 
	vector<int>nums;
	nums = { 1, 1, 1, 2, 3 };
	//nums = { 2,2,1,1,1,2,2 };
	//nums = { 1  };
	 nums = { 6,5,5  };
	Solution s1;
	int i = s1.majorityElement(nums);
}
 
void testmaxProfit() {
	vector<int>nums;
	nums = { 1,2 };
	nums = { 3,2,6,5,0,3 };
	nums = { 3,2,6,5,0,3 };
	Solution s1;
	int i = s1.maxProfit(nums);

}

int main() {
	testmaxProfit();
}