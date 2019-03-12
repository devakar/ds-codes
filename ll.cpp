#include <iostream>
#include <bits/stdc++.h>
#include <unordered_set>

using namespace std;

struct node {
    int data;
    struct node* next;
};

struct specialNode {
    int data;
    struct specialNode *right;
    struct specialNode *down;
};

void push(struct node** head, int data){
    struct node* newnode;
    newnode = (struct node*)malloc(sizeof(struct node));
    newnode->data = data;
    newnode->next = *head;
    *head = newnode;
}

void append(struct node** head, int data){
    struct node* start, *newnode;
    start = *head;
    newnode = (struct node*)malloc(sizeof(struct node));
    newnode->data=data;
    newnode->next=NULL;
    if(!start){
        *head=newnode;
        return;
    }
    while(start->next){
        start=start->next;
    }
    start->next=newnode; 
}

void insert(struct node *prev, int data){
    struct node *newnode;
    newnode = (struct node *)malloc(sizeof(struct node));
    newnode->data=data;
    newnode->next=prev->next;
    prev->next = newnode;
}

void deletebyKey(struct node **head, int key){
    struct node *start, *prev;
    start=*head;
    if(!head){
        return;
    }
    if(start->data==key){
        *head=start->next;
        free(start);
        return;
    }
    prev=start;
    start=start->next;
    while(start){
        if(start->data==key){
            prev->next=start->next;
            start->next=NULL;
            free(start);
            return;
        }
        start=start->next;
        prev=prev->next;
    }
}

void deletebyPos(struct node **head, int pos){
    struct node *cur, *temp;
    if(!*head){
        return;
    }
    cur = *head;
    if(pos==1){
        *head=cur->next;
        free(cur);
        return;
    }
    for(int i=1;cur && i<pos-1;i++){
        cur = cur->next;
    }
    if(!cur){
        return;
    }
    temp = cur->next;
    cur->next=temp->next;
    free(temp);
}

void deleteList (struct node **head){
    struct node *cur, *temp;
    if(!*head){
        return;
    }
    cur=*head;
    while(cur){
        temp = cur;
        *head=cur->next;
        free(temp);
        cur=cur->next;
    }
}

int lengthByIteration(struct node *head){
    struct node * cur =head;
    int count =0;
    while(cur){
        count++;
        cur = cur->next;
    }
    return count;
}

int lengthByRecursion(struct node *head){
    if(!head){
        return 0;
    }
    else{
        return 1+lengthByRecursion(head->next);
    }
}

bool isKeyByIteration(struct node *head, int key){
    if(!head){
        return false;
    }
    struct node *cur = head;
    while(cur){
        if(cur->data==key){
            return true;
        }
        cur =cur->next;
    }
    return false;
}

bool isKeyByRecursion(struct node *head, int key){
    if(!head){
        return false;
    }
    if(head->data==key){
        return true;
    }
    else{
        return false || isKeyByRecursion(head->next, key);
    }
}

int getKeyByPos(struct node *head, int pos){
    if(!head){
        assert(0);
        //return;
    }
    struct node *cur=head;
    for(int i=0;cur&&i<pos;i++){
        cur=cur->next;
    }
    if(!cur){
        assert(0);
        //return;
    }
    return cur->data;
}

int getKeyFromEnd(struct node *head, int pos){
    struct node *slow, *fast;
    fast=head;
    slow=head;
    for(int i=1;fast && i<pos;i++){
        fast=fast->next;
    }
    while(fast->next && slow){
        fast=fast->next;
        slow=slow->next;
    }
    if(slow){
        return slow->data;
    }
    else{
        assert(0);
    }
}

void getMiddle(struct node *head){
    if(!head){
        return;
    }
    struct node *slow, *fast;
    slow=head;
    fast=head;
    while(slow && fast && fast->next && slow->next){
        slow=slow->next;
        fast=fast->next->next;
    }
    cout<<slow->data;
}

//----------------------------------
// Reverse
void reverseList(struct node **head){
    if(!*head || !(*head)->next){
        return;
    }

    struct node *prev, *cur, *nxt;
    prev=NULL;
    cur=*head;
    nxt=NULL;
    while(cur){
        nxt=cur->next;
        cur->next=prev;
        prev=cur;
        cur=nxt;  
    }
    *head=prev;
}

void reverseListByRecursion(struct node **head){
    if(!*head || !(*head)->next){
        return;
    }
    struct node *first, *rest;
    first=*head;
    rest=(*head)->next;

    reverseListByRecursion(&rest);

    first->next->next=first;
    first->next=NULL;

    *head=rest;
}
//---------------------------------


bool checkPalindromeByStack(struct node *head){
    stack <int> s;
    struct node *cur=head;
    while(cur){
        s.push(cur->data);
        cur=cur->next;
    }
    cur=head;
    while(!s.empty() && cur){
        cout<<s.top()<<" ";
        if(s.top()!=cur->data){
            return false;
        }
        s.pop();
        cur=cur->next;
    }
    cout<<"\n";
    return true;
}

bool compareTwoList(struct node *list1, struct node *list2){
    while(list1 && list2){
        if(list1->data != list2->data){
            return false;
        }
        list1=list1->next;
        list2=list2->next;
    }

    if((!list1 && list2) || (list1 && !list2)){
        return false;
    }

    return true;
}

bool checkPalindromeByReverse(struct node *head){
    if(!head || !head->next){
        return true;
    }

    struct node *fast, *slow, *mid, *slow_prev;
    slow=head;
    fast=head;
    mid=NULL;
    slow_prev=NULL;

    while(slow && fast && fast->next){
        slow_prev=slow;
        slow=slow->next;
        fast=fast->next->next;
    }

    //in odd fast is not null and in case of even fast is null
    if(fast){
        mid=slow;
        slow=slow->next;
    }

    slow_prev->next=NULL;

    reverseList(&slow);
    bool res=compareTwoList(head, slow);
    reverseList(&slow);

    if(mid){
        mid->next=slow;
        slow=mid;
    }

    slow_prev->next=slow;
    return res;
}

//---------------------------------
// check palindrome by recursion
bool checkPalindromeByRecursionUtil(struct node **left, struct node *right){
    if(!right){
        return true;
    }
    bool isPalindrome = checkPalindromeByRecursionUtil(left, right->next);
    if(!isPalindrome){
        return false;
    }
    bool isSameValue = ((*left)->data==right->data);

    *left=(*left)->next;
    return isSameValue;
}

bool checkPalindromeByRecursion(struct node *head){
    if(!head || !head->next){
        return true;
    }
    return checkPalindromeByRecursionUtil(&head, head);
}

//----------------------------------


void removeDuplicateInSorted(struct node *head){
    struct node *cur, *temp;
    cur=head;
    if(!head){
        return;
    }
    while(cur->next){
        if(cur->data==cur->next->data){
            temp=cur->next;
            cur->next=temp->next;
            free(temp);
        }
        else{
            cur=cur->next;
        }
    }
}

void removeDuplicateInSortedByRecursion(struct node *head){
    if(!head || !head->next){
        return;
    }
    struct node *cur, *temp;
    cur=head;
    if(cur->data==cur->next->data){
        temp=cur->next;
        cur->next=temp->next;
        free(temp);
        removeDuplicateInSortedByRecursion(cur);
    }
    else{
        removeDuplicateInSortedByRecursion(cur->next);
    }
}

void removeDuplicateInUnsortedByHash(struct node *head){
    if(!head || !head->next){
        return;
    }
    unordered_set <int> seen;
    struct node *cur, *temp, *prev;
    cur=head;
    prev=NULL;
    while(cur){
        if(seen.find(cur->data) != seen.end()){
            prev->next=cur->next;
            temp=cur;
            free(temp);
            cur=prev->next;
        }
        else{
            seen.insert(cur->data);
            prev=cur;
            cur=cur->next;
        }
    }
}

//------------------------------------------
// Quick Sort
struct node * getTail(struct node *head){
    if(!head || !head->next){
        return head;
    }
    while(head && head->next){
        head=head->next;
    }
    return head;
}

struct node *getPivot(struct node *head, struct node *end, struct node **newhead, struct node **newend){
    struct node *pivot=end;
    struct node *cur=head, *prev=NULL, *tail=pivot;
    while(cur!=pivot){
        if(cur->data < pivot->data){
            if(!(*newhead))
                *newhead=cur;
            prev=cur;
            cur=cur->next;
        }
        else{
            if(prev)
                prev->next=cur->next;
            struct node *temp=cur->next;
            cur->next=NULL;
            tail->next=cur;
            tail=cur;
            cur=temp;
        }
    }

    if(!*newhead)
        *newhead=pivot;

    *newend=tail;
    return pivot;
    
}

struct node * quicksortUtil(struct node *head, struct node *tail){
    if(!head || head==tail)
        return head;
    struct node *newhead=NULL, *newtail=NULL, *temp=NULL;
    struct node *pivot=getPivot(head, tail, &newhead, &newtail);

    //if pivot is not smallest element
    if(newhead!=pivot){
        temp=newhead;
        while(temp->next!=pivot)
            temp=temp->next;
        temp->next=NULL;
        newhead=quicksortUtil(newhead, temp);
        temp=getTail(newhead);
        temp->next=pivot;
    }

    pivot->next=quicksortUtil(pivot->next, newtail);
    return newhead;
}

void quicksort(struct node **head){
    *head=quicksortUtil(*head, getTail(*head));
    return;
}
//------------------------------------------

//insertion sort
void sortedinsert(struct node **head, struct node *newnode){
    if(!*head || (*head)->data>newnode->data){
        newnode->next=*head;
        *head=newnode;
    }
    else{
        struct node *cur=*head;
        while(cur->next && cur->next->data<newnode->data){
            cur=cur->next;
        }
        newnode->next=cur->next;
        cur->next=newnode;
    }
    
}

void insertionsort(struct node **head){
    if(!*head || !(*head)->next)
        return;
    struct node *cur=*head, *next=NULL, *sorted=NULL;
    while(cur){
        next=cur->next;
        sortedinsert(&sorted, cur);
        cur=next;
    }
    *head=sorted;
}

//----------------------------------------

//Merge sort
void splitfrontback(struct node *head, struct node **a, struct node **b){
    if(!head){
        *a=NULL;
        *b=NULL;
        return;
    }
    if(!head->next){
        *a=head;
        *b=NULL;
        return;
    }

    struct node *slow=head, *fast=head, *slow_prev=NULL;
    while(slow && slow->next && fast && fast->next){
        slow_prev=slow;
        slow=slow->next;
        fast=fast->next->next;
    }
    *a=head;
    *b=slow;
    slow_prev->next=NULL;
}

struct node* sortedmerge(struct node *a, struct node *b){
    if(!a)
        return b;
    if(!b)
        return a;

    struct node *res=NULL;
    while(a && b){
        if(a->data < b->data){
            append(&res, a->data);
            a=a->next;
        }
        else{
            append(&res, b->data);
            b=b->next;
        }
    }
    while(a){
        append(&res, a->data);
        a=a->next;
    }
    while(b){
        append(&res, b->data);
        b=b->next;
    }
    return res;
}
void mergesort(struct node **head){
    if(!*head || !(*head)->next)
        return;
    struct node *cur=*head, *a, *b;
    splitfrontback(cur,&a, &b);
    mergesort(&a);
    mergesort(&b);
    *head=sortedmerge(a,b);
}

//------------------------------------------


// Flatten linked list with down and right nodes
struct specialNode* merge(struct specialNode *a, struct specialNode *b){
    if(!a)
        return b;
    if(!b)
        return a;
    struct specialNode *result;
    if(a->data < b->data){
        result=a;
        result->down=merge(a->down, b);
    }
    else{
        result=b;
        result->down=merge(a, b->down);
    }
    return result;
    
}


struct specialNode* flatten(struct specialNode *head){
    if(!head || !head->right)
        return head;
    return merge(head, flatten(head->right));
}

void push (struct specialNode** head_ref, int new_data) 
{ 
    /* allocate node */
    specialNode* new_node = (specialNode *) malloc(sizeof(specialNode)); 
    new_node->right = NULL; 
  
    /* put in the data  */
    new_node->data  = new_data; 
  
    /* link the old list off the new node */
    new_node->down = (*head_ref); 
  
    /* move the head to point to the new node */
    (*head_ref)    = new_node; 
} 

void printSpecialList(struct specialNode* head){
    while(head){
        cout<<head->data<<"   ";
        head= head->down;
    }
    cout<<"\n";
}

//------------------------------------------------------------------------
void printList(struct node* head){
    while(head){
        cout<<head->data<<"   ";
        head= head->next;
    }
    cout<<"\n";
}
int main(){
    struct node * head = NULL;
    push(&head, 1);
    push(&head, 2);
    //printList(head);

    struct node* head2 = NULL;
    append(&head2, 1);
    append(&head2, 2);
    //printList(head2);

    insert(head->next, 3);
    insert(head->next->next, 4);
    //printList(head);

    // deletebyKey(&head, 3);
    // deletebyKey(&head, 2);
    // cout<<"-----------------\n";
    // printList(head);

    // deletebyPos(&head, 3);
    // deletebyPos(&head, 6);
    // deletebyPos(&head, 1);
    // cout<<"-----------------\n";
    // printList(head);

    struct node *head3=NULL;
    append(&head3, 2);
    append(&head3, 1);
    append(&head3, 1);
    //cout<<"-----------------,\n"<<lengthByIteration(head3)<<"\n"<<lengthByRecursion(head3)<<"\n-------------\n";
    //printList(head3);
    //deleteList(&head3);
    //cout<<"-----------------\n"<<lengthByIteration(head3)<<"\n"<<lengthByRecursion(head3)<<"\n-------------\n";
    //printList(head3);

    // cout<<"\n---------\n"<<isKeyByIteration(head3, 3);
    // cout<<"\n---------\n"<<isKeyByIteration(head3, 1);
    // cout<<"\n---------\n"<<isKeyByRecursion(head3, 3);
    // cout<<"\n---------\n"<<isKeyByRecursion(head3, 1)<<"\n";
    //cout<<"\n---------\n"<<getKeyByPos(head3, 3);
    //cout<<"\n---------\n"<<getKeyByPos(head3, 1)<<"\n";
    //cout<<"\n---------\n"<<getKeyFromEnd(head3, 1)<<"\n";
    //getMiddle(head3);
    // reverseList(&head3);
    // printList(head3);
    // reverseListByRecursion(&head3);
    // printList(head3);

    //cout<<"\n"<<checkPalindromeByStack(head3)<<"\n";
    //cout<<"\n"<<checkPalindromeByReverse(head3)<<"\n";
    //cout<<"\n"<<checkPalindromeByRecursion(head3)<<"\n";
    //removeDuplicateInSorted(head3);
    printList(head3);
    //removeDuplicateInSortedByRecursion(head3);
    //printList(head3);
    //removeDuplicateInUnsortedByHash(head3);
    //printList(head3);
    //quicksort(&head3);
    //insertionsort(&head3);
    mergesort(&head3);
    printList(head3);

    // struct specialNode *root=NULL;
    // push( &root, 30 ); 
    // push( &root, 8 ); 
    // push( &root, 7 ); 
    // push( &root, 5 ); 
  
    // push( &( root->right ), 20 ); 
    // push( &( root->right ), 10 ); 
  
    // push( &( root->right->right ), 50 ); 
    // push( &( root->right->right ), 22 ); 
    // push( &( root->right->right ), 19 ); 
  
    // push( &( root->right->right->right ), 45 ); 
    // push( &( root->right->right->right ), 40 ); 
    // push( &( root->right->right->right ), 35 ); 
    // push( &( root->right->right->right ), 20 ); 

    // flatten(root);
    // printSpecialList(root);
}