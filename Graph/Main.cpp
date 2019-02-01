#include"Graph.cpp"
void emptyFiles()
{
     ofstream f;
     f.open("Dijkstra.txt");
     f.close();
     f.open("BFS.txt");
     f.close();
     f.open("DFS.txt");
     f.close();
     f.open("Path.txt");
     f.close();
}
int main()
{    
     emptyFiles();
     vector<int> nodes = {1,2,3,4,5,6,7,8};
     vector<Edge> edges=  {{1,2,2},{1,3,4},{1,4,1},{2,4,3},{2,5,10},{3,4,2},{3,6,5},{4,5,2},{4,6,8},{4,7,4},{5,7,6},{6,7,1}}; //{from,to,weight}     
     Graph graph(nodes,edges);
     graph.print();
     graph.BFS(1);
     graph.DFS(2);
     graph.isConnected();
     graph.isPath(1,5);
     cout<<"Weight 2 to 6:"<<graph.dijkstra(2,6)<<endl;
}