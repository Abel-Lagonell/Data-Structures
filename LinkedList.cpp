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

    void PushFront(T key){ //add to Front 
        Node<T> *temp = new Node<T>;
        temp->data = key;
        temp->next = head;
        head = temp;
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

    void AddAfterAllIntances(Node<T> *node, T key){ //adds key after all instances of the node
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

    void AddAfterPosition(Node<T> *node, int position) {  // adds the node after specified position
        Node<T> *curr = head;
        if (Empty()){
            cout << "List is empty" << endl;
            return;
        }
        for (int i = 0; i < position; i++){
            curr = curr->next;
        }
        node->next = curr->next;
        curr->next = node;
        makeTail();
    }

    void AddBeforePosition(Node<T> *node, int position){ // add the node before the specified position
        Node<T> *curr = head;
        Node<T> *prev = nullptr;
        if (Empty()){
            cout << "List is empty" << endl;
            return;
        }
        for (int i = 0; i < position; i++){
            prev = curr;
            curr = curr->next;
        }
        node->next = curr;
        if (prev == nullptr)
            head = node;
        else
            prev->next = node;
        makeTail();
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

    void ReplaceKey(Node<T> *node, T key){ //replaces the first instance of key with node
        Node<T> *curr = head;
        if (Empty()){
            cout << "List is empty" << endl;
            return;
        }
        while (curr->next != nullptr){
            if (curr->data == key){
                node->next = curr->next;
                curr->data = node->data;
                curr->next = node->next;
                break;
            }
            curr = curr->next;
        }
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
