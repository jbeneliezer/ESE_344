
#define MAX_SIZE 10

#include <iostream>
#include <cstdlib>   // for rand(), srand()
#include <ctime>     // for time()
#include <assert.h>
#include <vector>
#include <math.h>    // for sqrt()
#include <set>
#include "List.h"
#include "Edge.h"

using namespace std;

void traverse(int v, vector<bool>& vis, const vector<List<Edge>>& g)
{
	vis[v] = true;

	cout << " " << v;

	for (auto& w : g[v])
	{
		if (!vis[w.tv])
			traverse(w.tv, vis, g);
	}
}

void bf_traverse(int v, vector<bool>& vis, const vector<List<Edge>>& g)
{
	List<int> q;

	vis[v] = true;
	q.push_back(v);

	while (!q.empty())
	{
		v = q.front();
		cout << " " << v;
		q.pop_front();

		for (auto& w: g[v])
		{
			if (!vis[w.tv])
			{
				vis[w.tv] = true;
				q.push_back(w.tv);
			}
		}
	}
}

void shortest_path(int v, int d, const vector<List<Edge>>& g)
{
	vector<int> distance(g.size(), INT_MAX);
	vector<vector<int>> paths(g.size());
	set<int> connected = { v }, network_copy;
	distance[v] = 0;
	paths[v] = { v };

	while (connected != network_copy) // will iterate over all vertices connected to v, stops when no change is detected.
	{
		network_copy = connected;
		for (auto& w : connected)
		{
			for (auto& x : g[w])
			{
				if (distance[x.tv] > distance[w] + x.weight)
				{
					distance[x.tv] = distance[w] + x.weight;
					paths[x.tv] = paths[w];
					paths[x.tv].push_back(x.tv);
				}
				connected.insert(x.tv);
			}
		}
	}

	cout << "distance from " << v << " to " << d << ": ";
	if (distance[d] == INT_MAX) cout << "no path available." << endl;
	else
	{
		cout << distance[d] << endl << "path:";
		for (auto& i : paths[d]) cout << " " << i;
		cout << endl;
	}
}

int main()
{
	int nv = 0; // number of vertices
	int ne = 0; // number of edges
	cin >> nv >> ne; // input; assume no error in input.

	if ((nv < 0) || (nv > 10000) || (ne < 0) || (ne > 10000))
	{
		cerr << "Input values out of range." << endl;
		exit(1);
	}

	vector<List<Edge>> g2(nv); //graph
	int cv1 = 0, cv2 = 0; // Edge from current vertex cv1 to cv2
	double wt = 0.0; // weight

	for (int ne1 = 0; ne1 < ne; ne1++)
	{
		cin >> cv1 >> cv2 >> wt; // input; assume no error in input.
		if ((cv1 < 0) || (cv1 > nv) || (cv2 < 0) || (cv2 > nv) || (wt < 0) || (wt > 10000.0))
		{
			cerr << "Input values out of range." << endl;
			exit(1);
		}
		Edge nsq(cv1, cv2, wt);
		g2[cv1].push_back(nsq);
	}

	cout << endl << "Graph " << endl;
	
	for (int i = 0; i < nv; i++)
	{
		cout << i << " : ";
		g2[i].printList();
	}

	vector<bool> visited(nv, false);
	//cout << endl << "Depth First traversal " << endl << "Order of vertices visited : ";
	//for (int v = 0; v < nv; v++)
	//{
	//	if (!visited[v])
	//		traverse(v, visited, g2);
	//}
	//cout << endl;

	// (a). breadth first traversal.
	for (int v = 0; v < nv; ++v)
	{
		cout << endl << "Breadth First traversal " << endl << "Order of vertices visited : ";
		visited.assign(nv, false);
		bf_traverse(v, visited, g2);
		cout << endl;
	}
	cout << endl;

	// (b). shortest path.
	for (int v = 0; v < nv; ++v)
	{
		for (int w = 0; w < nv; ++w)
		{
			shortest_path(v, w, g2);
			cout << endl;
		}
	}
	cout << endl;

	cout << "Clearing..." << endl;
	for (int i = 0; i < nv; ++i)
	{
		g2[i].clear();
		cout << endl;
	}
	return 0;
}