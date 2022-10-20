#include "pch.h"
#include <iostream>
#include "head.h"
#include "Peng.h"

int a = 5;
using namespace Peng;
int main()
{
	Peng::graph test_g(vector<vector<int>>{ {0, 1}, { 0,2 }, { 0,5 }, { 0,6 }, { 3,4 }, { 3,5 }, { 4,5 }, { 4,6 }, { 7,8 }, { 9,10 }, { 9,11 }, { 9,12 }, { 11,12 } });
	Peng::digraph test_g2({ {0,1},{0,2},{0,5},{5,0},{0,6},{3,4},{3,5},{4,5},{4,6},{7,8},{9,10},{9,11},{9,12},{11,12} });
	Peng::digraph test_g3({ {0,5},{0,1},{0,2},{3,5},{3,6},{3,4},{5,2},{6,4},{6,0},{3,2},{1,4} });

	cout << test_g2.edge_num() << endl;

	Peng::directedcycle test_cy(test_g3);
	Peng::topological_sort test_to(test_g3);
	//test_to.print_topology();
	//print_vector(test_cy.get_cycle());

	edge_weighted_graph abc({ {2,3,0.17},{6,4,0.93},{6,0,0.58},{1,7,0.19},{0,2,0.26},{5,7,0.28},{1,3,0.29},{1,5,0.32},{2,7,0.34},{4,5,0.35},{1,2,0.36},{4,7,0.37},{0,4,0.38},{6,2,0.40},{3,6,0.52} });
	abc.add_edge({ 0,7,0.16 });

	edge_weighted_digraph dijkstra_map({ {0,1,5.0},{0,4,9.0}, {0,7,8.0}, {1,2,12.0}, {1,3,15.0}, {1,7,4.0}, {2,3,3.0}, {2,6,11.0}, {3,6,9.0}, {4,5,4.0}, {4,6,20.0}, {4,7,5.0}, {5,2,1.0}, {5,6,13.0}, {7,5,6.0}, {7,2,7.0} });

	//dijkstra_sp dijkstra_sp1(dijkstra_map, 0);
	//for (int i = 0; i < dijkstra_map.vertex_num(); i++)
	//{
	//	dijkstra_sp1.path_to_vertex(i);
	//	cout << "weight:" << dijkstra_sp1.weight_to(i) << endl;
	//}

	lazyprimmst k_mst(abc);
	k_mst.print_edges();
	cout << k_mst.weights() << endl;

	cout << "-------------------------------------------------" << endl;

	eagerprimmst eager_mst(abc);
	eager_mst.print_edges();
	cout << eager_mst.weights() << endl;

	bellman_ford_sp_all all_bellman_ford_sp(dijkstra_map);
	for (int i = 0; i < dijkstra_map.vertex_num(); i++)
		for (int j = 0; j < dijkstra_map.vertex_num(); j++)
		{
			all_bellman_ford_sp.path_vertex(i, j);
			cout << "weight: " << all_bellman_ford_sp.weight_to(i, j) << endl;
		}

	floyd_warshall_sp all_floyd_warshall_sp(dijkstra_map);
	for (int i = 0; i < dijkstra_map.vertex_num(); i++)
		for (int j = 0; j < dijkstra_map.vertex_num(); j++)
		{
			cout << "(" << i << " , " << j << ")" << endl;
			all_floyd_warshall_sp.path_vertex(i, j);
			cout << "weight: " << all_floyd_warshall_sp.weight_to(i, j) << endl;
		}
	cout << "-----------------------------------------------" << endl;
	cout << all_floyd_warshall_sp.edge_to.at(1).at(6) << endl;
	cout << "weight_edge:" << abc.edge_num() << endl;
	//test_g.add_edge(6, 7);
	cc test_con(test_g);
	if (cycle(test_g).has_cycle())
		cout << "has cycle" << endl;
	cout << test_con.count() << endl;

	cout << test_g.vertex_num() << endl;
	path re(test_g, 1);
	Peng::bfs testa(test_g, 1);
	cout << testa.dist_from.at(7) << endl;
	print_vector(re.path_to(7));
	cout << test_g.degree(3) << endl;
	print_vector(test_g.adj(3));
	std::set<int> myset{ 1, 4, 3, 9, 5 };
	for (auto a : myset)
		cout << a << endl;

	Peng::QuickFindUF_leetcode<double>  test(12);
	test.union_two(2, 5);
	test.union_two(5, 7);
	test.union_two(1, 9);
	test.union_two(0, 8);
	test.union_two(6, 9);
	test.print_union();

	return 0;
}