#include<iostream>
#include<vector>
#include<algorithm> 
#include<queue>
#include<stack>
#include<fstream>
using namespace std;

struct vertice
{
	int start;
     int end;
};

class Graph{
     
   public:
     
   //Attributes
   vector<vector<int>> list;
   vector<int> nodes;
   int size;
     
   //Constructor 
   Graph(vector<int> nodes,vector<vertice> vertList)
   {          
        this->nodes = nodes;
        this->size = *max_element(nodes.begin(),nodes.end())+1; 
        list.resize(size); //resize list in order to properly add edges
        for(auto it=vertList.begin();it!=vertList.end();it=next(it))   
             addVertice(*it); //add all vertices to the list
   }
   
   //Methods
   void addNode(int node, vector<int> vertices)
   {    
        // Function to add another node along with its vertices to the graph; not necessary to be a consecutive value
        if(find(nodes.begin(),nodes.end(),node) != nodes.end() || node<1) // Invalid if node already added or not positive
        {
             cout<<"Invalid node"<<endl;
             return;
        }  
        nodes.push_back(node);
        if(node+1>this->size) //resize the list if it requires
        {
             this->size=node+1;        
             list.resize(this->size);
        }
        //cout<<"Added node "<<node<<endl;
        for(auto it=vertices.begin();it!=vertices.end();it=next(it))                
             addVertice({node,*it}); //create a temp vertice to pass it to addVertice()        
   }
     
   void addVertice(vertice vert)
   {    
        //Function to add a vertice to the graph. The flags make it less efficient and be commented out to sacrifice security in favor of efficiency
        //cout<<"Adding vertice "<<vert.start<< " and "<<vert.end<<endl;
        bool startFlag = find(nodes.begin(),nodes.end(),vert.start) != nodes.end(); //Is the start a valid node
        bool endFlag = find(nodes.begin(),nodes.end(),vert.end) != nodes.end(); //Is the end a valid node
        bool repeatFlag =  find(list[vert.start].begin(),list[vert.start].end(),vert.end) == list[vert.start].end(); //Is the vertice already added
        if(!startFlag || !endFlag || !repeatFlag)
        {
             cout<<"Can't add vertice.  ";
             cout<<"Start Flag:"<<startFlag<<" ";
             cout<<"End Flag:"<<endFlag<<" ";
             cout<<"Repeat Flag:"<<repeatFlag<<endl;
             return;
        }
        list[vert.start].push_back(vert.end);
        list[vert.end].push_back(vert.start); //commenting this line out makes the graph directed
   
   }
     
   void print()
   {
     //Function to print the graph
     cout<<"------Graph-------"<<endl;
     for(auto it=nodes.begin();it!=nodes.end();it=next(it))
     {
         cout<<*it<<" : ";
         for (int j=0; j<list[*it].size(); j++) // list - vector of vector containing connections; list[*it] - specific vector containing connections of the element we are printing
               cout<<list[*it][j]<<' ';
         cout<<endl;
     }
  }
     
  vector<int> BFS(int node)
  {   
       ofstream f;
       f.open("BFS.txt");
       queue<int> toVisit; 
       vector<int> visited, cameFrom; //cameFrom contains the node we reached each node from
       cameFrom.resize(this->size); //vector is full of 0's.
       toVisit.push(node); 
       while(!toVisit.empty()) //while there are still elements to visit 
       {    
            node = toVisit.front();
            if(find(visited.begin(),visited.end(),node) != visited.end()) //if we already visited this node, pop it and move on
            {
                 toVisit.pop();
                 continue;
            }
            for(auto it=list[node].begin();it!=list[node].end();it=next(it)) // for every child of this element
            {    
                 if(find(visited.begin(),visited.end(), *it) == visited.end()) //if it's not already in visited
                 {
                      toVisit.push(*it);
                      cameFrom[*it] = node; //record how we came to the node
                 }   
            }
            f<<node<<"  "; //output to a .txt
            visited.push_back(node); //mark the node as visited
            toVisit.pop();
       }
       f.close();
       return cameFrom; // isPath uses this vector
  }
  
  vector<int> DFS(int node) 
  {    
       ofstream f;
       f.open("DFS.txt");
       stack<int> toVisit; //main difference between BFS and DFS is stack/queue
       vector<int> visited;
       toVisit.push(node);
       while(!toVisit.empty())
       {    
            node = toVisit.top(); 
            toVisit.pop(); //we have to pop it immediately so we don't stack on top of it before we want to pop it
            if(find(visited.begin(),visited.end(),node) != visited.end()) //if we already visited this node, move on
                 continue;
            
            for(auto it=list[node].rbegin();it!=list[node].rend();it=next(it)) //for every child of this element    
                 if(find(visited.begin(),visited.end(), *it) == visited.end()) //if it's not already in visited
                      toVisit.push(*it);  
            
            f<<node<<"  "; //output to a .txt
            visited.push_back(node); //mark the node as visited
             
       }
       f.close();
       return visited;
  } 
        
  bool isPath(vertice isPath)
  {
       //Function to check if a given vertice exists. If it exists, output the shortest path to a .txt
       //cout<<"Checking if "<<isPath.start<<" and "<<isPath.end<<" is a vertice."<<endl;
       vector<int> cameFrom = BFS(isPath.end); // call BFS with the second part of the vertice 
       int source = isPath.start,  target = isPath.end; 
       vector<int> path;
       ofstream f;
       f.open("Path.txt");
       while(true)        
       {
            path.push_back(source); //start the path from the first part of the vertice 
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
                 return true;
            }
            else source = cameFrom[source]; //continue going backwards in the path       
       }
       f.close();       
  }

  void isConnected()
  {   
      //function to check if the graph is connected
      vector<int> dfsTrav = DFS(nodes[0]); //do a DFS traversal with the first node of the graph 
      if(dfsTrav.size() == nodes.size()) //check if DFS found all the nodes
           cout<< "Yes."<<endl;
      else
           cout<< "No."<<endl;     
  }
        
};