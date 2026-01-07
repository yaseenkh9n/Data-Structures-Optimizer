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
    
    void insert(const T& vertex) {
        if (adjacencyList.find(vertex) == adjacencyList.end()) {
            adjacencyList[vertex] = vector<Edge>();
        }
    }
    
    void insert(const T& source, const T& destination, double weight = 1.0) {
        insert(source);
        insert(destination);
        
        for (const Edge& e : adjacencyList[source]) {
            if (e.destination == destination) {
                return;
            }
        }
        
        adjacencyList[source].push_back(Edge(destination, weight));
        edgeCount++;
        
        if (!isDirected) {
            adjacencyList[destination].push_back(Edge(source, weight));
        }
    }
    
    bool remove(const T& vertex) {
        auto it = adjacencyList.find(vertex);
        if (it == adjacencyList.end()) {
            return false;
        }
        
        int edgesFromVertex = it->second.size();
        
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
        
        if (isDirected) {
            edgeCount -= edgesFromVertex;
        } else {
            edgeCount -= edgesFromVertex;
        }
        
        adjacencyList.erase(vertex);
        return true;
    }
    
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
            return false;
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
    
    bool search(const T& vertex) const {
        return adjacencyList.find(vertex) != adjacencyList.end();
    }
    
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
    
    vector<T> getVertices() const {
        vector<T> vertices;
        vertices.reserve(adjacencyList.size());
        for (const auto& pair : adjacencyList) {
            vertices.push_back(pair.first);
        }
        return vertices;
    }
    
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
    
    int getVertexCount() const {
        return adjacencyList.size();
    }
    
    int getEdgeCount() const {
        return edgeCount;
    }
    
    bool getIsDirected() const {
        return isDirected;
    }
    
    bool isEmpty() const {
        return adjacencyList.empty();
    }
    
    void clear() {
        adjacencyList.clear();
        edgeCount = 0;
    }
    
};

#endif // GRAPH_H