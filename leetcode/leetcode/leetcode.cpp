// leetcode.cpp : 此檔案包含 'main' 函式。程式會於該處開始執行及結束執行。
//

#pragma once

#include "pch.h"
#include <iostream>
#include "head.h"
#include "Peng.h"
#include <numeric>
using namespace std;
using namespace Peng;

struct TreeNode {
	int val;
	TreeNode *left;
	TreeNode *right;
	TreeNode() : val(0), left(nullptr), right(nullptr) {}
	TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
	TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};
class Solution242 {                    //Valid_Anagram
public:
	bool isAnagram(string s, string t) {
		map<char, int> word_map;
		for (const char c : s)
			word_map[c]++;

		for (auto a = t.cbegin(); a != t.cend(); a++)
		{
			if (--word_map[*a] < 0)
				return false;
		}
		for (auto a = word_map.cbegin(); a != word_map.cend(); a++)
		{
			if (a->second > 0)
				return false;
		}
		return true;
	}
};

class Solution438 {               //Find All Anagrams in a String
public:
	vector<int> isAnagram(string s, string p) {
		/*int p_size = p.size();
		vector<int> result;
		map<char, int> map1;
		map<char, int> map2;
		for (const auto c : p)
			map2[c]++;
		if (s.size() < p_size || p_size == 0)
			return {};
		else
		{
			bool first = true;
			for (int i = 0; i < s.size();)
			{
				if (first == false)
				{
					map1[s.at(i++)]++;
				}
				if (first)
				{
					while (i != p_size)
					{
						map1[s.at(i++)]++;
					}
					first = false;
				}
				if (map1 == map2)
					result.push_back(i - p_size);
				map1[s.at(i - p_size)]--;
				if (map1[s.at(i - p_size)] == 0)
					map1.erase(s.at(i - p_size));
			}
			return result;
		}*/

		int p_size = p.size();
		int s_size = s.size();
		if (s_size < p_size || p_size == 0)
			return {};
		vector<int> result;
		vector<int> map1(26, 0);
		vector<int> map2(26, 0);
		for (const auto c : p)
			map2[c - 97]++;
		for (int i = 0; i < s_size;)
		{
			map1[s.at(i++) - 97]++;
			if (map1 == map2)
				result.push_back(i - p_size);
			if (i - p_size >= 0)
			{
				map1[s.at(i - p_size) - 97]--;
			}
		}
		return result;
	}
};

class Solution567 {               //Permutation in String
public:
	bool isAnagram(string s1, string s2) {
		/*int p_size = p.size();
		vector<int> result;
		map<char, int> map1;
		map<char, int> map2;
		for (const auto c : p)
			map2[c]++;
		if (s.size() < p_size || p_size == 0)
			return {};
		else
		{
			bool first = true;
			for (int i = 0; i < s.size();)
			{
				if (first == false)
				{
					map1[s.at(i++)]++;
				}
				if (first)
				{
					while (i != p_size)
					{
						map1[s.at(i++)]++;
					}
					first = false;
				}
				if (map1 == map2)
					result.push_back(i - p_size);
				map1[s.at(i - p_size)]--;
				if (map1[s.at(i - p_size)] == 0)
					map1.erase(s.at(i - p_size));
			}
			return result;
		}*/

		int s2_size = s2.size();
		int s1_size = s1.size();
		if (s2_size < s1_size || s1_size == 0)
			return {};
		vector<int> result;
		vector<int> map1(26, 0);
		vector<int> map2(26, 0);
		for (const auto c : s1)
			map1[c - 97]++;
		for (int i = 0; i < s2_size;)
		{
			map2[s2.at(i++) - 97]++;
			if (map1 == map2)
				return true;
			if (i - s1_size >= 0)
			{
				map2[s2.at(i - s1_size) - 97]--;
			}
		}
		return false;
	}
};

class Solution76 {               //Minimum Window Substring
public:

	string minWindow(string s, string t) {
		char first_char = ' ';
		int first_pos = -1;
		int min_length = INT_MAX;
		string result = "";
		int t_size = t.size();
		int s_size = s.size();
		if (s_size < t_size || t_size == 0)
			return "";
		map<char, int> map2;
		for (const auto iter2 : t)
			map2[iter2]++;
		map<char, int> map1(map2);
		for (auto &iter3 : map1)
			iter3.second = 0;

		map<char, int>::const_iterator test_iter = map1.cbegin();
		while (test_iter != map1.cend())
		{
			test_iter++;
		}
		for (int i = 0; i < s_size; i++)
		{
			if (map2.count(s.at(i)) != 0)//用find可能比較好
			{
				map1.at(s.at(i))++;
				if (first_pos == -1)
				{
					first_pos = i;
					first_char = s.at(i);
				}
				else if (first_char == s.at(i) && map1.at(s.at(i)) > map2.at(s.at(i)))
				{
					map<char, int>::const_iterator test_iter = map1.cbegin();
					map<char, int>::const_iterator test_iter2 = map2.cbegin();
					while (test_iter != map1.cend())
					{
						test_iter++;
						test_iter2++;
					}
					map1.at(s.at(i))--;
					next_first_char_pos(s, first_char, first_pos, map1, map2);
					cout << first_pos << endl;
				}
			}

			if (map_bigger(map1, map2))
			{
				cout << s.substr(first_pos, i - first_pos + 1) << endl;
				if (i - first_pos + 1 < min_length)
				{
					result = s.substr(first_pos, i - first_pos + 1);
					min_length = i - first_pos + 1;
				}
			}
		}
		return result;
	}
	void next_first_char_pos(string &s, char &first_char, int &first_pos, map<char, int> &map1, map<char, int> &map2)
	{
		for (int i = first_pos + 1; i < s.size(); i++)
		{
			if (map2.count(s.at(i)) != 0)
			{
				if (map2.at(s.at(i)) >= map1.at(s.at(i)))
				{
					first_char = s.at(i);
					first_pos = i;
					return;
				}
				else
					map1.at(s.at(i))--;
			}
		}
	}

	bool map_bigger(map<char, int> &map1, map<char, int> &map2)
	{
		map<char, int>::const_iterator test_iter = map1.cbegin();
		map<char, int>::const_iterator test_iter2 = map2.cbegin();
		while (test_iter != map1.cend())
		{
			if (test_iter->second < test_iter2->second)
				return false;
			test_iter++;
			test_iter2++;
		}
		return true;
	}
};

class Solution239 { //Sliding Window Maximum
public:
	vector<int> maxSlidingWindow(vector<int>& nums, int k) {
		/*if (nums.size() == 0 || k == 0)
			return {};
		if (nums.size() < k)
			return { *min_element(nums.begin(), nums.end()) };
		vector<int> result;
		int most_left = *nums.begin();
		int most_right = *(nums.begin()+k-1);
		vector<int>::const_iterator bigest_pos = max_element(nums.begin(), nums.begin() + k);
		result.push_back(*bigest_pos);
		for (vector<int>::size_type i = 1; i < nums.size()-k+1; i++)
		{
			if (bigest_pos == nums.cbegin() + i - 1)
			{
				bigest_pos = max_element(nums.begin()+i, nums.begin() + i+ k);
				result.push_back(*bigest_pos);
			}
			else
			{
				if (*bigest_pos < *(nums.begin() + i + k - 1))
				{
					result.push_back(*(nums.begin() + i + k - 1));
					bigest_pos = nums.begin() + i + k - 1;
				}
				else
					result.push_back(*bigest_pos);
			}
		}
		return result;*/
		vector<int> res;
		deque<int> getMax;
		int i = 0, j = 0;

		while (j < nums.size()) {
			while (getMax.empty() == false and getMax.back() < nums[j]) { //會把比較小的值排掉
				getMax.pop_back();
			}

			getMax.push_back(nums[j]);

			if (j - i + 1 < k)
				j++;

			else if (j - i + 1 == k) {
				res.push_back(getMax.front());

				if (nums[i] == getMax.front()) {//不再下一輪的window範圍
					getMax.pop_front();
				}

				i++, j++;
			}
		}

		return res;
	}
};

class Solution257 {   // Binary Tree Paths
public:
	struct TreeNode {
		int val;
		TreeNode *left;
		TreeNode *right;
		TreeNode() : val(0), left(nullptr), right(nullptr) {}
		TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
		TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
	};
	vector<string> binaryTreePaths(TreeNode* root) {
		deque<char> path;
		vector<string> result;

		dfs(root, result, path);
		return result;
	}

	bool dfs(TreeNode* root, vector<string> &result, deque<char> &path)
	{
		if (!root)
			return false;
		path.push_back(root->val);
		bool first_bool = dfs(root->left, result, path);
		bool second_bool = dfs(root->right, result, path);
		if (!first_bool && !second_bool)
		{
			string temp = "";
			for (int i = 0; i < path.size() - 1; i++)
			{
				temp += to_string(path.at(i));
				temp += "->";
			}
			temp += to_string(path.back());
			result.push_back(temp);
		}
		path.pop_back();
		return true;
	}
};

class Solution988 { //Smallest String Starting From Leaf
public:
	string smallestFromLeaf(TreeNode* root) {
		deque<int> path;
		deque<int> result;
		string result_string = "";

		dfs(root, result, path);
		for (const auto i : result)
			result_string += i + 97;

		return result_string;
	}

	bool dfs(TreeNode* root, deque<int> &result, deque<int> &path)
	{
		if (!root)
			return false;
		path.push_front(root->val);
		bool first_bool = dfs(root->left, result, path);
		bool second_bool = dfs(root->right, result, path);
		if (!first_bool && !second_bool)
		{
			if (result.size() == 0)
				result = path;
			else
			{
				if (lexicographical_compare(path.begin(), path.end(), result.begin(), result.end()) == true)
				{
					result = path;
				}
			}
		}
		path.pop_front();
		return true;
	}
};

class Solution653 { //Two Sum IV - Input is a BST
public:
	vector<int> num;
	bool findTarget(TreeNode* root, int k) {
		return	dfs(root, num, k);
	}

	bool dfs(TreeNode* root, vector<int> &num, int k)
	{
		if (!root)
			return false;
		else
		{
			int val1 = root->val;
			for (int i = 0; i < num.size(); i++)
			{
				if (num.at(i) + val1 == k)
					return true;
			}
			num.push_back(val1);
			return(dfs(root->left, num, k) || dfs(root->right, num, k));
		}
	}
};
class Solution258 { //Add Digits
public:
	int addDigits(int num) {
		int temp = 0;
		while (num >= 10)
		{
			do
			{
				temp += num % 10;
				num /= 10;
			} while (num >= 10);
			temp += num;
			num = temp;
			temp = 0;
		}
		return num;
	}
};

class Solution1945 {    //Sum of Digits of String After Convert
public:
	int getLucky(string s, int k) {
		vector<int> trans_to_int;
		for (int i = 0; i < s.size(); i++)
			trans_to_int.push_back(s.at(i) - 'a' + 1);
		bool first = true;
		long num = 0;
		int temp = 0;
		while (k > 0)
		{
			if (first == true)
			{
				for (int i = 0; i < s.size(); i++)
				{
					temp = trans_to_int.at(i);
					while (temp >= 10)
					{
						num += temp % 10;
						temp /= 10;
					}
					num += temp;
				}
				first = false;
				k--;
				continue;
			}
			if (num < 10)
				return num;
			temp = num;
			num = 0;
			while (temp >= 10)
			{
				do
				{
					num += temp % 10;
					temp /= 10;
				} while (temp >= 10);
				num += temp;
			}
			k--;
		}
		return num;
	}
};

class Solution2180 { //Count Integers With Even Digit Sum
public:
	int countEven(int num) {
		int result = 0;
		for (int i = 1; i <= num; i++)
		{
			int result_num = 0;
			int num = i;
			while (num > 0)
			{
				int temp = num % 10;
				result_num += temp;
				num /= 10;
			}
			if (result_num % 2 == 0)
				result++;
		}
		return result;
	}
};

class Solution788 {            //Rotated Digits
public:
	int rotatedDigits(int n) {
		int result = 0;
		for (int i = 1; i <= n; i++)
		{
			int roated_i = i;
			if (rotated_num(roated_i))
			{
				if (roated_i != i)
					result++;
			}
		}
		return result;
	}

	bool rotated_num(int &num)
	{
		int temp_num = 0;
		int pow_num = 1;
		while (num > 0)
		{
			int temp = num % 10;
			if (temp == 0 || temp == 1 || temp == 8)
				temp = temp;
			else if (temp == 5)
				temp = 2;
			else if (temp == 2)
				temp = 5;
			else if (temp == 6)
				temp = 9;
			else if (temp == 9)
				temp = 6;
			else
				return false;
			temp_num += temp * pow_num;
			pow_num *= 10;
			num /= 10;
		}
		num = temp_num;
		return true;
	}
};

class Solution1627 {   //Graph Connectivity With Threshold
public:
	vector<bool> areConnected(int n, int threshold, vector<vector<int>>& queries) {
		QuickUnionUF test_union(n + 1);
		vector<bool> visit(n + 1, false), result;

		for (int i = threshold + 1; i <= n; i++)
		{
			if (visit.at(i) == true)
				continue;
			for (int j = i + i; j <= n; j += i)
			{
				if (test_union.find(i) != test_union.find(j))
					test_union.union_two(i, j);
			}
		}
		for (const auto t : queries)
		{
			if (test_union.find(t.at(0)) == test_union.find(t.at(1)))
				result.push_back(true);
			else
				result.push_back(false);
		}
		return result;
	}
};

class Solution260 {         //.Single Number III
public:
	vector<int> singleNumber(vector<int>& nums) {
		vector<int> result;
		map<int, int> test_map;
		for (unsigned int i = 0; i < nums.size(); i++)
		{
			test_map[nums.at(i)]++;
		}
		for (auto j = test_map.cbegin(); j != test_map.cend(); j++)
		{
			if (j->second == 1)
				result.push_back(j->first);
		}
		return result;
	}
};

class Solution1035 {  //Uncrossed Lines
public:
	int maxUncrossedLines(vector<int>& nums1, vector<int>& nums2) {
		int m = nums1.size(), n = nums2.size();
		vector<vector<int>> dp(m + 1, vector<int>(n + 1));
		for (int i = 1; i <= m; ++i) {
			for (int j = 1; j <= n; ++j) {
				if (nums1[i - 1] == nums2[j - 1]) {
					dp[i][j] = dp[i - 1][j - 1] + 1;
				}
				else {
					dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);//max(dp[i - 1][j], dp[i][j - 1]);
				}
			}
		}
		return dp[m][n];
	}
};

class Solution645 {    //Set Mismatch
public:
	vector<int> findErrorNums(vector<int>& nums) {
		vector<int> num_dup(nums.size() + 1, 0);
		vector<int> result(2, -1);
		auto nums_size = nums.size();
		for (int i = 0; i < nums_size; i++)
		{
			num_dup.at(nums.at(i))++;
		}

		for (int i = 1; i < nums_size + 1; i++)
		{
			if (num_dup.at(i) == 2)
				result.at(0) = i;
			else if (num_dup.at(i) == 0)
			{
				result.at(1) = i;
			}
		}
		return result;
	}
};

class Solution674 {  //Longest Continuous Increasing Subsequence
public:
	int findLengthOfLCIS(vector<int>& nums) {
		auto nums_size = nums.size();
		if (nums_size == 0)
			return 0;
		int big_seq = 1;
		int now_seq = 1;
		/*for (int i = 1; i < (nums_size - big_seq +now_seq); i++)//較慢  原因不明
		{
			if (nums.at(i) > nums.at(i-1))
			{
				now_seq++;
				if (big_seq < now_seq)
					big_seq++;
			}
			else
				now_seq = 1;
		}
		return big_seq;*/
		for (int i = 1; i < nums_size; i++)
		{
			if (nums.at(i) > nums.at(i - 1))
			{
				now_seq++;
			}
			else
			{
				if (big_seq < now_seq)
					big_seq = now_seq;
				now_seq = 1;
			}
		}
		if (big_seq < now_seq)
			big_seq = now_seq;
		return big_seq;
	}
};

class Solution673 {
public:
	int findNumberOfLIS(vector<int>& nums) {
		auto nums_size = nums.size();
		if (nums_size == 0)
			return 0;
		int biggest = 1;
		int result = 0;
		vector<pair<int, int>> max_count(nums.size(), make_pair<int, int>(1, 1)); //make_pair紀錄最大長度和有幾個這個最大長度的path
		for (int i = 1; i < nums_size; i++)
		{
			for (int j = 0; j < i; j++)
			{
				if (nums.at(j) < nums.at(i))
				{
					if (max_count.at(i).first < max_count.at(j).first + 1)
					{
						max_count.at(i).first = max_count.at(j).first + 1;
						max_count.at(i).second = max_count.at(j).second;
						if (max_count.at(i).first > biggest)
							biggest = max_count.at(i).first;
					}
					else if (max_count.at(i).first == max_count.at(j).first + 1)
					{
						max_count.at(i).second += max_count.at(j).second;
					}
				}
			}
		}
		for (int i = 0; i < nums_size; i++)
		{
			if (max_count.at(i).first == biggest)
			{
				result += max_count.at(i).second;
			}
		}
		return result;
	}
};

class Solution300 {  //Longest Increasing Subsequence
public:
	int lengthOfLIS(vector<int>& nums) {
		auto nums_size = nums.size();
		if (nums_size == 0)
			return 0;
		int biggest = 1;
		vector<int> max_count(nums.size(), 1); //make_pair紀錄最大長度和有幾個這個最大長度的path
		for (int i = 1; i < nums_size; i++)
		{
			for (int j = 0; j < i; j++)
			{
				if (nums.at(j) < nums.at(i))
				{
					if (max_count.at(i) < max_count.at(j) + 1)
					{
						max_count.at(i) = max_count.at(j) + 1;
						if (max_count.at(i) > biggest)
							biggest = max_count.at(i);
					}
				}
			}
		}
		return biggest;
	}
};

class Solution334 {      //Increasing Triplet Subsequence
public:
	bool increasingTriplet(vector<int>& nums) {
		int min1 = INT_MAX;
		int min2 = INT_MAX;

		auto nums_size = nums.size();
		for (int i = 0; i <= nums_size; i++)
		{
			if (nums.at(i) < min1)
				min1 = nums.at(i);
			else if (nums.at(i) < min2)
				min2 = nums.at(i);
			else if (nums.at(i) > min2)
				return true;
		}
		return false;
	}
};

class Solution1995 {
public:
	int countQuadruplets(vector<int>& nums) {    //##Count Special Quadruplets   o(n^2)複雜度
		int count = 0;
		vector<int>m(201, 0); // max nums value is 100 so two elements sum can be max 200
		for (int i = 1; i < nums.size() - 2; i++) {
			for (int j = 0; j < i; j++)
				m[nums[j] + nums[i]]++; // update all possible 2 sums
			for (int j = i + 2; j < nums.size(); j++) {
				int diff = nums[j] - nums[i + 1]; // fix third element and search for fourth - third in 2 sums as a  + b + c = d == a +  b = d - c
				if (diff >= 0)
					count += m[diff];
			}
		}
		return count;
	}
	/*int result = 0;
	auto nums_size = nums.size();
	for (int i = 0; i < nums_size-3; i++)
	{
		for (int j = i + 1; j < nums_size - 2; j++)
		{
			for (int k = j + 1; k < nums_size - 1; k++)
			{
				for (int l = k + 1; l < nums_size; l++)
					if (nums.at(i) + nums.at(j) + nums.at(k) == nums.at(l))
						result++;
			}
		}
	}
	return result;
}*/
};

class Solution1534 {     //Count Good Triplets
public:
	int countGoodTriplets(vector<int>& arr, int a, int b, int c) {
		int count = 0;
		int arr_size = arr.size();
		for (int i = 0; i < arr_size; i++)
		{
			for (int j = i + 1; j < arr_size; j++)
			{
				if (abs(arr[i] - arr[j]) <= a)
				{
					for (int k = j + 1; k < arr_size; k++)
					{
						int B = abs(arr[j] - arr[k]);
						int C = abs(arr[k] - arr[i]);
						if (B <= b and C <= c)
						{
							count++;
						}
					}
				}
			}
		}
		return count;
	}
};

class Solution804 {    //Unique Morse Code Words
public:
	int uniqueMorseRepresentations(vector<string>& words) {
		map<string, int> map_mose;
		int result = 0;
		vector<string> alpha_map = { ".-","-...","-.-.","-..",".","..-.","--.","....","..",".---","-.-",".-..","--","-.","---",".--.","--.-",".-.","...","-","..-","...-",".--","-..-","-.--","--.." };
		for (const auto a : words)
		{
			string temp;
			for (const auto b : a)
				temp.append(alpha_map.at(b - 'a'));
			if (map_mose.insert({ temp,0 }).second)
			{
				result++;
			}
		}
		return result;
	}
};

class Solution525 { //##Contiguous Array
public:
	int findMaxLength(vector<int>& nums)
	{
		unordered_map<int, int> mp; mp[0] = -1;
		int sum = 0, longest_subarray = 0;
		for (int i = 0; i < nums.size(); i++)
		{
			sum += nums[i] == 0 ? -1 : 1;
			if (mp.find(sum) != mp.end())
			{
				if (longest_subarray < i - mp[sum])
				{
					longest_subarray = i - mp[sum];
				}
			}
			else
			{
				mp[sum] = i;
			}
		}
		return longest_subarray;
	}
};

class Solution575 {  //Distribute Candies
public:
	int distributeCandies(vector<int>& candyType) {
		unordered_map<int, int>  candy_type_map;
		for (const auto a : candyType)
		{
			candy_type_map[a]++;
		}

		if (candy_type_map.size() < candyType.size() / 2)
			return candy_type_map.size();
		else
			return candyType.size() / 2;
	}
};

class Solution268 { //Missing Number
public:
	int missingNumber(vector<int>& nums) {
		auto nums_size = nums.size();
		int result = -1;
		vector<bool> test(nums.size() + 1, false);
		for (const auto a : nums)
			test.at(a) = true;
		for (int i = 0; i < nums_size + 1; i++)
		{
			if (test.at(i) == false)
			{
				result = i;
				return result;
			}
		}
		return result;
	}
};

class Solution1138 {     //Alphabet Board Path
public:
	string alphabetBoardPath(string target) {
		int now_row = 0;
		int now_col = 0;
		int target_row = 0;
		int target_col = 0;
		string result;
		for (const auto ch : target)
		{
			target_col = (ch - 'a') / 5;
			target_row = (ch - 'a') % 5;
			if (target_col == 5)
			{
				if (target_row - now_row > 0)
					result.append(target_row - now_row, 'R');
				else
					result.append(now_row - target_row, 'L');

				if (target_col - now_col > 0)
					result.append(target_col - now_col, 'D');
				else
					result.append(now_col - target_col, 'U');
			}
			else if (now_col == 5)
			{
				if (target_col - now_col > 0)
					result.append(target_col - now_col, 'D');
				else
					result.append(now_col - target_col, 'U');

				if (target_row - now_row > 0)
					result.append(target_row - now_row, 'R');
				else
					result.append(now_row - target_row, 'L');
			}
			else if (abs(target_col - now_col) >= abs(target_row - now_row))
			{
				if (target_col - now_col > 0)
					result.append(target_col - now_col, 'D');
				else
					result.append(now_col - target_col, 'U');

				if (target_row - now_row > 0)
					result.append(target_row - now_row, 'R');
				else
					result.append(now_row - target_row, 'L');
			}
			else
			{
				if (target_row - now_row > 0)
					result.append(target_row - now_row, 'R');
				else
					result.append(now_row - target_row, 'L');

				if (target_col - now_col > 0)
					result.append(target_col - now_col, 'D');
				else
					result.append(now_col - target_col, 'U');
			}
			result.append("!");
			now_col = target_col;
			now_row = target_row;
		}
		return result;
	}
};

class Solution {
public:
	bool checkString(string s) {
		int count_a = 0;
		string test_b;
		for (int i = 0; i < s.size() / 2; i++)
		{
			if (s.at(i) == 'a')
				count_a++;
			else
				test_b = s.substr(i);
		}
		for (int j = 0; j < test_b.size(); j++)
		{
			if (test_b.at(j) == 'b')
				count_a--;
			else
				return false;
		}
		if (count_a == 0)
			return true;
		else
			return false;
	}
};

class Solution2124 {   // Check if All A's Appears Before All B's
public:
	bool checkString(string s) {
		int count_a = 0;
		string test_b;
		for (int i = 0; i < s.size() / 2 + 1; i++)
		{
			if (s.at(i) == 'b')
			{
				test_b = s.substr(i);
				break;
			}
		}
		for (int j = 0; j < test_b.size(); j++)
		{
			if (test_b.at(j) == 'a')
				return false;
		}
		return true;
	}
};

class Solution1752 { //Check if Array Is Sorted and Rotated
public:
	bool check(vector<int>& nums) {
		int sub_array = INT_MAX;
		int nums_size = nums.size();
		for (int i = 1; i < nums_size; i++)
		{
			if (nums.at(i) < nums.at(i - 1))
			{
				rotate(nums.begin(), nums.begin() + i, nums.end());
				return is_sorted(nums.begin(), nums.end());
			}
		}
		return true;
	}
};

class Solution2150 {            //Find All Lonely Numbers in the Array
public:
	vector<int> findLonely(vector<int>& nums) {
		unordered_map<int, int> test_map;
		int nums_size = nums.size();
		vector<int> result;
		for (int i = 0; i < nums_size; i++)
		{
			test_map[nums.at(i)]++;
		}

		for (int i = 0; i < nums_size; i++)
		{
			if (test_map[nums.at(i)] == 1 && test_map.find(nums.at(i) + 1) == test_map.end() && test_map.find(nums.at(i) - 1) == test_map.end())
				result.push_back(nums.at(i));
		}
		return result;
	}
};

class Solution1838 {
public:
	int maxFrequency(vector<int>& arr, int k) {
		/*sort(nums.begin(), nums.end());
		if(nums.size()<2)
			return 1;
		int result = 0;
		int begin1 = 0;
		int end1 = 0;
		long long test_k = 0;
		while (begin1 != nums.size() && end1 != nums.size())
		{
			if(test_k <= k)
			{
				if (end1 - begin1+1 > result)
					result = end1 - begin1+1;
				end1++;
				if(end1 == nums.size())
					break;
				test_k += (nums.at(end1) - nums.at(end1-1))*(end1-begin1);//此部會錯
			}
			else
			{
				test_k-=nums.at(end1)-nums.at(begin1);
				begin1++;
			}
		}
		return result;*/
		int n = arr.size();

		if (n < 2) {
			return n;
		}

		sort(arr.begin(), arr.end());

		int res = 1; // minimum value of res will be 1 no matter what is k
		int i = n - 1; // we are maximizing frq of arr[i]
		int j = i - 1;
		int left = k; // number of operations we are left with
		while (i > 0 && j >= 0) {
			while (j >= 0 && arr[i] - arr[j] <= left) {
				left -= arr[i] - arr[j];
				j--;
			}
			res = max(res, i - j);

			left += (arr[i] - arr[i - 1])*(i - j - 1);
			i--;
		}
		return res;
	}
};

class Solution263 {   //Ugly Number
public:
	bool isUgly(int n) {
		if (n == 0)
			return false;
		while (n != 1)
		{
			if (n % 2 == 0)
			{
				n = n / 2;
				continue;
			}
			if (n % 3 == 0)
			{
				n = n / 3;
				continue;
			}
			if (n % 5 == 0)
			{
				n = n / 5;
				continue;
			}
			return false;
		}
		return true;
	}
};

class Solution264 {  //Ugly Number II
public:
	int nthUglyNumber(int n) {
		static	vector<int> result(1, 1);
		static unsigned int pow2 = 0;
		static unsigned int pow3 = 0;
		static unsigned int pow5 = 0;
		while (n > result.size())
		{
			int next2 = result.at(pow2) * 2;
			int next3 = result.at(pow3) * 3;
			int next5 = result.at(pow5) * 5;
			int result_min = min(next2, min(next3, next5));
			/*if (result_min == next2)
				pow2++;
			else if (result_min == next3)
				pow3++;
			else if (result_min == next5)
				pow5++;*/

			if (result_min == next2)  //用if比較好，可以一次更新多個pow
				pow2++;
			if (result_min == next3)
				pow3++;
			if (result_min == next5)
				pow5++;
			result.push_back(result_min);
		}
		return result.at(n - 1);
	}
};

class Solution313 {    //Super Ugly Number
public:
	int nthSuperUglyNumber(int n, vector<int>& primes) {
		vector<int> result(1, 1);
		auto primes_size = primes.size();
		//vector<int> pow_num(primes.size(), 0);
		vector<int> now_min_index(primes_size, 0);
		vector<long long> next_min(primes_size, 0);
		for (int j = 0; j < primes_size; j++)
		{
			next_min.at(j) = primes.at(j);
		}

		while (n > result.size())
		{
			auto min_num = *min_element(next_min.begin(), next_min.end());
			result.push_back(min_num);
			for (unsigned int i = 0; i < primes_size; i++)
			{
				if (min_num == next_min.at(i))
				{
					now_min_index.at(i)++;
					next_min.at(i) = (long)result.at(now_min_index.at(i))*primes.at(i);
				}
			}
		}
		return result.at(n - 1);
	}
};

class Solution279 {     //Perfect Squares
public:
	int numSquares(int n) {
		vector<int> dp(n + 1, INT_MAX);
		dp[0] = 0;
		dp[1] = 1;
		dp[2] = 2;
		for (int i = 3; i <= n; i++)
		{
			for (int j = 1; j <= i; j = pow(j + 1, 2))
			{
				dp[i] = min(dp[i], dp[i - j] + 1);
			}
		}
		return dp[n];
	}
};

class Solution1547 {     //Minimum Cost to Cut a Stick
public:
	int minCost(int n, vector<int>& cuts) {
		sort(cuts.begin(), cuts.end());
		cuts.insert(cuts.begin(), 0);
		cuts.push_back(n);
		auto cuts_size = cuts.size();
		vector<vector<int>>dp(cuts_size, vector<int>(cuts_size, INT_MAX));
		for (int i = 0; i < cuts_size - 1; i++)
			dp.at(i).at(i + 1) = 0;

		for (int len = 2; len < cuts_size; len++)
		{
			for (int border_first = 0; border_first < cuts_size - len; border_first++)
			{
				auto border_end = border_first + len;
				for (int j = border_first + 1; j < border_end; j++)//
				{
					dp.at(border_first).at(border_end) = min(dp.at(border_first).at(j), cuts.at(j) - cuts.at(border_first) + dp.at(border_first).at(j) + dp.at(j).at(border_end));
				}
			}
		}
		return dp.at(0).at(cuts_size - 1);
	}
};
bool isBadVersion(int test) //此題目測試用的
{
	return test;
}
class Solution278 {  //First Bad Version
public:
	int firstBadVersion(int n) {
		int first = 1;
		int last = n;
		while (first != last)
		{
			int pivot = first + (last - first) / 2;
			if (isBadVersion(pivot) == false)
			{
				if (isBadVersion(pivot + 1) == true)
					return pivot + 1;
				else
					first = pivot + 1;
			}
			else
			{
				last = pivot;
			}
		}
		return first;
	}
};

int guess(int test) //此題目測試用的
{
	return test;
}
class Solution374 {  //Guess Number Higher or Lower
public:
	int firstBadVersion(int n) {
		int first = 1;
		int last = n;
		while (first != last)
		{
			int pivot = first + (last - first) / 2;
			if (guess(pivot) == 1)
				first = pivot + 1;
			else if (guess(pivot) == -1)
				last = pivot - 1;
			else
				return pivot;
		}
		return first;
	}
};

class Solution375 {           //Guess Number Higher or Lower II
public:
	static vector<vector<int>> dp;
	int fun(int i, int j)
	{
		if (i >= j)
			return 0;
		if (dp[i][j] != -1)
			return dp[i][j];
		int a = INT_MAX;
		for (int k = i; k <= j; k++)
		{
			a = min(a, k + max(fun(i, k - 1), fun(k + 1, j)));
		}
		return dp[i][j] = a;
	}
	int getMoneyAmount(int n) {
		return fun(1, n);
		/*vector<vector<int>> dp(n + 2, vector<int>(n + 2, 0));
		auto row_size = dp.size();
		auto col_size = dp.at(0).size();
		for (int len = 1; len <= n - 1; len++)
			for (int i = 1; i <= n - len; i++)
			{
				dp.at(i).at(i + len) = INT_MAX;
				for (int k = i; k <= i + len; k++)
					dp.at(i).at(i + len) = min(dp.at(i).at(i + len), k + max(dp.at(i).at(k - 1), dp.at(k + 1).at(i + len)));
			}
		return dp.at(1).at(n);*/
	}
};

class Solution464 {   //Can I Win
public:
	bool win(int sum, int used, vector<char>& mem, int maxNum, int total) {
		if (mem[used] != -1) return mem[used];
		for (int i = 1; i <= maxNum; i++)
			if ((used & (1 << i)) == 0 && (i + sum >= total || !win(i + sum, used | (1 << i), mem, maxNum, total))) //used & (1 << i)) == 0判斷是否已經有先取過，有先取過後面不用進行了
				return mem[used] = 1;
		return mem[used] = 0;
	}
	bool canIWin(int maxChoosableInteger, int desiredTotal) {
		if (maxChoosableInteger*(maxChoosableInteger + 1) / 2 < desiredTotal)
			return false;
		vector<char> mem(1 << (maxChoosableInteger + 1), -1);//紀錄當前選擇者是否一定贏，選擇總共有2^n種選法，所以有1 << (maxChoosableInteger+1)筆資料
		return win(0, 0, mem, maxChoosableInteger, desiredTotal);
	}
};

class Solution1266 {  //Minimum Time Visiting All Points
public:
	int minTimeToVisitAllPoints(vector<vector<int>>& points) {
		int result = 0;
		if (points.empty())
			return result;
		for (int i = 0; i < points.size() - 1; i++)
		{
			result += max(abs(points.at(i).at(0) - points.at(i + 1).at(0)), abs(points.at(i).at(1) - points.at(i + 1).at(1)));
		}
		return result;
	}
};

class Solution1690 {  //Stone Game VII
public:
	/*int predict(int total, vector<int> &stones, int first, int last, vector<vector<int>> &dp)//top down method //設置參照很重要不然要重複複製
	{
		if (first >= last)
			return dp[first][last] = 0;
		if (dp[first][last] != -1)
			return dp[first][last];
		int remove_start = total- stones[first] - predict(total - stones[first],stones, first + 1, last, dp);
		int remove_end = total - stones[last] - predict(total - stones[last], stones, first, last-1, dp);
		return dp[first][last] = max(remove_start, remove_end);
	}

	int stoneGameVII(vector<int>& stones) {
		auto stones_size = stones.size();
		vector<vector<int>> dp(stones_size, vector<int>(stones_size, -1));
		int total = accumulate(stones.begin(),stones.end(), 0);
		return predict(total, stones, 0, stones_size - 1, dp);
	}*/
	int stoneGameVII(vector<int>& stones) {
		auto stones_size = stones.size();
		vector<vector<int>> dp(stones_size, vector<int>(stones_size, -1));
		vector<vector<int>> sum(stones_size, vector<int>(stones_size, -1));
		for (int i = 0; i < stones_size; i++)
		{
			dp.at(i).at(i) = 0;
			sum.at(i).at(i) = stones.at(i);
		}
		for (int len = 2; len <= stones_size; len++)
		{
			int last = len - 1;
			for (int first = 0; first <= stones_size - len; first++)
			{
				sum.at(first).at(last) = sum.at(first).at(last - 1) + stones.at(last);
				dp.at(first).at(last) = max(sum.at(first + 1).at(last) - dp.at(first + 1).at(last), sum.at(first).at(last - 1) - dp.at(first).at(last - 1));
				last++;
			}
		}
		return dp.at(0).at(stones_size - 1);
	}
};

class Solution877 { //Stone Game
public:
	bool stoneGame(vector<int>& piles) {
		int n = piles.size();
		int total = 0;
		for (auto& p : piles) total += p;

		vector<int> cache(n + 1, -1);
		return check(piles, n, total, 0, n - 1, 0, cache);
	}

	bool check(const vector<int>& piles, int n, int total, int from, int to, int alice, vector<int>& cache)
	{
		if (from > to)
			return alice > total / 2;
		else
		{
			if (cache[from] >= 0) return cache[from];

			int r = check(piles, n, total, from + 2, to, alice + piles[from], cache) ||
				check(piles, n, total, from + 1, to - 1, alice + piles[from], cache) ||
				check(piles, n, total, from + 1, to - 1, alice + piles[to], cache) ||
				check(piles, n, total, from, to - 2, alice + piles[to], cache);

			cache[from] = r;
			return r;
		}
	}
};

class Solution1140 {  //Stone Game II
	//max stones won by Alice = ( (A+B) + (A-B))/2 or (sum + diff)/2.
public:
	int find(int first, int M, vector<vector<int>> &dp, vector<int> &sum, vector<int> &piles)
	{
		if (first >= piles.size())
			return 0;
		if (dp.at(first).at(M) != -1)
			return dp.at(first).at(M);
		int now_sum = 0;
		for (int i = 1; i <= 2 * M; i++)
		{
			if (first + i - 1 >= piles.size())
				break;
			now_sum += piles.at(first + i - 1);
			dp.at(first).at(M) = max(dp.at(first).at(M), now_sum + sum.at(first + i) - find(first + i, max(i, M), dp, sum, piles));
		}
		return dp.at(first).at(M);
	}
	int stoneGameII(vector<int>& piles) {
		//if(piles.size() == 1)
			//return piles.at(0);
		auto piles_size = piles.size();
		vector<int> sum(piles_size + 1, 0);
		vector<vector<int>> dp(piles_size, vector<int>(101, -1));
		sum.at(piles_size - 1) = piles.at(piles_size - 1);
		for (int i = piles_size - 2; i >= 0; i--)
		{
			sum.at(i) = sum.at(i + 1) + piles.at(i);
		}
		return find(0, 1, dp, sum, piles);
	}
};

class Solution1563 {  //Stone Game V
public:
	int stoneGameV(vector<int>& stoneValue) {
	}
};

class Solution1957  //Delete Characters to Make Fancy String
{
public:
	string makeFancyString(string s) {
		if (s.size() < 3)
			return s;
		string result(1, s.at(0));
		int dup = 1;
		char pivot = s.at(0);
		for (int i = 1; i < s.size(); i++)
		{
			if (pivot == s.at(i))
				dup++;
			else
			{
				dup = 1;
				pivot = s.at(i);
			}
			if (dup < 3)
				result += s.at(i);
		}
		return result;
	}
};

class Solution1584 { //Min Cost to Connect All Points
public:
	int minCostConnectPoints(vector<vector<int>>& points) {
		int size_p = points.size();
		vector<bool> marked(points.size(), false);
		vector<edge> change_to;
		map<pair<int, int>, int> test;
		for (int i = 0; i < points.size(); i++)
			test[{points.at(i).at(0), points.at(i).at(1)}] = i;
		for (int i = 0; i < size_p; i++)
		{
			for (int j = 0; j < i; j++)
			{
				if (i != j)
				{
					change_to.push_back(edge(i, j, distance(points.at(i), points.at(j))));
				}
			}
		}
		Peng::QuickUnionUF check_cycle(size_p);
		sort(change_to.begin(), change_to.end(), [](edge a, edge b)->bool {return a.weight() < b.weight(); });
		int prim_size = 1;
		int result = 0;
		for (const auto a : change_to)
		{
			int vertex_1 = a.either();
			int vertex_2 = a.other(vertex_1);
			if (!check_cycle.connect(vertex_1, vertex_2))
			{
				check_cycle.union_two(vertex_1, vertex_2);
				result += a.weight();
				prim_size++;
				if (prim_size == size_p)
					break;
			}
		}
		return result;
	}

	int distance(const vector<int> &a, const vector<int> &b)
	{
		return abs(a.at(0) - b.at(0)) + abs(a.at(1) - b.at(1));
	}
};

class Solution2401 {  // Longest Nice Subarray
public:
	int longestNiceSubarray(const vector<int>& nums) {
		int pre = 0;
		int post = 1;
		//int next = 1;
		int result = 1;
		int now_seq = 1;
		while (post <= nums.size() - 1)
		{
			for (int i = pre; i < post; i++)
			{
				if ((nums.at(i) & nums.at(post)) != 0)
				{
					pre = i + 1;
					now_seq = 1;
					continue;
				}
				now_seq++;
				if (now_seq > result)
					result = now_seq;
			}
			post++;
			now_seq = 1;
		}
		return result;
	}
};

class Solution898 {  //Bitwise ORs of Subarrays
public:
	int subarrayBitwiseORs(const vector<int>& arr) {
		set<int> st;

		for (int i = 0; i < arr.size(); i++)
		{
			// take this element in curr_OR , now calculate OR value in backward

			// direction till that both curr_OR & prev_OR equals

			// Why we consider till only that -> because curr_subarray considering

			// arr[i] , then give same OR value which is previously calculated

			// from arr[i-1] , so no new subarray value will be founded.

			int curr_OR = arr[i];
			int prev_OR = 0;
			int j = i - 1;
			st.insert(curr_OR);

			while (j >= 0 && curr_OR != prev_OR)
			{
				curr_OR = curr_OR | arr[j];
				prev_OR = prev_OR | arr[j];
				st.insert(curr_OR);
				j--;
			}
		}

		return (int)st.size();
	}
};

class Solution904 {  //Fruit Into Baskets
public:
	int totalFruit(const vector<int>& fruits) {
		int first = 0;
		int second = 0;
		int post = 1;
		int biggest_num_first = 1;
		int biggest_num_second = 0;
		int result = 0;

		for (int i = 1; i < fruits.size(); i++)
		{
			post++;
			if (fruits.at(i) != fruits.at(first))
			{
				second = i;
				biggest_num_second = 1;
				break;
			}
			else
			{
				biggest_num_first++;
			}
		}

		for (int i = post; i < fruits.size(); i++)
		{
			if (fruits.at(i) == fruits.at(first))
			{
				biggest_num_first++;
			}
			else if (fruits.at(i) == fruits.at(second))
			{
				biggest_num_second++;
			}
			else
			{
				if (result < (biggest_num_first + biggest_num_second))
					result = biggest_num_first + biggest_num_second;

				if (fruits.at(i - 1) == fruits.at(second))
				{
					first = second;
				}
				biggest_num_first = 0;
				for (int j = i - 1; j >= 0; j--)
				{
					if (fruits.at(j) == fruits.at(first))
						biggest_num_first++;
					else
						break;
				}
				second = i;
				biggest_num_second = 1;
			}
		}
		if (result < (biggest_num_first + biggest_num_second))
			result = biggest_num_first + biggest_num_second;
		return result;
	}
};

class Solution1497 { //Check If Array Pairs Are Divisible by k
public:
	bool canArrange(const vector<int>& arr, int k) {
		map<int, int> remainder_map;
		for (int i = 0; i <= k; i++)
			remainder_map.insert({ i,0 });

		for (const auto a : arr)
		{
			if (a < 0)
				remainder_map.at(a%k + k)++;
			else
				remainder_map.at(a%k)++;
		}

		for (int i = 1; i <= k / 2; i++)
		{
			if (remainder_map.at(i) != remainder_map.at(k - i))
				return false;
			if (k % 2 == 0 && i == k / 2)
			{
				return (remainder_map.at(i) % 2 == 0);
			}
		}

		return true;
	}
};
class Solution2183 {
public:
	long long countPairs(vector<int>& nums, int k) {
		unordered_map<long, long> mp;
		long  long ans = 0;
		for (int i = 0; i < nums.size(); i++) {
			int gcd1 = gcd(nums[i], k);
			int gcd2 = k / gcd1;
			for (auto it : mp) {
				if (it.first % gcd2 == 0) ans += it.second;
			}
			mp[gcd1]++;
		}

		return ans;
	}
};

class Solution2344 {
public:
	int minOperations(const vector<int>& nums, const vector<int>& numsDivide)
	{
		int count = 0;
		int min1 = numsDivide.at(0);
		priority_queue<int, vector<int>, greater<int>> pq(nums.begin(), nums.end());
		if (numsDivide.size() > 1)
		{
			for (int i = 1; i < numsDivide.size() - 1; i++)
			{
				min1 = min(min1, gcd(min1, numsDivide.at(i)));
			}
		}
		while (!pq.empty())
		{
			int temp = pq.top();
			pq.pop();
			if (min1 % temp == 0)
			{
				return count;
			}
			else
			{
				if (temp > min1)
					return -1;
			}
			count++;
		}
		return -1;
	}
};

class Solution915 { //Partition Array into Disjoint Intervals
public:
	int partitionDisjoint(const vector<int>& nums) {
		if (nums.empty())
			return 0;
		auto min_index = min_element(nums.begin(), nums.end());
		int left_max = INT_MIN;
		for (auto i = nums.begin(); i != min_index; i++)
		{
			left_max = max(left_max, *i);
		}
		int result = min_index - nums.begin() + 1;
		int now_right_max = left_max;
		for (auto i = min_index + 1; i != nums.end(); i++)
		{
			if (*i < left_max)
			{
				left_max = now_right_max;
				result = (i - nums.begin()) + 1;
			}
			now_right_max = max(left_max, *i);
		}
		return result;
	}
};

class MountainArray
{
public:
	int get(int index);
	int length();
};

class Solution290 { //Word Pattern
public:
	bool wordPattern(string pattern, string s) {
		map<char, string> string_map;
		set<string> string_pool;
		vector<string> split_str = Peng::split(s);
		if (split_str.size() != pattern.size())
			return false;
		for (int i = 0; i < pattern.size(); i++)
		{
			if (string_map.find(pattern.at(i)) == string_map.end())
			{
				if (string_pool.find(split_str.at(i)) != string_pool.end())
					return false;
				string_map.insert(make_pair(pattern.at(i), split_str.at(i)));
				string_pool.insert(split_str.at(i));
			}
			else
			{
				if (string_map.at(pattern.at(i)) != split_str.at(i))
					return false;
			}
		}
		return true;
	}
};

class Solution326 { //Power of Three
public:
	bool isPowerOfThree(int n) {
	}
};

class Solution2220 {  //Minimum Bit Flips to Convert Number
public:
	int minBitFlips(int start, int goal) {
		int result = 0;
		while (start != 0 || goal != 0)
		{
			if (start % 2 != goal % 2)
				result++;
			start /= 2;
			goal /= 2;
		}
		return result;
	}
};

class Solution345 { //Reverse Vowels of a String
public:
	string reverseVowels(string s) {
		int last = s.size() - 1;
		int first = 0;
		last = s.find_last_of("aeiou", last);
		first = s.find_first_of("aeiou", first);
		while (last > first && last != -1 && first != -1)
		{
			char temp = s.at(last);
			s.at(last) = s.at(first);
			s.at(first) = temp;
			last = last - 1;
			first = first + 1;
			last = s.find_last_of("aeiou", last);
			first = s.find_first_of("aeiou", first);
		}
		return s;
	}
};

class Solution350 { //Intersection of Two Arrays II
public:
	vector<int> intersect(vector<int>& nums1, vector<int>& nums2) {
		/*vector<int> result;
		map<int, int> nums1_map;
		map<int, int> nums2_map;
		for (auto a : nums1)
			nums1_map[a]++;
		for (auto a : nums2)
			nums2_map[a]++;
		for (auto a : nums1_map)
		{
			if (nums2_map.find(a.first) != nums2_map.end())
			{
				int max_num = min(a.second, nums2_map.find(a.first)->second);
				while (max_num != 0)
				{
					result.push_back(a.first);
					max_num--;
				}
			}
		}
		return result;*/
		sort(nums1.begin(), nums1.end());
		sort(nums2.begin(), nums2.end());
		int n1 = (int)nums1.size(), n2 = (int)nums2.size();
		int i1 = 0, i2 = 0;
		vector<int> res;
		while (i1 < n1 && i2 < n2) {
			if (nums1[i1] == nums2[i2]) {
				res.push_back(nums1[i1]);
				i1++;
				i2++;
			}
			else if (nums1[i1] > nums2[i2]) {
				i2++;
			}
			else {
				i1++;
			}
			//while(i1 > 0 && i1 < n1 && nums1[i1] == nums1[i1 - 1]) i1++;
			//while(i2 > 0 && i2 < n2 && nums2[i2] == nums2[i2 - 1]) i2++;
		}
		return res;
	}
};

class Solution1002 { //Find Common Characters
public:
	vector<string> commonChars(vector<string>& words) {
		string result = words.at(0);
		sort(result.begin(), result.end());
		int size_w = words.size();
		for (int i = 1; i < size_w; i++)
		{
			string compare_word = words.at(i);
			sort(compare_word.begin(), compare_word.end());
			int n1 = (int)result.size(), n2 = (int)compare_word.size();
			int i1 = 0, i2 = 0;
			string temp;
			while (i1 < n1 && i2 < n2) {
				if (result[i1] == compare_word[i2]) {
					temp += result[i1];
					i1++;
					i2++;
				}
				else if (result[i1] > compare_word[i2]) {
					i2++;
				}
				else {
					i1++;
				}
				//while(i1 > 0 && i1 < n1 && nums1[i1] == nums1[i1 - 1]) i1++;
				//while(i2 > 0 && i2 < n2 && nums2[i2] == nums2[i2 - 1]) i2++;
			}
			result = temp;
		}
		vector<string> final_result;
		for (auto a : result)
			final_result.push_back(string(1, a));
		return final_result;
	}
};

class Solution2248 { //Intersection of Multiple Arrays
public:
	vector<int> intersection(vector<vector<int>>& nums) {
		vector<int> temp = nums.at(0);
		sort(temp.begin(), temp.end());
		for (int i = 1; i < nums.size(); i++)
		{
			temp = intersect(temp, nums.at(i));
		}
		return temp;
	}

	vector<int> intersect(vector<int>& nums1, vector<int>& nums2) {
		sort(nums2.begin(), nums2.end());
		int n1 = (int)nums1.size(), n2 = (int)nums2.size();
		int i1 = 0, i2 = 0;
		vector<int> res;
		while (i1 < n1 && i2 < n2) {
			if (nums1[i1] == nums2[i2]) {
				res.push_back(nums1[i1]);
				i1++;
				i2++;
			}
			else if (nums1[i1] > nums2[i2]) {
				i2++;
			}
			else {
				i1++;
			}
			//while(i1 > 0 && i1 < n1 && nums1[i1] == nums1[i1 - 1]) i1++;
			//while(i2 > 0 && i2 < n2 && nums2[i2] == nums2[i2 - 1]) i2++;
		}
		return res;
	}
};

class Solution2169 { //Count Operations to Obtain Zero
public:
	int countOperations(int num1, int num2) {
		// int max_num = max(num1,num2);
		// int min_num = min(num1,num2);
		// int result = 0;
		// while(min_num != 0)
		// {
		//     pair<int,int> temp_max;
		//     temp_max = minmax(max_num - min_num,min_num);
		//     min_num = temp_max.first;
		//     max_num = temp_max.second;
		//     result++;
		// }
		// return result;
		int count = 0;
		while (num1 != 0 && num2 != 0)
		{
			if (num1 >= num2)
			{
				count += num1 / num2;
				num1 = num1 % num2;
			}
			else
			{
				count += num2 / num1;
				num2 = num2 % num1;
			}
		}
		return count;
	}
};

class Solution869 { //Reordered Power of 2
public:
	bool reorderedPowerOf2(int n) {
		long c = counter(n);
		for (int i = 0; i < 32; i++)
			if (counter(1 << i) == c) return true;
		return false;
	}

	long counter(int N) {
		long res = 0;
		for (; N; N /= 10) res += pow(10, N % 10);
		return res;
	}
};

class Solution310 {  //Minimum Height Trees
public:
	vector<int> findMinHeightTrees(int n, vector<vector<int>>& edges) {
		{
			if (n == 1) return { 0 };
			if (n == 2) return { 0,1 };

			vector<vector<int>>next(n);
			vector<int>degree(n);

			for (auto edge : edges)
			{
				int a = edge[0], b = edge[1];
				degree[a]++;
				degree[b]++;
				next[a].push_back(b);
				next[b].push_back(a);
			}

			queue<int>q;
			vector<int>visited(n);
			for (int i = 0; i < n; i++)
			{
				if (degree[i] == 1)
					q.push(i);
			}

			int count = 0;
			while (!q.empty())
			{
				int len = q.size();
				while (len--)
				{
					int cur = q.front();
					q.pop();
					count++;
					visited[cur] = 1;
					for (int nxt : next[cur])
					{
						degree[nxt]--;
						if (degree[nxt] == 1)
							q.push(nxt);
					}
				}
				if (count == n - 1 || count == n - 2)
					break;
			}

			vector<int>rets;
			while (!q.empty())
			{
				rets.push_back(q.front());
				q.pop();
			}

			return rets;
		}
	}
};

class Solution733 {  //Flood Fill
public:
	vector<vector<int>> floodFill(vector<vector<int>>& image, int sr, int sc, int color) {
		queue<pair<int, int>> flood_path;
		vector<vector<bool>> marked(image.size(), vector<bool>(image.at(0).size(), false));
		int now_color = image.at(sr).at(sc);
		image.at(sr).at(sc) = color;
		marked.at(sr).at(sc) = true;
		flood_path.push(make_pair(sr, sc));

		while (!flood_path.empty())
		{
			int test_sr = flood_path.front().first;
			int test_sc = flood_path.front().second;
			flood_path.pop();
			if (test_sr > 0)
			{
				if (image.at(test_sr - 1).at(test_sc) == now_color)
				{
					if (!marked.at(test_sr - 1).at(test_sc))
					{
						flood_path.push(make_pair(test_sr - 1, test_sc));
						image.at(test_sr - 1).at(test_sc) = color;
						marked.at(test_sr - 1).at(test_sc) = true;
					}
				}
			}

			if (test_sr < image.size() - 1)
			{
				if (image.at(test_sr + 1).at(test_sc) == now_color)
				{
					if (!marked.at(test_sr + 1).at(test_sc))
					{
						flood_path.push(make_pair(test_sr + 1, test_sc));
						image.at(test_sr + 1).at(test_sc) = color;
						marked.at(test_sr + 1).at(test_sc) = true;
					}
				}
			}

			if (test_sc > 0)
			{
				if (image.at(test_sr).at(test_sc - 1) == now_color)
				{
					if (!marked.at(test_sr).at(test_sc - 1))
					{
						flood_path.push(make_pair(test_sr, test_sc - 1));
						image.at(test_sr).at(test_sc - 1) = color;
						marked.at(test_sr).at(test_sc - 1) = true;
					}
				}
			}

			if (test_sc < image.at(0).size() - 1)
			{
				cout << test_sr << " , " << test_sc << endl;
				if (image.at(test_sr).at(test_sc + 1) == now_color)
				{
					if (!marked.at(test_sr).at(test_sc + 1))
					{
						flood_path.push(make_pair(test_sr, test_sc + 1));
						image.at(test_sr).at(test_sc + 1) = color;
						marked.at(test_sr).at(test_sc + 1) = true;
					}
				}
			}
		}
		return image;
	}
};

class Solution463 { //Island Perimeter
public:
	int islandPerimeter(vector<vector<int>>& grid) {
		queue<pair<int, int>> flood_path;
		vector<vector<bool>> marked(grid.size(), vector<bool>(grid.at(0).size(), false));
		int result = 0;
		for (int i = 0; i < grid.size(); i++)
		{
			bool break_p = false;
			for (int j = 0; j < grid.at(i).size(); j++)
			{
				if (grid.at(i).at(j) == 1)
				{
					flood_path.push(make_pair(i, j));
					result += 4;
					break_p = true;
					marked.at(i).at(j) = true;
					break;
				}
			}
			if (break_p)
				break;
		}
		while (!flood_path.empty())
		{
			int test_sr = flood_path.front().first;
			int test_sc = flood_path.front().second;
			flood_path.pop();
			if (test_sr > 0)
			{
				if (grid.at(test_sr - 1).at(test_sc) == 1)
				{
					result--;
					if (!marked.at(test_sr - 1).at(test_sc))
					{
						flood_path.push(make_pair(test_sr - 1, test_sc));
						marked.at(test_sr - 1).at(test_sc) = true;
						result += 4;
					}
				}
			}
			cout << result << endl;
			if (test_sr < grid.size() - 1)
			{
				if (grid.at(test_sr + 1).at(test_sc) == 1)
				{
					result--;
					if (!marked.at(test_sr + 1).at(test_sc))
					{
						flood_path.push(make_pair(test_sr + 1, test_sc));
						marked.at(test_sr + 1).at(test_sc) = true;
						result += 4;
					}
				}
			}
			cout << result << endl;
			if (test_sc > 0)
			{
				if (grid.at(test_sr).at(test_sc - 1) == 1)
				{
					result--;
					if (!marked.at(test_sr).at(test_sc - 1))
					{
						flood_path.push(make_pair(test_sr, test_sc - 1));
						marked.at(test_sr).at(test_sc - 1) = true;
						result += 4;
					}
				}
			}
			cout << result << endl;
			if (test_sc < grid.at(0).size() - 1)
			{
				if (grid.at(test_sr).at(test_sc + 1) == 1)
				{
					result--;
					if (!marked.at(test_sr).at(test_sc + 1))
					{
						flood_path.push(make_pair(test_sr, test_sc + 1));
						marked.at(test_sr).at(test_sc + 1) = true;
						result += 4;
					}
				}
			}
			cout << result << endl;
			cout << "----------------------" << endl;
		}
		return result;
	}
};

class Solution42 {
public:
	int trap(vector<int>& height) {
		int pool_size = height.size();
		int right = height.size() - 1;
		int left = 0;
		int result = 0;
		int left_wall = height.at(left);
		int right_wall = height.at(right);
		while (right > left)
		{
			if (left_wall > right_wall)
			{
				result += right_wall - height.at(right);
				right--;
				right_wall = max(right_wall, height.at(right));
			}
			else
			{
				result += left_wall - height.at(left);
				left++;
				left_wall = max(left_wall, height.at(left));
			}
		}
		return result;
	}
};

class Solution2139 {  //Minimum Moves to Reach Target Score
public:
	int minMoves(int target, int maxDoubles) {
		if (target == 1)
			return 0;
		int result = 0;
		if (target % 2 == 1)
		{
			result++;
			target--;
		}
		while (target != 1)
		{
			if (maxDoubles != 0 && target % 2 == 0)
			{
				target /= 2;
				maxDoubles--;
			}
			else
			{
				if (maxDoubles == 0)
				{
					result += target - 1;
					return result;
				}
				target--;
			}
			result++;
		}
		return result;
	}
};

class Solution1404 { //Number of Steps to Reduce a Number in Binary Representation to One
public:
	int numSteps(string s) {
		int carry = 0;
		int result = 0;
		for (int i = s.length() - 1; i >= 1; i--)
		{
			if (s.at(i) - 48 + carry == 1)
			{
				result += 2;
				carry = 1;
			}
			else
				result++;
		}
		return result + carry;
	}
};

class Solution407 {
public:
	int trapRainWater(vector<vector<int>>& heightMap) {
		typedef pair<int, int> cell;
		priority_queue<cell, vector<cell>, greater<cell>> q;
		int m = heightMap.size();
		if (m == 0) return 0;
		int n = heightMap[0].size();
		vector<int> visited(m*n, false);

		for (int i = 0; i < m; ++i)
			for (int j = 0; j < n; ++j) {
				if (i == 0 || i == m - 1 || j == 0 || j == n - 1) {
					if (!visited[i*n + j])
						q.push(cell(heightMap[i][j], i*n + j));
					visited[i*n + j] = true;
				}
			}

		int dir[4][2] = { {0,1}, {0, -1}, {1, 0}, {-1, 0} };
		int ans = 0;
		while (!q.empty()) {
			cell c = q.top();
			q.pop();
			int i = c.second / n, j = c.second%n;

			for (int r = 0; r < 4; ++r) {
				int ii = i + dir[r][0], jj = j + dir[r][1];
				if (ii < 0 || ii >= m || jj < 0 || jj >= n || visited[ii*n + jj])
					continue;
				ans += max(0, c.first - heightMap[ii][jj]);
				q.push(cell(max(c.first, heightMap[ii][jj]), ii*n + jj));
				visited[ii*n + jj] = true;
			}
		}
		return ans;
	}
};

class Solution2062 { //Count Vowel Substrings of a String:sliding window
public:
	int countVowelSubstrings(string word) {
		int ans = 0, N = word.size();
		unordered_map<char, int> cnt;
		for (int i = 0; i < N - 4; ++i) {
			cnt.clear();
			int temp = 0;
			for (int j = i; j < N && isVowel(word[j]); ++j) {
				if (isVowel(word[j]))
				{
					cnt[word[j]]++;
					if (cnt.size() == 5)
					{
						++ans;
						temp++;
					}
				}
				else
				{
					if (temp > 0)
					{
						while (cnt[word[i]] > 1)
						{
							ans += temp;
							cnt[word[i]]--;
							i++;
						}
					}
					i = j + 1;
				}
			}
		}
		return ans;
	}
	bool isVowel(char c) {
		return c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u';
	};
};

class Solution1004 { //Max Consecutive Ones III:sliding window
public:
	int longestOnes(vector<int>& nums, int k) {
		int start = 0, max1 = INT_MIN, zeroCounter = 0;
		int nums_s = nums.size();
		for (int end = 0; end < nums_s; end++) {
			if (nums[end] == 0) {
				zeroCounter++;
			}
			while (zeroCounter > k) {
				//max1 = std::max(max1,end-start);
				if (nums[start] == 0) {
					zeroCounter--;
				}
				start++;
			}
			max1 = max(max1, end - start + 1);
		}
		//max1 = max(max1,(nums_s-start));
		return max1;
	}
};

int main()
{
	Solution42 test;
	vector<int> test2 = { 1,2,3,4,6,7,8,9,9 };
	auto it = upper_bound(test2.begin(), test2.end(), 5);
	cout << *it << endl;
	cout << test2.capacity() << endl;
	test2.resize(30, 0);
	cout << test2.at(5) << endl;
	cout << test2.capacity() << endl;
	test2.push_back(55);
	cout << test2.capacity() << endl;
}

// 執行程式: Ctrl + F5 或 [偵錯] > [啟動但不偵錯] 功能表
// 偵錯程式: F5 或 [偵錯] > [啟動偵錯] 功能表

// 開始使用的秘訣:
//   1. 使用 [方案總管] 視窗，新增/管理檔案
//   2. 使用 [Team Explorer] 視窗，連線到原始檔控制
//   3. 使用 [輸出] 視窗，參閱組建輸出與其他訊息
//   4. 使用 [錯誤清單] 視窗，檢視錯誤
//   5. 前往 [專案] > [新增項目]，建立新的程式碼檔案，或是前往 [專案] > [新增現有項目]，將現有程式碼檔案新增至專案
//   6. 之後要再次開啟此專案時，請前往 [檔案] > [開啟] > [專案]，然後選取 .sln 檔案