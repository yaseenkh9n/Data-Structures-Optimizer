#ifndef GRAPH_H
#define GRAPH_H

#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <queue>
#include <stdexcept>

using namespace std;

template<typename T>
class Graph {
private:
    struct Edge {
        T destination;
        double weight;
        
        Edge(const T& dest, double w = 1.0) : destination(dest), weight(w) {}
    };
    
    map<T, vector<Edge>> adjacencyList;
    bool isDirected;
    int edgeCount;

public:
    Graph(bool directed = false) : isDirected(directed), edgeCount(0) {}
    
    ~Graph() {
        clear();
    }
    
    // INSERT: Add a vertex to the graph
    void insert(const T& vertex) {
        if (adjacencyList.find(vertex) == adjacencyList.end()) {
            adjacencyList[vertex] = vector<Edge>();
        }
    }
    
    // INSERT: Add an edge between two vertices
    void insert(const T& source, const T& destination, double weight = 1.0) {
        // Ensure both vertices exist
        insert(source);
        insert(destination);
        
        // Check if edge already exists
        for (const Edge& e : adjacencyList[source]) {
            if (e.destination == destination) {
                return;  // Edge already exists
            }
        }
        
        adjacencyList[source].push_back(Edge(destination, weight));
        edgeCount++;
        
        if (!isDirected) {
            adjacencyList[destination].push_back(Edge(source, weight));
        }
    }
    
    // DELETE: Remove a vertex and all its edges from the graph
    bool remove(const T& vertex) {
        auto it = adjacencyList.find(vertex);
        if (it == adjacencyList.end()) {
            return false;
        }
        
        // Count edges being removed from this vertex
        int edgesFromVertex = it->second.size();
        
        // Remove all edges TO this vertex from other vertices
        for (auto& pair : adjacencyList) {
            if (pair.first != vertex) {
                auto& edges = pair.second;
                int sizeBefore = edges.size();
                edges.erase(
                    remove_if(edges.begin(), edges.end(),
                              [&vertex](const Edge& e) { return e.destination == vertex; }),
                    edges.end()
                );
                int edgesRemoved = sizeBefore - edges.size();
                if (isDirected) {
                    edgeCount -= edgesRemoved;
                }
            }
        }
        
        // Update edge count for edges from this vertex
        if (isDirected) {
            edgeCount -= edgesFromVertex;
        } else {
            edgeCount -= edgesFromVertex;  // Already counted in removal from other vertices
        }
        
        // Remove the vertex itself
        adjacencyList.erase(vertex);
        return true;
    }
    
    // DELETE: Remove an edge between two vertices
    bool remove(const T& source, const T& destination) {
        auto it = adjacencyList.find(source);
        if (it == adjacencyList.end()) {
            return false;
        }
        
        auto& edges = it->second;
        int sizeBefore = edges.size();
        edges.erase(
            remove_if(edges.begin(), edges.end(),
                      [&destination](const Edge& e) { return e.destination == destination; }),
            edges.end()
        );
        
        if (edges.size() == sizeBefore) {
            return false;  // Edge not found
        }
        
        edgeCount--;
        
        if (!isDirected) {
            auto destIt = adjacencyList.find(destination);
            if (destIt != adjacencyList.end()) {
                auto& destEdges = destIt->second;
                destEdges.erase(
                    remove_if(destEdges.begin(), destEdges.end(),
                              [&source](const Edge& e) { return e.destination == source; }),
                    destEdges.end()
                );
            }
        }
        
        return true;
    }
    
    // SEARCH: Check if a vertex exists in the graph
    bool search(const T& vertex) const {
        return adjacencyList.find(vertex) != adjacencyList.end();
    }
    
    // SEARCH: Check if an edge exists between two vertices
    bool search(const T& source, const T& destination) const {
        auto it = adjacencyList.find(source);
        if (it == adjacencyList.end()) {
            return false;
        }
        
        for (const Edge& e : it->second) {
            if (e.destination == destination) {
                return true;
            }
        }
        
        return false;
    }
    
    // Get all vertices in the graph
    vector<T> getVertices() const {
        vector<T> vertices;
        vertices.reserve(adjacencyList.size());
        for (const auto& pair : adjacencyList) {
            vertices.push_back(pair.first);
        }
        return vertices;
    }
    
    // Get all neighbors of a vertex
    vector<T> getNeighbors(const T& vertex) const {
        vector<T> neighbors;
        auto it = adjacencyList.find(vertex);
        if (it != adjacencyList.end()) {
            neighbors.reserve(it->second.size());
            for (const Edge& e : it->second) {
                neighbors.push_back(e.destination);
            }
        }
        return neighbors;
    }
    
    // Get the number of vertices
    int getVertexCount() const {
        return adjacencyList.size();
    }
    
    // Get the number of edges
    int getEdgeCount() const {
        return edgeCount;
    }
    
    // Check if graph is directed
    bool getIsDirected() const {
        return isDirected;
    }
    
    // Check if graph is empty
    bool isEmpty() const {
        return adjacencyList.empty();
    }
    
    // Clear all vertices and edges
    void clear() {
        adjacencyList.clear();
        edgeCount = 0;
    }
    
    // Print the adjacency list representation
    void print() const {
        cout << "\nGraph Adjacency List:" << endl;
        cout << "=====================" << endl;
        
        for (const auto& pair : adjacencyList) {
            cout << pair.first << " -> ";
            bool first = true;
            for (const Edge& e : pair.second) {
                if (!first) cout << ", ";
                cout << e.destination;
                if (e.weight != 1.0) {
                    cout << "(" << e.weight << ")";
                }
                first = false;
            }
            cout << endl;
        }
    }
};

#endif // GRAPH_H