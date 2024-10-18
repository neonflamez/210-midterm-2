// COMSC 210 || Midterm 2 || Shayan Khan

#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <string>
#include <fstream>
using namespace std;


class DoublyLinkedList {
private:
    struct Node {
        string data;
        Node* prev;
        Node* next;
        Node(string val, Node* p = nullptr, Node* n = nullptr) {
            data = val; 
            prev = p;
            next = n;
        }
    };

    Node* head;
    Node* tail;

public:
    DoublyLinkedList() { head = nullptr; tail = nullptr; }

    void push_back(string v) {
        Node* newNode = new Node(v);
        if (!tail)
            head = tail = newNode;
        else {
            tail->next = newNode;
            newNode->prev = tail;
            tail = newNode;
        }
    }
    
    void push_front(string v) {
        Node* newNode = new Node(v);
        if (!head)
            head = tail = newNode;
        else {
            newNode->next = head;
            head->prev = newNode;
            head = newNode;
        }
    }

    void pop_front() {

        if (!head) {
            cout << "List is empty." << endl;
            return;
        }

        Node * temp = head;
        cout << head->data << " is served\n";
        if (head->next) {
            head = head->next;
            head->prev = nullptr;
        }
        else
            head = tail = nullptr;
        delete temp;
    }

    void pop_back() {
        if (!tail) {
            cout << "List is empty." << endl;
            return;
        }
        Node * temp = tail;

        if (tail->prev) {
            tail = tail->prev;
            tail->next = nullptr;
        }
        else
            head = tail = nullptr;
        delete temp;
    }

    void delete_pos(int pos) {
        if (!head) {
            cout << "List is empty." << endl;
            return;
        }
    
        if (pos == 1) {
            pop_front();
            return;
        }
    
        Node* temp = head;
    
        for (int i = 1; i < pos; i++){
            if (!temp) {
                cout << "Position doesn't exist." << endl;
                return;
            }
            else
                temp = temp->next;
        }
        if (!temp) {
            cout << "Position doesn't exist." << endl;
            return;
        }
    
        if (!temp->next) {
            pop_back();
            return;
        }
    
        Node* tempPrev = temp->prev;
        tempPrev->next = temp->next;
        temp->next->prev = tempPrev;
        delete temp;
    }

    string front(){
        return head ? head->data : "";
    }
    string back(){
        return tail ? tail->data : "";
    }

    ~DoublyLinkedList() {
        while (head) {
            Node* temp = head;
            head = head->next;
            delete temp;
        }
    }
    void print() {
        Node* current = head;
        if (!current) {
            cout << "List is empty." << endl;
            return;
        }
        while (current) {
            cout << current->data << " ";
            current = current->next;
        }
        cout << endl;
    }

    void print_reverse() {
        Node* current = tail;
        if (!current) { 
            cout << "List is empty." << endl;
            return;
        }
        while (current) {
            cout << current->data << " ";
            current = current->prev;
        }
        cout << endl;
    }
};

string getRandomName(vector<string>& names){
    int index = rand() % names.size();
    return names[index];
}

void loadNamesFromFile(vector<string>& names, const string& filename){
    ifstream file(filename);
    string name;
    if(file.is_open()){
        while(getline(file, name)){
            if (!name.empty()){
                names.push_back(name);
            }
        }
        file.close();
    }
}

int main() {
    srand(time(nullptr));

    DoublyLinkedList line;
    vector<string> names;
    loadNamesFromFile(names, "names.txt");

    if(names.empty()){
        cout << "No names were loaded from file." << endl;
        return 1;
    }

    cout << "Store opens:\n";
    
    for(int i = 0; i < 5; i++){
        string newCustomer = getRandomName(names);
        line.push_back(newCustomer);
        cout << newCustomer << " joins the line\n";
    }

    cout << "Resulting line:\n";
    line.print();

    for(int timeStep = 1; timeStep <= 20; timeStep++){
        cout << "Time step #" << timeStep << ":\n";

        //40% chance
        int prob = rand() % 100 + 1;
        if(prob <= 40){
            line.pop_front();
        }

        //60% chance
        prob = rand() % 100 + 1;
        if(prob <= 60){
            string newCustomer = getRandomName(names);
            line.push_back(newCustomer);
            cout << newCustomer << " joins the line\n";
        }

        //20% chance
        prob = rand() % 100 + 1;
        if(prob <= 20){
            cout << line.back() << " (at the rear) left the line\n";
            line.pop_back();
        }

        //10% chance, any customer leaves randomly
        prob = rand() % 100 + 1;
        if(prob <= 10){
            int randomPos = rand() % 5 + 1;
            cout << "Customer at position " << randomPos << " left the line\n";
            line.delete_pos(randomPos);
        }

        //10% chance, VIP joins
        prob = rand() % 100 + 1;
        if(prob <= 10){
            string vipCustomer = getRandomName(names);
            line.push_front(vipCustomer);
            cout << vipCustomer << " (VIP) joins the front of the line\n";
        }

        cout << "Resulting Line:\n";
        line.print();
    }

    return 0;
}