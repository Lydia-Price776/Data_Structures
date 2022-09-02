//Lydia Price
//20004521

#include <cstdlib>
#include <iostream>
#include <fstream>
#include <string>
#include <cmath>

using namespace std;

//List Class
template<class T>
class List{
private:
    struct Node{
        T data;
        Node *next;
    };
    Node *front, *current;
    int counter;
public:
    List();
    ~List();
    void Add_To_Front(T New_Element);
    void Add_to_end(T New_Element);
    bool First_item(T &element);
    bool Next_Item(T &element);
    void Reverse();
    int Length();
};

//Constructor
template<class T>
List<T>::List() {
    front = NULL;
    current = NULL;
}
//Destructor
template<class T>
List<T>::~List() {}

//Method to add new elements to front of list
template<class T>
void List<T>::Add_To_Front(T New_Element) {
    Node *temp;
    temp = new Node;
    temp->data = New_Element;
    temp->next = front;
    front = temp;
    counter++;
}

//Method to add new elements to end of list
template<class T>
void List<T>::Add_to_end(T New_Element) {
    Node *current;
    current = front;
    if(current != NULL) {
        while(current->next != NULL) {
            current = current->next;
        }
    }
    Node *temp;
    temp = new Node;
    temp->data = New_Element;
    temp->next = NULL;
    if(current != NULL) {
        current->next = temp;
    } else {
        front = temp;
    }
}


//Method to identify front element
template<class T>
bool List<T>::First_item(T &element) {
    if(front == NULL) {return false;}
    element = front->data;
    current = front;
    return true;
}
//Method to Identify the next item in list
template<class T>
bool List<T>::Next_Item(T &element) {
    current = current->next;
    if(current == NULL) {return false;}
    element = current->data;
    return true;
}

//Method to reverse list
template<class T>
void List<T>::Reverse() {
    Node *temp1, *temp2;
    current = front->next;
    temp2 = front;
    while(current != NULL) {
        temp1 = current->next;
        current->next = front;
        front = current;
        current = temp1;
    }
    temp2->next = NULL;
}

//Returns the length of specified list
template<class T>
int List<T>::Length() {
    return counter;
}


//Big Number Class
class BigNumber{
private:
    List<int> List_of_Digits;
public:
    BigNumber();
    ~BigNumber();
    void ReadFromString(string Dec_String);
    void PrintBigNumber();
    void AddBigNumbers(BigNumber B1, BigNumber B2);
};

//Constructor
BigNumber::BigNumber() {}

//Destructor
BigNumber::~BigNumber() {}

//Method to read number from a string, convert its digits to integers and add to list.
void BigNumber::ReadFromString(string Dec_String) {
    for(int i = 0; i < Dec_String.size(); i++) {
        if(Dec_String[i] != '\n' && Dec_String[i] != '\r') {
            int temp = (int) Dec_String[i] - 48;
            List_of_Digits.Add_To_Front(temp);
        }
    }
    List_of_Digits.Reverse();
}

//Function to print list of Big Number
void BigNumber::PrintBigNumber() {
    bool ok;
    int temp;
    ok = List_of_Digits.First_item(temp);
    while(ok) {
        cout << temp;
        ok = List_of_Digits.Next_Item(temp);

    }
}
//function to add two big numbers together
void BigNumber::AddBigNumbers(BigNumber B1, BigNumber B2) {
    int carry = 0;
    int partial_result;
    int digit1, digit2;

    B1.List_of_Digits.Reverse();
    B2.List_of_Digits.Reverse();

    if(B1.List_of_Digits.Length() != B2.List_of_Digits.Length()) {
        if(B1.List_of_Digits.Length() > B2.List_of_Digits.Length()) {
            int Length_Difference = B1.List_of_Digits.Length() - B2.List_of_Digits.Length();
            for(int i = 0; i < Length_Difference; i++) {
                B2.List_of_Digits.Add_to_end(0);
            }
        } else {
            int Length_Difference = B2.List_of_Digits.Length() - B1.List_of_Digits.Length();
            for(int i = 0; i < Length_Difference; i++) {;
                B1.List_of_Digits.Add_to_end(0);
            }
        }
    }

    bool checker1 = B1.List_of_Digits.First_item(digit1);
    bool checker2 = B2.List_of_Digits.First_item(digit2);

    while(checker1 && checker2) {
        partial_result = digit1 + digit2 + carry;
        List_of_Digits.Add_To_Front(partial_result % 10);

        if(partial_result <= 9) {
            carry = 0;
        } else {
            carry = partial_result / 10;
            // cout << "carry is " << carry << endl;
        }
        checker1 = B1.List_of_Digits.Next_Item(digit1);
        checker2 = B2.List_of_Digits.Next_Item(digit2);
    }
    if(carry > 0) {
        List_of_Digits.Add_To_Front(carry);
    }
}


BigNumber B1, B2, RES;

int main(int argc, char **argv) {
    string Number_String;
    int count = 0;
    ifstream input_file;

    if(argc == 2) {
        input_file.open(argv[1]);
    } else {
        cout << "cannot read the file " << argv[1] << endl;
        exit(0);
    }

    if(input_file.is_open()) {
        while(!input_file.eof()) {
            getline(input_file, Number_String);
            if(!input_file.eof()) {
                //   cout << "reading a big number from file: " << Number_String << endl;//Comment this out for your final version
                if(count == 0) {
                    B1.ReadFromString(Number_String);
                    count = 1;
                } else {
                    B2.ReadFromString(Number_String);
                }
            }
        }
    } else {
        cout << "Unable to open file.\n";
        exit(0);
    }
    input_file.close();

    B1.PrintBigNumber();
    cout << endl << "+" << endl;
    B2.PrintBigNumber();
    cout << endl << "=" << endl;
    RES.AddBigNumbers(B1, B2);
    RES.PrintBigNumber();
}

