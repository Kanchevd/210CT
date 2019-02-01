#include "Graph.cpp"
int main()
{    
     vector<int> nodes = {1,2,3,4,5,6,7,8,9};
     vector<vertice> vertices=  { {1,2},{1,3},{2,3},{2,5},{3,4},{4,7},{5,6},{6,7},{7,8},{8,9}} ;     
     Graph graph(nodes,vertices);    
     graph.print();
     graph.BFS(2);
     graph.DFS(5);
     graph.isPath({3,7});
     graph.isConnected();
     return 0;
}