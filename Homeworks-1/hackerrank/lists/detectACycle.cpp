#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cmath>
using namespace std;
struct Node
{
    int data;
    Node* next;
};

/*
Detect a cycle in a linked list. Note that the head pointer may be 'NULL' if the list is empty.

A Node is defined as:
    struct Node {
        int data;
        struct Node* next;
    }
*/

bool has_cycle(Node* head) {
    Node* secondHead = head->next;

    while (head != nullptr && secondHead->next != nullptr) {
        head = head->next;
        secondHead = secondHead->next->next;
        if (head == secondHead) {
            return true;
        }
    }
    return false;
}

int main()
{
    Node *A, *B, *C, *D,*E,*F;
    A = new Node();	B= new Node();  C= new Node(); D = new Node(); E = new Node(); F= new Node();
    // case 1:  NULL list
    if(has_cycle(NULL)) cout<<true<<endl;
    else cout<<false<<endl;
    //case 2:
    A->next = B;
    B->next = C;
    C->next = A;
    if(has_cycle(A)) cout<<true<<endl;
    else cout<<false<<endl;
    //case 3:
    A->next = B; B->next = C; C->next = D; D->next = E; E->next = F; F->next = E;
    if(has_cycle(A)) cout<<true<<endl;
    else cout<<false<<endl;
    //case 4:
    A->next = B; B->next = C; C->next = D; D->next = E; E->next = F; F->next = NULL;
    if(has_cycle(A)) cout<<true<<endl;
    else cout<<false<<endl;
    // case 5:
    A->next = B; B->next = C; C->next = D; D->next = E; E->next = F; F->next = A;
    if(has_cycle(A)) cout<<true<<endl;
    else cout<<false<<endl;
}