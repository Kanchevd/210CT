/*************************************************************************
Unit Testing Library: Catch2
Link: https://github.com/catchorg/Catch2
*************************************************************************/
#include "binarySearchTree.cpp"
#include "../catchDef.hpp"
Node* decTree()
{
     Node* strTree = insertNode(NULL,"c");
     vector<string> letters = {"b","a","e","d","h",};
     for(auto it=letters.begin();it!=letters.end();it=next(it))
          insertNode(strTree,*it);
     return strTree;
}


TEST_CASE("Inserting nodes")
{     
     Node* strTree = decTree();
     strTree = strTree->right; //these 2 lines needed to get to "h"
     strTree = strTree->right;
     REQUIRE(childNo(strTree)==0);
     insertNode(strTree,"f");
     REQUIRE(childNo(strTree)==1);
     insertNode(strTree,"m");
     REQUIRE(childNo(strTree)==2);    
     while(strTree->parent!=NULL)
          strTree = strTree->parent;
     deleteTree(strTree);
}

TEST_CASE("Deleting a node")
{
     Node* strTree = decTree();
     SECTION("0 children")
     {    
          strTree = strTree->right;
          REQUIRE(childNo(strTree)==2);
          deleteNode(strTree,"h");
          REQUIRE(childNo(strTree)==1);
          deleteNode(strTree,"d");
          REQUIRE(childNo(strTree)==0);
     }    
     SECTION("1 left child")
     {
          REQUIRE((strTree->left)->val=="b");
          deleteNode(strTree,"b");
          REQUIRE((strTree->left)->val=="a"); 
     }
     SECTION("1 right child")
     {    
          insertNode(strTree,"f");
          strTree = strTree->right;
          REQUIRE((strTree->right)->val=="h");
          deleteNode(strTree,"h");
          REQUIRE((strTree->right)->val=="f"); 
     }
     SECTION("2 children")
     {
          REQUIRE((strTree->right)->val=="e");
          deleteNode(strTree,"e");
          REQUIRE((strTree->right)->val=="h");
     }
     while(strTree->parent!=NULL)
          strTree = strTree->parent;
     deleteTree(strTree);
}

/*
TEST_CASE("Finding a node")
{    
     Node* strTree = decTree();
     SECTION("Valid nodes")
     {
         REQUIRE(findNode(strTree,"e")==true);
         REQUIRE(findNode(strTree,"c")==true);
         REQUIRE(findNode(strTree,"a")==true);
     }
     SECTION("Invalid nodes")
     {
         REQUIRE(findNode(strTree,"q")==false);
         REQUIRE(findNode(strTree,"hmm")==false);
     }
     deleteTree(strTree);
}
*/
TEST_CASE("Child No")
{    
     Node* strTree = decTree();
     REQUIRE(childNo(strTree)==2); //c
     strTree = strTree->left;
     REQUIRE(childNo(strTree)==1); //b
     strTree = strTree->left;
     REQUIRE(childNo(strTree)==0); //a
     while(strTree->parent!=NULL)
          strTree = strTree->parent;
     deleteTree(strTree);
}
TEST_CASE("Min Node")
{
     Node* strTree = decTree();
     REQUIRE(minNode(strTree)->val=="a");
     strTree = strTree->right;
     REQUIRE(minNode(strTree)->val=="d");
     strTree = strTree->right;
     REQUIRE(minNode(strTree)->val=="h");
     while(strTree->parent!=NULL)
          strTree = strTree->parent;
     deleteTree(strTree);
} 

