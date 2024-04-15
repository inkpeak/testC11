
#include"head.h" 




class Solution {
public:
	//给定一个字符串 s ，找出其中不含有重复字符的最长子串的长度。
	int lengthOfLongestSubstring(string s) {
		return 0;
	}

	//给你一个有序数组 nums ，请你 原地 删除重复出现的元素，
	//使得出现次数超过两次的元素只出现两次，返回删除后数组的新长度。
	//不要使用额外的数组空间，你必须在,原地修改输入数组并在
	//使用 O(1) 额外空间的条件下完成
	int removeDuplicates(vector<int>& nums) {
		/*
		 int n = nums.size();
			if (n <= 2) {
				return n;
			}
			int slow = 2, fast = 2;
			while (fast < n) {
				if (nums[slow - 2] != nums[fast]) {
					nums[slow] = nums[fast];
					++slow;
				}
				++fast;
			}
			return slow;
	作者：力扣官方题解
	链接：https://leetcode.cn/problems/remove-duplicates-from-sorted-array-ii/solutions/702644/shan-chu-pai-xu-shu-zu-zhong-de-zhong-fu-yec2/
	来源：力扣（LeetCode）
	著作权归作者所有。商业转载请联系作者获得授权，非商业转载请注明出处。*/
		if (nums.size() <= 2) {
			return nums.size();
		}

		int index = 2; // 初始化新数组的位置

		for (int i = 2; i < nums.size(); ++i) {
			if (nums[i] != nums[index - 2]) { // 当前元素不等于前两个元素
				nums[index++] = nums[i]; // 将当前元素放置在新数组的位置
			}
		}

		return index; // 返回新数组的长度
	}

	//给定一个大小为 n 的数组 nums ，返回其中的多数元素。
	//多数元素是指在数组中出现次数 大于 n / 2 的元素
	int majorityElement(vector<int>& nums) {
		//摩尔投票法： 核心理念为 票数正负抵消  
		//此方法时间和空间复杂度分别为 O(N) 和 O(1) 
		int x = 0, votes = 0;
		for (int num : nums) {
			if (votes == 0) x = num;
			votes += num == x ? 1 : -1;
		}
		return x;
	}

	//给你一个整数数组nums,请你找出一个具有最大和的
	//连续子数组（子数组最少包含一个元素）,返回其最大和。
	int maxSubArray(vector<int>& nums) {
		int pre = 0, maxAns = nums[0];
		for (const auto& x : nums) {
			pre = max(pre + x, x);
			maxAns = max(maxAns, pre);
		}
		return maxAns;
	}

	//给定一个长度为 n 的环形整数数组 nums ，
	//返回 nums 的 非空子数组 的最大可能和
	int maxSubarraySumCircular(vector<int>& nums) {
		/*作者：力扣官方题解
链接：https ://leetcode.cn/problems/maximum-sum-circular-subarray/solutions/2350660/huan-xing-zi-shu-zu-de-zui-da-he-by-leet-elou/
		*/
		int n = nums.size();
		vector<int> leftMax(n);
		// 对坐标为 0 处的元素单独处理，避免考虑子数组为空的情况
		leftMax[0] = nums[0];
		int leftSum = nums[0];
		int pre = nums[0];
		int res = nums[0];
		for (int i = 1; i < n; i++) {
			pre = max(pre + nums[i], nums[i]);
			res = max(res, pre);
			leftSum += nums[i];
			leftMax[i] = max(leftMax[i - 1], leftSum);
		}

		// 从右到左枚举后缀，固定后缀，选择最大前缀
		int rightSum = 0;
		for (int i = n - 1; i > 0; i--) {
			rightSum += nums[i];
			res = max(res, rightSum + leftMax[i - 1]);
		}
		return res;
	}

	/*
	* 给定一个数组 prices,它的第 i 个元素 prices[i]
	表示一支给定股票第 i 天的价格.你只能选择 某一天 买入这只股票,
	并选择在 未来的某一个不同的日子 卖出该股票.设计一个算法来计算
	你所能获取的最大利润.返回你可以从这笔交易中获取的最大利润.
	如果你不能获取任何利润，返回 0
	*/
	int maxProfit(vector<int>& prices) {
		/*作者：力扣官方题解
			链接：https ://leetcode.cn/problems/best-time-to-buy-and-sell-stock/solutions/136684/121-mai-mai-gu-piao-de-zui-jia-shi-ji-by-leetcode-/*/
		int minprice = 1e9, maxprofit = 0;
		for (int price : prices) {
			maxprofit = max(maxprofit, price - minprice);
			minprice = min(price, minprice);
		}
		return maxprofit;
	}

	/*给定一个罗马数字，将其转换成整数
	*	字符          数值
		I             1
		V             5
		X             10
		L             50
		C             100
		D             500
		M             1000
	罗马数字中小的数字在大的数字的右边。但也存在特例，
	例如 4 不写做 IIII，而是 IV。数字 1 在数字 5 的左边,
	所表示的数等于大数 5 减小数 1 得到的数值 4 .同样地,
	数字 9 表示为 IX。这个特殊的规则只适用于以下六种情况：

	I 可以放在 V (5) 和 X (10) 的左边，来表示 4 和 9。
	X 可以放在 L (50) 和 C (100) 的左边，来表示 40 和 90。
	C 可以放在 D (500) 和 M (1000) 的左边，来表示 400 和 900。
	*/
	int romanToInt(string s) {
		/*
		unordered_map<char, int> symbolValues = {
        {'I', 1},
        {'V', 5},
        {'X', 10},
        {'L', 50},
        {'C', 100},
        {'D', 500},
        {'M', 1000},
		 };
	 
		int ans = 0;
        int n = s.length();
        for (int i = 0; i < n; ++i) {
            int value = symbolValues[s[i]];
            if (i < n - 1 && value < symbolValues[s[i + 1]]) {
                ans -= value;
            } else {
                ans += value;
            }
        }
        return ans;

作者：力扣官方题解
链接：https://leetcode.cn/problems/roman-to-integer/solutions/774992/luo-ma-shu-zi-zhuan-zheng-shu-by-leetcod-w55p/
 
		*/
		int sum = 0; 
		while (s.length() != 0)
		{ 
			switch (s[0])
			{
			case 'I': {
				if (s.length() >= 2) {
					if (s[1] == 'V') {
						sum += 4;
						s.erase(0, 2);
					}
					else if (s[1] == 'X') {
						sum += 9;
						s.erase(0, 2);
					}
					else {
						sum += 1;
						s.erase(0, 1);
					}
				}
				else {
					sum += 1;
					s.erase(0, 1);
				}
			}break;

			case 'V': {
				sum += 5;
				s.erase(0, 1);
			}break;

			case 'X': {
				if (s.length() >= 2) {
					if (s[1] == 'L') {
						sum += 40;
						s.erase(0, 2);
					}
					else if (s[1] == 'C') {
						sum += 90;
						s.erase(0, 2);
					}
					else {
						sum += 10;
						s.erase(0, 1);
					}
				}
				else {
					sum += 10;
					s.erase(0, 1);
				}
			}break;

			case 'L': {
				sum += 50;
				s.erase(0, 1);
			}break;

			case 'C': {
				if (s.length() >= 2) {
					if (s[1] == 'D') {
						sum += 400;
						s.erase(0, 2);
					}
					else if (s[1] == 'M') {
						sum += 900;
						s.erase(0, 2);
					}
					else {
						sum += 100;
						s.erase(0, 1);
					}
				}
				else {
					sum += 100;
					s.erase(0, 1);
				}
			}break;

			case 'D': {
				sum += 500;
				s.erase(0, 1);
			}break;

			case 'M': {
				sum += 1000;
				s.erase(0, 1);
			}break;
			}
		} 
		return sum;
	}

	//给你一个字符串 s,由若干单词组成,单词前后用一些空格字符隔开.
	//返回字符串中 最后一个 单词的长度
	int lengthOfLastWord(string s) { 
		int num = 0;
		int i = s.length()-1;
		while (i >= 0) {
			if (s[i] == ' ' && num != 0) {
				return num;
			}
			if (s[i] != ' ') {
				num++;
			}
			i--;
		}
		return num; 
	}


};