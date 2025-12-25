#ifndef PERFORMANCEMETRICS_H
#define PERFORMANCEMETRICS_H

#include <cstddef>
#include <iostream>
#include <cstddef>
#include <iostream>
#include <string>
#include <sstream>
#include <locale>
#include <iomanip>

using namespace std;

class PerformanceMetrics {
public:
    // timing data in milliseconds
    double insertTime;
    double searchTime;
    double deleteTime;
    double totalTime;

    // operation counts
    int insertCount;
    int searchCount;
    int deleteCount;

    // memory usage in bytes
    size_t memoryUsed;

    // metadata
    string structureName;
    int dataSize;
    double score; // Stored score from recommendation engine

    // constructor
    PerformanceMetrics(string name = "Unknown") : structureName(name) {
        insertTime = searchTime = deleteTime = totalTime = 0.0;
        insertCount = searchCount = deleteCount = 0;
        memoryUsed = 0;
        dataSize = 0;
        score = 0.0;
    }

    // calculate average times
    double getAverageInsertTime() const {
        return insertCount > 0 ? insertTime / insertCount : 0.0;
    }

    double getAverageSearchTime() const {
        return searchCount > 0 ? searchTime / searchCount : 0.0;
    }

    double getAverageDeleteTime() const {
        return deleteCount > 0 ? deleteTime / deleteCount : 0.0;
    }

    // operations per second
    double getInsertThroughput() const {
        return insertTime > 0 ? (insertCount / insertTime) * 1000.0 : 0.0;
    }

    double getSearchThroughput() const {
        return searchTime > 0 ? (searchCount / searchTime) * 1000.0 : 0.0;
    }

    double getDeleteThroughput() const {
        return deleteTime > 0 ? (deleteCount / deleteTime) * 1000.0 : 0.0;
    }

    // memory per element
    double getMemoryPerElement() const {
        return dataSize > 0 ? static_cast<double>(memoryUsed) / dataSize : 0.0;
    }

    // print report to console


    // convert to string for GUI display
    string toString() const {
        string result = "\n" + structureName + " Performance Report:\n";
        result += "Dataset: " + to_string(dataSize) + " elements\n";
        result += "Total Time: " + to_string(totalTime) + " ms\n";
        result += "Memory: " + to_string(memoryUsed) + " bytes (" +
                  to_string(memoryUsed / 1024.0) + " KB)\n";

        if (insertCount > 0) {
            result += "\nInsert: " + to_string(insertCount) + " ops, " +
                      to_string(insertTime) + " ms (" +
                      to_string(getAverageInsertTime()) + " ms/op)\n";
        }

        if (searchCount > 0) {
            result += "Search: " + to_string(searchCount) + " ops, " +
                      to_string(searchTime) + " ms (" +
                      to_string(getAverageSearchTime()) + " ms/op)\n";
        }

        if (deleteCount > 0) {
            result += "Delete: " + to_string(deleteCount) + " ops, " +
                      to_string(deleteTime) + " ms (" +
                      to_string(getAverageDeleteTime()) + " ms/op)\n";
        }

        result += "Memory/element: " + to_string(getMemoryPerElement()) + " bytes\n";
        return result;
    }

    // export to CSV format
    string toCSV() const {
        std::stringstream ss;
        ss.imbue(std::locale::classic()); // Force C locale (dot for decimals)
        ss << structureName << ","
           << dataSize << ","
           << insertTime << ","
           << searchTime << ","
           << deleteTime << ","
           << totalTime << ","
           << memoryUsed << ","
           << getMemoryPerElement() << ","
           << score; // Export Score
        return ss.str();
    }
};

#endif
