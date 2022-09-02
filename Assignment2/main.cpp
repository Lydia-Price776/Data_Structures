//Lydia Price
//ID 20004521

#include <iostream>
#include <fstream>
#include <locale>
#include <sstream>

using namespace std;

struct Node {
    int data;
    Node *next;
};

class Stack {
private:
    Node *list_pointer;
public:
    Stack();
    ~Stack();
    void Push(int new_element);
    void Pop();
    int Top();
    bool isEmpty();
};

//Constructor
Stack::Stack() {
    list_pointer = NULL;
}

//Destructor
Stack::~Stack() {}

// Places new element on top of the stack
void Stack::Push(int new_element) {
    Node *temp;
    temp = new Node;
    temp->data = new_element;
    temp->next = list_pointer;
    list_pointer = temp;
}

//Removes top element from the stack
void Stack::Pop() {
    Node *p;
    p = list_pointer;
    if (list_pointer != NULL) {
        list_pointer = list_pointer->next;
        delete p;
    }
}

//Returns the values of the top item
int Stack::Top() {
    return list_pointer->data;
}

//Returns true if the stack is empty
bool Stack::isEmpty() {
    if (list_pointer == NULL) {
        return true;
    }
    return false;
}

int main(int argc, char **argv) {
    Stack S;
    int result, op1, op2, number, final_answer;
    char Operator;
    string expression;
    ifstream input_file;

    if (argc != 2) {
        cout << "needs a filename as argument  " << endl;
        exit(0);
    }

    input_file.open(argv[1]);

    if (!input_file.good()) {
        cout << "cannot read file " << argv[1] << endl;
        exit(0);
    }
    while (!input_file.eof()) {
        getline(input_file, expression);
        if (isdigit(expression[0])) {
            stringstream line(expression);
            line >> number;
            cout << "reading number " << number << endl;
            S.Push(number);
        } else {
            if (expression[0] == '+' || expression[0] == '-' || expression[0] == '/' || expression[0] == '*') {
                stringstream line(expression);
                line >> Operator;
                cout << "reading operator " << Operator << endl;
                if (!S.isEmpty()) { //Checking for too many operators
                    op2 = S.Top();
                    S.Pop();
                } else {
                    cout << "too many operators" << endl;
                    exit(0);
                }
                if (!S.isEmpty()) { //Checking for too many operators
                    op1 = S.Top();
                    S.Pop();
                } else {
                    cout << "too many operators" << endl;
                    exit(0);
                }
                if (Operator == '+') { result = op1 + op2; }
                if (Operator == '*') { result = op1 * op2; }
                if (Operator == '-') { result = op1 - op2; }
                if (Operator == '/') { result = op1 / op2; }
                S.Push(result);
                final_answer = S.Top();
            }
        }
    }
    S.Pop();
    if (!S.isEmpty()) { //Checking for too many numbers
        cout << "too many numbers" << endl;
    } else {
        cout << "The result is " << final_answer << endl;
    }
}