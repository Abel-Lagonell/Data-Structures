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
    Node<T> *head;

    void printNode(Node<T> *node){ //For debugging purposes
        cout << node->data << endl;
    }


public:
    SinglyLinkedList():head(nullptr){}

    void PushFront(T key){ //add to Front 
        Node<T> *temp = new Node<T>;
        temp->data = key;
        temp->next = head;
        head = temp;
    }
    
    T TopFront(){ // return front item
        return head->data;
    }
    
    void PopFront(){ //remove front item
        Node<T> *temp = head;
        head = head->next;
        delete temp;
    }
    
    void PushBack(T key){ // add to back
        Node<T> *temp = new Node<T>;
        temp->data = key;
        temp->next = nullptr;
        if(head == nullptr){
            head = temp;
        }
        else{
            Node<T> *curr = head;
            while(curr->next != nullptr){
                curr = curr->next;
            }
            curr->next = temp;
        }
    }
    
    T TopBack(){ //return back item
        Node<T> *curr = head;
        while(curr->next != nullptr){
            curr = curr->next;
        }
        return curr->data;
    }
    
    void PopBack(){ //remove back item
        Node<T> *curr = head;
        Node<T> *prev = nullptr;
        while(curr->next != nullptr){
            prev = curr;
            curr = curr->next;
        }
        delete curr;
        prev->next = nullptr;
    }
    
    bool Find (T key){ //is key in list?
        Node<T> *curr = head;
        while (curr->next != nullptr){
            if (curr->data == key)
                return true;
            curr = curr->next;
        }
        return false;
    }

    void Erase(T key){ // remove first instances of key from list
        Node<T> *curr = head;
        Node<T> *prev = nullptr;
        while (curr->next != nullptr){
            if (curr->data == key){
                prev->next = curr->next;
                delete curr;
                break;
            }
            prev = curr;
            curr = curr->next;
        }
    }

    void EraseAll(T key){ // remove all instances of key from list
        while(Find(key)){
            Erase(key);
        }
    }

    bool Empty(){ //empty list?
        return ((head == NULL)? true : false);
    }
    
    void AddBefore(Node<T> *node, T key){ //adds key before first instance of node
        Node<T> *curr = head;
        Node<T> *prev = nullptr;
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
    void AddAfter(Node<T> *node, T key){ //adds key after first instance of the node
        Node<T> *curr = head;
        while (curr->next != nullptr){
            if (curr->data == key){
                node->next = curr->next;
                curr->next = node;
                break;
            }
            curr = curr->next;
        }
    }

    void AddBeforeAll(Node<T> *node, T key){ //adds key before all instances of the node
        Node<T> *curr = head;
        Node<T> *prev = nullptr;
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

    void AddAfterAll(Node<T> *node, T key){ //adds key after all instances of the node
        Node<T> *curr = head;
        while (curr->next != nullptr){
            if (curr->data == key){
                Node<T> *newNode = new Node<T>;
                newNode->data = node->data;
                newNode->next = curr->next;
                curr->next = newNode;
                printList();
            }
            curr = curr->next;
        }
    }

    void printList(){ //Uses a function to print the list
        Node<T> *curr = head;
        while (curr != nullptr){
            cout << curr->data << ((curr->next == nullptr)? "":", ");
            curr = curr->next;
        }
        cout << endl;
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


int main(){
    SinglyLinkedList<int> arr;
    cout << "Is the array empty?\t" << (arr.Empty()? "yes":"no") << endl;

    for (int i =0; i <11; i++){
        if(i%2==0)
            arr.PushFront(i);
        else
            arr.PushBack(i*2);
    }
    cout << arr;
    //arr.Erase(2);
    cout << arr;
    cout << "Is 3 in the array?\t"<< (arr.Find(3)? "yes":"no") << endl;
    arr.PopFront(); arr.PopBack(); 
    cout << arr << arr.TopFront() << " is the front of the array while " << arr.TopBack() << " is the in the back" << endl;
    Node<int> *node1 = new Node<int>; node1->data=13;
    Node<int> *node2 = new Node<int>; node2->data=13;
    arr.AddAfter(node1, 0);
    arr.AddBefore(node2, 0);
    cout << arr;    

    arr.EraseAll(13);
    cout << arr;
    Node<int> *node3 = new Node<int>;node3->data=22;
    Node<int> *node4 = new Node<int>;node4->data=11;
    arr.AddAfterAll(node3, 2);
    cout<<arr;
    arr.AddBeforeAll(node4,2);
    cout<<arr;


}