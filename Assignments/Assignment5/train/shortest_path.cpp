#include "graph.h"
#include "shortest_path.h"
#include "heap.hpp"

Path shortestPath(const Graph& g, int source, int dest) {
	int n = g.num_vertices();

	if (source < 0 || source >= n) {
		throw std::runtime_error(std::string("Error: source vertex ") + std::to_string(source) + " is out of bounds.");
	}
	if (dest < 0 || dest >= n) {
		throw std::runtime_error(std::string("Error: destination vertex ") + std::to_string(dest) + " is out of bounds.");
	}

	vector<int> prev(n);
	vector<int> dist(n);
	for (int i = 0; i < n; i++) {
		prev[i] = -1;
		dist[i] = -1;
	}

	struct State {
		int negative_dist;
		int vertex;

		State() : negative_dist(0), vertex(-1) {}
		State(int d, int v) : negative_dist(-d), vertex(v) {}

		bool operator>(const State& other) const {
			return negative_dist > other.negative_dist;
		}
	};

	Heap<State> pq;

	dist[source] = 0;
	pq.insert(State(0, source));

	while (!pq.empty()) {
		State cur = pq.extractMax();
		int distance = -cur.negative_dist;
		int vertex = cur.vertex;

		if (distance > dist[vertex] && dist[vertex] != -1) {
			continue;
		}
		if (vertex == dest) {
			break;
		}

		for (const GraphEdge& edge : g.edges_from(vertex)) {
			int v = edge.dest();
			int weight = edge.weight();
			int new_dist = weight + distance;
			if (new_dist < dist[v] || dist[v] == -1) {
				dist[v] = new_dist;
				prev[v] = vertex;
				pq.insert(State(new_dist, v));
			}
		}
	}

	int total_dist = dist[dest];
	vector<int> path;
	if (dist[dest] != -1) {
		int cur = dest;
		while (cur != -1) {
			path.push_back(cur);
			cur = prev[cur];
		}

		vector<int> reversed_path;
		for (int i = path.size() - 1; i >= 0; i--) {
			reversed_path.push_back(path[i]);
		}
		return Path(total_dist, reversed_path);
	}
	throw std::runtime_error("No path found!");
}