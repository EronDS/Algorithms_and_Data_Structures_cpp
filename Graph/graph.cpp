#include <vector>
#include <cmath>
#include <map>
#include <iostream>
#include <string>
#include <queue> 
#include <stack>
#include <algorithm>

using namespace std;

class Graph{
    public:
        vector<vector<int>> adjMatrix;
        int numVertices;
        int key;
        map<string, int> vertexMap;
        map<int, string> reverseVertexMap;

        Graph(){numVertices = 0; key = 0;};
        

        void addVertex(const string & A, const string & B, const int & weight, const bool & direct = true){
            if(vertexMap.find(A) == vertexMap.end()){
                this->addNode(A);
            }
            if(vertexMap.find(B) == vertexMap.end()){
                this->addNode(B);
            }

            adjMatrix[vertexMap[A]][vertexMap[B]] = weight;
            if(!direct) adjMatrix[vertexMap[B]][vertexMap[A]] = weight;
        }


        void MinimumPath(const string & from, const string & to){
            map<string, string> path;
            path[from] = "start";

            int from_idx = this->vertexMap[from];
            int to_idx = this->vertexMap[to];

            const int INF = INT_MAX;
            vector<int> distance_matrix(this->numVertices, INF);
            distance_matrix[from_idx] = 0;

            bool running = true;
            vector<int> visited;
            visited.push_back(from_idx); 

            int current_idx = from_idx;

            while(running){
                vector<int> connections = this->adjMatrix[current_idx];

                // CORREÇÃO 1: Comparar índices corretos
                if(current_idx == to_idx){
                    running = false;
                    break;
                }
                
                for(int i = 0; i < connections.size(); i++){
                    if(connections[i] != 0){
                        if(distance_matrix[i] == INF){
                            distance_matrix[i] = distance_matrix[current_idx] + connections[i];
                            path[this->reverseVertexMap[i]] = this->reverseVertexMap[current_idx];
                        }
                        else if(distance_matrix[i] > distance_matrix[current_idx] + connections[i]){
                            distance_matrix[i] = distance_matrix[current_idx] + connections[i];
                            path[this->reverseVertexMap[i]] = this->reverseVertexMap[current_idx];
                        }
                    }
                }
                
                int next_idx = -1;
                int min_distance = INF;
                
                for(int i = 0; i < this->numVertices; i++){
                    if(!this->is_visited(i, visited) && distance_matrix[i] < min_distance){
                        min_distance = distance_matrix[i];
                        next_idx = i;
                    }
                }
                
                if(next_idx == -1 || min_distance == INF){
                    running = false; 
                }
                else{
                    current_idx = next_idx;
                    visited.push_back(current_idx);
                }
            }

            vector<string> minimum_path = this->reconstructPath(path, to);

            cout << "Minimum Path Length: " << distance_matrix[to_idx] << endl;

            if(!minimum_path.empty()){
                for(int i = minimum_path.size()-1; i >= 0; i--){
                    cout << minimum_path[i] + " -> ";
                }
            }
            cout << endl;
        }
        void printAdjMatrix(){
            cout << "    ";
            for(int k = 0; k < adjMatrix.size(); k++){
                cout <<  reverseVertexMap[k] + " ";
            }
            cout << endl;
            for(int i = 0; i < adjMatrix.size(); i++){
                cout <<  reverseVertexMap[i] + "< ";
                vector<int> node_connections = adjMatrix[i];
                for(int connection : node_connections){
                    cout << to_string(connection) + " "; 
                }
                cout << "> " << endl;

            }
        }

        void DFS(const string & start_at){
            int current_node_idx = this->vertexMap[start_at];
            stack<int> s;
            vector<int> visited;
            visited.push_back(current_node_idx);
            s.push(current_node_idx);


            while(!s.empty()){
                current_node_idx = s.top();
                
                cout << this->reverseVertexMap[current_node_idx] + " ";

                s.pop();

                vector<int> connections = this->adjMatrix[current_node_idx];

                for(int i = 0; i < connections.size() ;i ++){
                    if(connections[i] != 0){
                        if(!this->is_visited(i, visited)){
                            s.push(i);
                            visited.push_back(i);
                        }

                    }
                }
                
            }
        }

        void BFS(const string & start_at){
            int current_node_idx = this->vertexMap[start_at];

            
            queue<int> q;
            vector<int> visited; 
            q.push(current_node_idx);
            visited.push_back(current_node_idx);

            while(!q.empty()){
                int current_node = q.front();
                q.pop();
                cout << this->reverseVertexMap[current_node] + " ";
                
                vector<int> current_node_connections = adjMatrix[current_node];

                for(int i = 0; i<current_node_connections.size();i++){
                    if(current_node_connections[i] != 0){
                        if(!is_visited(i, visited)){
                            q.push(i);
                            visited.push_back(i);
                        };
                    }
                }
            }
        }

        private:
        
        void addNode(const string & node){
            vertexMap[node] = key;
            reverseVertexMap[key] = node;
            key++;
            numVertices++;

            for(int i = 0; i < adjMatrix.size(); i++){
                adjMatrix[i].push_back(0);
            }

            adjMatrix.push_back(vector<int>(adjMatrix.size() + 1, 0));
            return;
        }

        bool is_visited(int value, vector<int>visited){
            auto it = find(visited.begin(), visited.end(), value);
            return(it != visited.end()) ? true : false;
        }

        vector<string> reconstructPath(map<string, string> path, const string & final_node){
            vector<string> node_path;
            string current = final_node;
            while(current != "start"){
                node_path.push_back(current);
                current = path[current];
            }
            return node_path;
        }
};


int main(){
    Graph graph;
    // Edges existentes
    graph.addVertex("A", "B", 10);
    graph.addVertex("B", "C", 20);
    
    // Adicione estas edges para criar um grafo mais interessante:
    graph.addVertex("A", "D", 15);     // A -> D
    graph.addVertex("B", "E", 25);     // B -> E  
    graph.addVertex("C", "F", 30);     // C -> F
    graph.addVertex("D", "E", 5);      // D -> E
    graph.addVertex("E", "F", 10);     // E -> F
    graph.addVertex("A", "C", 35);     // A -> C (caminho alternativo)
    
    graph.printAdjMatrix();
    cout << endl;
    graph.BFS("A");
    cout << endl;
    graph.DFS("A");
    cout << endl;

    graph.MinimumPath("A", "F");
}