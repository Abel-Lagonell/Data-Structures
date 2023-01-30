/**
 * @file Lagonell.cpp
 * @author Abel Lagonell (alagonell1730@floridapoly.edu)
 * @brief Single Linked List
 * @version 0.1
 * @date 2023-01-30
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#include <iostream>
using namespace std;

class Node{
public:
    int data;
    Node *next;

    Node(){
        next=nullptr;
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
        if(tail->next != nullptr){
            while(curr->next != nullptr){
                curr = curr->next;
            }
            tail = curr;
        }
    }

public:
    SinglyLinkedList():head(nullptr){}

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
        Node *prev = nullptr;
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
    
    bool Find (int key){ //is key in list?
        Node *curr = head;
        if(Empty())
            return false;
        while (curr->next != nullptr){
            if (curr->data == key)
                return true;
            curr = curr->next;
        }
        return false;
    }

    bool Empty(){ //empty list?
        return ((head == NULL)? true : false);
    }

    void AddAfter(Node *node, int position) {  // adds the node after specified position
        Node *curr = head;
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

    void AddBefore(Node *node, int position){ // add the node before the specified position
        Node *curr = head;
        Node *prev = nullptr;
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
        Node *curr = head;
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
        Node *curr = head;
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

    void ReplaceKey(Node *node, int key){ //replaces the first instance of key with node
        Node *curr = head;
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
};
