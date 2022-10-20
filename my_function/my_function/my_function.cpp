// my_function.cpp : 此檔案包含 'main' 函式。程式會於該處開始執行及結束執行。
//

#include "pch.h"
#include <iostream>
#include "head.h"
#include "Peng.h"

void bfs_leetcode(vector<vector<int>>adjacency_list, int source)//leetcode:310
{
	vector<bool> marked(adjacency_list.size(), false);
	queue<int> q;
	q.push(source);
	marked.at(source) = true;

	while (!q.empty())
	{
		int temp = q.front();
		q.pop();
		for (int i : adjacency_list.at(temp))
		{
			if (marked.at(i) == false)
			{
				marked.at(i) = true;
				q.push(i);
			}
		}
	}
}

void bfs_leetcode(vector<set<int>>adjacency_list, int source)//leetcode:310
{
	vector<bool> marked(adjacency_list.size(), false);
	queue<int> q;
	q.push(source);
	marked.at(source) = true;

	while (!q.empty())
	{
		int temp = q.front();
		q.pop();
		for (int i : adjacency_list.at(temp))
		{
			if (marked.at(i) == false)
			{
				marked.at(i) = true;
				q.push(i);
			}
		}
	}
}

void trim(string &input)
{
	if (input.empty())
		return;
	input.erase(0, input.find_first_not_of(' '));
	input.erase(input.find_last_not_of(' ') + 1);
	return;
}

vector<string> split(const string &input, char delim, int pos)
{
	int before = 0;
	int last = 0;
	vector<string> result;
	last = input.find_first_of(delim, pos);

	while (last != -1)
	{
		result.push_back(input.substr(before, last - before));
		before = last + 1;
		last = input.find_first_of(delim, last + 1);
	}
	result.push_back(input.substr(before));
	return result;
}

namespace Peng
{
	int gcd(int a, int b)
	{
		if (b == 0) {
			return a;
		}
		return gcd(b, a % b);
	}

	graph::graph(int v) : adjacency_matrix(v + 1, vector<int>(v + 1)), incident_matrix(v + 1), adjacency_list(v + 1)
	{
	}
	int graph::vertex_num() const
	{
		int result = 0;
		for (auto a : adjacency_list)
		{
			if (!a.empty())
				result++;
		}
		return result;
	}

	int graph::edge_num() const
	{
		int result = 0;
		for (int i = 0; i < adjacency_list.size(); i++)
		{
			for (int j = 0; j < adjacency_list.at(i).size(); j++)
				if (adjacency_list.at(i).at(j) == i)//selfedge
					result += 2;
				else
					result++;
		}

		return result / 2;
	}

	graph::graph(vector<pair<int, int>> in)
	{
		for (auto a : in)
		{
			if (a.first > biggest_vertex)
				biggest_vertex = a.first;
			if (a.second > biggest_vertex)
				biggest_vertex = a.second;
		}

		adjacency_list.assign(biggest_vertex + 1, vector<int>());

		for (auto a : in)
		{
			adjacency_list.at(a.first).push_back(a.second);
			adjacency_list.at(a.second).push_back(a.first);
		}
	}

	//會和graph::graph(vector<pair<int, int>> in)有衝突
	graph::graph(vector<vector<int>> in)
	{
		for (auto a : in)
		{
			if (a.at(0) > biggest_vertex)
				biggest_vertex = a.at(0);
			if (a.at(1) > biggest_vertex)
				biggest_vertex = a.at(1);
		}

		adjacency_list.assign(biggest_vertex + 1, vector<int>());

		for (auto a : in)
		{
			adjacency_list.at(a.at(0)).push_back(a.at(1));
			adjacency_list.at(a.at(1)).push_back(a.at(0));
		}
	}

	vector<int> graph::adj(int v) const
	{
		vector<int> result;
		for (auto a : adjacency_list.at(v))
		{
			result.push_back(a);
		}
		return result;
	}

	int graph::degree(int v) const
	{
		return  adj(v).size();
	}

	void graph::add_edge(int v, int w)
	{
		if (v >= adjacency_list.size())
		{
			for (int i = adjacency_list.size(); i <= v; i++)
			{
				adjacency_list.push_back(vector<int>());
			}
		}

		if (w >= adjacency_list.size())
		{
			for (int i = adjacency_list.size(); i <= w; i++)
			{
				adjacency_list.push_back(vector<int>());
			}
		}
		if (find(adjacency_list.at(v).begin(), adjacency_list.at(v).end(), w) == adjacency_list.at(v).end())
		{
			adjacency_list.at(v).push_back(w);
			adjacency_list.at(w).push_back(v);
		}

		return;
	}

	void graph::add_edge(pair<int, int> vec)
	{
		add_edge(vec.first, vec.second);
	}

	void graph::adli_to_adma()
	{
		adjacency_matrix.assign(adjacency_list.size(), vector<int>(adjacency_list.size(), 0));
		for (int i = 0; i < adjacency_list.size(); i++)
			for (int j = 0; j < adjacency_list.at(i).size(); j++)
			{
				adjacency_matrix.at(i).at(j) = 1;
				adjacency_matrix.at(j).at(i) = 1;
			}
	}

	void graph::adli_to_inma()
	{
		incident_matrix.push_back(vector<int>(adjacency_list.size(), 0));
		for (int i = 0; i < adjacency_list.size(); i++)
			for (int j = 0; j < adjacency_list.at(i).size(); j++)
			{
				incident_matrix.back().at(i) = 1;
				incident_matrix.back().at(j) = 1;
			}
	}

	//---------------------------------------------------------------------------------------------

	digraph::digraph(int v) :in_map(v + 1, false), adjacency_matrix(v + 1, vector<int>(v + 1)), incident_matrix(v + 1), adjacency_list(v + 1)
	{
	}

	int digraph::vertex_num() const
	{
		int result = 0;
		//for (auto a : adjacency_list)  //這會錯
		//{
		//	if (!a.empty())
		//		result++;
		//}

		for (const auto a : in_map)
		{
			if (a)
			{
				result++;
			}
		}
		return result;
	}

	int digraph::edge_num() const
	{
		int result = 0;
		for (int i = 0; i < adjacency_list.size(); i++)
		{
			for (int j = 0; j < adjacency_list.at(i).size(); j++)
				result++;
		}

		return result;
	}

	digraph::digraph(vector<pair<int, int>> in)
	{
		for (auto a : in)
		{
			if (a.first > biggest_vertex)
				biggest_vertex = a.first;
			if (a.second > biggest_vertex)
				biggest_vertex = a.second;
		}

		adjacency_list.assign(biggest_vertex + 1, vector<int>());
		in_map.assign(biggest_vertex + 1, false);
		for (auto a : in)
		{
			in_map.at(a.first) = true;
			in_map.at(a.second) = true;
			adjacency_list.at(a.first).push_back(a.second);
		}
	}

	vector<int> digraph::adj(int v) const
	{
		vector<int> result;
		for (auto a : adjacency_list.at(v))
		{
			result.push_back(a);
		}
		return result;
	}

	int digraph::out_degree(int v) const//這應該要又分outdegree 和indegree
	{
		return  adj(v).size();
	}

	void digraph::add_edge(int v, int w)
	{
		if (v >= adjacency_list.size())
		{
			for (int i = adjacency_list.size(); i <= v; i++)
			{
				adjacency_list.push_back(vector<int>());
				in_map.push_back(false);
			}
		}

		if (w >= adjacency_list.size())
		{
			for (int i = adjacency_list.size(); i <= w; i++)
			{
				adjacency_list.push_back(vector<int>());
				in_map.push_back(false);
			}
		}
		if (find(adjacency_list.at(v).begin(), adjacency_list.at(v).end(), w) == adjacency_list.at(v).end())
		{
			adjacency_list.at(v).push_back(w);
			in_map.at(v) = true;
			in_map.at(w) = true;
		}
		return;
	}

	void digraph::add_edge(pair<int, int> vec)
	{
		add_edge(vec.first, vec.second);
	}

	void digraph::adli_to_adma()
	{
		adjacency_matrix.assign(adjacency_list.size(), vector<int>(adjacency_list.size(), 0));
		for (int i = 0; i < adjacency_list.size(); i++)
			for (int j = 0; j < adjacency_list.at(i).size(); j++)
			{
				adjacency_matrix.at(i).at(j) = 1;
			}
	}

	void digraph::adli_to_inma()
	{
		incident_matrix.push_back(vector<int>(adjacency_list.size(), 0));
		for (int i = 0; i < adjacency_list.size(); i++)
			for (int j = 0; j < adjacency_list.at(i).size(); j++)
			{
				incident_matrix.back().at(i) = 1;
				incident_matrix.back().at(j) = 1;
			}
	}

	int edge::either() const
	{
		return v;
	}

	int edge::other(int v) const
	{
		try
		{
			if (v != this->v)
				throw domain_error("not from either()");
		}
		catch (domain_error err)
		{
			err.what();
			return v;
		}
		return w;
	}

	double edge::weight() const
	{
		return weight_num;
	}

	void edge::change_weight(double num)
	{
		weight_num = num;
	}

	int edge::compare_to(const edge& input) const
	{
		if (this->weight_num > input.weight())
			return 1;
		else if (this->weight_num < input.weight())
			return -1;
		else
			return 0;
	}

	int directededge::from() const
	{
		return v;
	}

	int directededge::to() const
	{
		return w;
	}

	double directededge::weight() const
	{
		return weight_num;
	}

	void directededge::change_weight(double num)
	{
		weight_num = num;
	}

	int directededge::compare_to(const directededge& input) const
	{
		if (this->weight_num > input.weight())
			return 1;
		else if (this->weight_num < input.weight())
			return -1;
		else
			return 0;
	}

	bool operator<(const edge a, const edge b)
	{
		return a.weight() < b.weight();
	}

	bool operator==(const edge a, const edge b)
	{
		return a.weight() == b.weight();
	}

	bool operator>(const edge a, const edge b)
	{
		return a.weight() > b.weight();
	}

	bool operator<(const directededge a, const directededge b)
	{
		return a.weight() < b.weight();
	}

	bool operator==(const directededge a, const directededge b)
	{
		return a.weight() == b.weight();
	}

	bool operator>(const directededge a, const directededge b)
	{
		return a.weight() > b.weight();
	}

	edge_weighted_graph::edge_weighted_graph(int v) : adjacency_matrix(v + 1, vector<double>(v + 1, DBL_MAX)), adjacency_list(v + 1)
	{
	}

	int edge_weighted_graph::vertex_num() const
	{
		int result = 0;
		for (auto a : adjacency_list)
		{
			if (!a.empty())
				result++;
		}
		return result;
	}

	int edge_weighted_graph::edge_num() const
	{
		int result = 0;
		for (int i = 0; i < adjacency_list.size(); i++)
		{
			for (int j = 0; j < adjacency_list.at(i).size(); j++)
				if (adjacency_list.at(i).at(j).either() == i && adjacency_list.at(i).at(j).other(adjacency_list.at(i).at(j).either()) == i)//selfedge
					result += 2;
				else
					result++;
		}

		return result / 2;
	}

	edge_weighted_graph::edge_weighted_graph(vector<edge> in)
	{
		for (auto a : in)
		{
			int vertex_1 = a.either();
			int vertex_2 = a.other(vertex_1);
			if (vertex_1 > biggest_vertex)
				biggest_vertex = vertex_1;
			if (vertex_2 > biggest_vertex)
				biggest_vertex = vertex_2;
		}

		adjacency_list.assign(biggest_vertex + 1, vector<edge>());

		for (auto a : in)
		{
			int vertex_1 = a.either();
			int vertex_2 = a.other(vertex_1);

			adjacency_list.at(vertex_1).push_back(a);
			edge temp(vertex_2, vertex_1, a.weight());
			adjacency_list.at(vertex_2).push_back(temp);//預防後續會由重複情況
		}
	}

	vector<edge> edge_weighted_graph::adj(int v) const
	{
		vector<edge> result;
		for (const auto a : adjacency_list.at(v))
		{
			result.push_back(a);
		}
		return result;
	}

	int edge_weighted_graph::degree(int v)
	{
		return  adj(v).size();
	}

	void edge_weighted_graph::add_edge(int v, int w, double weight)
	{
		if (v >= adjacency_list.size())
		{
			for (int i = adjacency_list.size(); i <= v; i++)
			{
				adjacency_list.push_back(vector<edge>());
			}
		}

		if (w >= adjacency_list.size())
		{
			for (int i = adjacency_list.size(); i <= w; i++)
			{
				adjacency_list.push_back(vector<edge>());
			}
		}
		edge add1(v, w, weight);
		adjacency_list.at(v).push_back(add1);
		edge add2(w, v, weight);
		adjacency_list.at(w).push_back(add2);

		return;
	}

	void edge_weighted_graph::add_edge(const edge& vec)
	{
		int vertex_1 = vec.either();
		int vertex_2 = vec.other(vertex_1);
		if (vertex_1 >= adjacency_list.size())
		{
			for (int i = adjacency_list.size(); i <= vertex_1; i++)
			{
				adjacency_list.push_back(vector<edge>());
			}
		}

		if (vertex_2 >= adjacency_list.size())
		{
			for (int i = adjacency_list.size(); i <= vertex_2; i++)
			{
				adjacency_list.push_back(vector<edge>());
			}
		}
		adjacency_list.at(vertex_1).push_back(vec);
		edge temp(vertex_2, vertex_1, vec.weight());
		adjacency_list.at(vertex_2).push_back(temp);
		return;
	}

	void edge_weighted_graph::adli_to_adma()
	{
		adjacency_matrix.assign(adjacency_list.size(), vector<double>(adjacency_list.size(), DBL_MAX));
		for (const auto &a : adjacency_list)
			for (const auto &b : a)
			{
				int vertex_1 = b.either();
				int vertex_2 = b.other(b.either());
				adjacency_matrix.at(vertex_1).at(vertex_2) = b.weight();
				adjacency_matrix.at(vertex_2).at(vertex_1) = b.weight();
			}
	}

	void edge_weighted_graph::adli_to_inma()
	{
		for (const auto &a : adjacency_list)
			for (const auto &b : a)
			{
				int vertex_1 = b.either();
				int vertex_2 = b.other(b.either());
				incident_matrix.push_back(vector<double>(adjacency_list.size(), 0));
				incident_matrix.back().at(vertex_1) = b.weight();
				incident_matrix.back().at(vertex_2) = b.weight();
			}
	}

	edge_weighted_digraph::edge_weighted_digraph(int v) : adjacency_matrix(v + 1, vector<double>(v + 1, DBL_MAX)), adjacency_list(v + 1)
	{
	}

	int edge_weighted_digraph::vertex_num() const
	{
		int result = 0;
		for (const auto a : in_map)
		{
			if (a)
			{
				result++;
			}
		}
		return result;
	}

	int edge_weighted_digraph::edge_num() const
	{
		int result = 0;
		for (int i = 0; i < adjacency_list.size(); i++)
		{
			for (int j = 0; j < adjacency_list.at(i).size(); j++)
				result++;
		}

		return result;
	}

	edge_weighted_digraph::edge_weighted_digraph(vector<directededge> in)
	{
		for (auto a : in)
		{
			int vertex_1 = a.from();
			int vertex_2 = a.to();
			if (vertex_1 > biggest_vertex)
				biggest_vertex = vertex_1;
			if (vertex_2 > biggest_vertex)
				biggest_vertex = vertex_2;
		}

		adjacency_list.assign(biggest_vertex + 1, vector<directededge>());
		in_map.assign(biggest_vertex + 1, false);
		for (auto a : in)
		{
			int vertex_1 = a.from();
			int vertex_2 = a.to();
			in_map.at(vertex_1) = true;
			in_map.at(vertex_2) = true;
			adjacency_list.at(vertex_1).push_back(a);
		}
	}

	vector<directededge> edge_weighted_digraph::adj(int v) const
	{
		vector<directededge> result;
		for (const auto a : adjacency_list.at(v))
		{
			result.push_back(a);
		}
		return result;
	}

	int edge_weighted_digraph::degree(int v)
	{
		return  adj(v).size();
	}

	void edge_weighted_digraph::add_edge(int v, int w, double weight)
	{
		if (v >= adjacency_list.size())
		{
			for (int i = adjacency_list.size(); i <= v; i++)
			{
				adjacency_list.push_back(vector<directededge>());
				in_map.push_back(false);
			}
		}

		if (w >= adjacency_list.size())
		{
			for (int i = adjacency_list.size(); i <= w; i++)
			{
				adjacency_list.push_back(vector<directededge>());
				in_map.push_back(false);
			}
		}
		directededge add(v, w, weight);
		in_map.at(v) = true;
		in_map.at(w) = true;
		adjacency_list.at(v).push_back(add);

		return;
	}

	void edge_weighted_digraph::add_edge(const directededge& vec)
	{
		int vertex_1 = vec.from();
		int vertex_2 = vec.to();
		if (vertex_1 >= adjacency_list.size())
		{
			for (int i = adjacency_list.size(); i <= vertex_1; i++)
			{
				adjacency_list.push_back(vector<directededge>());
				in_map.push_back(false);
			}
		}

		if (vertex_2 >= adjacency_list.size())
		{
			for (int i = adjacency_list.size(); i <= vertex_2; i++)
			{
				adjacency_list.push_back(vector<directededge>());
				in_map.push_back(false);
			}
		}
		in_map.at(vertex_1) = true;
		in_map.at(vertex_2) = true;
		adjacency_list.at(vertex_1).push_back(vec);
		return;
	}

	void edge_weighted_digraph::adli_to_adma()
	{
		adjacency_matrix.assign(adjacency_list.size(), vector<double>(adjacency_list.size(), DBL_MAX));
		for (const auto &a : adjacency_list)
			for (const auto &b : a)
			{
				adjacency_matrix.at(b.from()).at(b.to()) = b.weight();
			}
	}

	void edge_weighted_digraph::adli_to_inma()
	{
		for (const auto &a : adjacency_list)
			for (const auto &b : a)
			{
				incident_matrix.push_back(vector<double>(adjacency_list.size(), 0));
				incident_matrix.back().at(b.from()) = b.weight();
				incident_matrix.back().at(b.to()) = b.weight();
			}
	}

	void dfs::run(int source)
	{
		for (int i : goal.adj(source))
		{
			if (marked.at(i) == false)
			{
				marked.at(i) = true;
				edge_from.at(i) = source;
				run(i);
			}
		}
		//for (auto i = goal.adjacency_list.at(source).cbegin(); i != goal.adjacency_list.at(source).cend(); i++)
		//{
		//	if (marked.at(*i) == false)
		//	{
		//		marked.at(*i) = true;
		//		edge_from.at(*i) = source;
		//		run(*i);
		//	}
		//}
	}

	void bfs::run(int source)
	{
		queue<int> q;
		q.push(source);
		marked.at(source) = true;
		edge_from.at(source) = -1;//起點
		dist_from.at(source) = 0;
		while (!q.empty())
		{
			int temp = q.front();
			q.pop();
			for (int i : goal.adj(temp))
			{
				if (marked.at(i) == false)
				{
					marked.at(i) = true;
					edge_from.at(i) = temp;
					dist_from.at(i) = dist_from.at(temp) + 1;
					q.push(i);
				}
			}
			//for (auto i = goal.adjacency_list.at(temp).cbegin(); i != goal.adjacency_list.at(temp).cend(); i++)
			//{
			//	if (marked.at(*i) == false)
			//	{
			//		marked.at(*i) = true;
			//		edge_from.at(*i) = temp;
			//		dist_from.at(*i) = dist_from.at(temp) + 1;
			//		q.push(*i);
			//	}
			//}
		}
	}

	bool path::has_path_to(int v)
	{
		return result.marked.at(v);
	}
	vector<int> path::path_to(int v)
	{
		vector<int> path;
		path.push_back(v);
		while (result.edge_from.at(v) != -1)
		{
			path.push_back(result.edge_from.at(v));
			v = result.edge_from.at(v);
		}
		reverse(path.begin(), path.end());
		return path;
	}

	void cc::dfs(int source)
	{
		marked.at(source) = true;
		id_num.at(source) = count_num;
		for (int i : goal.adj(source))
		{
			if (marked.at(i) == false)
			{
				dfs(i);
			}
		}
	}

	void cycle::dfs(int source, int before)
	{
		marked.at(source) = true;
		for (int i : goal.adj(source))
		{
			if (marked.at(i) == false)
			{
				//edge_from.at(i) = source;//之後可以做印出cycle(目前還沒做)
				dfs(i, source);
			}
			else
			{
				if (i != before)
				{
					has_cycle_num = true;
					break;
				}
			}
		}
	}
	bool cycle::has_cycle()
	{
		return has_cycle_num;
	}

	void directedcycle::dfs(int source)
	{
		on_stack.at(source) = true;
		marked.at(source) = true;
		for (int i : goal.adj(source))
		{
			if (has_cycle())
				return;
			else if (marked.at(i) == false)
			{
				edge_from.at(i) = source;
				dfs(i);
			}
			else if (on_stack.at(i) == true)
			{
				for (int j = source; j != i; j = edge_from.at(j))
				{
					cycle.push_back(j);
				}
				cycle.push_back(i);
				cycle.push_back(source);
			}
		}
		on_stack.at(source) = false;
	}
	bool directedcycle::has_cycle()
	{
		return !cycle.empty();
	}

	vector<int> directedcycle::get_cycle()
	{
		return cycle;
	}

	int cc::count()
	{
		return count_num;
	}

	int cc::id(int v)
	{
		return id_num.at(v);
	}

	bool cc::connected(int v, int w)
	{
		return id_num.at(v) == id_num.at(w);
	}

	void topological_sort::dfs(int source)
	{
		marked.at(source) = true;
		preorder.push_back(source);
		for (int i : goal.adj(source))
		{
			if (marked.at(i) == false)
			{
				//edge_from.at(i) = source;//之後可以做印出cycle(目前還沒做)
				dfs(i);
			}
		}
		reverse_postorder.push_front(source);
		postorder.push_back(source);
	}

	void topological_sort::dfs_weigted_digraph(int source)
	{
		marked.at(source) = true;
		preorder.push_back(source);
		for (const auto i : goal2.adj(source))
		{
			if (marked.at(i.to()) == false)
			{
				//edge_from.at(i) = source;//之後可以做印出cycle(目前還沒做)
				dfs_weigted_digraph(i.to());
			}
		}
		reverse_postorder.push_front(source);
		postorder.push_back(source);
	}

	vector<int> topological_sort::print_topology()
	{
		vector<int> result(reverse_postorder.begin(), reverse_postorder.end());
		Peng::print_vector(result);
		return result;
	}

	vector<int> topological_sort::print_postorder()
	{
		vector<int> result(postorder.begin(), postorder.end());
		Peng::print_vector(result);
		return result;
	}

	vector<int> topological_sort::print_preorder()
	{
		vector<int> result(preorder.begin(), preorder.end());
		Peng::print_vector(result);
		return result;
	}
	kruskalmst::kruskalmst(const edge_weighted_graph &g) :goal(g)
	{
		QuickUnionUF check_cycle(goal.vertex_num());
		heap<edge, less<edge>> for_mst;

		for (int i = 0; i < goal.adjacency_list.size(); i++)
		{
			for (int j = 0; j < goal.adjacency_list.at(i).size(); j++)
			{
				if (goal.adjacency_list.at(i).at(j).either() <= goal.adjacency_list.at(i).at(j).other(g.adjacency_list.at(i).at(j).either()))
					for_mst.push(goal.adjacency_list.at(i).at(j));
			}
		}

		int vertex = goal.vertex_num();
		while (!for_mst.empty() && now_mst_vertex < vertex)
		{
			edge temp = for_mst.pop();
			if (!check_cycle.connect(temp.either(), temp.other(temp.either())))
			{
				mst_edge.push_back(temp);
				check_cycle.union_two(temp.either(), temp.other(temp.either()));
				now_mst_vertex++;
			}
		}
	}
	vector<edge> kruskalmst::edges() const
	{
		return mst_edge;
	}

	void  kruskalmst::print_edges() const
	{
		for (const auto a : mst_edge)
		{
			cout << "(" << a.either() << " , " << a.other(a.either()) << ")" << endl;
		}
	}

	double kruskalmst::weights() const
	{
		double result = 0;
		for (const auto a : mst_edge)
		{
			result += a.weight();
		}
		return result;
	}

	bool kruskalmst::check_mst() const
	{
		if (goal.vertex_num() == now_mst_vertex)
			return true;
		return false;
	}

	lazyprimmst::lazyprimmst(const edge_weighted_graph &g) :goal(g), marked(g.adjacency_list.size(), false)
	{
		visit(0);
		while (!min_edge.empty() && mst_edge.size() < goal.vertex_num() - 1)
		{
			edge temp = min_edge.pop();
			int vertex_to = temp.other(temp.either());
			if (marked.at(vertex_to))
				continue;
			mst_edge.push_back(temp);
			visit(vertex_to);
		}
	}
	void lazyprimmst::visit(int v)
	{
		marked.at(v) = true;
		for (const auto a : goal.adj(v))
		{
			if (!marked.at(a.other(a.either())))
			{
				//cout << a.either() << " , " << a.other(a.either()) << endl;
				min_edge.push(a);
			}
		}
	}

	vector<edge> lazyprimmst::edges() const
	{
		return mst_edge;
	}

	void  lazyprimmst::print_edges() const
	{
		for (const auto a : mst_edge)
		{
			cout << "(" << a.either() << " , " << a.other(a.either()) << ")" << endl;
		}
	}

	double lazyprimmst::weights() const
	{
		double result = 0;
		for (const auto a : mst_edge)
		{
			result += a.weight();
		}
		return result;
	}

	bool lazyprimmst::check_mst() const
	{
		if (goal.vertex_num() == mst_edge.size() + 1)
			return true;
		return false;
	}

	eagerprimmst::eagerprimmst(const edge_weighted_graph &g) :goal(g), marked(g.adjacency_list.size(), false), distto(g.adjacency_list.size(), DBL_MAX), edgeto(g.adjacency_list.size(), edge()), pq(g.adjacency_list.size())
	{
		distto.at(0) = 0;
		pq.insert(0, 0.0);
		while (!pq.empty())
		{
			auto v = pq.pop();
			visit(v);
			//cout << v << endl;
			if (!pq.empty())
				mst_edge.push_back(edgeto.at(pq.minIndex()));
		}
	}

	void eagerprimmst::visit(int v)
	{
		marked.at(v) = true;
		for (const auto a : goal.adj(v))
		{
			int w = a.other(a.either());
			if (!marked.at(w))
			{
				//cout << a.either() << " , " << a.other(a.either()) << endl;
				if (a.weight() < distto.at(w))
				{
					edgeto.at(w) = a;
					distto.at(w) = a.weight();
					if (pq.contains(w))
						pq.changeKey(w, a.weight());
					else
						pq.insert(w, a.weight());
				}
			}
		}
	}

	vector<edge> eagerprimmst::edges() const
	{
		return mst_edge;
	}

	void  eagerprimmst::print_edges() const
	{
		for (const auto a : mst_edge)
		{
			cout << "(" << a.either() << " , " << a.other(a.either()) << ")" << endl;
		}
	}

	double eagerprimmst::weights() const
	{
		double result = 0;
		for (const auto a : mst_edge)
		{
			result += a.weight();
		}
		return result;
	}

	bool eagerprimmst::check_mst() const
	{
		if (goal.vertex_num() == mst_edge.size() + 1)
			return true;
		return false;
	}

	dijkstra_sp::dijkstra_sp(const edge_weighted_digraph &g, int s) :goal(g), initial_vertex(s), edge_to(g.vertex_num()), dist_to(g.vertex_num(), DBL_MAX), pq(g.vertex_num())
	{
		dist_to.at(s) = 0;
		edge_to.at(s) = directededge(s, s, 0);
		pq.insert(s, 0);
		while (!pq.empty())
		{
			int v = pq.pop();
			//cout << "v: " << v << endl;
			for (const auto a : goal.adj(v))
			{
				//cout << a.to() << " , ";
				relax(a);
			}
		}
	}

	void dijkstra_sp::relax(directededge e)
	{
		int v = e.from();
		int w = e.to();
		if (dist_to.at(w) > dist_to.at(v) + e.weight())
		{
			//cout << "w: " << w << endl;
			dist_to.at(w) = dist_to.at(v) + e.weight();
			edge_to.at(w) = e;
			if (pq.contains(w))
				pq.decreaseKey(w, dist_to.at(w));
			else
				pq.insert(w, dist_to.at(w));
		}
	}

	vector<directededge> dijkstra_sp::path_to(int v)
	{
		stack<directededge> temp;
		if (edge_to.at(v).from() == -1)
		{
			cout << "no path from: " << initial_vertex << " to " << v << endl;
			return vector<directededge>();
		}
		for (directededge e = edge_to.at(v); e.to() != initial_vertex; e = edge_to.at(e.from()))
		{
			temp.push(e);
		}

		vector<directededge> result;
		while (!temp.empty())
		{
			result.push_back(temp.top());
			cout << temp.top().from() << "->";
			temp.pop();
		}
		cout << v << endl;
		return result;
	}

	vector<int> dijkstra_sp::path_to_vertex(int v)
	{
		stack<directededge> temp;
		if (edge_to.at(v).from() == -1)
		{
			cout << "no path from: " << initial_vertex << " to " << v << endl;
			return vector<int>();
		}
		for (directededge e = edge_to.at(v); e.to() != initial_vertex; e = edge_to.at(e.from()))
		{
			temp.push(e);
		}

		vector<int> result;
		while (!temp.empty())
		{
			result.push_back(temp.top().from());
			cout << temp.top().from() << "->";
			temp.pop();
		}
		cout << v << endl;
		result.push_back(v);
		print_vector(result);
		return result;
	}

	double dijkstra_sp::weight_to(int v)
	{
		if (edge_to.at(v).from() == -1)//沒這個if 印出來的會是DBL_MAX
			return 0;
		return dist_to.at(v);
	}

	acyclic_sp::acyclic_sp(const edge_weighted_digraph &g, int s) :goal(g), initial_vertex(s), edge_to(g.vertex_num()), dist_to(g.vertex_num(), DBL_MAX)
	{
		dist_to.at(s) = 0;
		edge_to.at(s) = directededge(s, s, 0);
		vector<int> topo_sort = topological_sort(g).print_topology();
		for (int i = 0; i < topo_sort.size(); i++)
		{
			for (const auto a : goal.adj(topo_sort.at(i)))
				relax(a);
		}
	}

	void acyclic_sp::relax(directededge e)
	{
		int v = e.from();
		int w = e.to();
		if (dist_to.at(w) > dist_to.at(v) + e.weight())
		{
			//cout << "w: " << w << endl;
			dist_to.at(w) = dist_to.at(v) + e.weight();
			edge_to.at(w) = e;
			print_vector(dist_to);
		}
	}

	vector<directededge> acyclic_sp::path_to(int v)
	{
		stack<directededge> temp;
		if (edge_to.at(v).from() == -1)
		{
			cout << "no path from: " << initial_vertex << " to " << v << endl;
			return vector<directededge>();
		}
		for (directededge e = edge_to.at(v); e.to() != initial_vertex; e = edge_to.at(e.from()))
		{
			temp.push(e);
		}

		vector<directededge> result;
		while (!temp.empty())
		{
			result.push_back(temp.top());
			cout << temp.top().from() << "->";
			temp.pop();
		}
		cout << v << endl;
		return result;
	}

	vector<int> acyclic_sp::path_to_vertex(int v)
	{
		stack<directededge> temp;
		if (edge_to.at(v).from() == -1)
		{
			cout << "no path from: " << initial_vertex << " to " << v << endl;
			return vector<int>();
		}
		for (directededge e = edge_to.at(v); e.to() != initial_vertex; e = edge_to.at(e.from()))
		{
			temp.push(e);
		}

		vector<int> result;
		while (!temp.empty())
		{
			result.push_back(temp.top().from());
			cout << temp.top().from() << "->";
			temp.pop();
		}
		cout << v << endl;
		result.push_back(v);
		print_vector(result);
		return result;
	}

	double acyclic_sp::weight_to(int v)
	{
		if (edge_to.at(v).from() == -1)//沒這個if 印出來的會是DBL_MAX
			return 0;
		return dist_to.at(v);
	}

	dijkstra_sp_all::dijkstra_sp_all(const edge_weighted_digraph &g) :all(g.vertex_num(), dijkstra_sp())
	{
		for (int i = 0; i < g.vertex_num(); i++)
		{
			all.at(i) = dijkstra_sp(g, i);
		}
	}

	vector<directededge> dijkstra_sp_all::path(int s, int v)
	{
		return all.at(s).path_to(v);
	}
	vector<int> dijkstra_sp_all::path_vertex(int s, int v)
	{
		return all.at(s).path_to_vertex(v);
	}
	double dijkstra_sp_all::weight_to(int s, int v)
	{
		return all.at(s).weight_to(v);
	}

	acyclic_sp_all::acyclic_sp_all(const edge_weighted_digraph &g) :all(g.vertex_num(), acyclic_sp())
	{
		for (int i = 0; i < g.vertex_num(); i++)
		{
			all.at(i) = acyclic_sp(g, i);
		}
	}

	vector<directededge> acyclic_sp_all::path(int s, int v)
	{
		return all.at(s).path_to(v);
	}

	vector<int> acyclic_sp_all::path_vertex(int s, int v)
	{
		return all.at(s).path_to_vertex(v);
	}

	double acyclic_sp_all::weight_to(int s, int v)
	{
		return all.at(s).weight_to(v);
	}

	bellman_ford_sp_all::bellman_ford_sp_all(const edge_weighted_digraph &g) :all(g.vertex_num(), bellman_ford_sp())
	{
		for (int i = 0; i < g.vertex_num(); i++)
		{
			all.at(i) = bellman_ford_sp(g, i);
		}
	}

	vector<directededge> bellman_ford_sp_all::path(int s, int v)
	{
		return all.at(s).path_to(v);
	}

	vector<int> bellman_ford_sp_all::path_vertex(int s, int v)
	{
		return all.at(s).path_to_vertex(v);
	}

	double bellman_ford_sp_all::weight_to(int s, int v)
	{
		return all.at(s).weight_to(v);
	}

	bellman_ford_sp::bellman_ford_sp(const edge_weighted_digraph &g, int s) :goal(g), initial_vertex(s), edge_to(g.vertex_num()), dist_to(g.vertex_num(), DBL_MAX), on_qe(g.vertex_num(), false)
	{
		dist_to.at(s) = 0;
		edge_to.at(s) = directededge(s, s, 0);
		qe.push(s);
		on_qe.at(s) = true;
		while (!qe.empty())
		{
			int v = qe.front();
			qe.pop();
			on_qe.at(s) = false;
			//cout << "v: " << v << endl;
			for (const auto a : goal.adj(v))
			{
				//cout << a.to() << " , ";
				relax(a);
			}
		}
	}

	void bellman_ford_sp::relax(directededge e)
	{
		int v = e.from();
		int w = e.to();
		if (dist_to.at(w) > dist_to.at(v) + e.weight())
		{
			//cout << "w: " << w << endl;
			dist_to.at(w) = dist_to.at(v) + e.weight();
			edge_to.at(w) = e;
			if (!on_qe.at(w))
			{
				on_qe.at(w) = true;
				qe.push(w);
			}
		}
	}

	vector<directededge> bellman_ford_sp::path_to(int v)
	{
		stack<directededge> temp;
		if (edge_to.at(v).from() == -1)
		{
			cout << "no path from: " << initial_vertex << " to " << v << endl;
			return vector<directededge>();
		}
		for (directededge e = edge_to.at(v); e.to() != initial_vertex; e = edge_to.at(e.from()))
		{
			temp.push(e);
		}

		vector<directededge> result;
		while (!temp.empty())
		{
			result.push_back(temp.top());
			cout << temp.top().from() << "->";
			temp.pop();
		}
		cout << v << endl;
		return result;
	}

	vector<int> bellman_ford_sp::path_to_vertex(int v)
	{
		stack<directededge> temp;
		if (edge_to.at(v).from() == -1)
		{
			cout << "no path from: " << initial_vertex << " to " << v << endl;
			return vector<int>();
		}
		for (directededge e = edge_to.at(v); e.to() != initial_vertex; e = edge_to.at(e.from()))
		{
			temp.push(e);
		}

		vector<int> result;
		while (!temp.empty())
		{
			result.push_back(temp.top().from());
			cout << temp.top().from() << "->";
			temp.pop();
		}
		cout << v << endl;
		result.push_back(v);
		print_vector(result);
		return result;
	}

	double bellman_ford_sp::weight_to(int v)
	{
		if (edge_to.at(v).from() == -1)//沒這個if 印出來的會是DBL_MAX
			return 0;
		return dist_to.at(v);
	}

	floyd_warshall_sp::floyd_warshall_sp(const edge_weighted_digraph &g) :goal(g)
	{
		goal.adli_to_adma();
		edge_to.assign(goal.adjacency_matrix.size(), vector<int>(goal.adjacency_matrix.size(), -1));
		dist_to = goal.adjacency_matrix;
		int vertex_num = dist_to.size();
		for (int i = 0; i < vertex_num; i++)
			for (int j = 0; j < vertex_num; j++)
				if (dist_to.at(i).at(j) != DBL_MAX)
					edge_to.at(i).at(j) = i;

		for (int k = 0; k < vertex_num; k++) {
			// Pick all vertices as source one by one
			for (int i = 0; i < vertex_num; i++) {
				// Pick all vertices as destination for the
				// above picked source
				for (int j = 0; j < vertex_num; j++) {
					// If vertex k is on the shortest path from
					// i to j, then update the value of
					// dist[i][j]
					if (dist_to[i][k] + dist_to[k][j] < dist_to[i][j])
					{
						dist_to[i][j] = dist_to[i][k] + dist_to[k][j];
						edge_to.at(i).at(j) = edge_to.at(k).at(j);
					}
				}
			}
		}
	}

	double floyd_warshall_sp::weight_to(int s, int v)
	{
		if (dist_to.at(s).at(v) == DBL_MAX)
			return 0;
		return dist_to.at(s).at(v);
	}

	vector<int> floyd_warshall_sp::path_vertex(int s, int v)
	{
		vector<int> result;
		stack<int> temp;
		temp.push(v);
		int from = edge_to.at(s).at(v);
		while (from != s)
		{
			temp.push(from);
			if (from == -1)
			{
				cout << "no path from " << s << "to" << v << endl;
				return vector<int>();
			}
			from = edge_to.at(s).at(from);
		}
		temp.push(s);
		while (!temp.empty())
		{
			result.push_back(temp.top());
			temp.pop();
		}
		print_vector(result);
		return result;
	}

	void inner_msd_bucket_sort(vector<string> &input, vector<string> &aux, bucket<char> &input_bucket, int lo, int hi, int d) //hi要放size-1
	{
		if (hi <= lo)
			return;
		vector<int> count(input_bucket.size() + 2, 0);
		for (int i = lo; i <= hi; i++)
		{
			if (input.at(i).length() - 1 < d)
				count.at(1) += 1;                 //空格的下一個bucket加1 也就是把下一格的起始位置加1  所以count的每一格內容是紀錄上一格的數目
			else
				count.at((input_bucket[input.at(i).at(d)] + 2))++;//我的bucket從0開始的
		}
		for (int i = 0; i < count.size() - 1; i++)
			count.at(i + 1) += count.at(i);

		for (int i = lo; i <= hi; i++)
		{
			if (input.at(i).length() - 1 < d)
				aux.at(lo + count.at(0)++) = input.at(i);
			else
				aux.at(lo + count.at(input_bucket[input.at(i).at(d)] + 1)++) = input.at(i);//input.at(i).at(d)+1 +1是因為要有記入""空字串的原因
		}
		cout << "b" << endl;
		//print_vector<int>(count);
		for (int i = lo; i <= hi; i++)
			input.at(i) = aux.at(i);

		for (int i = 0; i < count.size() - 2; i++)//應該-2也可以
			inner_msd_bucket_sort(input, aux, input_bucket, lo + count.at(i), lo + count.at(i + 1) - 1, d + 1);  //這裡的""不需要再sort了
	}

	void msd_bucket_sort(vector<string> &input, bucket<char> char_bucket)
	{
		vector<string> aux(input.size(), "");
		inner_msd_bucket_sort(input, aux, char_bucket, 0, input.size() - 1);
	}

	void lsd_bucket_sort(vector<string> &input, bucket<char> input_bucket)
	{
		int d = 0;//紀錄最長字串長度
		int length = input.size();
		vector<string> aux(length, "");
		for (int i = 0; i < length; i++)
		{
			if (input.at(i).length() > d)
				d = input.at(i).length();
		}
		vector<int> count(input_bucket.size() + 2, 0);
		for (int h = d - 1; h >= 0; h--)    //h紀錄第一項(最長自串的最後一個index)
		{
			for (int i = 0; i < count.size(); i++)  //count歸零
				count.at(i) = 0;

			for (int i = 0; i < length; i++)
			{
				if (input.at(i).length() - 1 < h)
					count.at(1) += 1;                 //空格的下一個bucket加1 也就是把下一格的起始位置加1  所以count的每一格內容是紀錄上一格的數目
				else
					count.at(input_bucket[input.at(i).at(h)] + 2)++;
			}

			for (int i = 0; i < count.size() - 1; i++)
				count.at(i + 1) += count.at(i);

			for (int i = 0; i < length; i++)
			{
				if (input.at(i).length() - 1 < h)
					aux.at(count.at(0)++) = input.at(i);
				else
					aux.at(count.at(input_bucket[input.at(i).at(h)] + 1)++) = input.at(i);
			}

			//print_vector<int>(count);
			for (int i = 0; i < length; i++)
				input.at(i) = aux.at(i);
		}
	}

	void integer_lsd_bucket_sort(vector<int> &input, bool direct)
	{
		bucket<int> input_bucket;
		if (direct)
			input_bucket.increase();
		else
			input_bucket.decrease();

		int length = input.size();
		vector<int> aux(length, 0);
		vector<int> count(20, 0);
		for (int h = 1; h <= 1000000000; h = h * 10)    //h紀錄第一項(最長自串的最後一個index)
		{
			for (int i = 0; i < count.size(); i++)  //count歸零
				count.at(i) = 0;

			for (int i = 0; i < length; i++)
				count.at(input_bucket[(input.at(i) / h) % 10] + 1)++;

			for (int i = 0; i < count.size() - 1; i++)
				count.at(i + 1) += count.at(i);

			for (int i = 0; i < length; i++)
			{
				aux.at(count.at(input_bucket[(input.at(i) / h) % 10])++) = input.at(i);
			}

			//print_vector<int>(count);
			for (int i = 0; i < length; i++)
				input.at(i) = aux.at(i);
		}
	}

	void output_randnum_num(string name, unsigned int num, char delim) //num 是要put的數量
	{
		ofstream ofile(name, ios::out);
		if (ofile.is_open())
		{
			if (num <= 0)
				return;
			srand(static_cast<unsigned int>(time(NULL)));
			for (unsigned int i = 0; i < num - 1; i++)
				ofile << rand() << delim;

			ofile << rand();
		}
		else
		{
			cout << "開啟檔案失敗" << endl;
			return;
		}
		ofile.close();
		cout << "以製作亂數表" << endl;
		return;
	}

	void output_string(string name, unsigned int num, vector<string> &output_data, char delim)
	{
		ofstream ofile(name, ios::out);
		if (ofile.is_open())
		{
			if (num <= 0)
				return;
			for (unsigned int i = 0; i < (num - 1) && i < output_data.size(); i++)
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

	void output_num(string name, unsigned int num, vector<int> output_data, char delim)
	{
		ofstream ofile(name, ios::out);
		if (ofile.is_open())
		{
			if (num <= 0)
				return;
			for (unsigned int i = 0; i < num - 1 && i < output_data.size(); i++)
				ofile << output_data.at(i) << delim;

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

	unsigned int input_num(string name, unsigned int num, vector<int>& input, char delim) //讀取txt檔數字  num是讀入的數量  input是要傳入的vector
	{
		string temp;
		ifstream ifile(name, ios::in);
		unsigned int loop_time = 0;
		if (ifile.is_open())
		{
			while (!ifile.eof() && loop_time < num)
			{
				getline(ifile, temp, delim);
				//temp = temp2;
				input.push_back(stoi(temp));
				loop_time++;
			}
		}
		else
		{
			cout << "檔案開啟失敗" << endl;
			return 0;
		}
		ifile.close();
		return input.size();
	}

	unsigned int input_string(string name, unsigned int num, vector<string>& input, char delim)
	{
		string temp;
		ifstream ifile(name, ios::in);
		unsigned int loop_time = 0;
		if (ifile.is_open())
		{
			while (!ifile.eof() && loop_time < num)
			{
				getline(ifile, temp, delim);
				input.push_back(temp);
				loop_time++;
			}
		}
		else
		{
			cout << "檔案開啟失敗" << endl;
			return 0;
		}
		ifile.close();
		return input.size();
	}

	unsigned int input_string_filter(string name, unsigned int num, vector<string>& input, char delim)
	{
		string temp;
		ifstream ifile(name, ios::in);
		unsigned int loop_time = 0;
		if (ifile.is_open())
		{
			while (!ifile.eof() && loop_time < num)
			{
				bool allow = true;
				getline(ifile, temp, delim);
				for (unsigned int i = 0; i < temp.size(); i++)
				{
					if (temp.at(i) < 'a' || temp.at(i) > 'z')
					{
						allow = false;
						break;
					}
				}
				if (allow)
					input.push_back(temp);
				loop_time++;
			}
		}
		else
		{
			cout << "檔案開啟失敗" << endl;
			return 0;
		}
		ifile.close();
		return input.size();
	}

	QuickFindUF::QuickFindUF()
	{
	}
	QuickFindUF::QuickFindUF(int size)
	{
		for (int i = 0; i < size; i++)
		{
			union_set.push_back(i);
		}
	}
	int QuickFindUF::find(int p)
	{
		if (p < 0 || p >= union_set.size())
			return -1;
		return union_set.at(p);
	}

	bool QuickFindUF::connect(int p, int q)
	{
		if (find(p) == find(q) && find(p) != -1)
			return true;
		return false;
	}

	void QuickFindUF::union_two(int p, int q)
	{
		if (p < 0 || q < 0 || p >= union_set.size() || q >= union_set.size())
			return;
		int pid = union_set[p];
		int qid = union_set[q];
		for (int i = 0; i < union_set.size(); i++)
		{
			if (union_set[i] == pid)
				union_set[i] = qid;
		}
		return;
	}
	void QuickFindUF::print_union(void)
	{
		map<int, vector<int> > result;
		for (int i = 0; i < union_set.size(); i++)
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

	QuickUnionUF::QuickUnionUF()
	{
	}
	QuickUnionUF::QuickUnionUF(int size)
	{
		for (int i = 0; i < size; i++)
		{
			union_set.push_back(i);
			sz.push_back(1);
		}
	}
	int QuickUnionUF::find(int p)
	{
		if (p < 0 || p >= union_set.size())
			return -1;
		int temp = p;
		while (union_set.at(p) != p)
		{
			union_set.at(p) = union_set.at(union_set.at(p));
			p = union_set.at(p);
		}
		union_set.at(temp) = p;
		return p;
	}

	bool QuickUnionUF::connect(int p, int q)
	{
		if (find(p) == find(q) && find(p) != -1)
			return true;
		return false;
	}

	void QuickUnionUF::union_two(int p, int q)
	{
		if (p < 0 || q < 0 || p >= union_set.size() || q >= union_set.size())
			return;
		int i = find(p);
		int j = find(q);
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
	void QuickUnionUF::print_union(void)
	{
		map<int, vector<int> > result;
		for (int i = 0; i < union_set.size(); i++)
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

	void QuickUnionUF::print_union_num(void)
	{
		for (int i : sz)
		{
			cout << i << ',';
		}
		cout << endl;
		return;
	}

	int binary_search(vector<int>& input, int point)
	{
		int low = 0;
		int high = input.size() - 1;
		int index = -1;
		while (low <= high)
		{
			index = (low + high) / 2;
			if (input.at(index) > point)
				high = index - 1;
			else if (input.at(index) < point)
				low = index + 1;
			else
				return index;
			cout << index << "," << low << "," << high << endl;
		}
		return -1;
	}

	string opsite_string(const string input)
	{
		string result;
		stack<char> temp;
		for (int i = input.length() - 1; i >= 0; i--)
		{
			if (input.at(i) == ' ')
			{
				while (!temp.empty())
				{
					result += temp.top();

					temp.pop();
				}
				result.append(" ");
			}
			else
			{
				temp.push(input.at(i));
			}
		}

		while (!temp.empty())
		{
			result += temp.top();
			temp.pop();
		}
		return result;
	}

	template<class T>
	void test_sort(vector<T> input)
	{
		if (input.size() <= 1)
			return;
		for (int i = 1; i < input.size(); i++)
		{
			if (input.at(i) < input.at(i - 1))
			{
				cout << "錯誤排序" << endl;
				return;
			}
		}
		cout << "正確!" << endl;
		return;
	}
	double Permutations_c(int up, int down)
	{
		if (up == down || up < 1 || down < 1)
			return 1;
		else
			return Permutations_c(up - 1, down) + Permutations_c(up - 1, down - 1);
	}
	double Permutations_p(int up, int down)
	{
		if (up < down || up < 1 || down < 1)
			return 1;
		double class_step1 = 1;
		for (int i = up; i > (up - down); i--)
			class_step1 *= i;
		return class_step1;
	}
	//double poker_prehand()
		//double poker_flop()
		//double poker_river()
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