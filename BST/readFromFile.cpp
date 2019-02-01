#include "binarySearchTree.cpp"
Node* readFromFile(string fileName)
{
     string temp; // string to hold words 
     ifstream f;
     f.open(fileName);
     f>>temp; //get the first word
     int skip = 1; // first word is used to initialize tree; so we skip it in the while loop
     Node* strTree = insertNode(NULL,temp);
     while(f)
     {      
          if(skip==1)
          {    
               f>>temp;
               skip--;
               continue;
          }
               insertNode(strTree,temp);  // insert current word in the tree
               f>>temp;          
    }
    f.close();
    return strTree;
}

int main()
{   
     Node* tree = readFromFile("Text.txt");
     cout<<"Finding (F):";
     findNode(tree,"F");
     preOrder(tree);
     cout<<endl<<"Deleting Leaf(A):"<<endl;
     deleteNode(tree,"A");
     preOrder(tree);
     cout<<endl<<"Deleting Node with 1 Child(C):"<<endl;
     deleteNode(tree,"C");
     preOrder(tree);
     cout<<endl<<"Deleting Node with 2 Childred(E):"<<endl;
     deleteNode(tree,"E");
     preOrder(tree);
     cout<<endl;
     return 0;
}