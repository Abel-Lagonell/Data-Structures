/**
 * @file Lagonell.cpp
 * @author Abel Lagonell (alagonell1730@floridapoly.edu)
 * @brief Single Linked List
 * @version 0.1
 * @date 2023-01-30
 * 
 * @copyright Copyright (c) 2023
 */

#include <iostream>
using namespace std;

class Node{
public:
    int data;
    Node *next;

    Node(){
        next=NULL;
    }
};

class SinglyLinkedList{
private:
    Node *head,*tail;

    void printNode(Node *node){ //For debugging purposes
        cout << node->data << endl;
    }

    void makeTail(){
        Node *curr = head;
        if(tail->next != NULL){
            while(curr->next != NULL){
                curr = curr->next;
            }
            tail = curr;
        }
    }

public:
    SinglyLinkedList():head(NULL){}

    void PushFront(int key){ //add to Front 
        Node *temp = new Node;
        temp->data = key;
        temp->next = head;
        head = temp;
        makeTail();
    }
    
    int TopFront(){ // return front item
        if(!Empty())
            return head->data;
        else
            cout << "List is empty" << endl;
            return -1;
    }   
    
    void PopFront(){ //remove front item
        Node *temp = head;
        if (Empty()){
            cout << "List is empty" << endl;
            return;
        }
        head = head->next;
        delete temp;
        makeTail();
    }
    
    void PushBack(int key){ // add to back
        Node *temp = new Node;
        temp->data = key;
        tail->next = temp;
        tail = temp;
    }
    
    int TopBack(){ //return back item
        if (Empty()){
            cout << "List is empty" << endl;
            return -1;
        }    
        return tail->data;
    }
    
    void PopBack(){ //remove back item
        Node *curr = head;
        Node *prev = NULL;
        if (Empty()){
            cout << "List is empty" << endl;
            return;
        }    
        while(curr->next != NULL){
            prev = curr;
            curr = curr->next;
        }
        delete curr;
        prev->next = NULL;
        tail = prev;
    }
    
    bool Find (int key){ //is key in list?
        Node *curr = head;
        if(Empty())
            return false;
        while (curr->next != NULL){
            if (curr->data == key)
                return true;
            curr = curr->next;
        }
        return false;
    }

    bool Empty(){ //empty list?
        return ((head == NULL)? true : false);
    }

    void AddBefore(int data, int index){//adds the data before the specified index
        Node *curr = head;
        Node *prev = NULL;
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
        Node *newNode = new Node;
        newNode->data = data;
        newNode->next = curr;
        if (prev == NULL)
            head = newNode;
        else
            prev->next = newNode;
    }

    void AddAfter(int data, int index){//adds the data after the specified index
        Node *curr = head;
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
        Node *newNode = new Node;
        newNode->data = data;
        newNode->next = curr->next;
        curr->next = newNode;
        makeTail();
    }

    void DisplayAll(){ //Uses a function to print the list
        Node *curr = head;
        if (Empty()){
            cout << "List is empty" << endl;
            return;
        }
        while (curr != NULL){
            cout << curr->data << ((curr->next == NULL)? "":", ");
            curr = curr->next;
        }
        cout << endl;
    }

    int Size(){ //returns the number of elements
        Node *curr = head;
        int count = 0;
        if (Empty()){
            cout << "List is empty" << endl;
            return -1;
        }
        while (curr != NULL){
            count++;
            curr = curr->next;
        }
        return count;
    }

    void ReplaceKey(int data, int index){ //replaces the data at the specified index with data
        Node *curr = head;
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
};

int main(){
    SinglyLinkedList list;
    list.PushFront(25);
    list.PushFront(50);
    list.PushFront(90);
    list.PushFront(40);
    list.PushBack(35);

    list.DisplayAll();
    cout << list.TopFront() << endl << list.TopBack() << endl;
    list.PopFront();
    list.DisplayAll();
    list.PopBack();
    list.DisplayAll();
    list.PushBack(10);
    list.PushBack(12);
    list.PushBack(14);

    list.DisplayAll();
    cout << ((list.Find(25))? "TRUE":"FALSE") <<endl << ((list.Find(6))? "TRUE":"FALSE") << endl << ((list.Empty())? "TRUE":"FALSE") << endl;
    list.AddBefore(94,3);
    list.DisplayAll();
    list.AddAfter(5,2);
    list.DisplayAll();
    cout << list.Size() << endl;
    list.ReplaceKey(87,6);
    list.DisplayAll(); 
    list.PopFront();
    list.PopFront();
    list.PopFront();
    list.PopFront();
    list.PopFront();
    list.PopFront();
    list.PopFront();
    list.PopFront();
    cout << ((list.Empty())? "TRUE":"FALSE") << endl;
}
