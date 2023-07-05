#include <stdio.h>
#include <stdlib.h>

typedef enum SIDE{
    LEFT, // 0
    RIGHT // 1
}SIDE; 

typedef struct Node 
{
    int NodeIndex;
    struct Node * Left;
    struct Node * Right;
}Node;

Node * SearchByIndex(Node * NodeToBeSearched, int IndexToBeFound)
{   
    Node * TargetNode = NULL;
    if(NULL!=NodeToBeSearched)
    {
        if (NodeToBeSearched->NodeIndex == IndexToBeFound)
        {
            TargetNode = NodeToBeSearched;
        }
        else 
        {
            if (NULL == TargetNode) TargetNode = SearchByIndex(NodeToBeSearched->Left, IndexToBeFound);
            if (NULL == TargetNode) TargetNode = SearchByIndex(NodeToBeSearched->Right, IndexToBeFound);
        }
    }
    return TargetNode;
}

Node * InitNode(Node * NodeToInit, int NodeIndex)
{
    if(NULL == NodeToInit)
    {
        NodeToInit = malloc(sizeof(struct Node));
        NodeToInit->Left = NULL;
        NodeToInit->Right = NULL;
        NodeToInit->NodeIndex = NodeIndex;        
    }
    return NodeToInit;
}

void AddNode(Node * Root, int ParentIndex, int NodeIndex, SIDE side)
{
    Node * Parent = SearchByIndex(Root, ParentIndex);
    if(NULL!=Parent)
    {
        Node * NodeToAdd = NULL;
        NodeToAdd = InitNode(NodeToAdd, NodeIndex);
        if(LEFT == side)
        {
            Parent->Left=NodeToAdd;
        }
        else if(RIGHT==side)
        {
            Parent->Right=NodeToAdd;
        }
    }
}

void PrintTree (Node * Node)
{
    if (NULL!=Node)
    {
        printf("%d\n\r", Node->NodeIndex);
        PrintTree(Node->Left);
        PrintTree(Node->Right);
    }
}

void FreeTree (Node * Node)
{
    if (NULL!=Node)
    {
        FreeTree(Node->Left);
        FreeTree(Node->Right);
        free(Node);
    }
}

int main()
{
    Node * Root = NULL;
    Root = InitNode (Root, 0);
    AddNode(Root, 0, 1, LEFT);
    AddNode(Root, 0, 2, RIGHT);
    AddNode(Root, 1, 3, LEFT);
    AddNode(Root, 1, 4, RIGHT);
    AddNode(Root, 2, 5, LEFT);
    AddNode(Root, 2, 6, RIGHT);
    PrintTree(Root);
    FreeTree(Root);
    return 0 ;
}