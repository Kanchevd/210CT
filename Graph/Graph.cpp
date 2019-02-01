#include<iostream>
#include<vector>
#include<algorithm> 
#include<queue>
#include<stack>
#include<fstream>
#include<climits>
using namespace std;

struct Edge
{
	int start;
     int end;
     int weight;
};

class Graph{
     
   public:
     
   //Attributes
   vector<vector<Edge>> list;
   vector<int> nodes;
   int size;
     
   //Constructor 
   Graph(vector<int> nodes,vector<Edge> edgeList)
   {          
        this->nodes = nodes;
        this->size = *max_element(nodes.begin(),nodes.end()); 
        list.resize(size+1); //resize list in order to properly add edges
        for(auto it=edgeList.begin();it!=edgeList.end();it=next(it))
             addEdge(*it); //add all edges to the list
   }
   
   //Methods
   void addNode(int node)
   {    
        // Function to add another node along with its edges to the graph; not necessary to be a consecutive value
        if(find(nodes.begin(),nodes.end(),node) != nodes.end() || node<1) // Invalid if node already added or not positive
        {
             //cout<<"Invalid node"<<endl;
             return;
        }  
        nodes.push_back(node);
        if(node>this->size) //resize the list if it requires
        {
             this->size=node;        
             list.resize(this->size+1);
        }       
   }
     void addEdge(Edge edge) 
     {
        //Function to add an edge to the graph. The flags make it less efficient and be commented out to sacrifice security in favor of efficiency
        bool startFlag = find(nodes.begin(),nodes.end(),edge.start) != nodes.end(); //Is the start a valid node
        bool endFlag = find(nodes.begin(),nodes.end(),edge.end) != nodes.end(); //Is the end a valid node
        bool weightFlag = edge.weight>=0; //weight is a positive number
        if(!startFlag || !endFlag || !weightFlag)
        {
             //cout<<"Can't add edge.  ";
             //cout<<"Weight Flag:"<<wightFlag<<" ";
             //cout<<"Start Flag:"<<startFlag<<" ";
             //cout<<"End Flag:"<<endFlag<<" "<<endl;;
             return;
        }
        list[edge.start].push_back(edge);
        Edge revEdge = {edge.end,edge.start,edge.weight}; //reverse start and end so start is always the source in the adjacency list
        list[edge.end].push_back(revEdge); //commenting this line out makes the graph directed
   
   }
     
   void print()
   {
     //Function to print the graph
     cout<<"------Graph-------"<<endl;
     cout<<"\nNode: {child,weight}\n"<<endl;
     for(auto it=nodes.begin();it!=nodes.end();it=next(it))
     {
        cout<<*it<<" : ";
        for (int j=0; j<list[*it].size(); j++)
             cout<<'{'<<list[*it][j].end<<','<<list[*it][j].weight<<"} ";// list - vector of vector containing connections; list[node] - specific vector containing connections of the element we are printing               
        cout<<endl;
     }
  }
      
  vector<int> BFS(int node)
  {   
       ofstream f;
       f.open("BFS.txt",ios::app);
       queue<int> toVisit; 
       vector<int> visited, cameFrom; //cameFrom contains the node we reached each node from
       cameFrom.resize(this->size+1); //vector is full of 0's.
       toVisit.push(node); 
       while(!toVisit.empty()) //while there are still elements to visit 
       {    
            node = toVisit.front();
            if(find(visited.begin(),visited.end(),node) != visited.end()) //if we already visited this node, pop it and move on
            {
                 toVisit.pop();
                 continue;
            }
            visited.push_back(node); //mark the node as visited
            //for(auto it=list[node].begin();it!=list[node].end();it=next(it)) // for every child of this element
            for(int i=0;i<list[node].size();i++)
            {                    
                 int child = list[node][i].end;               
                 if(find(visited.begin(),visited.end(), child) == visited.end()) //if it's not already in visited
                 {
                      toVisit.push(child);
                      if(!cameFrom[child])
                           cameFrom[child] = node; //record how we came to the node
                 }   
            }
            f<<node<<"  "; //output to a .txt
            
            toVisit.pop();
       }
       f<<'\n';
       f.close();
       return cameFrom; // isPath uses this vector
  }
  
  vector<int> DFS(int node) 
  {    
       if(find(nodes.begin(),nodes.end(),node) == nodes.end())
            return {0};
       ofstream f;
       f.open("DFS.txt",ios::app);
       stack<int> toVisit; //main difference between BFS and DFS is stack/queue
       vector<int> visited;
       toVisit.push(node);
       while(!toVisit.empty())
       {    
            node = toVisit.top(); 
            toVisit.pop(); //we have to pop it immediately so we don't stack on top of it before we want to pop it
            if(find(visited.begin(),visited.end(),node) != visited.end()) //if we already visited this node, move on
                 continue;
            
            visited.push_back(node); //mark the node as visited
            for(int i=0;i<list[node].size();i++) //for every child of this element
            {
                 int child = list[node][i].end;
                 if(find(visited.begin(),visited.end(), child) == visited.end()) //if it's not already in visited
                      toVisit.push(child);  
            }
            f<<node<<"  "; //output to a .txt                        
     }
       f<<endl;
       f.close();
       return visited;
  } 
       
  bool isPath(int source,int target)
  {
       //Function to check if a connection between two nodes exists. If it exists, output the shortest path to a .txt
       if (find(nodes.begin(),nodes.end(),source)==nodes.end() || find(nodes.begin(),nodes.end(),target)==nodes.end()) //if either of the nodes don't exist
            return false;
       if (source==target) // if they're the same, there is a path
            return true;       
       vector<int> cameFrom = BFS(target); // call BFS with the second part of the edge 
       vector<int> path;
       ofstream f;
       f.open("Path.txt",ios::app);
       while(true)        
       {          
            path.push_back(source); //start the path from the first part of the edge 
            if(!cameFrom[source]) //if we can't find where it came from
            {
                 f<<"The path doesn't exist."<<endl;
                 return false;
            }    
            if(cameFrom[source] == target) //if we get to the target we were looking for
            {
                 path.push_back(target); //add it to the path
                 f<<"Path: "; //output to a .txt
                 for(auto it=path.begin();it!=path.end();it=next(it))
                      f<<*it<<" ";
                 f<<endl;
                 return true;
            }
            else source = cameFrom[source]; //continue going backwards in the path       
       }
       f.close();       
  }
  
  bool isConnected()
  {   
      //function to check if the graph is connected
      //cout<<"Graph connected:";
      vector<int> dfsTrav = DFS(nodes[0]); //do a DFS traversal with the first node of the graph 
      if(dfsTrav.size() == nodes.size()) //check if DFS found all the nodes
           return true;
      else
           return false;     
  }
 int dijkstra(int source,int target)
  {    
       if(!isPath(source,target)) // if the path doesn't exist
            return -1;
       ofstream f;
       f.open("Dijkstra.txt", ios::app);
       int currWeight,i,node = source; 
       vector<int> weights, cameFrom;  
       bool* visited; //keep track of visited nodes
       visited = new bool[this->size+1];
       for(i=0;i<this->size+1;i++)
            visited[i]=false;
       weights.resize(this->size+1); //resize both vectors to fit all nodes
       cameFrom.resize(this->size+1);
       for(auto it=nodes.begin();it!=nodes.end();it=next(it)) // set all weights to max possible value
            weights[*it] = INT_MAX;
       weights[node] = 0; // cost to get to current node is 0
       while(node!=target) 
       {   
            currWeight = INT_MAX; //needed to find lowest weight
            for(i=1;i<this->size+1;i++)
                 if(!visited[i] && weights[i]<currWeight) //find element with lowest weight we haven't visited
                 { 
                      node = i;
                      currWeight = weights[i];                      
                 }      
            for(int i=0;i<list[node].size();i++) //for every edge of the current element
            {
                 Edge edge = list[node][i]; //done for code readability
                 if(weights[edge.end]>edge.weight + currWeight) //check if we can improve the current weight
                 {
                      weights[edge.end] = edge.weight + currWeight;
                      cameFrom[edge.end] = node; //record where we came from
                 }                 
            }     
            visited[node] = true; //mark the node as visited
       }
       int trav = target;
       f<<"Path:"<<trav<<" "; 
       while(trav!=source) //go through cameFrom[] and display the path
       {           
          trav = cameFrom[trav];
          f<<trav<<" ";
       }
       f<<endl;
       f.close();
       delete [] visited;              
       return weights[target];
  }
};