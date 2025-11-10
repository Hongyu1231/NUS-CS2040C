#pragma once
#define INFINITY_WEIGHT 100000000

#define NEGATIVECYCLESTRING "Negative Cycle!"
class WeightedEdge {
public:
    int v1, v2, weight;
};


class Graph {
private:
    WeightedEdge* _edges;
    int _nv; // number of nodes
    int _ne; // number of edges

public:
    Graph(const char* filename);
    void BF(int source);

    //    int shortestDistance(int s, int d);
    void printGraph();

    ~Graph();
};

