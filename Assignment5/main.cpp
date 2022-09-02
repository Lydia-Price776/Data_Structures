//Lydia Price
//ID - 2004521

#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <fstream>

using namespace std;

//Tree Class
class Tree{
private:
    char data;
    Tree *leftptr, *rightptr;

public:
    Tree(char New_Element, Tree *L, Tree *R);
    ~Tree() {} //Destructor
    char RootData() {return data;}
    Tree *Left() {return leftptr;}
    Tree *Right() {return rightptr;}
};
//Constructor for Tree class
Tree::Tree(char New_Element, Tree *L, Tree *R) {
    data = New_Element;
    leftptr = L;
    rightptr = R;
}

struct Node{
    Tree *data;
    Node *next;
};
//Stack Class
class Stack{
private:
    Node *List_pointer;
public:
    Stack();
    ~Stack() {}; //Destructor
    void Push(Tree *New_Element);
    void Pop();
    Tree *Top();
};

//Constructor
Stack::Stack() {
    List_pointer = NULL;
}

//Adds new element to top of stack
void Stack::Push(Tree *New_Element) {
    Node *temp;
    temp = new Node;
    temp->data = New_Element;
    temp->next = List_pointer;
    List_pointer = temp;
}

//Removes element from top of stack
void Stack::Pop() {
    Node *p;
    p = List_pointer;
    if(List_pointer != NULL) {
        List_pointer = List_pointer->next;
        delete p;
    }
}

//Returns Item on top of stack
Tree *Stack::Top() {
    return List_pointer->data;
}

//Function to print in In-fix notation
void Inorder(Tree *t) {
    if(t == NULL)return;
    if(t->Left() && t->Right()) {
        cout << "(";
    }
    Inorder(t->Left());
    cout << t->RootData();
    Inorder(t->Right());
    if(t->Left() && t->Right()) {
        cout << ")";
    }
}

//Function to print in Post-fix notation
void PostOrder(Tree *t) {
    if(t == NULL)return;
    PostOrder(t->Left());
    PostOrder(t->Right());
    cout << t->RootData() << " ";
}

Stack S;
Tree *T1, *T2, *T;
int main(int argc, char **argv) {
    char Digit;
    char Operator;
    char expression[100];
    ifstream input_file;
    if(argc == 2) input_file.open(argv[1]);
    else {
        printf("The program needs a filename as argument \n");
        exit(0);
    }

    while(input_file >> expression) {
        if(isdigit(expression[0])) {
            sscanf(expression, "%c", &Digit);
            S.Push(new Tree(Digit, NULL, NULL));
        } else {
            sscanf(expression, "%c", &Operator);
            T1 = S.Top();
            S.Pop();
            T2 = S.Top();
            S.Pop();
            S.Push(new Tree(Operator, T2, T1));
        }
    }
    T = S.Top();
    cout << "In-fix:\n";
    Inorder(T);
    cout << endl;
    cout << "Post-fix:\n";
    PostOrder(T);
    cout << endl;
}