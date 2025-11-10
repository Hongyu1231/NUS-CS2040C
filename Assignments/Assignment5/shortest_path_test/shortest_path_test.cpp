#include <utility>
#include "graph.h"
#include "shortest_path.h"

using namespace std;

int main(){
  Graph g0(4);
  g0.addEdge(0, 1, 1);
  g0.addEdge(0, 2, 2);
  g0.addEdge(1, 3, 5);
  g0.addEdge(2, 3, 1);

  for (int d = 0; d < 4; d++) {
    Path p = shortestPath(g0, 0,d);
    std::cout << "The shortest distance from " << 0 << " to " << d << " is " << p.total_distance() << " and the path is: { ";
    for (int i = 0; i < p.path().size(); i++) {
      std::cout << p.path()[i];
      if (i!=p.path().size()-1) std::cout << " , ";
    }
    std::cout << " }" << endl;
  }
  
  std::cout << "Next Graph" << endl;
  Graph g(8);
  g.addEdge(0, 1, 5);
  g.addEdge(0, 7, 8);
  g.addEdge(0, 4, 9);
  g.addEdge(1, 3, 15);
  g.addEdge(1, 2, 12);
  g.addEdge(1, 7, 4);
  g.addEdge(3, 6, 9);
  g.addEdge(2, 3, 3);
  g.addEdge(2, 6, 11);
  g.addEdge(4, 7, 5);
  g.addEdge(4, 5, 4);
  g.addEdge(4, 6, 20);
  g.addEdge(5, 2, 1);
  g.addEdge(5, 6, 13);
  g.addEdge(7, 5, 6);
  g.addEdge(7, 2, 7);

  for (int d = 0; d < 8; d++) {
    Path p = shortestPath(g, 0,d);
    std::cout << "The shortest distance from " << 0 << " to " << d << " is " << p.total_distance() << " and the path is: { ";
    for (int i = 0; i < p.path().size(); i++) {
      std::cout << p.path()[i];
      if (i!=p.path().size()-1) std::cout << " , ";
    }
    std::cout << " }" << endl;
  }

}

