/*************************************************************************
Unit Testing Library: Catch2
Link: https://github.com/catchorg/Catch2
*************************************************************************/

#include "Graph.cpp" 
#include "../catchDef.hpp"
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

bool emptied = false;
vector<int> nodes = {1,2,3,4,5,6,7,8};
vector<Edge> edges=  {{1,2,2},{1,3,4},{1,4,1},{2,4,3},{2,5,10},{3,4,2},{3,6,5},{4,5,2},{4,6,8},{4,7,4},{5,7,6},{6,7,1}}; //{from,to,weight}     
Graph graph(nodes,edges);
Graph g1({1,2,3},{{1,2,5}});
Graph g2({1,2,3},{{1,2,5},{1,3,6}});

TEST_CASE( "DFS") 
{   
    if (!emptied)
    {
         emptyFiles();
         emptied = true;
    }
    SECTION("Connected Nodes")
    {
       vector<int> v1 {1,4,7,6,3,5,2};
       REQUIRE( graph.DFS(1) == v1);
       vector<int> v2 {2,5,7,6,4,3,1};
       REQUIRE( graph.DFS(2) == v2);
       vector<int> v3 {3,6,7,5,4,2,1};
       REQUIRE( graph.DFS(3) == v3);
       vector<int> v4 {4,7,6,3,1,2,5};
       REQUIRE( graph.DFS(4) == v4);
       vector<int> v5 {5,7,6,4,3,1,2};
       REQUIRE( graph.DFS(5) == v5);
       vector<int> v6 {6,7,5,4,3,1,2};
       REQUIRE( graph.DFS(6) == v6);
       vector<int> v7 {7,6,4,5,2,1,3};
       REQUIRE( graph.DFS(7) == v7);
       vector<int> v8 {1,2};
       REQUIRE( g1.DFS(1) == v8);
       vector<int> v9 {2,1,3};
       REQUIRE( g2.DFS(2) == v9);
    }
    SECTION("Unconnected nodes")
    {
       vector<int> v10 {8};
       REQUIRE( graph.DFS(8) == v10);
       vector<int> v11 {3};
       REQUIRE( g1.DFS(3) == v11);
    }
    SECTION("Invalid nodes")
    {  
       vector<int> v12 {0};
       REQUIRE( graph.DFS(15) == v12);
       REQUIRE( g1.DFS(5) == v12);
    }
}

TEST_CASE("isPath")
{
   SECTION("Valid Paths");
   {
        REQUIRE(graph.isPath(1,2)==true);
        REQUIRE(graph.isPath(2,1)==true);
        REQUIRE(g1.isPath(1,2)==true);
        REQUIRE(g2.isPath(1,3)==true);   
   }
   SECTION("Valid Self Path");
   {
        REQUIRE(graph.isPath(1,1)==true);
        REQUIRE(graph.isPath(5,5)==true);
        REQUIRE(graph.isPath(8,8)==true);
   }
   SECTION("Invalid Path");
   {
        REQUIRE(graph.isPath(5,8)==false); 
        REQUIRE(graph.isPath(7,8)==false);
        REQUIRE(g1.isPath(1,3)==false);
   }
   SECTION("Path to/from unexisting node");
   {
        REQUIRE(graph.isPath(7,9)==false);
        REQUIRE(graph.isPath(9,7)==false);
   }
   SECTION("Unexisting node to self");
   {
        REQUIRE(graph.isPath(9,9)==false);      
   }       
}
    
TEST_CASE("isConnected")
{         
   SECTION("Connected")
   {
       REQUIRE(g2.isConnected()==true); 
   }
   SECTION("Unconnected")
   {
       REQUIRE(g1.isConnected()==false);
       REQUIRE(graph.isConnected()==false);
   }    
}

TEST_CASE("Dijkstra")
{  
   SECTION("Valid Paths/Weight tests")
   {
        REQUIRE(graph.dijkstra(1,7) == 5);
        REQUIRE(graph.dijkstra(7,1) == 5);
        REQUIRE(graph.dijkstra(2,6) == 8);
        REQUIRE(graph.dijkstra(3,7) == 6);
        REQUIRE(g1.dijkstra(1,2) == 5);
        REQUIRE(g2.dijkstra(2,3) == 11);
   }
   SECTION("Weight to self")
   {
        REQUIRE(graph.dijkstra(1,1) == 0);
        REQUIRE(graph.dijkstra(5,5) == 0);
   }  
   SECTION("Unexisting path")
   {
        REQUIRE(graph.dijkstra(3,8) == -1);
         REQUIRE(g1.dijkstra(1,3) == -1);
   }
   SECTION("Path to/from invalid node")
   {
        REQUIRE(graph.dijkstra(3,9) == -1);
        REQUIRE(graph.dijkstra(9,2) == -1);
   }
 
}
TEST_CASE("Add node")
{    
     REQUIRE(g1.size==3); //size of g1 is 3
     SECTION("Already added node")
     {
          g1.addNode(1);
          REQUIRE(g1.size==3);
     }
     SECTION("Invalid node")
     {
          g1.addNode(-6); 
          REQUIRE(g1.size==3);
          g1.addNode(0); //test adding 0 (invalid)
          REQUIRE(g1.size==3);
     }
     SECTION("Valid node")
     {
         g1.addNode(4); 
         REQUIRE(g1.size==4);
         g1.addNode(7); //test adding bigger node
         REQUIRE(g1.size==7);  
     }         
}
TEST_CASE("Add edge")
{
     REQUIRE(g2.list[2].size()==1); //node 2 has 2 connections
     SECTION("Invalid Weight")
     {
         g2.addEdge({2,3,-5}); 
         REQUIRE(g2.list[2].size()==1);  
     }
     SECTION("Edge to unexisting Node")
     {
         g2.addEdge({2,7,5}); 
         REQUIRE(g2.list[2].size()==1); 
     }
     SECTION("Valid Edge")
     {  
         REQUIRE(g2.list[2].size()==1);
         g2.addEdge({2,3,5});
         REQUIRE(g2.list[2].size()==2); 
     }     
}
