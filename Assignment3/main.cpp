// Lydia Price
//ID: 20004521

#include <cstdlib>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
using namespace std;

struct Node{
    int data;
    Node *next;
};

class Queue{
private:
    Node *front, *rear;
    int counter;
public:
    Queue();
    ~Queue();
    void Join(int New_Element);
    void Leave();
    int Front();
    bool isEmpty();
    int Length();
};

// Constructor
Queue::Queue() {
    front = NULL;
    rear = NULL;
    counter =0;
}
//Destructor
Queue::~Queue() {}

//This method adds a new element at the end of the queue
void Queue::Join(int New_Element) {
    Node *temp;
    temp = new Node;
    temp->data = New_Element;
    temp->next = NULL;
    if(rear != NULL) {rear->next = temp;}
    rear = temp;
    if(front == NULL) {front = temp;}
    counter ++;
}

//This Method removes the front item from the queue
void Queue::Leave() {
    Node *temp;
    if(front == NULL) {return;}
    temp = front;
    front = front->next;
    if(front == NULL) {rear = NULL;}
    delete temp;
    counter --;
}

//This method returns the value of the front item
int Queue::Front() {
    return front->data;
}

//This method returns true if the queue is empty
bool Queue::isEmpty() {
    if(front == NULL) {return true;}
    return false;
}

//This method returns the length of the queue
int Queue::Length() const {
    return counter;
}


#define TIMEDELAY 3
#define N 128
int OutQueues_current[N];
int Congestion_Size[N];

Queue InputQueues[N];
Queue OutputQueues[N];

void init_simulation() {
    for(int a = 0; a < N; a++) {
        OutQueues_current[a] = 0;
        Congestion_Size[a] = 0;
    }
}

int sum_elements_array(int array[]) {
    int sum = 0;
    for(int a = 0; a < N; a++) {
        sum = sum + array[a];
    }
    return sum;
}

int number_of_ports = 0;

int main(int argc, char **argv) {
    int Port_Number = 0;
    string expression;
    string Get_Input;
    ifstream input_file;
    if(argc != 2) {
        cout << "Type a file name. " << endl << argv[1] << endl;
        exit(0);
    }
    input_file.open(argv[1]);
    if(!input_file.is_open()) {
        cout << "Could not read file: " << endl << argv[1] << endl;
        exit(0);
    }
    string token;
    while(!input_file.eof()) {
        getline(input_file, expression);
        stringstream line(expression);
        if(input_file.eof()) break;
        if(expression[0] == '#') continue;
        if(expression[0] == 'P') {
            getline(line, token, ' ');
            getline(line, token, ' ');
            number_of_ports = atoi(token.c_str());
            continue;
        }

        while(getline(line, token, ' ')) {
            int destination;
            destination = atoi(token.c_str());//use this one if your compiler is not C++11
            if(destination < 0 || destination > number_of_ports || number_of_ports < Port_Number) {
                cout << "ERROR in the format of the text file" << endl;
                exit(0);
            }
            InputQueues[Port_Number].Join(destination);
        }
        Port_Number++;
    }
    init_simulation();

    unsigned long int Total_Packets = 999999;
    unsigned long int clock = 0;
    Port_Number = 0;

    while(Total_Packets > 0) {
        if(!InputQueues[Port_Number].isEmpty()) {
            int temp = InputQueues[Port_Number].Front();
            OutputQueues[temp - 1].Join(temp);
            InputQueues[Port_Number].Leave();
        }
        if(clock % (TIMEDELAY * number_of_ports) == 0 && clock != 0) {
            for(int a = 0; a < number_of_ports; a++) {
                OutputQueues[a].Leave();
            }
        }
        clock++;

        for(int i = 0; i < number_of_ports; i++) {
            OutQueues_current[i] = OutputQueues[i].Length();
        }
        Total_Packets = sum_elements_array(OutQueues_current);


        Port_Number++;
        if(Port_Number > (number_of_ports -1 )){Port_Number = 0;}



        if(Total_Packets > sum_elements_array(Congestion_Size)) {
            for(int a = 0; a < number_of_ports; a++) {
                Congestion_Size[a] = OutQueues_current[a];
            }
        }

    }
    for(int i = 0; i < number_of_ports; i++) {
        cout << "output port " << i + 1 << ": " << Congestion_Size[i] << " packets" << endl;
    }
}