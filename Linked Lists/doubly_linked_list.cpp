#include <iostream>
using namespace std;


class Node{
    public:
    int value; 
    Node* next;
    Node* prev;
    Node(int value_, Node* next_=nullptr, Node* prev_ = nullptr){
        value = value_;
        next = next_;
        prev = prev_;
    }
};


class DoublyLinkedList{
    public:
    Node* head;
    Node* tail;
    DoublyLinkedList(){
        head = nullptr;
        tail = nullptr;
    }
    
    void addHead(int value){
        Node*new_node = new Node(value);
        if(head == nullptr){
            head = new_node;
            tail = head;
        }
        else{
            head->prev = new_node;
            new_node->next = head;
            head = new_node;
        }
    }

    void addTail(int value){
        Node*new_node = new Node(value);
        if(tail == nullptr){
            tail = new_node;
            head = tail;
        }
        else{
            tail->next = new_node;
            new_node->prev = tail;
            tail = new_node;
        }
    }
    void describeForward(){
        Node*current = head;
        if(head == nullptr){return;}
        else{
            cout << "Head: " << head->value << " Tail: " << tail->value << endl;
            while(current != nullptr){
                cout << current->value <<" -> ";
                current = current->next;
            }
            cout << endl;
        }
    }
    bool findElementForward(int element){
        if(head == nullptr){
            return false;
        }
        Node*current = head;
        while(current != nullptr){
            if(element == current->value){
                return true;
            }
            current = current->next;
        }
        return false;
    }
    bool findElementBackward(int element){
        if(tail == nullptr){return false;}
        Node*current = tail;
        while(current!=nullptr){
            if(element == current->value){
                return true;
            }
            current = current->prev;
        }
        return false;
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

    void insertAt(int value, int index){
        Node*prev_node = nullptr;
        Node*current_node = head;
        Node*new_node= new Node(value);
        int current_index = 0;
        if(index == 0){addHead(value);}
        else if(index == size()){addTail(value);return;}
        else{
            while(current_node != nullptr){
                if(index==current_index){
                    new_node->next = current_node;
                    new_node->prev = prev_node;
                    
                    prev_node->next = new_node;
                    current_node->prev= new_node;
                    return;
                }
                else{
                prev_node = current_node;
                current_node = current_node->next;
                current_index++;}
            }
        }

    }

    void removeElement(int value){
        Node*current = head;
        Node*prev = nullptr;
        int index = 0;
        
        while(current!=nullptr){
            prev = current->prev;
            if(current->value == value){
                Node*toDelete = current;
                if(prev == nullptr){
                    head = current->next;
                    current->next->prev = prev;
                    delete toDelete;
                    return;
                }
                else if(current->next == nullptr){
                    tail = current->prev;
                    tail->next = nullptr;
                    delete toDelete;
                    return;
                }
                else{
                current = current->next;
                current->prev = prev;
                toDelete->next->prev = current;
                toDelete->prev->next = current;
                delete toDelete;
                return;
            }
            }
            current = current->next;
        }
    }

    void insertAtBackward(int value, int index){
        Node*next_node = nullptr;
        Node*current_node = tail;
        Node*new_node = new Node(value);
        int current_index = 0;
        if(index == 0){addTail(value); return;}
        else if(index == size()){addHead(value); return;}
        else{
            while(current_node != nullptr){
                if(index == current_index){
                    new_node->next = next_node;
                    new_node->prev = current_node;

                    next_node->prev = new_node;
                    current_node->next = new_node;
                    return;
                }
                else{
                    next_node = current_node;
                    current_node = current_node->prev;
                    current_index++;
                }
            }
        }
    }
    void describeBackward(){
        Node*current = tail;
        if(tail == nullptr){return;}
        else{
            cout << "Head: " << head->value << " Tail: " << tail->value << endl;
            while(current != nullptr){
                cout << current->value << " <- ";
                current = current->prev;

            }
            cout << endl;
        }
    }
};



int main(){
    DoublyLinkedList d_linked_list;
    d_linked_list.addHead(30);
    d_linked_list.addHead(20);
    d_linked_list.addHead(10);
    d_linked_list.addTail(40);
    d_linked_list.addTail(50);
    d_linked_list.addTail(60);
    d_linked_list.describeForward();
    d_linked_list.addTail(1);
    d_linked_list.describeForward();
    d_linked_list.removeElement(10);
    d_linked_list.describeForward();
    d_linked_list.addHead(0);
    d_linked_list.describeForward();
    d_linked_list.removeElement(1);
    d_linked_list.addTail(2);
    d_linked_list.describeForward();
    return 0;}