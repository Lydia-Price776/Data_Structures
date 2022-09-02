//159201 Assignment One
// Lydia Price 20004521

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

using namespace std;

struct Node {  //declaration
    int row;
    int column;
    int value;
    Node *next;
};

int c = 0, r = 0; // Declaration of global variables for matrix dimensions. This is done on the bases that matrices are both the same size.

// Function to Add Node to Tail
void Add_Node_Tail(Node *&listpointer, int row, int column, int value) {
    Node *current;
    current = listpointer;
    if (current != NULL) {
        while (current->next != NULL) {
            current = current->next;
        }
    }
    Node *temp;
    temp = new Node;
    temp->row = row;
    temp->column = column;
    temp->value = value;
    temp->next = NULL;
    if (current != NULL) {
        current->next = temp;
    }
    else {
        listpointer = temp;
    }
}

// Function to Search Nodes
int search(Node *listpointer, int x, int y) {
    Node *current;
    current = listpointer;
    while (current != NULL) {
        if ((current->row == x) && (current->column == y)) {
            return current->value;
        }
        else {
            current = current->next;
        }
    }
    return 0;
}

//Function to Print Matrix
void PrintMatrix(Node *listpointer) {
    for (int x = 0; x < r; x++) {
        for (int y = 0; y < c; y++) {
            int element1 = search(listpointer, x, y);
            printf("%d ", element1);
        }
        printf("\n");
    }
}

//Function to Print Linked List
void PrintLinkedList(Node *listpointer) {
    Node *current;
    current = listpointer;
    while (current != NULL) {
        printf("%i ", current->value);
        current = current->next;
    }
    printf("\n");
}


// Function to Read Matrix from file
void read_matrix(Node *&listpointer, char *file_name) {
    int value = 0;
    ifstream input;
    input.open(file_name);
    if (!input.good()) {
        cout << "Cannot open file " << file_name << endl;
        exit(0);
    }
    //int c;
    string line;
    if (input.good()) {
        getline(input, line);
        stringstream sline(line);
        sline >> r >> c;
    }
    for (int i = 0; i < r; ++i) {
        if (input.good()) {
            getline(input, line);
            stringstream sline(line);
            for (int j = 0; j < c; ++j) {
                sline >> value;
                if (value == 0) { continue; }
                Add_Node_Tail(listpointer, i, j, value);
            }
        }
    }
    input.close();
}

//Function to Add Matrices
void AddMatrices(Node *A, Node *B, Node *&Result) {
    for (int x = 0; x < r; x++) {
        for (int y = 0; y < c; y++) {
            int element1 = search(A, x, y);
            int element2 = search(B, x, y);
            int result = element1 + element2;
            if (result != 0) {
                Add_Node_Tail(Result, x, y, result);
            }
        }
    }
}

Node *A = NULL, *B = NULL, *Result = NULL;

int main(int argc, char **argv) {
    if (argc != 3) {
        printf("needs two matrices \n");
        exit(0);
    }

    printf("Matrix 1: ");
    read_matrix(A, argv[1]);
    PrintLinkedList(A);
    PrintMatrix(A);

    printf("Matrix 2: ");
    read_matrix(B, argv[2]);
    PrintLinkedList(B);
    PrintMatrix(B);

    printf("Matrix Result: ");
    AddMatrices(A, B, Result);
    PrintLinkedList(Result);
    PrintMatrix(Result);

}