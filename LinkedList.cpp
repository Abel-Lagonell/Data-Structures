#include <iostream>
using namespace std;

template <typename T>
class Node{
public:
    T data;
    Node *next;

    Node(){
        next=nullptr;
    }
};

template <typename T>
class SinglyLinkedList{
private:
    Node<T> *head,*tail;

    void printNode(Node<T> *node){ //For debugging purposes
        cout << node->data << endl;
    }

    void makeTail(){
        Node<T> *curr = head;
        if(tail->next != nullptr){
            while(curr->next != nullptr){
                curr = curr->next;
            }
            tail = curr;
        }
    }

public:
    SinglyLinkedList():head(nullptr){}

    void PushFront(T key){ //add data to Front 
        Node<T> *temp = new Node<T>;
        temp->data = key;
        temp->next = head;
        head = temp;
        makeTail();
    }

    void PushFront(Node<T> *node){ //add node to Front
        node->next = head;
        head = node;
        makeTail();
    }
    
    T TopFront(){ // return front item
        if(!Empty())
            return head->data;
        else
            return NULL;
    }   
    
    void PopFront(){ //remove front item
        Node<T> *temp = head;
        if (Empty()){
            cout << "List is empty" << endl;
            return;
        }
        head = head->next;
        delete temp;
        makeTail();
    }
    
    void PushBack(T key){ // add to back
        Node<T> *temp = new Node<T>;
        temp->data = key;
        tail->next = temp;
        tail = temp;
    }

    void PushBack(Node<T> *node){ // add node to back
        tail->next = node;
        tail = node;
    }
    
    T TopBack(){ //return back item
        if (Empty()){
            cout << "List is empty" << endl;
            return NULL;
        }    
        return tail->data;
    }
    
    void PopBack(){ //remove back item
        Node<T> *curr = head;
        Node<T> *prev = nullptr;
        if (Empty()){
            cout << "List is empty" << endl;
            return;
        }    
        while(curr->next != nullptr){
            prev = curr;
            curr = curr->next;
        }
        delete curr;
        prev->next = nullptr;
        tail = prev;
    }
    
    bool Find (T key){ //is key in list?
        Node<T> *curr = head;
        if(Empty())
            return false;
        while (curr->next != nullptr){
            if (curr->data == key)
                return true;
            curr = curr->next;
        }
        return false;
    }

    void EraseInstance(T key){ // remove first instances of key from list
        Node<T> *curr = head;
        Node<T> *prev = nullptr;
        if (Empty()){
            cout << "List is empty" << endl;
            return;
        }
        while (curr->next != nullptr){
            if (curr->data == key){
                prev->next = curr->next;
                delete curr;
                break;
            }
            prev = curr;
            curr = curr->next;
        }
        makeTail();
    }

    void EraseAllInstances(T key){ // remove all instances of key from list
        if (Empty()){
            cout << "List is empty" << endl;
            return;
        }  
        while(Find(key))
            EraseInstance(key);
        makeTail();
    }

    bool Empty(){ //empty list?
        return ((head == NULL)? true : false);
    }

    void AddBeforeInstance(T data, T key){//adds data before first instance of the node with the key
        Node<T> *curr = head;
        Node<T> *prev = nullptr;
        if (Empty()){
            cout << "List is empty" << endl;
            return;
        }
        while (curr->next != nullptr){
            if (curr->data == key){
                Node<T> *newNode = new Node<T>;
                newNode->data = data;
                newNode->next = curr;
                if (prev == nullptr)
                    head = newNode;
                else
                    prev->next=newNode;
                break;
            }
            prev = curr;
            curr = curr->next;
        }
    }
    
    void AddBeforeInstance(Node<T> *node, T key){ //adds key before first instance of node
        Node<T> *curr = head;
        Node<T> *prev = nullptr;
        if (Empty()){
            cout << "List is empty" << endl;
            return;
        }
        while (curr->next != nullptr){
            if (curr->data == key){
                node->next = curr;
                if (prev == nullptr)
                    head = node;
                else
                    prev->next=node;
                break;
            }
            prev = curr;
            curr = curr->next;
        }
    }

    void AddAfterInstance(T data, T key){ // adds data after first instance of node with the key
        Node<T> *curr = head;
        if (Empty()){
            cout << "List is empty" << endl;
            return;
        }
        while (curr->next != nullptr){
            if (curr->data == key){
                Node<T> *newNode = new Node<T>;
                newNode->data = data;
                newNode->next = curr->next;
                curr->next = newNode;
                break;
            }
            curr = curr->next;
        }
        makeTail();
    }

    void AddAfterInstance(Node<T> *node, T key){ //adds key after first instance of the node
        Node<T> *curr = head;
        if (Empty()){
            cout << "List is empty" << endl;
            return;
        }
        while (curr->next != nullptr){
            if (curr->data == key){
                node->next = curr->next;
                curr->next = node;
                break;
            }
            curr = curr->next;
        }
        makeTail();
    }

    void AddBeforeAllInstances(T data, T key){ //adds the data before all instances of the node with the key
        Node<T> *curr = head;
        Node<T> *prev = nullptr;
        if (Empty()){
            cout << "List is empty" << endl;
            return;
        }
        while (curr->next != nullptr){
            if (curr->data == key){
                Node<T> *newNode = new Node<T>;
                newNode->data = data;
                newNode->next = curr;
                if (prev == nullptr)
                    head = newNode;
                else
                    prev->next=newNode;
            }
            prev = curr;
            curr = curr->next;
        }

    }

    void AddBeforeAllInstances(Node<T> *node, T key){ //adds key before all instances of the node
        Node<T> *curr = head;
        Node<T> *prev = nullptr;
        if (Empty()){
            cout << "List is empty" << endl;
            return;
        }
        while (curr->next != nullptr){
            if (curr->data == key){
                Node<T> *newNode = new Node<T>;
                newNode->data=node->data;
                newNode->next = curr;
                if (prev == nullptr)
                    head = newNode;
                else
                    prev->next=newNode;
            }
            prev = curr;
            curr = curr->next;
        }
    }

    void AddAfterAllInstances(T data, T key){ //adds data after all instances of the node with the key
        Node<T> *curr = head;
        if (Empty()){
            cout << "List is empty" << endl;
            return;
        }
        while (curr->next != nullptr){
            if (curr->data == key){
                Node<T> *newNode = new Node<T>;
                newNode->data = data;
                newNode->next = curr->next;
                curr->next = newNode;
                DisplayAll();
            }
            curr = curr->next;
        }
        makeTail();

    }

    void AddAfterAllInstances(Node<T> *node, T key){ //adds key after all instances of the node
        Node<T> *curr = head;
        if (Empty()){
            cout << "List is empty" << endl;
            return;
        }
        while (curr->next != nullptr){
            if (curr->data == key){
                Node<T> *newNode = new Node<T>;
                newNode->data = node->data;
                newNode->next = curr->next;
                curr->next = newNode;
                DisplayAll();
            }
            curr = curr->next;
        }
        makeTail();
    }

    void AddAfterIndex(T data, int index){//adds the data after the specified index
        Node<T> *curr = head;
        if (Empty()){
            cout << "List is empty" << endl;
            return;
        }
        if (!(index >= 0)){
            cout << "Index out of bounds" << endl;
            return;
        }
        for (int i = 0; i < index; i++){
            curr = curr->next;
        }
        Node<T> *newNode = new Node<T>;
        newNode->data = data;
        newNode->next = curr->next;
        curr->next = newNode;
        makeTail();
    }

    void AddAfterIndex(Node<T> *node, int index) {  // adds the node after specified index
        Node<T> *curr = head;
        if (Empty()){
            cout << "List is empty" << endl;
            return;
        }
        if (!(index >= 0)){
            cout << "Index out of bounds" << endl;
            return;
        }
        for (int i = 0; i < index; i++){
            curr = curr->next;
        }
        node->next = curr->next;
        curr->next = node;
        makeTail();
    }

    void AddBeforeIndex(T data, T index){//adds the data before the specified index
        Node<T> *curr = head;
        Node<T> *prev = nullptr;
        if (Empty()){
            cout << "List is empty" << endl;
            return;
        }
        if (!(index >= 0)){
            cout << "Index out of bounds" << endl;
            return;
        }
        for (int i = 0; i < index; i++){
            prev = curr;
            curr = curr->next;
        }
        Node<T> *newNode = new Node<T>;
        newNode->data = data;
        newNode->next = curr;
        if (prev == nullptr)
            head = newNode;
        else
            prev->next = newNode;
    }

    void AddBeforeIndex(Node<T> *node, int index){ // add the node before the specified index
        Node<T> *curr = head;
        Node<T> *prev = nullptr;
        if (Empty()){
            cout << "List is empty" << endl;
            return;
        }
        if (!(index >= 0)){
            cout << "Index out of bounds" << endl;
            return;
        }
        for (int i = 0; i < index; i++){
            prev = curr;
            curr = curr->next;
        }
        node->next = curr;
        if (prev == nullptr)
            head = node;
        else
            prev->next = node;
    }

    void DisplayAll(){ //Uses a function to print the list
        Node<T> *curr = head;
        if (Empty()){
            cout << "List is empty" << endl;
            return;
        }
        while (curr != nullptr){
            cout << curr->data << ((curr->next == nullptr)? "":", ");
            curr = curr->next;
        }
        cout << endl;
    }

    int Size(){ //returns the number of elements
        Node<T> *curr = head;
        int count = 0;
        if (Empty()){
            cout << "List is empty" << endl;
            return -1;
        }
        while (curr != nullptr){
            count++;
            curr = curr->next;
        }
        return count;
    }

    void ReplaceInstance(T data, T key){ // replaces the first instance of key with data
        Node<T> *curr = head;
        if (Empty()){
            cout << "List is empty" << endl;
            return;
        }
        while (curr->next != nullptr){
            if (curr->data == key){
                curr->data = data;
                break;
            }
            curr = curr->next;
        }
        makeTail();
    }

    void ReplaceInstance(Node<T> *node, T key){ //replaces the first instance of key with node
        Node<T> *curr = head;
        if (Empty()){
            cout << "List is empty" << endl;
            return;
        }
        while (curr->next != nullptr){
            if (curr->data == key){
                curr->data = node->data;
                break;
            }
            curr = curr->next;
        }
        makeTail();
    }

    void ReplaceKey(T data, int index){ //replaces the data at the specified index with data
        Node<T> *curr = head;
        if (Empty()){
            cout << "List is empty" << endl;
            return;
        }
        for (int i = 0; i < index; i++){
            curr = curr->next;
        }
        curr->data = data;
        makeTail();
    }

    void ReplaceKey(Node<T> *node, int index){ //replaces the node at the specified index with node
        Node<T> *curr = head;
        if (Empty()){
            cout << "List is empty" << endl;
            return;
        }
        for (int i = 0; i < index; i++){
            curr = curr->next;
        }
        curr->data = node->data;
        makeTail();
    }

    friend ostream& operator<< (ostream& os, const SinglyLinkedList<T>& list){ //Uses overloading to print out the list
        Node<T> *curr = list.head;
        while (curr != nullptr){
            cout << curr->data << ((curr->next == nullptr)? "":", ");
            curr = curr->next;
        }
        cout << endl;
        return os;
    }
};
