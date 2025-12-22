


// #include "PerformanceMetrics.h"
// #include <iostream>
// using namespace std;

// void PerformanceMetrics::print() const {
//     cout << "Insert Time: " << insertTime << " ms\n";
//     cout << "Search Time: " << searchTime << " ms\n";
//     cout << "Delete Time: " << deleteTime << " ms\n";
//     cout << "Memory Used: " << memoryUsed << " bytes\n";
//     cout << "Total Ops: " << operationsCount << "\n";
//     cout << "Avg Time per Operation: " << avgOperationTime << " ms\n";
// }

// double PerformanceMetrics::calculateScore(const Weights& w) const {
//     double score = 0.0;

//     score += w.insertWeight * insertTime;
//     score += w.searchWeight * searchTime;
//     score += w.deleteWeight * deleteTime;
//     score += w.memoryWeight * memoryUsed;

//     return score;
// }
