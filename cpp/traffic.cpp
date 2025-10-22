#include <iostream>
using namespace std;

#define MAX 10

class CityMap {
    string cityNames[MAX];
    int adjMatrix[MAX][MAX];     // Adjacency Matrix
    int adjList[MAX][MAX];       // Adjacency List
    int listSize[MAX];           // Track size of each adjacency list
    int n;                       // Number of cities

public:
    CityMap(int cities) {
        n = cities;
        // Initialize matrix and list
        for (int i = 0; i < n; i++) {
            listSize[i] = 0;
            for (int j = 0; j < n; j++)
                adjMatrix[i][j] = 0;
        }
    }

    void setCityName(int index, string name) {
        cityNames[index] = name;
    }

    void addRoad(int u, int v) {
        // Update adjacency matrix
        adjMatrix[u][v] = 1;
        adjMatrix[v][u] = 1;

        // Update adjacency list
        adjList[u][listSize[u]++] = v;
        adjList[v][listSize[v]++] = u;
    }

    void displayAdjMatrix() {
        cout << "\nAdjacency Matrix (Road Connections):\n";
        cout << "     ";
        for (int i = 0; i < n; i++)
            cout << cityNames[i][0] << " ";
        cout << endl;

        for (int i = 0; i < n; i++) {
            cout << cityNames[i][0] << "  : ";
            for (int j = 0; j < n; j++)
                cout << adjMatrix[i][j] << " ";
            cout << endl;
        }
    }

    void displayAdjList() {
        cout << "\nAdjacency List (City Connections):\n";
        for (int i = 0; i < n; i++) {
            cout << cityNames[i] << " -> ";
            for (int j = 0; j < listSize[i]; j++)
                cout << cityNames[adjList[i][j]] << " ";
            cout << endl;
        }
    }

    void DFS(int start) {
        int visited[MAX] = {0};
        int stack[MAX];
        int top = -1;

        cout << "\nDFS Route starting from " << cityNames[start] << ": ";
        stack[++top] = start;

        while (top != -1) {
            int node = stack[top--];
            if (!visited[node]) {
                cout << cityNames[node] << " ";
                visited[node] = 1;

                for (int i = listSize[node] - 1; i >= 0; i--) {
                    int adjNode = adjList[node][i];
                    if (!visited[adjNode])
                        stack[++top] = adjNode;
                }
            }
        }
        cout << endl;
    }

    void BFS(int start) {
        int visited[MAX] = {0};
        int queue[MAX];
        int front = 0, rear = 0;

        cout << "\nBFS Route starting from " << cityNames[start] << ": ";
        visited[start] = 1;
        queue[rear++] = start;

        while (front < rear) {
            int node = queue[front++];
            cout << cityNames[node] << " ";

            for (int i = 0; i < listSize[node]; i++) {
                int adjNode = adjList[node][i];
                if (!visited[adjNode]) {
                    visited[adjNode] = 1;
                    queue[rear++] = adjNode;
                }
            }
        }
        cout << endl;
    }
};

int main() {
    CityMap map(5);

    // Set city names
    map.setCityName(0, "Delhi");
    map.setCityName(1, "Mumbai");
    map.setCityName(2, "Chennai");
    map.setCityName(3, "Kolkata");
    map.setCityName(4, "Bangalore");

    // Create roads (edges)
    map.addRoad(0, 1); // Delhi - Mumbai
    map.addRoad(0, 2); // Delhi - Chennai
    map.addRoad(1, 3); // Mumbai - Kolkata
    map.addRoad(2, 4); // Chennai - Bangalore

    cout << "\n=== City Map Navigation System ===\n";

    map.displayAdjMatrix();
    map.displayAdjList();

    map.DFS(0); // Start from Delhi
    map.BFS(0); // Start from Delhi

    return 0;
}
