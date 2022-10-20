#pragma once
#include "head.h"
#include <bitset>
using namespace std;
#ifndef Peng_H
#define Peng_H

namespace Peng
{
	//use in leetcode
	void bfs_leetcode(vector<vector<int>>adjacency_list, int source);//leetcode:310
	void bfs_leetcode(vector<set<int>>adjacency_list, int source);//leetcode:310

	void trim(string &input);
	vector<string> split(const string &input, char delim = ' ', int pos = 0);

	int gcd(int a, int b);

	inline vector<int> rand_int_vector(int vec_num, int min = INT_MIN, int max = INT_MAX)
	{
		default_random_engine e(static_cast<unsigned>(time(0)));
		uniform_int_distribution<int> u(min, max);
		vector<int> result(vec_num);
		for (auto &element : result)
			element = u(e);
		return result;
	}

	template<typename T1>
	inline vector<T1> rand_real_vector(int vec_num, T1 min = DBL_MIN, T1 max = DBL_MAX)
	{
		default_random_engine e(static_cast<unsigned>(time(0)));
		uniform_real_distribution< T1> u(min, max);
		vector<T1> result(vec_num);
		for (auto &element : result)
			element = u(e);
		return result;
	}
	template<typename T1>
	class QuickFindUF_leetcode
	{
	public:
		QuickFindUF_leetcode();
		QuickFindUF_leetcode(T1 size);
		T1 find(T1 p);
		void union_two(T1 p, T1 q);
		void print_union();
		vector<T1> union_set;
	};

	template<typename T1>
	class QuickUnionUF_leetcode
	{
	public:
		QuickUnionUF_leetcode();
		QuickUnionUF_leetcode(T1 size);
		T1 find(T1 p);
		void union_two(T1 p, T1 q);
		void print_union();
		void print_union_num();
		vector<T1> union_set;
		vector<T1> sz;
	};

	template<typename T1>
	QuickFindUF_leetcode<T1>::QuickFindUF_leetcode()
	{
	}

	template<typename T1>
	QuickFindUF_leetcode<T1>::QuickFindUF_leetcode(T1 size)
	{
		for (T1 i = 0; i < size; i++)
		{
			union_set.push_back(i);
		}
	}

	template<typename T1>
	T1 QuickFindUF_leetcode<T1>::find(T1 p)
	{
		if (p < 0 || p >= union_set.size())
			return -1;
		return union_set.at(p);
	}

	template<typename T1>
	void QuickFindUF_leetcode<T1>::union_two(T1 p, T1 q)
	{
		if (p < 0 || q < 0 || p >= union_set.size() || q >= union_set.size())
			return;
		T1 pid = union_set[static_cast<const unsigned int>(p)];
		T1 qid = union_set[static_cast<const unsigned int>(q)];
		for (T1 i = 0; i < union_set.size(); i++)
		{
			if (union_set[static_cast<const unsigned int>(i)] == pid)
				union_set[static_cast<const unsigned int>(i)] = qid;
		}
		return;
	}

	template<typename T1>
	void QuickFindUF_leetcode<T1>::print_union(void)
	{
		map<T1, vector<T1> > result;
		for (T1 i = 0; i < union_set.size(); i++)
		{
			result[union_set.at(static_cast<const unsigned int>(i))].push_back(i);
		}
		for (auto iter : result)
		{
			for (auto a : iter.second)
				cout << a << " , ";
			cout << endl;
		}
		cout << "-----------------------------------------------------------------------------------" << endl;
		return;
	}
	template<typename T1>
	QuickUnionUF_leetcode<T1>::QuickUnionUF_leetcode()
	{
	}

	template<typename T1>
	QuickUnionUF_leetcode<T1>::QuickUnionUF_leetcode(T1 size)
	{
		for (T1 i = 0; i < size; i++)
		{
			union_set.push_back(i);
			sz.push_back(1);
		}
	}

	template<typename T1>
	T1 QuickUnionUF_leetcode<T1>::find(T1 p)
	{
		if (p < 0 || p >= union_set.size())
			return -1;
		T1 temp = p;
		while (union_set.at(p) != p)
		{
			union_set.at(p) = union_set.at(union_set.at(p));
			p = union_set.at(p);
		}
		union_set.at(temp) = p;
		return p;
	}

	template<typename T1>
	void QuickUnionUF_leetcode<T1>::union_two(T1 p, T1 q)
	{
		if (p < 0 || q < 0 || p >= union_set.size() || q >= union_set.size())
			return;
		T1 i = find(p);
		T1 j = find(q);
		//if (i == j)
		//	return;
		if (sz.at(i) < sz.at(j))
		{
			union_set.at(i) = j;
			sz.at(j) = sz.at(i) + sz.at(j);
		}
		else
		{
			union_set.at(j) = i;
			sz.at(i) = sz.at(i) + sz.at(j);
		}
		return;
	}

	template<typename T1>
	void QuickUnionUF_leetcode<T1>::print_union(void)
	{
		map<T1, vector<T1> > result;
		for (T1 i = 0; i < union_set.size(); i++)
		{
			result[union_set.at(i)].push_back(i);
		}
		for (auto iter : result)
		{
			for (auto a : iter.second)
				cout << a << " , ";
			cout << endl;
		}
		cout << "-----------------------------------------------------------------------------------" << endl;
		return;
	}
	template<typename T1>
	void QuickUnionUF_leetcode<T1>::print_union_num(void)
	{
		for (T1 i : sz)
		{
			cout << i << ',';
		}
		cout << endl;
		return;
	}

	class QuickFindUF
	{
	public:
		QuickFindUF();
		QuickFindUF(int size);
		int find(int p);
		bool connect(int p, int q);
		void union_two(int p, int q);
		void print_union();
		vector<int> union_set;
	};

	class QuickUnionUF
	{
	public:
		QuickUnionUF();
		QuickUnionUF(int size);
		int find(int p);
		bool connect(int p, int q);
		void union_two(int p, int q);
		void print_union();
		void print_union_num();
		vector<int> union_set;
		vector<int> sz;
	};

	template <class T>
	void print_vector(const vector<T>& input) //沒辦法用串列初始器Peng::print_vector<int>({1,2,3,4});//會錯
	{
		unsigned int size_vec = input.size();
		if (size_vec == 0)
			return;
		for (unsigned int i = 0; i < (size_vec - 1); i++)//這段程式碼相當重要stl容器的size回傳的都是unsigned int 所以此時如果-1會變成4294967295
		{
			cout << input.at(i) << "->";
		}
		if (size_vec > 0)
			cout << input.at(input.size() - 1) << endl;
	}

	template <class T>
	void exch(vector<T>& input, typename vector<T>::size_type i, typename vector<T>::size_type j)
	{
		T temp = input.at(i);
		input.at(i) = input.at(j);
		input.at(j) = temp;
	}

	template<typename T1, typename  T2 = less<T1>>
	void inline selection_sort(vector<T1>& input, T2 f = T2())
	{
		auto input_size = input.size();
		for (typename vector<T1>::size_type i = 0; i < input_size; i++)
		{
			typename  vector<T1>::size_type min = i;
			for (typename vector<T1>::size_type j = i + 1; j < input_size; j++)
			{
				if (f(input.at(j), input.at(min)))
					min = j;
			}
			exch(input, i, min);
		}
	}
	template<typename T1, typename  T2 = less<T1>>
	void inline insertion_sort(vector<T1>& input, T2 f = T2())
	{
		auto input_size = input.size();
		for (typename vector<T1>::size_type i = 1; i < input_size; i++)
		{
			for (int j = i; j > 0; j--)
			{
				if (f(input.at(j), input.at(j - 1)))
					exch(input, j, j - 1);
				else
					break;
			}
		}
	}

	inline vector<unsigned int>  default_increment(unsigned int st)//inline 宣告則該定義只會在該檔案下找，因此定義要寫在同一個檔案下
	{
		{
			vector<unsigned int> result;
			unsigned int h = 1;
			do
			{
				result.push_back(h);
				h = 3 * h + 1;
			} while (h < st / 3);
			return result;
		}
	}

	template<typename T1, typename T2 = decltype(default_increment)*, typename  T3 = less<T1> >
	void inline shell_sort(vector<T1>& input, T2 increment_fnuc = default_increment, T3 f = T3())
	{
		auto input_size = input.size();
		vector<unsigned int> increment = increment_fnuc(input_size);
		auto increment_size = increment.size();
		for (unsigned int h = increment_size; h > 0; h--)
		{
			unsigned int incre = increment.at(h - 1);
			for (typename vector<T1>::size_type i = incre; i < input_size; i++)
			{
				for (typename vector<T1>::size_type j = i; j >= incre; j -= incre)
					if (f(input.at(j), input.at(j - 1)))
						exch(input, j, j - h);
					else
						break;
			}
		}
	}

	template<typename T1, typename  T2 = less<T1> >
	void inplace_merge(vector<T1> &input, vector<T1> &temp, typename vector<T1>::size_type lo, typename vector<T1>::size_type mid, typename vector<T1>::size_type hi, T2 f = T2())
	{
		for (int i = lo; i <= hi; i++)
			temp.at(i) = input.at(i);

		int j = lo, k = mid + 1;
		for (int i = lo; i <= hi; i++)
		{
			if (j > mid)
				input.at(i) = temp.at(k++);
			else if (k > hi)
				input.at(i) = temp.at(j++);
			else if (f(temp.at(j), temp.at(k)))
				input.at(i) = temp.at(j++);
			else
				input.at(i) = temp.at(k++);
		}
	}
	template<typename T1, typename  T2 = less<T1> >
	void merge_sort_sub(vector<T1> &input, vector<T1> &temp, typename vector<T1>::size_type lo, typename vector<T1>::size_type hi, T2 f = T2())
	{
		if (hi <= lo)return;
		int mid = lo + (hi - lo) / 2;

		merge_sort_sub(input, temp, lo, mid);
		merge_sort_sub(input, temp, mid + 1, hi);
		//greater<T1> test = greater<T1>();//一定要這樣寫test()會錯，原因是編譯器可能不把它當型別，template的緣故
		if (f(input.at(mid), input.at(mid + 1)))
			return;
		inplace_merge<T1, T2>(input, temp, lo, mid, hi);
	}
	template<typename T1>
	void merge_sort(vector<T1> &input)//temp size要和input依樣，hi要是size -1;
	{
		vector<T1> temp(input.size(), 0);
		merge_sort_sub(input, temp, 0, input.size() - 1);
	}
	template<typename T1, typename  T2 = less<T1>>
	void bottom_up_mergesort(vector<T1> &input, T2 f = T2())
	{
		vector<T1> temp(input.size(), 0);
		int N = input.size();
		for (int sz = 1; sz < N; sz = sz + sz)
			for (int lo = 0; lo < N - sz; lo += sz + sz)
			{
				vector<T1> temp(input.size(), 0);
				inplace_merge<T1, T2>(input, temp, lo, lo + sz - 1, min(lo + sz + sz - 1, N - 1));
			}
	}

	template<typename T1>
	T1 medianOf3(T1 a, T1 b, T1 c)
	{
		if ((a > b) ^ (a > c))
			return a;
		else if ((b < a) ^ (b < c))
			return b;
		else
			return c;
	}
	template<typename T1, typename  T2 = less<T1>>
	void quick_sort_sub(vector<T1> &input, int lo, int hi, T2 f = T2());

	template<typename T1, typename  T2 = less<T1>>
	int partition(vector<T1> &input, int lo, int hi, T2 f = T2());

	template<typename T1, typename  T2 = less<T1>>
	void quick_sort(vector<T1> &input, T2 f = T2())//這個正常來說要用在沒有重複值的序列上
	{
		quick_sort_sub(input, 0, input.size() - 1, f);
	}

	template<typename T1, typename  T2>
	void quick_sort_sub(vector<T1> &input, int lo, int hi, T2 f)
	{
		if (hi <= lo) return;
		print_vector(input);
		cout << "lo = " << lo << " , hi = " << hi << endl;
		int j = partition(input, lo, hi, f);
		quick_sort_sub(input, lo, j - 1, f);
		quick_sort_sub(input, j + 1, hi, f);
		return;
	}
	template<typename T1, typename  T2>
	int partition(vector<T1> &input, int lo, int hi, T2 f)
	{
		int front = lo + 1;
		int rear = hi;
		while (true)
		{
			while (f(input.at(front), input.at(lo)))
			{
				front++;
				if (front >= hi)           //這怪怪的，但結果應該是沒錯的
					break;
			}

			while (f(input.at(lo), input.at(rear)))
			{
				rear--;
				if (rear <= lo)
					break;
			}

			if (rear <= front)  //等號是因為front = hi時會用到
				break;
			else
			{
				exch(input, front, rear);
				front++;
				rear--;
				if (rear <= lo)                //以上三行很重要可節省交換調再次比對的時間，更重要的是可以防止less<T1>時會無限loop的情況
					break;
			}
		}
		exch(input, rear, lo);
		return rear;
	}

	template<typename T1, typename  T2 = less<T1>>
	void three_way_quick_sort_sub(vector<T1> &input, int lo, int hi, T2 f = T2())
	{
		if (hi <= lo) return;
		int front = lo;                  //front記著最前面pivot的位置
		int rear = hi;
		int pivot = input.at(front);
		int i = lo;

		while (i <= rear)   //要等於rear那個點才會測到
		{
			if (input.at(i) == pivot)
				i++;
			else if (f(input.at(i), pivot))
			{
				exch(input, i, front);
				front++;
				i++;
			}
			else
			{
				exch(input, i, rear);
				rear--;
			}
		}
		three_way_quick_sort_sub(input, lo, front - 1, f);
		three_way_quick_sort_sub(input, rear + 1, hi, f);
		return;
	}

	template<typename T1, typename  T2 = less<T1>>//default max heap 排序是升序
	void three_way_quick_sort(vector<T1> &input, T2 f = T2())
	{
		three_way_quick_sort_sub(input, 0, input.size() - 1, f);
	}

	template<typename T1, typename  T2 = greater<T1>>//default max heap 排序是升序
	class heap
	{
	public:
		typename vector<T1>::size_type N = heap_array.size() - 1;
		T2 f = T2();
		mutable vector<T1> heap_array;//類別初始化 只能用預設初始化或者提供=號的初始器
		heap()
		{
		}

		heap(const vector<T1>& input) :heap_array(input)
		{
			//heap_array.insert(heap_array.end(), input.begin(), input.end());
			for (int i = heap_array.size() / 2 - 1; i >= 0; i--)
				sink(i);
		}
		int swimup(int index)   //num是index   //回傳最後該元素所在位置 //index從1開始
		{
			if (index >= heap_array.size())
				return -1;
			while (index > 0 && f(heap_array.at(index), heap_array.at((index - 1) / 2)))
			{
				exch(heap_array, index, (index - 1) / 2);
				index = (index - 1) / 2;
			}
			return index;
		}
		int insert(int num)  //num是數值    //回傳最後該元素所在位置
		{
			heap_array.push_back(num);
			return swimup(heap_array.size() - 1);
		}

		int sink(int index)
		{
			if (index >= heap_array.size() || index < 0)
				return -1;
			int key = 0;
			while ((index + 1) * 2 <= heap_array.size())
			{
				if ((index + 1) * 2 == heap_array.size())
					key = (index + 1) * 2 - 1;
				else
				{
					if (f(heap_array.at((index + 1) * 2), heap_array.at((index + 1) * 2 - 1)))
						key = (index + 1) * 2;
					else
						key = (index + 1) * 2 - 1;
				}
				if (f(heap_array.at(index), heap_array.at(key)))
					return index;
				else
				{
					exch(heap_array, index, key);
					index = key;
				}
			}
			return index;
		}

		T1 pop()
		{
			if (heap_array.empty())
			{
				cout << "heap is empty" << endl;
				throw out_of_range("heap is empty");
			}
			T1 pop_num = heap_array.front();
			exch(heap_array, 0, heap_array.size() - 1);
			heap_array.pop_back();
			sink(0);
			return pop_num;
		}

		T1 top()
		{
			if (heap_array.empty())
			{
				cout << "heap is empty" << endl;
				return -1;
			}
			return heap_array.front();
		}

		int push(T1 push_num)//return push number index in heap;
		{
			heap_array.push_back(push_num);
			return swimup(heap_array.size() - 1);
		}

		template <class InputIterator>
		void assign(InputIterator first, InputIterator last)
		{
			heap_array.assign(first, last);
			for (int i = heap_array.size() / 2 - 1; i >= 0; i--)
				sink(i);
		}

		bool empty() const
		{
			return heap_array.empty();
		}

		unsigned int size() const
		{
			return heap_array.size();
		}

		T1& at(unsigned int index) const
		{
			return heap_array.at(index);
		}

		int find(T1 push_num) const//回傳index
		{
			for (int i = 0; i < heap_array.size(); i++)
				if (push_num == heap_array.at(i))
					return i;
			return -1;
		}
		void assign(int num, T1 value)
		{
			heap_array.assign(num, value);
		}

		typename vector<T1>::iterator begin(void)
		{
			return heap_array.begin();
		}

		typename vector<T1>::iterator end(void)
		{
			return heap_array.end();
		}

		typename vector<T1>::const_iterator cbegin(void) const
		{
			return heap_array.cbegin();
		}

		typename vector<T1>::const_iterator cend(void) const
		{
			return heap_array.cend();
		}
		typename vector<T1>& get_vector() const
		{
			return heap_array;
		}
		vector<T1> sort() const
		{
			vector<T1> result(heap_array);
			int index = 0;
			int key = 0;
			for (int i = result.size() / 2 - 1; i >= 1; i--)//這部因該可以不用，創建時已經有做了
				sink(i);
			for (int i = result.size() - 1; i >= 0; i--)
			{
				exch(result, 0, i);
				index = 0;
				while ((index + 1) * 2 <= i)
				{
					if ((index + 1) * 2 == i)
						key = (index + 1) * 2 - 1;
					else
					{
						if (result.at((index + 1) * 2) >= result.at((index + 1) * 2 - 1))
							key = (index + 1) * 2;
						else
							key = (index + 1) * 2 - 1;
					}
					if (result.at(index) > result.at(key))
						break;
					else
					{
						exch(result, index, key);
						index = key;
					}
				}
			}
			return result;
		}
		void inplace_sort()
		{
			int index = 0;
			int key = 0;
			for (int i = heap_array.size() / 2 - 1; i >= 1; i--)
				sink(i);
			for (int i = heap_array.size() - 1; i >= 0; i--)
			{
				exch(heap_array, 0, i);
				index = 0;
				while ((index + 1) * 2 <= i)
				{
					if ((index + 1) * 2 == i)
						key = (index + 1) * 2 - 1;
					else
					{
						if (heap_array.at((index + 1) * 2) >= heap_array.at((index + 1) * 2 - 1))
							key = (index + 1) * 2;
						else
							key = (index + 1) * 2 - 1;
					}
					if (heap_array.at(index) > heap_array.at(key))
						break;
					else
					{
						exch(heap_array, index, key);
						index = key;
					}
				}
			}
		}
		void print_sort() const
		{
			for (T1 i : heap_array)
				cout << i << "->";
		}

		void test_sort()
		{
			if (heap_array.size() <= 2)
				return;
			for (int i = 1; i < heap_array.size() - 1; i++)
			{
				if (f(heap_array.at(i), heap_array.at(i + 1)))
				{
					cout << "錯誤排序" << heap_array.at(i) << endl;
					return;
				}
			}
			cout << "正確!" << endl;
			return;
		}
	};

	template<typename T1 = double, typename  T2 = less<T1>>//此用法給directededge default max heap 排序是升序
	class min_indexed_PQ //此種方法無法用普通heap的方式排序
	{
	public:
		typename vector<T1>::size_type N = -1;
		typename vector<T1>::size_type NMAX = 0;
		T2 f = T2();
		mutable vector<T1> heap_array;//類別初始化 只能用預設初始化或者提供=號的初始器
		mutable vector<int> heap_index;
		mutable vector<int> edge_index;

		min_indexed_PQ()
		{
		}

		min_indexed_PQ(int max) :NMAX(max), heap_array(max), heap_index(max, -1), edge_index(max, -1)
		{
		}

		void swap(int i, int j)
		{
			int t = heap_index.at(i); heap_index.at(i) = heap_index.at(j); heap_index.at(j) = t;
			edge_index.at(heap_index.at(i)) = i; edge_index.at(heap_index.at(j)) = j;
		}

		bool contains(int i) {
			return edge_index.at(i) != -1;
		}

		int minIndex() {
			return heap_index.at(0);
		}

		T1 minKey() {
			return heap_array.at(heap_index.at(0));
		}

		int pop() {//回傳最小的點
			int top = heap_index.at(0);
			swap(0, N--);
			sink(0);
			edge_index.at(top) = -1;
			heap_index.at(N + 1) = -1;
			return top;
		}

		T1  pop_value() {//回傳最小的點
			int top = heap_index.at(0);
			T1 result = heap_array.at(heap_index.at(0));
			swap(0, N--);
			sink(0);
			edge_index[top] = -1;
			heap_index[N + 1] = -1;
			return result;
		}

		double keyOf(int i) {
			return heap_array.at(i);
		}

		void changeKey(int i, T1 value) {
			heap_array.at(i) = value;
			swimup(edge_index.at(i));
			sink(edge_index.at(i));
		}

		void decreaseKey(int i, double value) {
			heap_array.at(i) = value;
			swimup(edge_index.at(i));
		}

		void increaseKey(int i, double value) {
			heap_array.at(i) = value;
			sink(edge_index.at(i));
		}

		void deleteKey(int i) {
			int ind = edge_index.at(i);
			swap(ind, N--);
			swimup(ind);
			sink(ind);
			edge_index.at(i) = -1;
		}

		int swimup(int index)   //num是index   //回傳最後該元素所在位置 //index從1開始
		{
			if (index > N)
				return -1;
			while (index > 0 && f(heap_array.at(heap_index.at(index)), heap_array.at(heap_index.at((index - 1) / 2)
			)))
			{
				swap(index, ((index - 1) / 2));
				index = (index - 1) / 2;
			}
			return index;
		}

		int sink(int index)
		{
			if (index > N || index < 0)
				return -1;
			int key = 0;
			while ((index + 1) * 2 <= (N + 1))
			{
				if ((index + 1) * 2 == (N + 1))
					key = (index + 1) * 2 - 1;
				else
				{
					if (f(heap_array.at(heap_index.at((index + 1) * 2)), heap_array.at(heap_index.at((index + 1) * 2 - 1))))
						key = (index + 1) * 2;
					else
						key = (index + 1) * 2 - 1;
				}
				if (f(heap_array.at(heap_index.at(index)), heap_array.at(heap_index.at(key))))
					return index;
				else
				{
					swap(index, key);
					index = key;
				}
			}
			return index;
		}

		void insert(int i, T1 key) {
			N++;
			edge_index.at(i) = N;
			heap_index.at(N) = i;
			heap_array.at(i) = key;
			swimup(N);
		}

		T1 top()
		{
			if (heap_array.empty())
			{
				cout << "heap is empty" << endl;
				throw out_of_range("empty");
			}
			return heap_array.front();
		}

		bool empty() {
			return N == -1;
		}

		unsigned int size() const
		{
			return N + 1;
		}

		T1& at(unsigned int index) const
		{
			return heap_array.at(index);
		}

		int find(T1 push_num) const//回傳在heap的位置
		{
			for (int i = 0; i < heap_array.size(); i++)
				if (push_num == heap_array.at(i))
					return edge_index.at(i);
			return -1;
		}

		typename vector<T1>::iterator begin(void)
		{
			return heap_array.begin();
		}

		typename vector<T1>::iterator end(void)
		{
			return heap_array.end();
		}

		typename vector<T1>::const_iterator cbegin(void) const
		{
			return heap_array.cbegin();
		}

		typename vector<T1>::const_iterator cend(void) const
		{
			return heap_array.cend();
		}
		typename vector<T1>& get_vector() const
		{
			return heap_array;
		}
	};
	template <class T>
	class bucket
	{
	public:
		bucket()
		{
		}

		bucket(const vector<T> input)//input每個值對應一個大小
		{
			for (int i = 0; i < input.size(); i++)
				bucket_array[input.at(i)] = i;
		}

		map<T, int> bucket_array;

		int operator [](T a)
		{
			typename map<T, int>::const_iterator it = bucket_array.find(a);

			if (it == bucket_array.end())
			{
				cout << a << endl;
				cout << "無此索引" << endl;
				return -1;
			}
			else
				return bucket_array.at(a);
		}

		void reload(const vector<T> input)
		{
			bucket_array.clear();
			for (int i = 0; i < input.size(); i++)
				bucket_array[input.at(i)] = i;
		}

		unsigned int size()
		{
			return bucket_array.size();
		}
	};

	template <>
	class bucket<char>
	{
	public:
		bucket()
		{
		}

		bucket(const vector<char> input)//input每個值對應一個大小
		{
			for (int i = 0; i < input.size(); i++)
				bucket_array[input.at(i)] = i;
		}

		map<char, int> bucket_array;

		int& operator [](char a)
		{
			typename map<char, int>::const_iterator it = bucket_array.find(a);
			try
			{
				if (it == bucket_array.end())
					throw std::out_of_range("out of range");
			}
			catch (out_of_range err)
			{
				cout << err.what() << endl;
				exit(-2);
			}
			return bucket_array.at(a);
		}

		void reload(const vector<char> input)
		{
			bucket_array.clear();
			for (int i = 0; i < input.size(); i++)
				bucket_array[input.at(i)] = i;
		}

		unsigned int size()
		{
			return bucket_array.size();
		}

		void only_lower_case(bool order = true)  //字元用，只排小寫，order控制正向反向，ture正向，false反向
		{
			bucket_array.clear();
			if (order)
			{
				for (int i = 0; i < 26; i++)
				{
					bucket_array['a' + i] = i;
				}
			}
			else
			{
				for (int i = 0; i < 26; i++)
				{
					bucket_array['z' - i] = i;
				}
			}
		}

		void only_lower_case_with_dash(bool order = true)  //字元用，只排小寫，order控制正向反向，ture正向，false反向
		{
			bucket_array.clear();

			bucket_array['-'] = 0;
			bucket_array['/'] = 1;
			bucket_array['\''] = 2;
			bucket_array[')'] = 3;
			bucket_array['('] = 4;

			if (order)
			{
				for (int i = 0; i < 26; i++)
				{
					bucket_array['a' + i] = i + 5;
				}
			}
			else
			{
				for (int i = 0; i < 26; i++)
				{
					bucket_array['z' - i] = i + 5;
				}
			}
		}

		void only_captital(bool order = true)//字元用，只排大寫order控制正向反向，ture正向，false反向
		{
			bucket_array.clear();
			if (order)
			{
				for (int i = 0; i < 26; i++)
				{
					bucket_array['A' + i] = i;
				}
			}
			else
			{
				for (int i = 0; i < 26; i++)
				{
					bucket_array['Z' - i] = i;
				}
			}
		}

		void charsame1(bool order = true)//字元用，大小寫相同aAbB........  order控制正向反向，ture正向，false反向
		{
			bucket_array.clear();
			if (order)
			{
				for (int i = 0; i < 26; i++)
				{
					bucket_array['a' + i] = i * 2;
					bucket_array['A' + i] = i * 2 + 1;
				}
			}
			else
			{
				for (int i = 0; i < 26; i++)
				{
					bucket_array['Z' - i] = i * 2;
					bucket_array['z' - i] = i * 2 + 1;
				}
			}
		}

		void charsame2(bool order = true)//字元用，大小寫相同aAbB........  order控制正向反向，ture正向，false反向
		{
			bucket_array.clear();
			if (order)
			{
				for (int i = 0; i < 26; i++)
				{
					bucket_array['A' + i] = i * 2;
					bucket_array['a' + i] = i * 2 + 1;
				}
			}
			else
			{
				for (int i = 0; i < 26; i++)
				{
					bucket_array['z' - i] = i * 2;
					bucket_array['Z' - i] = i * 2 + 1;
				}
			}
		}

		void captital_smaller(bool order = true)//字元用，大寫較小ABCD....abcd    order控制正向反向，ture正向，false反向
		{
			bucket_array.clear();
			if (order)
			{
				for (int i = 0; i < 26; i++)
				{
					bucket_array['A' + i] = i;
				}

				for (int i = 0; i < 26; i++)
				{
					bucket_array['a' + i] = i + 26;
				}
			}
			else
			{
				for (int i = 0; i < 26; i++)
				{
					bucket_array['z' - i] = i;
				}

				for (int i = 0; i < 26; i++)
				{
					bucket_array['Z' - i] = i + 26;
				}
			}
		}

		void lowcase_smaller(bool order = true)//字元用，小寫較小abcd....ABCD      order控制正向反向，ture正向，false反向
		{
			bucket_array.clear();
			if (order)
			{
				for (int i = 0; i < 26; i++)
				{
					bucket_array['a' + i] = i;
				}

				for (int i = 0; i < 26; i++)
				{
					bucket_array['A' + i] = i + 26;
				}
			}
			else
			{
				for (int i = 0; i < 26; i++)
				{
					bucket_array['Z' - i] = i;
				}

				for (int i = 0; i < 26; i++)
				{
					bucket_array['z' - i] = i + 26;
				}
			}
		}
		void print_index()
		{
			typename map<char, int>::iterator it = bucket_array.begin();
			for (; it != bucket_array.end(); ++it)
				cout << it->first << " => " << it->second << '\n';
		}
	};

	template <>
	class bucket<int>
	{
	public:
		bucket()
		{
		}

		bucket(const vector<int> input)//input每個值對應一個大小
		{
			for (int i = 0; i < input.size(); i++)
				bucket_array[input.at(i)] = i;
		}

		map<int, int> bucket_array;

		int& operator [](char a)
		{
			typename map<int, int>::const_iterator it = bucket_array.find(a);
			try
			{
				if (it == bucket_array.end())
					throw std::out_of_range("out of range");
			}
			catch (out_of_range err)
			{
				cout << err.what() << endl;
				exit(-2);
			}
			return bucket_array.at(a);
		}

		void reload(const vector<int> input)
		{
			bucket_array.clear();
			for (int i = 0; i < input.size(); i++)
				bucket_array[input.at(i)] = i;
		}

		unsigned int size()
		{
			return bucket_array.size();
		}

		void print_index()
		{
			typename map<int, int>::iterator it = bucket_array.begin();
			for (; it != bucket_array.end(); ++it)
				cout << it->first << " => " << it->second << '\n';
		}
		void increase()
		{
			for (int i = -9; i < 10; i++)
				bucket_array[i] = i + 9;
		}

		void decrease()
		{
			for (int i = -9; i < 10; i++)
				bucket_array[i] = 9 - i;
		}
	};

	class graph
	{
	public:
		graph() = default;
		graph(int v);
		graph(vector<pair<int, int>> in);
		graph(vector<vector<int>> in);//須強制轉換 會跟上面的有衝突
		graph(const graph&) = default;
		graph& operator=(const graph&) = default;
		void add_edge(int v, int w);
		void add_edge(pair<int, int> vec);
		vector<int> adj(int v) const;
		int vertex_num() const;
		int edge_num() const;
		int degree(int v) const;
		void adli_to_adma();//adjacency_list to adjacency_matrix;
		void adli_to_inma();//adjacency_list to incident_matrix;
		int biggest_vertex = 0;
		vector< vector<int> > adjacency_matrix;
		vector< vector<int> > incident_matrix;
		vector< vector<int> > adjacency_list;
	};

	class digraph
	{
	public:
		digraph() = default;
		digraph(int v);
		digraph(vector<pair<int, int>> in);
		digraph(const digraph&) = default;
		digraph& operator=(const digraph&) = default;
		void add_edge(int v, int w);
		void add_edge(pair<int, int> vec);
		vector<int> adj(int v) const;
		int vertex_num() const;
		int edge_num() const;
		int out_degree(int v) const;
		void adli_to_adma();//adjacency_list to adjacency_matrix;
		void adli_to_inma();//adjacency_list to incident_matrix;
		int biggest_vertex = 0;
		vector<bool> in_map;//來確定vertex是否確實在map內
		vector< vector<int> > adjacency_matrix;
		vector< vector<int> > incident_matrix;
		vector< vector<int> > adjacency_list;
	};

	class edge//無向的dege
	{
	public:
		edge() :v(-1), w(-1), weight_num(DBL_MAX)
		{
		}

		edge(int a, int b, double c) :v(a), w(b), weight_num(c)
		{
		}
		int either() const;
		int other(int v) const;
		int compare_to(const edge&) const;
		void change_weight(double num);
		double weight() const;
	private:
		int v, w;
		double weight_num;
	};

	class directededge //無向的dege
	{
	public:
		directededge() :v(-1), w(-1), weight_num(DBL_MAX)
		{
		}

		directededge(int a, int b, double c) :v(a), w(b), weight_num(c)
		{
		}
		int from() const;
		int to() const;
		int compare_to(const directededge&) const;
		void change_weight(double num);
		double weight() const;
	private:
		int v, w;
		double weight_num;
	};

	bool operator<(const edge a, const edge b);
	bool operator==(const edge a, const edge b);
	bool operator>(const edge a, const edge b);

	class edge_weighted_graph//與許重複邊
	{
	public:
		edge_weighted_graph() = default;
		edge_weighted_graph(int v);
		edge_weighted_graph(vector<edge> in);
		edge_weighted_graph(const edge_weighted_graph&) = default;
		edge_weighted_graph& operator=(const edge_weighted_graph&) = default;
		void add_edge(int v, int w, double weight);
		void add_edge(const edge& vec);
		vector<edge> adj(int v) const;
		int vertex_num() const;
		int edge_num() const;
		int degree(int v);
		void adli_to_adma();//adjacency_list to adjacency_matrix;
		void adli_to_inma();//adjacency_list to incident_matrix;
		int biggest_vertex = 0;
		vector< vector<double> > adjacency_matrix;
		vector< vector<double> > incident_matrix;
		vector< vector<edge> > adjacency_list;
	};

	class edge_weighted_digraph//與許重複邊
	{
	public:
		edge_weighted_digraph() = default;
		edge_weighted_digraph(int v);
		edge_weighted_digraph(vector<directededge> in);
		edge_weighted_digraph(const edge_weighted_digraph&) = default;
		edge_weighted_digraph& operator=(const edge_weighted_digraph&) = default;
		void add_edge(int v, int w, double weight);
		void add_edge(const directededge& vec);
		vector<directededge> adj(int v) const;
		int vertex_num() const;
		int edge_num() const;
		int degree(int v);
		void adli_to_adma();//adjacency_list to adjacency_matrix;
		void adli_to_inma();//incident_matrix to adjacency_matrix;
		int biggest_vertex = 0;
		vector< vector<double> > adjacency_matrix;
		vector< vector<double> > incident_matrix;
		vector< vector<directededge> > adjacency_list;
		vector<bool> in_map;
	};

	class kruskalmst
	{
	public:
		kruskalmst(const edge_weighted_graph &g);

		vector<edge> edges() const;
		double weights() const;
		void print_edges() const;
		bool check_mst() const;
	private:
		edge_weighted_graph goal;
		vector<edge> mst_edge;
		int now_mst_vertex = 1;
	};

	class lazyprimmst
	{
	public:
		lazyprimmst(const edge_weighted_graph &g);

		void visit(int v);
		vector<edge> edges() const;
		double weights() const;
		void print_edges() const;
		bool check_mst() const;
	private:
		edge_weighted_graph goal;
		vector<bool> marked;
		vector<edge> mst_edge;
		heap<edge, less<edge>>   min_edge;
		int now_mst_vertex = 1;
	};

	class eagerprimmst
	{
	public:
		eagerprimmst(const edge_weighted_graph &g);

		void visit(int v);
		vector<edge> edges() const;
		double weights() const;
		void print_edges() const;
		bool check_mst() const;
	private:
		edge_weighted_graph goal;
		vector<bool> marked;
		vector<edge> mst_edge;
		vector<double> distto;
		vector<edge> edgeto;
		min_indexed_PQ<double> pq;

		heap<edge, less<edge>>   min_edge;
		int now_mst_vertex = 1;
	};

	class dijkstra_sp
	{
	public:
		dijkstra_sp() = default;
		dijkstra_sp(const edge_weighted_digraph &g, int s = 0);//s是起始點
		vector<directededge> path_to(int v);
		vector<int> path_to_vertex(int v);
		double weight_to(int v);
		void relax(directededge e);

	private:
		edge_weighted_digraph goal;
		vector<directededge> edge_to;
		vector<double> dist_to;
		min_indexed_PQ<double> pq;
		int initial_vertex = 0;
	};

	class dijkstra_sp_all
	{
	public:
		dijkstra_sp_all(const edge_weighted_digraph &g);//s是起始點

		vector<directededge> path(int s, int v);
		vector<int> path_vertex(int s, int v);
		double weight_to(int s, int v);

	private:
		vector<dijkstra_sp> all;
	};

	class acyclic_sp
	{
	public:
		acyclic_sp() = default;
		acyclic_sp(const edge_weighted_digraph &g, int s = 0);//s是起始點
		vector<directededge> path_to(int v);
		vector<int> path_to_vertex(int v);
		double weight_to(int v);
		void relax(directededge e);

	private:
		edge_weighted_digraph goal;
		vector<directededge> edge_to;
		vector<double> dist_to;
		int initial_vertex = 0;
	};

	class acyclic_sp_all
	{
	public:
		acyclic_sp_all(const edge_weighted_digraph &g);//s是起始點

		vector<directededge> path(int s, int v);
		vector<int> path_vertex(int s, int v);
		double weight_to(int s, int v);

	private:
		vector<acyclic_sp> all;
	};

	class bellman_ford_sp
	{
	public:
		bellman_ford_sp() = default;
		bellman_ford_sp(const edge_weighted_digraph &g, int s = 0);//s是起始點
		vector<directededge> path_to(int v);
		vector<int> path_to_vertex(int v);
		double weight_to(int v);
		void relax(directededge e);

	private:
		edge_weighted_digraph goal;
		vector<directededge> edge_to;
		vector<double> dist_to;
		queue<int> qe;
		vector<bool> on_qe;
		int initial_vertex = 0;
	};

	class bellman_ford_sp_all
	{
	public:
		bellman_ford_sp_all(const edge_weighted_digraph &g);//s是起始點

		vector<directededge> path(int s, int v);
		vector<int> path_vertex(int s, int v);
		double weight_to(int s, int v);

	private:
		vector<bellman_ford_sp> all;
	};

	class floyd_warshall_sp
	{
	public:
		floyd_warshall_sp(const edge_weighted_digraph &g);//s是起始點
		vector<int> path_vertex(int s, int v);
		double weight_to(int s, int v);
		vector<vector<int>> edge_to;
		vector < vector<double>> dist_to;

	private:
		edge_weighted_digraph goal;
	};

	class dfs
	{
	public:
		graph goal;
		vector<bool> marked;
		vector<int>  edge_from;
		int source = 0;
		dfs(const graph &g, int source) :goal(g), marked(g.adjacency_list.size(), false), edge_from(g.adjacency_list.size(), 0)
		{
			marked.at(source) = true;
			edge_from.at(source) = -1;//起點
			run(source);
		}
		void run(int source);
	};

	class bfs
	{
	public:
		graph goal;
		vector<bool> marked;
		vector<int>  edge_from;
		vector<int>  dist_from;
		queue<int> q;
		int source = 0;
		bfs(const graph &g, int source) :goal(g), marked(g.adjacency_list.size(), false), edge_from(g.adjacency_list.size(), 0), dist_from(g.adjacency_list.size(), 0)
		{
			run(source);
		}
		void run(int source);
	};

	class path//要放入起始點
	{
	public:
		graph goal;
		int source = 0;
		dfs result;
		path(graph g, int s = 0) :goal(g), source(s), result(g, s)//沒有預設建構器，一定要有graph 和 起點
		{
		}
		bool has_path_to(int v);
		vector<int> path_to(int v);
	};

	class cc
	{
	public:
		graph goal;
		cc(const graph& g) : goal(g), marked(g.adjacency_list.size(), false), id_num(g.adjacency_list.size(), -1)
		{
			for (int h = 0; h < goal.adjacency_list.size(); h++)
			{
				if (marked.at(h) == false)
				{
					dfs(h);
					count_num++;
				}
			}
		}
		bool connected(int v, int w);
		int count();
		int id(int v);
		void dfs(int source);
	private:
		int count_num = 0;
		vector<bool> marked;
		vector<int> id_num;
	};

	class cycle
	{
	public:
		cycle(const graph& g) : goal(g), marked(g.adjacency_list.size(), false), edge_from(g.adjacency_list.size(), 0)
		{
			for (int h = 0; h < goal.adjacency_list.size(); h++)
			{
				if (marked.at(h) == false)
				{
					dfs(h, h);
				}
			}
		}
		void dfs(int source, int before);
		bool has_cycle();
	private:
		vector<bool> marked;
		vector<int>  edge_from;
		bool has_cycle_num = false;
		graph goal;
	};

	class directedcycle
	{
	public:
		directedcycle(const digraph& g) : goal(g), marked(g.adjacency_list.size(), false), on_stack(g.adjacency_list.size(), false), edge_from(g.adjacency_list.size(), 0)
		{
			for (int h = 0; h < goal.adjacency_list.size(); h++)
			{
				if (marked.at(h) == false)
				{
					dfs(h);
				}
			}
		}
		void dfs(int source);
		bool has_cycle();
		vector<int> get_cycle();
	private:
		vector<bool> marked;
		vector<bool> on_stack;
		vector<int>  edge_from;
		vector<int> cycle;
		digraph goal;
	};

	class topological_sort
	{
	public:
		deque<int>  reverse_postorder;
		vector<int>  postorder;
		vector<int>  preorder;
		topological_sort(const digraph& g) : goal(g), marked(g.adjacency_list.size(), false)
		{
			for (int h = 0; h < goal.adjacency_list.size(); h++)
			{
				if (marked.at(h) == false)
				{
					dfs(h);
				}
			}
		}
		topological_sort(const edge_weighted_digraph& g) :goal2(g), marked(g.adjacency_list.size(), false)
		{
			for (int h = 0; h < goal2.adjacency_list.size(); h++)
			{
				if (marked.at(h) == false)
				{
					dfs_weigted_digraph(h);
				}
			}
		}

		void dfs(int source);
		void dfs_weigted_digraph(int source);
		bool has_cycle();
		vector<int> print_topology();
		vector<int> print_postorder();
		vector<int> print_preorder();
	private:
		vector<bool> marked;
		digraph goal;
		edge_weighted_digraph goal2;
	};

	void inner_msd_bucket_sort(vector<string> &input, vector<string> &aux, bucket<char> &input_bucket, int lo, int hi, int d = 0); //hi要放size - 1
	void msd_bucket_sort(vector<string> &input, bucket<char> char_bucket);
	void lsd_bucket_sort(vector<string> &input, bucket<char> input_bucket);
	void improve_lsd_bucket_sort(vector<int> &input, bool direct = true);

	void output_randnum_num(string name, unsigned int num, char delim = '\n');
	void output_string(string name, unsigned int num, vector<string> &output_data, char delim = '\n');
	void output_num(string name, unsigned int num, vector<int> output_data, char delim = '\n');
	unsigned int input_num(string name, unsigned int num, vector<int>& input, char delim = '\n');
	unsigned int input_string(string name, unsigned int num, vector<string>& input, char delim = '\n');
	unsigned int input_string_filter(string name, unsigned int num, vector<string>& input, char delim = '\n');

	int binary_search(vector<int>& input, int point);//回傳index
	string opsite_string(const string input);//ex:Today is a good day ->  day good a is Today

	template <class T>
	void output_file(string name, unsigned int num, vector<T> output_data, char delim = '\n')
	{
		ofstream ofile(name, ios::out);
		if (ofile.is_open())
		{
			if (num <= 0)
				return;
			for (int i = 0; i < (num - 1) && i < output_data.size(); i++)
			{
				ofile << output_data.at(i) << delim;
			}
			if (output_data.size() >= num)
				ofile << output_data.at(num - 1);
		}
		else
		{
			cout << "開啟檔案失敗" << endl;
			return;
		}
		ofile.close();
		cout << "已經輸出字串表" << endl;
		return;
	}

	double Permutations_c(int up, int down);
	double Permutations_p(int up, int down);

	template <class T>
	void shuffle(vector<T> &input)
	{
		default_random_engine e(time(0));
		for (int i = 0; i < input.size(); i++)
			exch(input, i, uniform_int_distribution<unsigned int>(0, i)(e));
	}

	template <typename T1, typename  T2 = less_equal<T1>>
	void test_sort(vector<T1> input, T2 f = T2())
	{
		if (input.size() <= 1)
			return;
		for (int i = 1; i < input.size(); i++)
		{
			if (f(input.at(i), input.at(i - 1)))
			{
				cout << "錯誤排序" << endl;
				return;
			}
		}
		cout << "正確!" << endl;
		return;
	}
	template <typename T1>
	int quick_selection(vector<T1> &input, int location)
	{
		int lo = 0;
		int hi = input.size() - 1;
		int index = 0;
		while (lo < hi)           //可以不用等於，因為最後一次就一定對了
		{
			index = partition(input, lo, hi, less<T1>());
			if (index > location)
				hi = index - 1;
			else if (index < location)
				lo = index + 1;
		}
		return input.at(index);
	}
}
#endif