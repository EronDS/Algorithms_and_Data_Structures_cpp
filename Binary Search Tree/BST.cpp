#include <iostream>
#include <queue>
#include <vector>
#include <cmath>
#include <map>
#include <algorithm>

using namespace std;

//TODO: remove element;

class Node{
    public:
    int value;
    Node*left;
    Node*right;

    Node(int value){
        this->value = value;
        this->left = nullptr;
        this->right = nullptr;
    }
};


class BST{
    public:
    Node*root = nullptr;
    vector<vector<int>> balanceFactor;
    BST(){}

    void insert(const int & value){
        Node*new_node = new Node(value);

        if(root == nullptr){
            this->root = new_node;
            return;
        }
        Node*current = root;

        while(current != nullptr){

            if(value < current->value){
                if(current->left == nullptr){
                    current->left = new_node;
                    break;
                }
                else{
                    current = current->left;
                }
            }

            else if(value > current->value){
                if(current->right == nullptr){
                    current->right = new_node;
                    break;
                }
                else{
                    current = current->right;
                }
            }
        }
    }

    void InOrderTraversal(){
        this->InOrderTraversal(this->root);
    }

    void PreOrderTraversal(){
        this->PreOrderTraversal(this->root);
    }

    void PostOrderTraversal(){
        this->PostOrderTraversal(this->root);
    }

    void LevelOrderTraversal(){
        this->LevelOrderTraversal(this->root);
    }

    int getHeight(){
        int height = this->getHeight(this->root);
        return height;
    }

    void InOrderGetBalanceFactor(){
        this->balanceFactor.clear();
        this->InOrderGetBalanceFactor(this->root);

        for(vector<int> e : this->balanceFactor){
            cout << to_string(e[0]) + " (" + to_string(e[1]) + ")" + " ";  
        }
    }

    void BalanceTree(){
        if(this->isBalanced()){
            cout << "Tree already Balanced (All nodes satisfy: -1 <= bf_i <= 1)" << endl;
            return;
        }

        // Coleta todos os valores em ordem (já estão ordenados)
        this->InOrderGetBalanceFactor();
        vector<int> nodes;
        for(vector<int> e : this->balanceFactor){
            nodes.push_back(e[0]);
        }

        this->root = this->BalanceTree(nodes, 0, nodes.size() - 1);
        cout << endl; 
        cout << " -------------------------------- " << endl;
        cout << "Balanced Tree, In-Order-Traversal" << endl;
        this->InOrderTraversal(this->root);
        cout << "Level Order Traversal and Height" << endl;
        this->LevelOrderTraversal(this->root);
        cout << endl;
        cout << "Height: " + to_string(this->getHeight(this->root)) << endl; 

    }

    void removeElement(int value){
        this->root = removeElement(this->root, value);
    }

    private:

    Node* removeElement(Node* node, int value){
        // Base case: node not found
        if(node == nullptr) return nullptr;
        
        // Search for the node to delete
        if(value < node->value){
            node->left = removeElement(node->left, value);
        }
        else if(value > node->value){
            node->right = removeElement(node->right, value);
        }
        else {
            // Node to be deleted found
            
            // Case 1: Node has no children (leaf)
            if(node->left == nullptr && node->right == nullptr){
                delete node;
                return nullptr;
            }
            
            // Case 2: Node has only right child
            else if(node->left == nullptr){
                Node* temp = node->right;
                delete node;
                return temp;
            }
            
            // Case 3: Node has only left child
            else if(node->right == nullptr){
                Node* temp = node->left;
                delete node;
                return temp;
            }
            
            // Case 4: Node has both children
            else {
                // Find inorder successor (leftmost node in right subtree)
                Node* successor = findMin(node->right);
                
                // Replace node's value with successor's value
                node->value = successor->value;
                
                // Delete the successor (which has at most one child)
                node->right = removeElement(node->right, successor->value);
            }
        }
        
        return node;
    }

    Node* findMin(Node* node){
        while(node->left != nullptr){
            node = node->left;
        }
        return node;
    }

    Node* BalanceTree(vector<int>& nodes, int left, int right){
        if(left > right) return nullptr;
        
        int mid = left + (right - left) / 2;
        Node* node = new Node(nodes[mid]);

        node->left = BalanceTree(nodes, left, mid - 1);
        node->right = BalanceTree(nodes, mid + 1, right);
        
        return node;
    }

    bool isBalanced(){
        this->balanceFactor.clear();
        this->InOrderGetBalanceFactor(this->root);
        
        for(vector<int> e : this->balanceFactor){
            if(abs(e[1]) > 1) return false;  // Era true, deveria ser false
        }
        return true;
    }


    void InOrderGetBalanceFactor(Node*node){
        // L V R
        if(node == nullptr) return;
        InOrderGetBalanceFactor(node->left);

        vector<int> nodeInfo;
        nodeInfo.push_back(node->value);
        nodeInfo.push_back(this->getBalanceFactor(node));
        this->balanceFactor.push_back(nodeInfo);
        
        InOrderGetBalanceFactor(node->right);
    }

    int getBalanceFactor(Node*node){
        // Balance Factor = Left Height - Right Height; 
        // if abs(Balance Factor) > 1 : Tree Unbalanced.
        int left_height = this->getHeight(node->left);
        int right_height = this->getHeight(node->right);
        return(left_height - right_height);
    }
    int getHeight(Node*node){
        if(node == nullptr){return 0;}
        int left_height = getHeight(node->left);
        int right_height = getHeight(node->right);
        return (max(left_height, right_height) + 1);
    }

    void LevelOrderTraversal(Node*node){
        if(node == nullptr) return;
        
        queue<Node*> q;
        q.push(node);

        while(!q.empty()){
            Node*current = q.front();
            q.pop();
            
            cout << current->value << " ";

            if(current->left != nullptr){
                q.push(current->left);
            }
            if(current->right != nullptr){
                q.push(current->right);
            }
        }
    }

    void InOrderTraversal(Node*node){
        // L V R
        if(node == nullptr){return;}
        InOrderTraversal(node->left);
        cout << node->value << " ";
        InOrderTraversal(node->right);
    }

    void PreOrderTraversal(Node*node){
        // V L R
        if(node == nullptr){return;}
        cout << node->value << " ";
        PreOrderTraversal(node->left);
        PreOrderTraversal(node->right);
    
    }

    void PostOrderTraversal(Node*node){
        // L R V
        if(node == nullptr){return;}
        PostOrderTraversal(node->left);
        PostOrderTraversal(node->right);
        cout << node->value << " ";
    }

};


int main(){
    BST bst;
    bst.insert(10);
    bst.insert(5);
    bst.insert(30);
    bst.insert(15);
    bst.insert(3);
    
    cout << "Root value: " << bst.root->value << endl;
    cout << "In-order: ";
    bst.InOrderTraversal();
    cout << endl;
    cout << "Pre-order: ";
    bst.PreOrderTraversal();
    cout << endl;
    cout << "Post-order: ";
    bst.PostOrderTraversal();
    cout << endl;
    cout << "Level-order: ";
    bst.LevelOrderTraversal();
    cout << endl;

    cout << "Tree Height: ";
    cout << bst.getHeight();
    cout << endl; 

    bst.insert(1);
    bst.insert(0);

    bst.BalanceTree();
    bst.removeElement(5);

    bst.InOrderTraversal();
    cout << endl;
    bst.BalanceTree();

    return 0;
}