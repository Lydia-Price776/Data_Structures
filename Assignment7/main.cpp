#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <iostream>
#include <fstream>

using namespace std;

vector<int> vector_random;
vector<int> vector_reversed;
vector<int> vector_sorted;

class Heap{
private:
    vector<int> data;
    int insertComparisons;
    int deleteComparisons;
public:;
    Heap() {
        insertComparisons = 0;
        deleteComparisons = 0;
    };
    ~Heap() {};
    void InsertHeap(int &newElement);
    int DeleteRoot();
    void PrintHeap();
    int getInsertComparisons() {return insertComparisons;};
    int getDeleteComparisons() {return deleteComparisons;};
    int checkForChildNum(int parentIndex, int n);
    void Debug(int parent_Index, int left_Index, int right_Index, int childNum);
};

//Inserts a new element to the heap
void Heap::InsertHeap(int &newElement) {
    data.push_back(newElement);
    if(data.size() == 1) return;
    int child_Index = data.size() - 1;
    int parent_Index = 0;
    bool swapping = true;

    while(swapping) {
        swapping = false;
        if(child_Index % 2 == 0) {
            parent_Index = child_Index / 2 - 1;

        } else {
            parent_Index = child_Index / 2;

        }
        if(parent_Index >= 0) {
            if(data[child_Index] > data[parent_Index]) {
                swap(data[child_Index], data[parent_Index]);
                swapping = true;
                child_Index = parent_Index;
            }
            insertComparisons++;
        }
    }
}

//Checks and returns the number of children given a parent index
int Heap::checkForChildNum(int parentIndex, int n) {
    int left_Index = parentIndex * 2 + 1;
    int right_Index = parentIndex * 2 + 2;

    if(left_Index <= n - 1 && right_Index <= n - 1) {
        return 2;
    } else if(left_Index <= n - 1) {
        return 1;
    } else {
        return 0;
    }
}

//Deletes the current root from the heap and reorganises the heap
int Heap::DeleteRoot() {

    if(data.size() < 1) {
        return -1;
    }
    int toReturn = data[0];
    data[0] = data[(data.size() - 1)];
    data.pop_back();

    int parent_Index = 0;
    int left_Index = parent_Index * 2 + 1;
    int right_Index = parent_Index * 2 + 2;
    int childNum;
    if(data.size() > 2) {
        childNum = checkForChildNum(parent_Index, data.size());
        deleteComparisons = deleteComparisons + childNum;

        while(data[parent_Index] < data[left_Index] || data[parent_Index] < data[right_Index]) {

            if(data[right_Index] < data[left_Index]) {
                swap(data[left_Index], data[parent_Index]);
                parent_Index = left_Index;

            } else {
                swap(data[right_Index], data[parent_Index]);
                parent_Index = right_Index;

            }

            left_Index = parent_Index * 2 + 1;
            right_Index = parent_Index * 2 + 2;
            childNum = checkForChildNum(parent_Index, data.size());
            deleteComparisons = deleteComparisons + childNum;

            if(left_Index > data.size() - 1) {
                break;
            } else {
                if(right_Index > data.size() - 1) {
                    if(data[parent_Index] < data[left_Index]) {
                        swap(data[parent_Index], data[left_Index]);
                    }
                    break;
                }
            }
        }
    } else {
        childNum = checkForChildNum(parent_Index, data.size());
        deleteComparisons = childNum + deleteComparisons;
        if(data[parent_Index] < data[left_Index]) {
            swap(data[parent_Index], data[left_Index]);
        }
    }
    return toReturn;
}

//Prints items in a heap
void Heap::PrintHeap() {
    for(int i = 0; i < data.size(); i++) {
        cout << data[i] << " ";
    }
    cout << endl;
}

//Sorts the given heap and displays the heap before and sorted vector after
void heapsort(vector<int> &sortingVector, int number_of_elements, char *filename) {
    Heap heap;
    vector<int> result;

    for(int i = 0; i < number_of_elements; i++) {
        heap.InsertHeap(sortingVector[i]);
    }

    cout << "Heap before sorting: " << filename << endl;
    heap.PrintHeap();
    cout << "InsertHeap: " << heap.getInsertComparisons() << " comparisons" << endl;

    int t = 0;
    while(t != -1) {
        t = heap.DeleteRoot();
        if(t != -1) {
            result.insert(result.begin(), t);
        }
    }

    cout << "DeleteRoot: " << heap.getDeleteComparisons() << " comparisons" << endl;

    cout << "Vector after sorting:\n";
    for(int i = 0; i < result.size(); i++) {
        cout << result[i] << " ";
    }
    cout << endl;
}


int main(int argc, char **argv) {
    char expression[100] = "";
    int number;
    ifstream input_file_random;
    ifstream input_file_reversed;
    ifstream input_file_sorted;
    if(argc == 4) {
        input_file_random.open(argv[1]);
        input_file_reversed.open(argv[2]);
        input_file_sorted.open(argv[3]);
    } else {
        printf("The program needs 3 filenames, in this order: random, reversed and sorted.\n");
        exit(0);
    }
    int number_of_elements_random = 0;
    while(input_file_random >> number) {
        sscanf(expression, "%d", &number);
        vector_random.push_back(number);
        number_of_elements_random++;
    }

    int number_of_elements_reversed = 0;
    while(input_file_reversed >> number) {
        sscanf(expression, "%d", &number);

        vector_reversed.push_back(number);
        number_of_elements_reversed++;
    }

    int number_of_elements_sorted = 0;
    while(input_file_sorted >> number) {
        sscanf(expression, "%d", &number);
        vector_sorted.push_back(number);
        number_of_elements_sorted++;
    }
    heapsort(vector_random, number_of_elements_random, argv[1]);
    cout << endl;
    heapsort(vector_reversed, number_of_elements_reversed, argv[2]);
    cout << endl;
    heapsort(vector_sorted, number_of_elements_sorted, argv[3]);
}
