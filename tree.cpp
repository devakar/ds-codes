#include <iostream>
#include <bits/stdc++.h>

using namespace std;

struct tree{
    int data;
    struct tree *left;
    struct tree *right;
};

void insertNode(struct tree **root, int data){
    struct tree *newnode = (struct tree*)malloc(sizeof(struct tree));
    newnode->data=data;
    newnode->left=NULL;
    newnode->right=NULL;
    if(!(*root)){
        *root=newnode;
        return;
    }
}

