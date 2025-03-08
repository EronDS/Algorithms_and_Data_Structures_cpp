#include <iostream>
#include <vector>
#include <cstdlib>
using namespace std;

class Node
{
public:
    int value;
    vector<Node *> next;
    int index;
    Node(int value, int height)
        : value(value), next(height, nullptr) {}
};

class SkipList
{
public:
    int max_height;
    vector<Node *> heads;
    SkipList(int max_height)
        : heads(max_height, nullptr), max_height(max_height) {}

    int getRandomHeight()
    {
        int chosen_height = 1;
        while (chosen_height < max_height && rand() % 2)
        {
            chosen_height++;
        }
        return chosen_height;
    }

    void addHead(int value)
    {
        int chosen_height = getRandomHeight();
        Node *new_node = new Node(value, max_height);
        for (int i = 0; i < chosen_height; i++)
        {
            Node *current_head = heads[i];
            new_node->next[i] = current_head;
            heads[i] = new_node;
        }
    }
    void addTail(int value)
    {
        int chosen_height = getRandomHeight();
        Node *new_node = new Node(value, max_height);
        Node *prev_node = nullptr;
        for (int i = 0; i < chosen_height; i++)
        {
            Node *current_node = heads[i];
            if (current_node == nullptr)
            {
                heads[i] = new_node;
            }
            else
            {
                while (current_node != nullptr)
                {
                    prev_node = current_node;
                    current_node = current_node->next[i];
                }
                prev_node->next[i] = new_node;
            }
        }
    }

    void print()
    {
        for (int i = 0; i < max_height; i++)
        {
            cout << "Level " << i << ": ";
            Node *current_node = heads[i];
            while (current_node != nullptr)
            {
                cout << current_node->value << " -> ";
                current_node = current_node->next[i];
            }
            cout << "nullptr " << endl;
        }
    }

    void removeElement(int element)
    {
        Node *toDelete = nullptr;

        for (int i = 0; i < max_height; i++)
        {
            Node *current = heads[i];
            Node *prev = nullptr;
            if (toDelete == nullptr)
            {
                while (current != nullptr)
                {
                    if (current->value == element)
                    {
                        Node *toDelete = current;
                        if (prev == nullptr)
                        {
                            heads[i] = current->next[i];
                            break;
                        }
                        else
                        {
                            prev->next[i] = current->next[i];
                            break;
                        }
                    }
                    else
                    {
                        prev = current;
                        current = current->next[i];
                    }
                }
            }
            else
            {
                while (current != nullptr)
                {
                    if (current == toDelete)
                    {
                        if (prev == nullptr)
                        {
                            heads[i] = current->next[i];
                            break;
                        }
                        else
                        {
                            prev = current;
                            current = current->next[i];
                        }
                    }
                }
            }
        }
        delete toDelete;
    }

    void insertAt(int value, int index)
    {
        indexate();
        int chosen_height = getRandomHeight();
        if (index == 0)
        {
            addHead(value);
        }
        else
        {
            Node *new_node = new Node(value, max_height);
            for (int i = 0; i < chosen_height; i++)
            {
                Node *current = heads[i];
                Node *prev = nullptr;
                while (current != nullptr)
                {

                    if ((prev != nullptr && prev->index < index && current->index >= index))
                    {
                        prev->next[i] = new_node;
                        new_node->next[i] = current;
                    }
                    prev = current;
                    current = current->next[i];
                }
                if (prev != nullptr && prev->index <= index && current == nullptr)
                {
                    prev->next[i] = new_node;
                    new_node->next[i] = current;
                }
            }

            indexate();
        }
    }

    void indexate()
    {
        Node *current = heads[0];
        int current_id = 0;

        while (current != nullptr)
        {
            current->index = current_id;
            current = current->next[0];
            current_id++;
        }
    }

    Node *findElement(int element)
    {
        for (int i = max_height - 1; i >= 0; i--)
        {
            Node *current_node = heads[i];
            while (current_node != nullptr)
            {
                if (current_node->value == element)
                {
                    cout << "Found in Level: " << i << endl;
                    return current_node;
                }
                else
                {
                    current_node = current_node->next[i];
                }
            }
        }
        return nullptr;
    }

    void print_indexes()
    {
        for (int i = 0; i < max_height; i++)
        {
            cout << "Level " << i << ": ";
            Node *current_node = heads[i];
            while (current_node != nullptr)
            {
                cout << current_node->index << " -> ";
                current_node = current_node->next[i];
            }
            cout << "nullptr " << endl;
        }
    }
};

int main()
{
    SkipList skip_list(3);
    skip_list.addTail(7);
    skip_list.addTail(9);
    skip_list.addTail(12);
    skip_list.addTail(14);
    skip_list.addTail(20);
    skip_list.addTail(22);
    skip_list.addTail(30);
    skip_list.addTail(14);
    skip_list.addTail(20);
    skip_list.addTail(22);
    skip_list.addTail(80);
    skip_list.print();
    cout << " ---------------- " << endl;
    skip_list.removeElement(7);
    skip_list.removeElement(12);
    skip_list.removeElement(80);
    skip_list.addTail(90);
    skip_list.addTail(100);
    skip_list.addHead(0);
    skip_list.addHead(5);
    skip_list.print();
    skip_list.findElement(100);
    skip_list.insertAt(44, 12);
    skip_list.print();
    return 0;
}
