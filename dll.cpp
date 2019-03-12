#include <iostream>
#include <bits/stdc++.h>
using namespace std;

struct node{
    int data;
    struct node *left;
    struct node *right;
};

void push(struct node **head, int data){
    struct node *newnode = (struct node *)malloc(sizeof(struct node));
    newnode->data=data;
    newnode->right=(*head);
    newnode->left=NULL;
    if(*head)
        (*head)->left=newnode;
    (*head)=newnode;
}

void append(struct node **head, int data){
    struct node *newnode = (struct node *)malloc(sizeof(struct node));
    newnode->data=data;
    newnode->right=NULL;
    if(!(*head)){
        newnode->left=NULL;
        *head=newnode;
        return;
    }
    struct node *cur=*head;
    while(cur->right){
        cur=cur->right;
    }
    cur->right=newnode;
    newnode->left=cur;
}

void insertAfter(struct node *head, int data){
    struct node *newnode = (struct node *)malloc(sizeof(struct node));
    newnode->data=data;
    newnode->right=head->right;
    newnode->left=head;
    head->right->left=newnode;
    head->right=newnode;
}

void insertBefore(struct node **head, struct node *insert, int data){
    struct node *newnode=(struct node *)malloc(sizeof(struct node));
    newnode->data=data;
    if(*head==insert){
        newnode->left=NULL;
        newnode->right=insert;
        insert->left=newnode;
        *head=newnode;
        return;
    }
    struct node *cur=*head;
    while(cur && cur!=insert)
        cur=cur->right;
    if(cur!=insert)
        return;
    
    newnode->right=insert;
    newnode->left=insert->left;
    insert->left->right=newnode;
    insert->left=newnode;
}

void deleteNode(struct node **head, struct node *del){
    struct node *temp=del,*cur=*head;
    if(*head==del){
        *head=del->right;
        del->left=NULL;
        free(temp);
        return;
    }
    while(cur && cur!=del)
        cur=cur->right;
    
    if(!cur)
        return;
    
    del->left->right=del->right;
    if(del->right)
        del->right->left=del->left;
    free(temp);
    
}

void reverse(struct node **head){
    struct node *cur=*head, *temp=NULL;
    while(cur){
        temp=cur->left;
        cur->left=cur->right;
        cur->right=temp;
        cur=cur->left;
    }
    if(temp)
        *head=temp->left;
}

//merge sort
struct node* split(struct node *head){
    if(!head || !head->right)
        return head;
    struct node *slow=head, *fast=head;
    while(fast->right && fast->right->right){
        slow=slow->right;
        fast=fast->right->right;
    }
    fast=slow->right;
    slow->right=NULL;
    return fast;
}

struct node* merge(struct node *first, struct node *second){
    if(!first)
        return second;
    if(!second)
        return first;

    struct node *res=NULL;
   
    if(first->data < second->data){
        first->right=merge(first->right, second);
        first->right->left=first;
        first->left=NULL;
        return first;
    }
    else{
        second->right=merge(first, second->right);
        second->right->left=second;
        second->left=NULL;
        return second;
    }
}

void mergesort(struct node **head){
    if(!*head || !(*head)->right)
        return;
    struct node *second = split(*head);
    mergesort(head);
    mergesort(&second);
    *head=merge(*head, second);
}

//quick sort

struct node* getTail(struct node *head){
    if(!head || !head->right)
        return head;
    while(head && head->right){
        head=head->right;
    }
    return head;
}

struct node* getPivot(struct node *head, struct node *tail, struct node **newhead, struct node **newtail){
    struct node *pivot=tail, *cur=head, *temp;
    while(cur!=pivot){
        if(cur->data<pivot->data){
            if(!*newhead)
                *newhead=cur;
                (*newhead)->left=NULL;
            cur=cur->right;
        }
        else{
            temp=cur->right;
            if(cur->left)
                cur->left->right=cur->right;
            if(cur->right)
                cur->right->left=cur->left;
            tail->right=cur;
            cur->left=tail;
            cur->right=NULL;
            tail=cur;
            temp->left=NULL;
            cur=temp;
        }
    }
    if(!*newhead)
        *newhead=pivot;
        (*newhead)->left=NULL;
    *newtail=tail;
    (*newtail)->right=NULL;
    return pivot;
}

struct node* quicksortUtil(struct node *l, struct node *h){
    if(!l || l==h)
        return l;
    struct node *newhead=NULL, *newtail=NULL, *temp=NULL, *temp2=NULL;
    struct node *pivot=getPivot(l,h,&newhead,&newtail);
    
    if(newhead!=pivot){
        temp=newhead;
        while(temp->right!=pivot){
            temp=temp->right;
        }
        temp->right=NULL;
        pivot->left=NULL;
        newhead=quicksortUtil(newhead, temp);
        temp=getTail(newhead);
        temp->right=pivot;
        pivot->left=temp;
    }
    temp2=quicksortUtil(pivot->right, newtail);
    pivot->right=temp2;
    if(temp2)
        temp2->left=pivot;
    return newhead;
}

void quicksort(struct node **head){
    if(!*head || !(*head)->right)
        return;
    *head=quicksortUtil(*head, getTail(*head));
}


void printList(struct node *head){
    cout<<"\n";
    while(head){
        cout<<head->data<<" ";
        head=head->right;
    }
    cout<<"\n";
}

void printListReverse(struct node *head){
    cout<<"\n";
    struct node *cur=head;
    while(cur->right){
        cur=cur->right;
    }
    while(cur && cur->right!=head){
        cout<<cur->data<<" ";
        cur=cur->left;
    }
    cout<<"\n";
}

int main(){
    struct node *head=NULL;
    push(&head,1);
    push(&head,2);
    push(&head,3);
    printList(head);
    append(&head,4);
    append(&head, 5);
    append(&head,6);
    printList(head);

    // insertAfter(head->right->right->right, 7);
    // printList(head);
    // insertBefore(&head, head->right->right->right, 8);
    // printList(head);
    // insertBefore(&head, head, 9);
    // printList(head);

    // deleteNode(&head, head->right);
    // printList(head);
    // deleteNode(&head, head);
    // printList(head);
    // deleteNode(&head, head->right->right->right->right->right);
    // printList(head);
    // deleteNode(&head, head->right->right->right->right->right);
    // printList(head);

    // reverse(&head);
    // printList(head);
    // printListReverse(head);
    //mergesort(&head);
    quicksort(&head);
    printList(head);
    printListReverse(head);
    // deleteNode(&head, head->right->right->right->right->right->right->right->right);
    // printList(head);
    // printListReverse(head);
    // quicksort(&head);
    // printList(head);
    // printListReverse(head);
}
