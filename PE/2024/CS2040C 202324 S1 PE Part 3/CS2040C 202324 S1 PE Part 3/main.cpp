#include "GraphBF.h"
// reading a text file

using namespace std;


int main()
{
    
    Graph g("example1.txt");
    g.BF(0);

    Graph g2("example2.txt");
    g2.BF(0);

    Graph g3("example3.txt");
    g3.BF(0);
    g3.BF(1);

    Graph g4("example4.txt");
    g4.BF(0);
    g4.BF(1);

    Graph g5("example5.txt");
    g5.BF(0);
    g5.BF(1);
    
    Graph g6("example6.txt");
    g6.BF(0);

    Graph g7("example7.txt");
    g7.BF(0);

    return 0;
}