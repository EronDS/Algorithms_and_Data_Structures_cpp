#include <iostream>
#include <vector>

using namespace std;

// TODO: deleteAt;

class Node
{
public:
    int value;
    vector<Node *> next;
    Node(int value, int max_height)
        : value(value), next(max_height, nullptr) {}
};

class OrderedSkipList
{
public:
    int max_height;
    vector<Node *> heads;
    OrderedSkipList(int max_height) : max_height(max_height), heads(max_height, nullptr) {}

    int getRandomHeight()
    {
        int chosen_height = 1;
        while (chosen_height < max_height && rand() % 2)
        {
            chosen_height++;
        }
        return chosen_height;
    }


    void insert(int value){
        Node* new_node = new Node(value, max_height);
        int chosen_height = getRandomHeight();
        
        for(int i = 0; i<chosen_height;i++){
            Node*current = heads[i];
            Node*prev = nullptr;

            if(current == nullptr){
                heads[i] = new_node;
                continue;
            }
            else if(current->value > new_node->value){
                new_node->next[i] = current;
                heads[i] = new_node;
                continue;
            }

            while(current!=nullptr && current->value < new_node->value){
                prev = current;
                current = current->next[i];
            }
            new_node->next[i] = current;
            prev->next[i] = new_node;
        
        }
    }
    void print()
    {
        if (heads[0] == nullptr){cout << "Empty List" << endl;return;}
        for (int i = 0; i < max_height; i++)
        {  
            cout << "Level " << i << ": " << endl;
            Node *current = heads[i];
            while (current != nullptr)
            {
                cout << current->value << " -> ";
                current = current->next[i];
            }
            cout << "nullptr" << endl;
        }
    }
};

int main()
{
    OrderedSkipList ordered_skip_list(3);
    
    ordered_skip_list.insert(42);
    ordered_skip_list.insert(17);
    ordered_skip_list.insert(89);
    ordered_skip_list.insert(23); 
    ordered_skip_list.insert(56);
    ordered_skip_list.insert(11);
    ordered_skip_list.insert(74);
    ordered_skip_list.insert(31);
    ordered_skip_list.insert(95);
    ordered_skip_list.insert(63);
    
    ordered_skip_list.print();
    return 0;
}