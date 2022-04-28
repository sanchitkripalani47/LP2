/* 
Name: Maitreyee Naik
Roll No: 31151
Batch: M1
*/

#include <iostream>
#include <list>
#include <map>
using namespace std;

class Graph {

    // Number of vertices in the graph
    int num_ver;
    // List to store all the vertices in the graph
    map<int, list<int>> adjList;

    // Map of visited vertices
    map<int, bool> visited;

public:

    // Constructor 
    Graph(){
        this->num_ver = 0;
        cout << "\nA New Graph has been created!!!\n";
    }

    // Function to add an edge in the graph
    void addEdge(int start, int end){

        if (adjList.find(start) == adjList.end()){
            num_ver++;
            cout << "\nVertex " << start << " added to graph!!!";
        } 
        if (adjList.find(end) == adjList.end()) {
            num_ver++;
            cout << "\nVertex " << end << " added to graph!!!" << endl;
        }

        // Since it is an undirected graph, edge will be from both start to end and visa versa
        adjList[start].push_back(end);
        adjList[end].push_back(start);

        cout << "\nEdge created between " << start << " and " << end << endl;
    }

    // Print the adjacency list
    void printList(){
        for (auto i: adjList){
            cout << "\nCurrent vertex head is " << i.first; 
            for (auto it: i.second){
                cout << "-> " << it;
            }
            cout << "\n";
        }
        cout << "\n\n";
    }

    // Breadth First Search using iteration
    void BFSitr(int start){
        for (auto i: adjList) visited[i.first] = false;

        // A queue is needed for BFS
        list<int> queue1;

        // Set current vertex as visited
        visited[start] = true;

        // Add the current vertex to queue
        queue1.push_back(start);

        // Get all the adjacent vertices to start using iterator
        list<int>:: iterator it;

        while(!queue1.empty()){
            // Get the vertex in front of the queue and then remove it
            int new_start = queue1.front();
            // Print the vertex
            cout << new_start << " ";
            queue1.pop_front();

            // Now move on to adjacent vertices of the current vertex.
            // If an adjacent vertex is not visited, then add it to the queue
            for (auto i: adjList){
                if (visited[i.first] == false){
                    visited[i.first] = true;
                    queue1.push_back(i.first);
                }
            }

        } 

    }

    // Function for Depth First Search
    void DFS(){
        for (auto i: adjList) visited[i.first] = false;

        for (auto i : adjList){
            // Will call DFSrec for all vertices which have not been visited
            // Including Disconned vertices
            if (visited[i.first] == false)
                DFSrec(i.first);
        }
    }

    // Recursive function for Depth First Search
    void DFSrec(int start){
        // Current vertice set as visited
        visited[start] = true;

        cout << start << " ";

        for (auto it: adjList[start]){
            if (!visited[it]){
                DFSrec(it);
            }
        }
    }

};

// Menu driven code
int main(){
    // Creating an object of Graph
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
                g1.BFSitr(start);
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