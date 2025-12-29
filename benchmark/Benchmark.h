#ifndef BENCHMARK_H
#define BENCHMARK_H

#include "PerformanceMetrics.h"
#include "Heap.h"
#include "BST.h"
#include "HashMap.h"
#include "Trie.h"
#include "Graph.h"
#include <vector>
#include <map>
#include <chrono>
#include <random>
#include <fstream>
#include <iostream>
#include <stdexcept>
#include <limits>
#include <string>
#include <functional>

using namespace std;
using namespace std::chrono;

// template class for benchmarking any data type
template<typename T>
class Benchmark {
public:
    // operation profile - defines test workload
    struct OperationProfile {
        int searchPercent;
        int insertPercent;
        int deletePercent;
        int totalOperations;

        OperationProfile(int search, int insert, int del, int total)
            : searchPercent(search), insertPercent(insert),
            deletePercent(del), totalOperations(total)
        {
            if (search + insert + del != 100)
                throw invalid_argument("Percentages must sum to 100");
            if (totalOperations <= 0)
                throw invalid_argument("Total operations must be positive");
        }

        int getSearchCount() const { return (totalOperations * searchPercent) / 100; }
        int getInsertCount() const { return (totalOperations * insertPercent) / 100; }
        int getDeleteCount() const { return (totalOperations * deletePercent) / 100; }



        string toString() const {
            string result = "\nOperation Profile:\n";
            result += "  Search: " + to_string(searchPercent) + "% (" +
                      to_string(getSearchCount()) + " ops)\n";
            result += "  Insert: " + to_string(insertPercent) + "% (" +
                      to_string(getInsertCount()) + " ops)\n";
            result += "  Delete: " + to_string(deletePercent) + "% (" +
                      to_string(getDeleteCount()) + " ops)\n";
            result += "  Total: " + to_string(totalOperations) + " operations\n";
            return result;
        }
    };

    // callback for progress updates (for GUI)
    using ProgressCallback = function<void(int percentage, const string& message)>;

    // constructor
    Benchmark() : progressCallback(nullptr) {
        random_device rd;
        rng.seed(rd());
    }

    // set progress callback for GUI
    void setProgressCallback(ProgressCallback callback) {
        progressCallback = callback;
    }

    // measure time of any operation
    template<typename Func>
    double measureTime(Func function) {
        auto start = high_resolution_clock::now();
        function();
        auto end = high_resolution_clock::now();
        duration<double, milli> elapsed = end - start;
        return elapsed.count();
    }

    // generate random keys from existing data
    vector<T> generateRandomKeys(const vector<T>& data, int count) {
        vector<T> keys;
        uniform_int_distribution<int> dist(0, data.size() - 1);
        for (int i = 0; i < count; i++) {
            keys.push_back(data[dist(rng)]);
        }
        return keys;
    }

    // generate new random values
    vector<T> generateNewValues(int count) {
        vector<T> newValues;

        if (is_arithmetic<T>::value) {
            uniform_int_distribution<long long> dist(1000000, 2000000);
            for (int i = 0; i < count; i++) {
                newValues.push_back(static_cast<T>(dist(rng)));
            }
        }
        else if (is_same<T, string>::value) {
            for (int i = 0; i < count; i++) {
                string newStr = "gen_" + to_string(i + 1000000);
                newValues.push_back(*reinterpret_cast<T*>(&newStr));
            }
        }
        else {
            for (int i = 0; i < count; i++) {
                newValues.push_back(T());
            }
        }

        return newValues;
    }

    void updateProgress(int pct, const string& msg) {
        if (progressCallback) {
            progressCallback(pct, msg);
        }
    }

    // test Heap
    PerformanceMetrics testBST(const vector<T>& initialData, const OperationProfile& profile) {
        PerformanceMetrics m("BST");
        m.dataSize = initialData.size();
        BST<T> bst;

        updateProgress(0, "[BST] Starting test");

        // phase 1: insert initial data
        updateProgress(5, "[BST] Inserting initial data");
        m.insertTime = measureTime([&]() {
            for (const T& val : initialData)
                bst.insert(val);
        });
        m.insertCount = initialData.size();

        // phase 2: search operations
        int searchCnt = profile.getSearchCount();
        if (searchCnt > 0) {
            updateProgress(30, "[BST] Performing searches");
            vector<T> searchKeys = generateRandomKeys(initialData, searchCnt);
            m.searchTime = measureTime([&]() {
                for (const T& key : searchKeys)
                    bst.searchValue(key);
            });
            m.searchCount = searchCnt;
        }

        // phase 3: additional inserts
        int addInserts = profile.getInsertCount();
        if (addInserts > 0) {
            updateProgress(60, "[BST] Additional inserts");
            vector<T> newVals = generateNewValues(addInserts);
            double addTime = measureTime([&]() {
                for (const T& val : newVals)
                    bst.insert(val);
            });
            m.insertTime += addTime;
            m.insertCount += addInserts;
        }

        // phase 4: delete operations
        int delCnt = profile.getDeleteCount();
        if (delCnt > 0) {
            updateProgress(80, "[BST] Deleting elements");
            vector<T> delKeys = generateRandomKeys(initialData, delCnt);
            m.deleteTime = measureTime([&]() {
                for (const T& key : delKeys)
                    bst.remove(key);
            });
            m.deleteCount = delCnt;
        }

        // phase 5: calculate memory
        int nodes = bst.countNodes();
        m.memoryUsed = nodes * (sizeof(T) + 2 * sizeof(void*) + sizeof(int));

        // phase 6: total time
        m.totalTime = m.insertTime + m.searchTime + m.deleteTime;

        updateProgress(100, "[BST] Complete");
        return m;
    }

    // test Heap
    PerformanceMetrics testHeap(const vector<T>& initialData,
                                const OperationProfile& profile) {
        PerformanceMetrics m("Heap");
        m.dataSize = initialData.size();
        Heap<T> heap(false);

        updateProgress(0, "[Heap] Starting test");

        // phase 1: insert
        updateProgress(5, "[Heap] Inserting initial data");
        m.insertTime = measureTime([&]() {
            for (const T& val : initialData)
                heap.insert(val);
        });
        m.insertCount = initialData.size();

        // phase 2: search
        int searchCnt = profile.getSearchCount();
        if (searchCnt > 0) {
            updateProgress(30, "[Heap] Performing searches");
            vector<T> searchKeys = generateRandomKeys(initialData, searchCnt);
            m.searchTime = measureTime([&]() {
                for (const T& key : searchKeys)
                    heap.search(key);
            });
            m.searchCount = searchCnt;
        }

        // phase 3: additional inserts
        int addInserts = profile.getInsertCount();
        if (addInserts > 0) {
            updateProgress(60, "[Heap] Additional inserts");
            vector<T> newVals = generateNewValues(addInserts);
            double addTime = measureTime([&]() {
                for (const T& val : newVals)
                    heap.insert(val);
            });
            m.insertTime += addTime;
            m.insertCount += addInserts;
        }

        // phase 4: delete
        int delCnt = profile.getDeleteCount();
        if (delCnt > 0) {
            updateProgress(80, "[Heap] Deleting elements");
            vector<T> delKeys = generateRandomKeys(initialData, delCnt);
            m.deleteTime = measureTime([&]() {
                for (const T& key : delKeys)
                    heap.removeValue(key);
            });
            m.deleteCount = delCnt;
        }

        // phase 5: memory
        m.memoryUsed = heap.size() * sizeof(T);

        // phase 6: total
        m.totalTime = m.insertTime + m.searchTime + m.deleteTime;

        updateProgress(100, "[Heap] Complete");
        return m;
    }

    // test HashMap
    template<typename V = T>
    PerformanceMetrics testHashMap(const vector<T>& initialData,
                                   const OperationProfile& profile) {
        PerformanceMetrics m("HashMap");
        m.dataSize = initialData.size();
        HashMap<T, V> map;

        updateProgress(0, "[HashMap] Starting test");

        // phase 1: insert
        updateProgress(5, "[HashMap] Inserting initial data");
        m.insertTime = measureTime([&]() {
            for (const T& val : initialData)
                map.insert(val, static_cast<V>(val));
        });
        m.insertCount = initialData.size();

        // phase 2: search
        int searchCnt = profile.getSearchCount();
        if (searchCnt > 0) {
            updateProgress(30, "[HashMap] Performing searches");
            vector<T> searchKeys = generateRandomKeys(initialData, searchCnt);
            m.searchTime = measureTime([&]() {
                for (const T& key : searchKeys)
                    map.search(key);
            });
            m.searchCount = searchCnt;
        }

        // phase 3: additional inserts
        int addInserts = profile.getInsertCount();
        if (addInserts > 0) {
            updateProgress(60, "[HashMap] Additional inserts");
            vector<T> newVals = generateNewValues(addInserts);
            double addTime = measureTime([&]() {
                for (const T& val : newVals)
                    map.insert(val, static_cast<V>(val));
            });
            m.insertTime += addTime;
            m.insertCount += addInserts;
        }

        // phase 4: delete
        int delCnt = profile.getDeleteCount();
        if (delCnt > 0) {
            updateProgress(80, "[HashMap] Deleting elements");
            vector<T> delKeys = generateRandomKeys(initialData, delCnt);
            m.deleteTime = measureTime([&]() {
                for (const T& key : delKeys)
                    map.remove(key);
            });
            m.deleteCount = delCnt;
        }

        // phase 5: memory
        int elements = map.getSize();
        int buckets = map.getCapacity();
        m.memoryUsed = (buckets * sizeof(void*)) +
                       (elements * (sizeof(T) + sizeof(V) + sizeof(void*)));

        // phase 6: total
        m.totalTime = m.insertTime + m.searchTime + m.deleteTime;

        updateProgress(100, "[HashMap] Complete");
        return m;
    }

    // test Graph
    PerformanceMetrics testGraph(const vector<T>& initialData,
                                 const OperationProfile& profile) {
        PerformanceMetrics m("Graph");
        m.dataSize = initialData.size();
        Graph<T> graph(false);  // undirected graph

        updateProgress(0, "[Graph] Starting test");

        // phase 1: insert vertices and edges
        updateProgress(5, "[Graph] Inserting initial data");
        m.insertTime = measureTime([&]() {
            // Insert vertices
            for (const T& val : initialData)
                graph.insert(val);
            // Create edges between consecutive elements
            for (size_t i = 1; i < initialData.size(); i++) {
                graph.insert(initialData[i-1], initialData[i]);
            }
        });
        m.insertCount = initialData.size();

        // phase 2: search operations (vertex search)
        int searchCnt = profile.getSearchCount();
        if (searchCnt > 0) {
            updateProgress(30, "[Graph] Performing searches");
            vector<T> searchKeys = generateRandomKeys(initialData, searchCnt);
            m.searchTime = measureTime([&]() {
                for (const T& key : searchKeys)
                    graph.search(key);
            });
            m.searchCount = searchCnt;
        }

        // phase 3: additional inserts (new vertices and edges)
        int addInserts = profile.getInsertCount();
        if (addInserts > 0) {
            updateProgress(60, "[Graph] Additional inserts");
            vector<T> newVals = generateNewValues(addInserts);
            double addTime = measureTime([&]() {
                for (const T& val : newVals)
                    graph.insert(val);
            });
            m.insertTime += addTime;
            m.insertCount += addInserts;
        }

        // phase 4: delete operations (vertex removal)
        int delCnt = profile.getDeleteCount();
        if (delCnt > 0) {
            updateProgress(80, "[Graph] Deleting vertices");
            vector<T> delKeys = generateRandomKeys(initialData, delCnt);
            m.deleteTime = measureTime([&]() {
                for (const T& key : delKeys)
                    graph.remove(key);
            });
            m.deleteCount = delCnt;
        }

        // phase 5: calculate memory
        int vertices = graph.getVertexCount();
        int edges = graph.getEdgeCount();
        // Memory: adjacency list with map overhead + edge vectors
        m.memoryUsed = vertices * (sizeof(T) + sizeof(vector<void*>)) + 
                       edges * (sizeof(T) + sizeof(double));

        // phase 6: total time
        m.totalTime = m.insertTime + m.searchTime + m.deleteTime;

        updateProgress(100, "[Graph] Complete");
        return m;
    }

    // run all tests
    map<string, PerformanceMetrics> runAllTests(const vector<T>& dataset,
                                                const OperationProfile& profile) {
        map<string, PerformanceMetrics> results;

        updateProgress(0, "Starting benchmark suite");
        
        try {
            updateProgress(10, "Testing BST");
            results["BST"] = testBST(dataset, profile);
        } catch (const exception& e) {
            cerr << "BST failed: " << e.what() << endl;
        }

        try {
            updateProgress(40, "Testing HashMap");
            results["HashMap"] = testHashMap(dataset, profile);
        } catch (const exception& e) {
            cerr << "HashMap failed: " << e.what() << endl;
        }

        try {
            updateProgress(70, "Testing Heap");
            results["Heap"] = testHeap(dataset, profile);
        } catch (const exception& e) {
            cerr << "Heap failed: " << e.what() << endl;
        }

        try {
            updateProgress(85, "Testing Graph");
            results["Graph"] = testGraph(dataset, profile);
        } catch (const exception& e) {
            cerr << "Graph failed: " << e.what() << endl;
        }

        updateProgress(100, "All tests complete");
        return results;
    }

    // save results to CSV
    bool saveResults(const string& filename,
                     const map<string, PerformanceMetrics>& results) {
        ofstream file(filename);
        if (!file.is_open()) {
            cerr << "Error: Cannot open " << filename << endl;
            return false;
        }

        file << "Structure,DataSize,InsertTime(ms),SearchTime(ms),DeleteTime(ms),"
             << "TotalTime(ms),MemoryUsed(bytes),MemoryPerElement(bytes)\n";

        for (const auto& pair : results) {
            file << pair.second.toCSV() << "\n";
        }

        file.close();
        return true;
    }

    // generate report as string (for GUI)
    string generateReportString(const map<string, PerformanceMetrics>& results) {
        string report = "\nPerformance Comparison:\n";

        for (const auto& pair : results) {
            report += pair.second.toString() + "\n";
        }

        // find winners
        string fastInsert, fastSearch, fastDelete, lowMemory;
        double minInsert = numeric_limits<double>::max();
        double minSearch = numeric_limits<double>::max();
        double minDelete = numeric_limits<double>::max();
        size_t minMemory = numeric_limits<size_t>::max();

        for (const auto& pair : results) {
            if (pair.second.insertTime > 0 && pair.second.insertTime < minInsert) {
                minInsert = pair.second.insertTime;
                fastInsert = pair.first;
            }
            if (pair.second.searchTime > 0 && pair.second.searchTime < minSearch) {
                minSearch = pair.second.searchTime;
                fastSearch = pair.first;
            }
            if (pair.second.deleteTime > 0 && pair.second.deleteTime < minDelete) {
                minDelete = pair.second.deleteTime;
                fastDelete = pair.first;
            }
            if (pair.second.memoryUsed > 0 && pair.second.memoryUsed < minMemory) {
                minMemory = pair.second.memoryUsed;
                lowMemory = pair.first;
            }
        }

        report += "\nWinners:\n";
        report += "  Fastest Insert: " + fastInsert + " (" + to_string(minInsert) + " ms)\n";
        report += "  Fastest Search: " + fastSearch + " (" + to_string(minSearch) + " ms)\n";
        report += "  Fastest Delete: " + fastDelete + " (" + to_string(minDelete) + " ms)\n";
        report += "  Least Memory: " + lowMemory + " (" + to_string(minMemory) + " bytes)\n";

        return report;
    }

    // get winner for specific metric
    string getWinner(const map<string, PerformanceMetrics>& results, const string& metric) {
        string winner;
        double minValue = numeric_limits<double>::max();

        for (const auto& pair : results) {
            double value = 0;
            if (metric == "insert") value = pair.second.insertTime;
            else if (metric == "search") value = pair.second.searchTime;
            else if (metric == "delete") value = pair.second.deleteTime;
            else if (metric == "memory") value = pair.second.memoryUsed;
            else if (metric == "total") value = pair.second.totalTime;

            if (value > 0 && value < minValue) {
                minValue = value;
                winner = pair.first;
            }
        }
        return winner;
    }

private:
    mt19937 rng;
    ProgressCallback progressCallback;
};

// specialization for strings (includes Trie)
template<>
class Benchmark<string> {
public:
    struct OperationProfile {
        int searchPercent, insertPercent, deletePercent, totalOperations;

        OperationProfile(int s, int i, int d, int t)
            : searchPercent(s), insertPercent(i), deletePercent(d), totalOperations(t) {
            if (s + i + d != 100) throw invalid_argument("Must sum to 100");
            if (t <= 0) throw invalid_argument("Must be positive");
        }

        int getSearchCount() const { return (totalOperations * searchPercent) / 100; }
        int getInsertCount() const { return (totalOperations * insertPercent) / 100; }
        int getDeleteCount() const { return (totalOperations * deletePercent) / 100; }



        string toString() const {
            return "\nOperation Profile:\n  Search: " + to_string(searchPercent) + "% (" +
                   to_string(getSearchCount()) + " ops)\n  Insert: " + to_string(insertPercent) +
                   "% (" + to_string(getInsertCount()) + " ops)\n  Delete: " +
                   to_string(deletePercent) + "% (" + to_string(getDeleteCount()) + " ops)\n";
        }
    };

    using ProgressCallback = function<void(int, const string&)>;

    Benchmark() : progressCallback(nullptr) {
        random_device rd;
        rng.seed(rd());
    }

    void setProgressCallback(ProgressCallback cb) { progressCallback = cb; }

    template<typename Func>
    double measureTime(Func f) {
        auto start = high_resolution_clock::now();
        f();
        auto end = high_resolution_clock::now();
        return duration<double, milli>(end - start).count();
    }

    vector<string> generateRandomKeys(const vector<string>& data, int cnt) {
        vector<string> keys;
        uniform_int_distribution<int> dist(0, data.size() - 1);
        for (int i = 0; i < cnt; i++)
            keys.push_back(data[dist(rng)]);
        return keys;
    }

    vector<string> generateNewValues(int cnt) {
        vector<string> vals;
        for (int i = 0; i < cnt; i++)
            vals.push_back("gen_" + to_string(i + 1000000));
        return vals;
    }

    void updateProgress(int pct, const string& msg) {
        if (progressCallback) progressCallback(pct, msg);
    }

    // BST, Heap, HashMap tests - same structure as template version
    PerformanceMetrics testBST(const vector<string>& data, const OperationProfile& prof) {
        PerformanceMetrics m("BST");
        m.dataSize = data.size();
        BST<string> bst;

        m.insertTime = measureTime([&]() {
            for (const auto& v : data) bst.insert(v);
        });
        m.insertCount = data.size();

        int sCnt = prof.getSearchCount();
        if (sCnt > 0) {
            auto keys = generateRandomKeys(data, sCnt);
            m.searchTime = measureTime([&]() {
                for (const auto& k : keys) bst.searchValue(k);
            });
            m.searchCount = sCnt;
        }

        int iCnt = prof.getInsertCount();
        if (iCnt > 0) {
            auto vals = generateNewValues(iCnt);
            double t = measureTime([&]() {
                for (const auto& v : vals) bst.insert(v);
            });
            m.insertTime += t;
            m.insertCount += iCnt;
        }

        int dCnt = prof.getDeleteCount();
        if (dCnt > 0) {
            auto keys = generateRandomKeys(data, dCnt);
            m.deleteTime = measureTime([&]() {
                for (const auto& k : keys) bst.remove(k);
            });
            m.deleteCount = dCnt;
        }

        m.memoryUsed = bst.countNodes() * (sizeof(string) + 2*sizeof(void*) + sizeof(int));
        m.totalTime = m.insertTime + m.searchTime + m.deleteTime;
        return m;
    }

    PerformanceMetrics testHeap(const vector<string>& data, const OperationProfile& prof) {
        PerformanceMetrics m("Heap");
        m.dataSize = data.size();
        Heap<string> heap(false);

        m.insertTime = measureTime([&]() {
            for (const auto& v : data) heap.insert(v);
        });
        m.insertCount = data.size();

        int sCnt = prof.getSearchCount();
        if (sCnt > 0) {
            auto keys = generateRandomKeys(data, sCnt);
            m.searchTime = measureTime([&]() {
                for (const auto& k : keys) heap.search(k);
            });
            m.searchCount = sCnt;
        }

        int iCnt = prof.getInsertCount();
        if (iCnt > 0) {
            auto vals = generateNewValues(iCnt);
            double t = measureTime([&]() {
                for (const auto& v : vals) heap.insert(v);
            });
            m.insertTime += t;
            m.insertCount += iCnt;
        }

        int dCnt = prof.getDeleteCount();
        if (dCnt > 0) {
            auto keys = generateRandomKeys(data, dCnt);
            m.deleteTime = measureTime([&]() {
                for (const auto& k : keys) heap.removeValue(k);
            });
            m.deleteCount = dCnt;
        }

        m.memoryUsed = heap.size() * sizeof(string);
        m.totalTime = m.insertTime + m.searchTime + m.deleteTime;
        return m;
    }

    PerformanceMetrics testHashMap(const vector<string>& data, const OperationProfile& prof) {
        PerformanceMetrics m("HashMap");
        m.dataSize = data.size();
        HashMap<string, string> map;

        m.insertTime = measureTime([&]() {
            for (const auto& v : data) map.insert(v, v);
        });
        m.insertCount = data.size();

        int sCnt = prof.getSearchCount();
        if (sCnt > 0) {
            auto keys = generateRandomKeys(data, sCnt);
            m.searchTime = measureTime([&]() {
                for (const auto& k : keys) map.search(k);
            });
            m.searchCount = sCnt;
        }

        int iCnt = prof.getInsertCount();
        if (iCnt > 0) {
            auto vals = generateNewValues(iCnt);
            double t = measureTime([&]() {
                for (const auto& v : vals) map.insert(v, v);
            });
            m.insertTime += t;
            m.insertCount += iCnt;
        }

        int dCnt = prof.getDeleteCount();
        if (dCnt > 0) {
            auto keys = generateRandomKeys(data, dCnt);
            m.deleteTime = measureTime([&]() {
                for (const auto& k : keys) map.remove(k);
            });
            m.deleteCount = dCnt;
        }

        int elem = map.getSize();
        int buck = map.getCapacity();
        m.memoryUsed = (buck * sizeof(void*)) + (elem * (2*sizeof(string) + sizeof(void*)));
        m.totalTime = m.insertTime + m.searchTime + m.deleteTime;
        return m;
    }

    PerformanceMetrics testTrie(const vector<string>& data, const OperationProfile& prof) {
        PerformanceMetrics m("Trie");
        m.dataSize = data.size();
        Trie trie;

        m.insertTime = measureTime([&]() {
            for (const auto& v : data) trie.insert(v);
        });
        m.insertCount = data.size();

        int sCnt = prof.getSearchCount();
        if (sCnt > 0) {
            auto keys = generateRandomKeys(data, sCnt);
            m.searchTime = measureTime([&]() {
                for (const auto& k : keys) trie.search(k);
            });
            m.searchCount = sCnt;
        }

        int iCnt = prof.getInsertCount();
        if (iCnt > 0) {
            auto vals = generateNewValues(iCnt);
            double t = measureTime([&]() {
                for (const auto& v : vals) trie.insert(v);
            });
            m.insertTime += t;
            m.insertCount += iCnt;
        }

        int dCnt = prof.getDeleteCount();
        if (dCnt > 0) {
            auto keys = generateRandomKeys(data, dCnt);
            m.deleteTime = measureTime([&]() {
                for (const auto& k : keys) trie.remove(k);
            });
            m.deleteCount = dCnt;
        }

        m.memoryUsed = trie.estimateMemory();
        m.totalTime = m.insertTime + m.searchTime + m.deleteTime;
        return m;
    }

    PerformanceMetrics testGraph(const vector<string>& data, const OperationProfile& prof) {
        PerformanceMetrics m("Graph");
        m.dataSize = data.size();
        Graph<string> graph(false);  // undirected graph

        m.insertTime = measureTime([&]() {
            // Insert vertices
            for (const auto& v : data) graph.insert(v);
            // Create edges between consecutive elements
            for (size_t i = 1; i < data.size(); i++) {
                graph.insert(data[i-1], data[i]);
            }
        });
        m.insertCount = data.size();

        int sCnt = prof.getSearchCount();
        if (sCnt > 0) {
            auto keys = generateRandomKeys(data, sCnt);
            m.searchTime = measureTime([&]() {
                for (const auto& k : keys) graph.search(k);
            });
            m.searchCount = sCnt;
        }

        int iCnt = prof.getInsertCount();
        if (iCnt > 0) {
            auto vals = generateNewValues(iCnt);
            double t = measureTime([&]() {
                for (const auto& v : vals) graph.insert(v);
            });
            m.insertTime += t;
            m.insertCount += iCnt;
        }

        int dCnt = prof.getDeleteCount();
        if (dCnt > 0) {
            auto keys = generateRandomKeys(data, dCnt);
            m.deleteTime = measureTime([&]() {
                for (const auto& k : keys) graph.remove(k);
            });
            m.deleteCount = dCnt;
        }

        int vertices = graph.getVertexCount();
        int edges = graph.getEdgeCount();
        m.memoryUsed = vertices * (sizeof(string) + sizeof(vector<void*>)) + 
                       edges * (sizeof(string) + sizeof(double));
        m.totalTime = m.insertTime + m.searchTime + m.deleteTime;
        return m;
    }

    map<string, PerformanceMetrics> runAllTests(const vector<string>& data, const OperationProfile& prof) {
        map<string, PerformanceMetrics> results;

        try { results["BST"] = testBST(data, prof); }
        catch (const exception& e) { cerr << "BST failed: " << e.what() << endl; }

        try { results["HashMap"] = testHashMap(data, prof); }
        catch (const exception& e) { cerr << "HashMap failed: " << e.what() << endl; }

        try { results["Heap"] = testHeap(data, prof); }
        catch (const exception& e) { cerr << "Heap failed: " << e.what() << endl; }

        try { results["Trie"] = testTrie(data, prof); }
        catch (const exception& e) { cerr << "Trie failed: " << e.what() << endl; }

        try { results["Graph"] = testGraph(data, prof); }
        catch (const exception& e) { cerr << "Graph failed: " << e.what() << endl; }

        return results;
    }

    bool saveResults(const string& file, const map<string, PerformanceMetrics>& res) {
        ofstream f(file);
        if (!f.is_open()) return false;
        f << "Structure,DataSize,InsertTime(ms),SearchTime(ms),DeleteTime(ms),"
          << "TotalTime(ms),MemoryUsed(bytes),MemoryPerElement(bytes)\n";
        for (const auto& p : res) f << p.second.toCSV() << "\n";
        f.close();
        return true;
    }


    string generateReportString(const map<string, PerformanceMetrics>& res) {
        string r = "\nPerformance Comparison:\n";
        for (const auto& p : res) r += p.second.toString() + "\n";
        return r;
    }

    string getWinner(const map<string, PerformanceMetrics>& res, const string& metric) {
        string winner;
        double minVal = numeric_limits<double>::max();
        for (const auto& p : res) {
            double v = 0;
            if (metric == "insert") v = p.second.insertTime;
            else if (metric == "search") v = p.second.searchTime;
            else if (metric == "delete") v = p.second.deleteTime;
            else if (metric == "memory") v = p.second.memoryUsed;
            if (v > 0 && v < minVal) { minVal = v; winner = p.first; }
        }
        return winner;
    }
private:
    mt19937 rng;
    ProgressCallback progressCallback;
};
#endif
