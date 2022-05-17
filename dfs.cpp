#include<iostream>
#include<list>
#include<queue>
#include<map>
using namespace std;

class Graph {
    // Number of edges in the graph
    int num_edges;
    // Using adjacency list map to store graph vertices and edges
    map<int, list<int>> adjList;

    // A list to maintain all the visited vertices
    map<int, bool> visited;

public:

    Graph() {
        this->num_edges = 0;
    }

    // Function to add an edge in the graph
    void addEdge(int start, int end){
        // Check if vertex has already been created
        if (adjList.find(start) == adjList.end()) {
            cout << "\nVertex " << start << " has been created!!!";
            num_edges++;
        }
        if (adjList.find(end) == adjList.end()) {
            cout << "\nVertex " << end << " has been created!!!";
            num_edges++;
        } 

        // Add edges in the adjacency list
        adjList[start].push_back(end);
        adjList[end].push_back(start);

        cout << "\nEdge has been added between " << start << " and " << end << endl; 

    }

    void printList(){
        for (auto it: adjList){
            cout << "\nThe list is: " << it.first;
            for (auto it2: it.second){
                cout << " -> " << it2;
            }
        }
        cout << "\n\n";
    }

    void BFS(int start) {
        for (auto i: adjList) visited[i.first] = false;

        if (adjList.find(start) == adjList.end()) {
            cout << "\nVertex not found. Please enter a correct starting vertex";
        }

        // Create a queue for bfs traversal
        queue<int> queue1;

        // Push the start element in the queue
        queue1.push(start);

        // Set the visited of the first element as true
        visited[start] = true;

        cout << "\n\n----------------------BFS TRAVERSAL----------------------";
        cout << "\nThe elements are: ";

        while(!queue1.empty()) {
            int front = queue1.front();
            cout << front << " ";

            queue1.pop();

            for (auto it: adjList[front]) {
                if (!visited[it]) queue1.push(it);
                visited[it] = true;
            }
        }
    }

    void DFSUtil(int start){
        // mark the start as visited
        visited[start] = true;
        // Print the start vertex
        cout << start << " ";

        // Recursively call this function for vertices adjacent to start
        for (auto it: adjList[start]) {
            if (!visited[it]) {
                DFSUtil(it);
            }
        }

    }

    void DFS() {
        for (auto i: adjList) visited[i.first] = false;

        for (auto it: adjList){
            if (!visited[it.first]) {
                DFSUtil(it.first);
            }
        }
    }


};

int main() {

    // Create a graph object
    Graph g1;

    int choice;
    bool flag = true;

    while(flag){
        cout << "\nMENU:"
             << "\n1) Add an Edge (Also adds vertices automatically): "
             << "\n2) Print Adjancency list: "
             << "\n3) Traverse using BFS: "
             << "\n4) Traverse using DFS: "
             << "\n5) Exit: "
             << endl;

        cout << "\nEnter your choice: ";
        cin >> choice;

        switch (choice)
        {
            case 1:
            {
                int start, end;
                cout << "\nEnter the first vertex: ";
                cin >> start;
                cout << "Enter the second vertex: ";
                cin >> end;
                
                g1.addEdge(start, end);
                break;
            }   
            case 2: 
            {
                cout << "\nThe Adjancency list is: " << endl;
                g1.printList();
                break;
            }
            case 3:
            {
                int start;
                cout << "\nEnter the first vertex for traversal: ";
                cin >> start;
                cout << "\nBreadth First Search result is: " << endl;
                g1.BFS(start);
                cout << "\n\n";
                break;
            }
            case 4: 
            {
                cout << "\nDepth first search is: " << endl;
                g1.DFS();
                cout << "\n\n";
                break;
            }
            case 5:
            {
                cout << "\nGood Bye!!!";
                flag = false;
                break;
            }

            default:
                cout << "\nEnter a valid option!!!" << endl;
                break;
            }
    }


    return 0;
}