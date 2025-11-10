#include "Graph.h"
#include "heap.h"

std::ostream& operator<<(std::ostream& os, nodeWeightPair const& n) {
	return os << " (idx:" << n._node << " w:" << n._weight << ")";
}


Graph::Graph(int n)
{
	_al = new List<nodeWeightPair> [n];
	_nv = n;
}

int Graph::shortestDistance(int s, int d)
{
	Heap<nodeWeightPair> hp;
	const int notvisited = 1;
	int* dist = new int[_nv];
	int* parent = new int[_nv];
	int* path = new int[_nv];

	int dNode, dWeight;
	for (int i = 0; i < _nv; i++)
		dist[i] = notvisited;

	hp.insert(nodeWeightPair(s, 0));
	parent[s] = s;
	while (!hp.empty())
	{

		nodeWeightPair nwp = hp.extractMax();
		int node = nwp.nodeIndex();
		int cDist = nwp.weight();

		if (node == d)
		{
			int i = 1;
			path[0] = d;
			while (node != s)
			{
				node = parent[node];
				path[i] = node;
				i++;
			}


			cout << "Path:";
			for (int j = i-1; j >=0;  j--)
				cout << " " << path[j];
			cout << endl;
			return -cDist;
		}
		for (_al[node].start(); !_al[node].end(); _al[node].next())
		{
 			dNode = _al[node].current().nodeIndex();
			dWeight = _al[node].current().weight();
			if (dist[dNode] == notvisited) {
				dist[dNode] = cDist - dWeight;
				hp.insert(nodeWeightPair(dNode, cDist - dWeight));
				parent[dNode] = node;
			}
			else if (dist[dNode] < cDist - dWeight) {
				dist[dNode] = cDist - dWeight;
				hp.increaseKey(nodeWeightPair(dNode, dWeight), nodeWeightPair(dNode, cDist - dWeight));
				parent[dNode] = node;
			}
	

		}
		

	}

	delete[] parent;
	delete[] dist;
	delete[] path;
	return -1;
}
void Graph::addEdge(int s, int d, int w)
{
	_al[s].insertHead(nodeWeightPair(d, w));
}

void Graph::printGraph()
{
	for (int i=0; i < _nv; i++)
	{
		cout << "Node " << i << ": ";
		for (_al[i].start(); !_al[i].end(); _al[i].next())
			cout << " (" << _al[i].current().nodeIndex() << "," << _al[i].current().weight() << ")";
		cout << endl;

	}

}
Graph::~Graph()
{

	delete[] _al;

}