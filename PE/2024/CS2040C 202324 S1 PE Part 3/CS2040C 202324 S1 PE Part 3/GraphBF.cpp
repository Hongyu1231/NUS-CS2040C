#include "GraphBF.h"
#include <iostream>
#include <fstream>
using namespace std;

Graph::Graph(const char* filename)
{
    string line;
    ifstream myfile(filename);

    int q; // number of queries

    if (myfile.fail()) {
        cout << "File not found" << endl;
    }

    myfile >> _nv;
    myfile >> _ne;


    _edges = new WeightedEdge[_ne];
    int s, d, w;

    // read in all the edges and add into the graph
    for (int i = 0; i < _ne; i++)
    {
        myfile >> s;
        myfile >> d;
        myfile >> w;
        _edges[i].v1 = s;
        _edges[i].v2 = d;
        _edges[i].weight = w;
    }
}

void Graph::printGraph()
{
    for (int i = 0; i < _ne; i++)
        cout << "(" << _edges[i].v1 << "," << _edges[i].v2 << "," << _edges[i].weight << ")" << endl;
}
Graph::~Graph()
{

    delete[] _edges;

}

void Graph::BF(int source) {
    int* dist = new int[_nv];
    for (int i = 0; i < _nv; i++) {
        dist[i] = INFINITY_WEIGHT;
        if (i == source) {
            dist[i] = 0;
        }
    }

    for (int i = 0; i < _nv + 1; i++) {
        int relax = 0;
        for (int j = 0; j < _ne; j++) {
            if (dist[_edges[j].v1] + _edges[j].weight < dist[_edges[j].v2]) {
                dist[_edges[j].v2] = dist[_edges[j].v1] + _edges[j].weight;
                relax++;
            }
        }

        if (relax == 0) {
            break;
        }

        for (int j = 0; j < _nv - 1; j++) {
            cout << dist[j] << ",";
        }
        cout << dist[_nv - 1];
        cout << endl;

        if (i == _nv) {
            cout << NEGATIVECYCLESTRING << endl;
        }
    }
}
