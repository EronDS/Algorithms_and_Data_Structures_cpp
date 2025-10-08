#include <vector>
#include <map>
#include <cmath>
#include <iostream>
#include <queue>
#include <fstream> // For file output

using namespace std;

class Node{
    public:
    int value;
    int lh, rh;
    int bf;
    Node*left;
    Node*right;
    Node(int value){
        this->value = value;
        this->lh=0;
        this->rh=0;
        this->bf=0;
        this->left = nullptr;
        this->right = nullptr;
    }
};



class AVL{
    public:
    Node*root = nullptr;
    AVL(){}

    void Insert(int value){
        Node*new_node = new Node(value);
        this->root = this->Insert(this->root, new_node);

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

    void printTree(){
        cout << "\n=== Tree Structure ===\n";
        printTreeHelper(root, "", true);
        cout << "=====================\n\n";
    }

    void saveTreeImage(string filename = "./tree_dots/avl_tree"){
        string dotFilename = filename + ".dot";
        ofstream file(dotFilename);
        file << "digraph AVL {\n";
        file << "    node [shape=circle, style=filled, fillcolor=lightblue];\n";
        generateDotFormat(root, file);
        file << "}\n";
        file.close();
        
        cout << "Tree saved as " << dotFilename << endl;
    }

    void removeElement(const int & value){
        this->root = this->removeElement(this->root, value);
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

        this->updateHeight(node);

        if (abs(node->bf)<=1) return node; 

        if((node->bf > 1)) {
            if (node->left->bf >= 0) node = this->rotateRight(node);
            else node = this->rotateLeftRight(node);
        }

        else if(node->bf < -1){
            if(node->right->bf <= 0) node = this->rotateLeft(node);
            else node = this->rotateRightLeft(node);
        }
    
        return node;
    }

    Node* findMin(Node* node){
        while(node->left != nullptr){
            node = node->left;
        }
        return node;
    }

    Node*Insert(Node*node, Node*new_node){
        if(node == nullptr) return new_node;
        
        else if(new_node->value < node->value){
            node->left = this->Insert(node->left, new_node);
        }

        else if(new_node->value > node->value){
            node->right = this->Insert(node->right, new_node);
        }

        else return node;

        this->updateHeight(node);

        if (abs(node->bf)<=1) return node; 

        if((node->bf > 1)) {
            if (node->left->bf >= 0) node = this->rotateRight(node);
            else node = this->rotateLeftRight(node);
        }

        else if(node->bf < -1){
            if(node->right->bf <= 0) node = this->rotateLeft(node);
            else node = this->rotateRightLeft(node);
        }

        return node;

    }

    Node* rotateLeftRight(Node*node){
        node->left = rotateLeft(node->left);
        return rotateRight(node);
    }

    Node* rotateRightLeft(Node*node){
        node->right = rotateRight(node->right);
        return rotateLeft(node);
    }

    Node* rotateLeft(Node*node){
        Node*pivot = node->right;
        node->right = pivot->left;
        pivot->left = node;

        updateHeight(node);
        updateHeight(pivot);
        return pivot;
    }
    Node* rotateRight(Node* node){
        Node* pivot = node->left;           
        node->left = pivot->right;          
        pivot->right = node;                
        
        updateHeight(node);
        updateHeight(pivot);
        
        return pivot;                      
    }      

    void updateHeight(Node*node){
        node->bf = this->getBalanceFactor(node);
        return;
    }

    int getHeight(Node*node){
        if(node == nullptr) return 0;
        int left_height = getHeight(node->left);
        int right_height = getHeight(node->right);
        return (max(left_height, right_height) + 1);
    }

    int getBalanceFactor(Node*node){
        if(node == nullptr) return 0;
        int left_subtree_height = this->getHeight(node->left);
        int right_subtree_height = this->getHeight(node->right);

        node->lh = left_subtree_height;
        node->rh = right_subtree_height;

        return (left_subtree_height - right_subtree_height);
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

    void printTreeHelper(Node* node, string prefix, bool isLast){
        if(node == nullptr) return;
        
        cout << prefix << (isLast ? "└── " : "├── ") 
             << node->value << " (bf:" << node->bf << ")\n";
        
        if(node->left != nullptr || node->right != nullptr){
            if(node->right != nullptr){
                printTreeHelper(node->right, prefix + (isLast ? "    " : "│   "), node->left == nullptr);
            }
            if(node->left != nullptr){
                printTreeHelper(node->left, prefix + (isLast ? "    " : "│   "), true);
            }
        }
    }

    void generateDotFormat(Node* node, ofstream& file){
        if(node == nullptr) return;
        
        // Write current node with balance factor
        file << "    " << node->value << " [label=\"" << node->value 
             << "\\nbf:" << node->bf << "\"];\n";
        
        // Add edges to children
        if(node->left != nullptr){
            file << "    " << node->value << " -> " << node->left->value << ";\n";
            generateDotFormat(node->left, file);
        }
        if(node->right != nullptr){
            file << "    " << node->value << " -> " << node->right->value << ";\n";
            generateDotFormat(node->right, file);
        }
    }

};

int main(){
    AVL avl;
    
    cout << "Inserting values: 10, 5, 15, 3, 7, 12, 20\n";
    
    avl.Insert(10); avl.Insert(5); avl.Insert(15);
    avl.Insert(3); avl.Insert(7); avl.Insert(12); avl.Insert(20);
    
    avl.printTree();  
    
    cout << "Adding 1, 2 (forces rotations):\n";
    avl.Insert(1); avl.Insert(2);
    
    avl.printTree();
    
    avl.saveTreeImage("balanced_tree_before_removal"); 

    avl.removeElement(10);
    
    cout << "Tree after removing element 10 (root)" << endl;
    avl.printTree();
    avl.saveTreeImage("balanced_tree_after_removal");

    return 0;
}