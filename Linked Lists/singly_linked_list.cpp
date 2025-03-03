#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

class Node{
    public:
    int value;
    Node* next;
    Node(int _value, Node* _next = nullptr){
        value = _value;
        next = _next;
    }

};

class LinkedList{
    public:
    Node* head;
    Node* tail;
    LinkedList(){
        head = nullptr;
        tail = nullptr;
    }
    void addTail(int value, Node*next=nullptr){
        Node*new_node = new Node(value, next); 
        if(head == nullptr && tail == nullptr){
            head = new_node;
            tail = new_node;
        }
        else{
            tail->next = new_node;
            tail = new_node;
        }
    }

    void addHead(int value){
        Node*new_node = new Node(value);
        if (head == nullptr && tail == nullptr){
            head = new_node;
            tail = new_node;
        }
        else{
            new_node->next=head;
            head = new_node;
        }
    }

    bool findElement(int element){ 
        Node*temp_node = head;
        if(head == nullptr){
            cout << "Linked List is Empty!" << endl;
            return false;
        }
        else{
            while(temp_node!=nullptr){
                if (temp_node->value == element){
                    return true;
                }
                temp_node = temp_node->next;
            }
            return false;
        }
    }
    
    void removeElement(int element){
        Node*current=head;
        Node*previous=nullptr;

        while(current!=nullptr){
            if(current->value == element){
                Node*toDelete = current;
                if(previous == nullptr){
                    head = current->next;
                    if(current->next == nullptr){
                        tail = head;
                    }
                    delete toDelete;
                    return;
                } 
                else if(current->next == nullptr){
                    previous->next = current->next;
                    tail = previous;
                    delete toDelete;
                    return;
                }
                else{
                    previous->next = current->next;
                    delete toDelete;
                    return;
                }

            }
            previous = current;
            current = current->next;
        }
        return;
    }

    void describe(){
        Node*temp_node = head;
        if(head == nullptr){
            cout << "Linked List is Empty!!!";
        } 
        else{
            cout << "Head: " << head->value << " Tail: " << tail->value << endl;
            while(temp_node != nullptr){
                cout << temp_node->value << " -> ";
                temp_node = temp_node->next;
            }
        }
    cout << endl;
    }
    void peekHead(){
        cout << "Head: "<< head->value << endl;
    }
    void peekTail(){
        cout << "Tail: " << tail->value << endl;
    }
    int size(){
        int count = 0;
        Node*current = head;
        if(head == nullptr){
            return count;
        }
        else{
        while(current != nullptr){
            current = current->next;
            count++;
            }
        }
        return count;
    }

    void reverse(){
        Node*prev = nullptr;
        Node*current = head;
        if(head == nullptr){return;}
        else{
            while(current!=nullptr){
                Node*next_node = current->next;
                current->next = prev;
                prev = current;
                current = next_node;
            }
        }
        head = prev;
        Node*temp_head = head;
        while(temp_head->next!=nullptr){
            temp_head = temp_head->next;
        }
        tail = temp_head;
    }

    void insertAt(int value, int index){
        Node*new_node = new Node(value);
        Node*current_node = head;
        Node*prev_node = nullptr;
        int current_index = 0;
        int linked_list_size = size();
        if (head == nullptr && index != 0){
            cout << "Empty Linked List, index is not in the linked list" << endl;
            return;
        }
        else if(index == 0){
            addHead(value);
        }
        else if(index >= linked_list_size){
            addTail(value);
        }
        else if(index+1 > linked_list_size){
            cout << "Index is higher than Linked List size" << endl;
            return;
        }
        else{
            while(current_node != nullptr){
                if (current_index == index){
                    Node*temp_node = current_node;
                    current_node = new_node;
                    prev_node->next = current_node;
                    current_node->next = temp_node;
                }
                prev_node = current_node; 
                current_node = current_node->next;
                current_index ++;
            }
        }
    }
    void ordenize(){
        vector<int> arr;
        Node*temp = head;
        while(temp!=nullptr){
            arr.push_back(temp->value);
            temp = temp->next;
        } 
        sort(arr.begin(), arr.end());
        clean();
        insertFromVector(arr);
    }

    void insertFromVector(vector<int>arr){
        for(int value:arr){
            addTail(value);
        }
    }
    void clean(){
        if(head == nullptr){
            cout << "Linked List is Empty!" << endl;
            return;
        }
        Node*temp_node = head;
        while(temp_node!=nullptr){
            Node*toDelete = temp_node;
            temp_node = temp_node->next;
            delete toDelete;
        }
        head = nullptr;
        tail = nullptr;
    }

    ~LinkedList(){
        if(head == nullptr){
            cout << "Linked List is Empty!" << endl;
            return;
        }
        Node*temp_node = head;
        while(temp_node!=nullptr){
            Node*toDelete = temp_node;
            temp_node = temp_node->next;
            delete toDelete;
        }
        head = nullptr;
        tail = nullptr;
        cout << "Linked List Destroyed " << endl;
    }
};



int main(){
    LinkedList linked_list;
    cout << linked_list.findElement(1) << endl;
    linked_list.addTail(1);
    linked_list.addTail(2);
    linked_list.addTail(3);
    linked_list.addHead(0);
    linked_list.describe();
    linked_list.removeElement(2);
    linked_list.describe();
    linked_list.addTail(4);
    linked_list.describe();
    linked_list.removeElement(0);
    linked_list.addHead(10);
    linked_list.describe();
    return 0;
}