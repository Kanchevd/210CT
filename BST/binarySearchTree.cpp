#include<iostream>
#include<string>
#include<fstream>
using namespace std;

class Node{
     // objects of this class represent nodes in the binary tree 
public:
     //Attributes
     string val;
     int frq;
     Node* left;
     Node* right;
     Node* parent;
     
     //Constructor
     Node(string val,Node* parent = NULL)
     {
		this->val = val; // node value
		this->left = NULL;  //node's left child
		this->right = NULL;  //node's right child 
          this->frq = 1; // node's frequency
          this->parent = parent; //node's parent
     }

};
Node* insertNode(Node* tree, string item) 
{
     /* Function to insert a node in the tree */
     if (tree==NULL) // if the tree is empty, place it as the root
          tree = new Node(item);
     
     else if(item==tree->val) // if the node is already in the tree, increment its frequency
               tree->frq++;
     else
     {          
          if(tree->val>item) // item is smaller than current node
               if (tree->left == NULL) 
                    tree->left = new Node(item,tree); 
			else
				insertNode(tree->left, item); //call the function, starting at the left child as the root
          else  
			if (tree->right == NULL)  // same as above for the right side
				tree->right = new Node(item,tree); 
			else
				insertNode(tree->right, item);
     }
     return tree;
}
void preOrder(Node* tree) 
{
     /* Function to print the tree in pre order */ 
     cout<<tree->val<<":"<<tree->frq<<" ";
	if (tree->left != NULL)
		preOrder(tree->left);
	if (tree->right != NULL)
		preOrder(tree->right);
}
bool findNode(Node* tree,string item)
{    
     /* Function to find if a certain node exists in the tree. Also displays path traversed to node */

     if(tree == NULL) //tree is empty 
     {
          //cout<<"Item not found."<<endl;
          return false;          
     }
     cout<<"Searching for '"<<item<<"'."<<endl;
     cout<<"Looking at '"<<tree->val<<"'."<<endl;
     if(tree->val>item) //if it's smaller - go to the left 
     {
          cout<<"'"<<item<<"' is smaller than '"<<tree->val<<"', going left"<<endl;
          findNode(tree->left,item);
     }             
     else if(tree->val<item) 
     {   
          cout<<"'"<<item<<"' is bigger than '"<<tree->val<<"', going right"<<endl;
          findNode(tree->right,item);
     }
     else 
     {    
          cout<<"Item found!"<<endl;
          return true;
     }
}
int childNo(Node* tree)
{    
     /* Function to count the number of children of a certain node and print their values */
     int children=0;   
     if(tree->left != NULL) // if node exists, increment counter
          children++;
     
     if(tree->right != NULL)
          children++;
  
     return children;
}
Node* minNode(Node* tree)
{ 
   /* Function to return the smallest node in the given tree */
   while(tree->left!=NULL)
   {
        tree=tree->left; //get to the left-most element
   }
   return tree;
}

void deleteNode(Node *tree,string item)
{    
     /* Function to delete a node with the given value from the tree */ 
     if(tree == NULL) //tree is empty
     {
          cout<<"Node not found."<<endl;
          return;
     }
     
     else if(tree->val>item)   
          deleteNode(tree->left,item);
     
     else if(tree->val<item)
          deleteNode(tree->right,item);
     
     else //we find the node 
     {    
          int children = childNo(tree); 
          if(children==0) //node has no children
          {  
             tree=tree->parent; //go to the parent 
             if(tree->val>item)  //check which child is the node we want to delete 
             {
                 delete  tree->left;
                 tree->left = NULL;
             }  
             else
             {
                 delete  tree->right;
                 tree->right = NULL;  
             }
              
          //note: if the child is equal to the parent, it still goes on the right. Relevant further down
         
          }              
          else  if(tree->left==NULL) // 1 right child
          {    
               if(tree->parent != NULL)
                    tree=tree->parent; // go to the parent 
               if(tree->val>item) //according to the side of the parent the node was on, redirect pointer to its child
               {
                    delete tree->left;                  
                    tree->left = (tree->left)->right;
               }               
               else 
               {
                    delete tree->right;
                    tree->right = (tree->right)->right;
               }
          }
          else if(tree->right==NULL) // 1 left child
          {    
              if(tree->parent != NULL)
                   tree=tree->parent;
              if(tree->val>item)
              {
                   delete tree->left;
                   tree->left = (tree->left)->left;
              }               
              else 
              {
                   delete tree->right;
                   tree->right = (tree->right)->left;
              }
          }
          else // node has 2 children
          {  
             Node* newNode =  minNode(tree->right);
             tree->val = newNode->val; // replace its value with smallest node in right subtree
             tree->frq = newNode->frq; // copy over the frequency
             deleteNode(tree->right,tree->val); // delete the node we took the value from
          }
     }    
}
void deleteTree(Node* tree)
{
     // Function to delete memory of nodes 
     if (tree->left != NULL)
		deleteTree(tree->left);    
	if (tree->right != NULL)
		deleteTree(tree->right);
     delete tree;
}
