#ifndef RECOMMENDATIONENGINE_H
#define RECOMMENDATIONENGINE_H

#include "PerformanceMetrics.h"
#include "DataAnalyzer.h"
#include <map>
#include <vector>
#include <string>
#include <algorithm>
#include <sstream>
#include <iomanip>
#include <cmath>


using namespace std;

class RecommendationEngine {
public:
    // ================= WEIGHTS =================
    struct Weights {
        double timeWeight;
        double spaceWeight;
        double suitabilityWeight;

        Weights(double t = 0.5, double s = 0.3, double suit = 0.2)
            : timeWeight(t), spaceWeight(s), suitabilityWeight(suit) {
            // normalize if sum != 1.0
            double sum = t + s + suit;
            if (sum != 1.0) {
                timeWeight /= sum;
                spaceWeight /= sum;
                suitabilityWeight /= sum;
            }
        }

        void print() const {
            cout << "Weights: Time=" << timeWeight
                 << ", Space=" << spaceWeight
                 << ", Suitability=" << suitabilityWeight << "\n";
        }
    };

    // ================= OPERATION PROFILE =================
    struct OperationProfile {
        int searchPercent;
        int insertPercent;
        int deletePercent;

        OperationProfile(int s = 33, int i = 33, int d = 34)
            : searchPercent(s), insertPercent(i), deletePercent(d) {}
    };

    // ================= STRUCTURE SCORE =================
    struct StructureScore {
        string name;
        double totalScore;
        double timeScore;
        double spaceScore;
        double suitabilityScore;
        string reasoning;

        StructureScore(string n = "Unknown")
            : name(n), totalScore(0.0), timeScore(0.0),
            spaceScore(0.0), suitabilityScore(0.0), reasoning("") {}

        void print() const {
            cout << "\n=== " << name << " Score ===\n";
            cout << "Total Score: " << fixed << setprecision(2) << totalScore << "/100\n";
            cout << "  Time Score: " << timeScore << "/100\n";
            cout << "  Space Score: " << spaceScore << "/100\n";
            cout << "  Suitability: " << suitabilityScore << "/100\n";
            cout << "Reasoning: " << reasoning << "\n";
        }

        string toString() const {
            stringstream ss;
            ss << fixed << setprecision(2);
            ss << "\n=== " << name << " Score ===\n";
            ss << "Total Score: " << totalScore << "/100\n";
            ss << "  Time Score: " << timeScore << "/100\n";
            ss << "  Space Score: " << spaceScore << "/100\n";
            ss << "  Suitability: " << suitabilityScore << "/100\n";
            ss << "Reasoning: " << reasoning << "\n";
            return ss.str();
        }
    };

    // ================= CONSTRUCTOR =================
    RecommendationEngine() : defaultWeights(0.5, 0.3, 0.2) {}

    // ================= MAIN RANKING FUNCTION =================
    vector<StructureScore> rankStructures(
        const map<string, PerformanceMetrics>& results,
        const DataAnalyzer::DataProfile& dataProfile,
        const OperationProfile& opProfile,
        const Weights& weights = Weights()
        ) {
        vector<StructureScore> scores;

        for (const auto& pair : results) {
            StructureScore score(pair.first);

            // calculate individual scores
            score.timeScore = calculateTimeScore(pair.second, opProfile);
            score.spaceScore = calculateSpaceScore(pair.second, dataProfile);
            score.suitabilityScore = calculateSuitability(pair.first, dataProfile, opProfile);

            // calculate weighted total
            score.totalScore = (score.timeScore * weights.timeWeight) +
                               (score.spaceScore * weights.spaceWeight) +
                               (score.suitabilityScore * weights.suitabilityWeight);

            // generate reasoning
            score.reasoning = generateReasoning(pair.first, score, pair.second, dataProfile, opProfile);

            scores.push_back(score);
        }

        // sort by total score (descending)
        sort(scores.begin(), scores.end(),
             [](const StructureScore& a, const StructureScore& b) {
                 return a.totalScore > b.totalScore;
             });

        return scores;
    }

    // ================= TIME SCORE =================
    double calculateTimeScore(const PerformanceMetrics& metrics,
                              const OperationProfile& profile) {
        // weighted average of operation times
        double weightedTime = 0.0;
        double totalWeight = 0.0;

        if (metrics.insertCount > 0 && profile.insertPercent > 0) {
            double avgInsert = metrics.getAverageInsertTime();
            weightedTime += avgInsert * profile.insertPercent;
            totalWeight += profile.insertPercent;
        }

        if (metrics.searchCount > 0 && profile.searchPercent > 0) {
            double avgSearch = metrics.getAverageSearchTime();
            weightedTime += avgSearch * profile.searchPercent;
            totalWeight += profile.searchPercent;
        }

        if (metrics.deleteCount > 0 && profile.deletePercent > 0) {
            double avgDelete = metrics.getAverageDeleteTime();
            weightedTime += avgDelete * profile.deletePercent;
            totalWeight += profile.deletePercent;
        }

        if (totalWeight == 0) return 50.0;

        double avgTime = weightedTime / totalWeight;

        // convert to score (lower time = higher score)
        // using exponential decay: score = 100 * e^(-k*time)
        double k = 0.5; // tuning parameter
        double score = 100.0 * exp(-k * avgTime);

        return min(100.0, max(0.0, score));
    }

    // ================= SPACE SCORE =================
    double calculateSpaceScore(const PerformanceMetrics& metrics,
                               const DataAnalyzer::DataProfile& profile) {
        double memPerElement = metrics.getMemoryPerElement();

        // base score
        double score = 100.0;

        // penalize based on memory usage
        // typical ranges: 8-16 bytes for simple structures, 40+ for complex ones
        if (memPerElement < 20) {
            score = 100.0;
        } else if (memPerElement < 50) {
            score = 90.0 - (memPerElement - 20);
        } else if (memPerElement < 100) {
            score = 60.0 - (memPerElement - 50) * 0.5;
        } else {
            score = max(0.0, 35.0 - (memPerElement - 100) * 0.2);
        }

        // adjust for memory constraints
        if (profile.memoryConstrained) {
            score *= 1.2; // boost importance
        }

        return min(100.0, max(0.0, score));
    }

    // ================= SUITABILITY SCORE =================
    double calculateSuitability(const string& structureName,
                                const DataAnalyzer::DataProfile& profile,
                                const OperationProfile& opProfile) {
        double score = 50.0; // base score

        if (structureName == "HashMap") {
            // HashMap excels at fast lookups
            if (opProfile.searchPercent > 60) score += 25;
            else if (opProfile.searchPercent > 40) score += 15;

            // good for unsorted data
            if (!profile.isSorted) score += 10;

            // not ideal for range queries
            if (profile.needsRangeQueries) score -= 20;

            // excellent for key-value pairs
            if (profile.dataSize > 1000) score += 10;

            // good for random access
            if (!profile.hasPattern) score += 5;
        }
        else if (structureName == "BST") {
            // BST is good for sorted operations
            if (profile.isSorted) score += 20;

            // excellent for range queries
            if (profile.needsRangeQueries) score += 30;

            // good for moderate searches
            if (opProfile.searchPercent > 40 && opProfile.searchPercent < 80) score += 15;

            // maintains order
            if (profile.hasPattern) score += 10;

            // balanced performance
            if (opProfile.searchPercent + opProfile.insertPercent > 60) score += 5;
        }
        else if (structureName == "Trie") {
            // Trie is specialized for strings
            if (profile.dataType == "string") score += 30;
            else score -= 30; // heavily penalize for non-strings

            // excellent for prefix searches
            if (profile.needsPrefixSearch) score += 40;

            // good for shorter strings
            if (profile.averageStringLength < 15) score += 10;
            else if (profile.averageStringLength > 30) score -= 10;

            // memory intensive for large datasets
            if (profile.dataSize > 10000) score -= 10;
        }
        else if (structureName == "Heap") {
            // Heap is for priority operations
            if (profile.needsPriorityQueue) score += 50;

            // good for extracting min/max
            if (opProfile.deletePercent > 30) score += 15;

            // not good for general searches
            if (opProfile.searchPercent > 50) score -= 25;

            // efficient insertions
            if (opProfile.insertPercent > 40) score += 10;

            // memory efficient
            if (profile.memoryConstrained) score += 15;
        }
        else if (structureName == "Graph") {
            // Graph is for relationship/network data
            if (profile.hasRelationships) score += 40;

            // good for connectivity problems
            if (profile.needsConnectivity) score += 35;

            // flexible for various operations
            if (opProfile.insertPercent > 30 && opProfile.searchPercent > 30) score += 15;

            // more memory intensive
            if (profile.memoryConstrained) score -= 15;

            // good for larger datasets with relationships
            if (profile.dataSize > 100) score += 10;
        }

        // general adjustments
        if (profile.speedCritical && score > 70) score += 5;
        if (profile.memoryConstrained && structureName != "Heap") score -= 5;

        return min(100.0, max(0.0, score));
    }

    // ================= GENERATE REASONING =================
    string generateReasoning(const string& structureName,
                             const StructureScore& score,
                             const PerformanceMetrics& metrics,
                             const DataAnalyzer::DataProfile& profile,
                             const OperationProfile& opProfile) {
        stringstream ss;

        // performance summary
        ss << structureName << " achieved ";
        if (score.totalScore >= 80) ss << "excellent";
        else if (score.totalScore >= 60) ss << "good";
        else if (score.totalScore >= 40) ss << "moderate";
        else ss << "poor";
        ss << " overall performance. ";

        // time analysis
        if (score.timeScore >= 70) {
            ss << "Fast operation times. ";
        } else if (score.timeScore < 40) {
            ss << "Slower operation times. ";
        }

        // memory analysis
        if (score.spaceScore >= 70) {
            ss << "Memory efficient. ";
        } else if (score.spaceScore < 40) {
            ss << "Higher memory usage. ";
        }

        // suitability analysis
        if (structureName == "HashMap") {
            if (opProfile.searchPercent > 60) {
                ss << "Ideal for search-heavy workloads. ";
            }
            if (profile.needsRangeQueries) {
                ss << "Not suitable for range queries. ";
            }
        }
        else if (structureName == "BST") {
            if (profile.needsRangeQueries) {
                ss << "Perfect for range queries. ";
            }
            if (profile.isSorted) {
                ss << "Works well with sorted data. ";
            }
        }
        else if (structureName == "Trie") {
            if (profile.dataType == "string") {
                ss << "Optimized for string operations. ";
            }
            if (profile.needsPrefixSearch) {
                ss << "Excellent for prefix searches. ";
            }
        }
        else if (structureName == "Heap") {
            if (profile.needsPriorityQueue) {
                ss << "Perfect for priority queue operations. ";
            }
            if (opProfile.searchPercent > 50) {
                ss << "Not ideal for frequent searches. ";
            }
        }
        else if (structureName == "Graph") {
            if (profile.hasRelationships) {
                ss << "Ideal for relationship/network data. ";
            }
            if (profile.needsConnectivity) {
                ss << "Perfect for connectivity and path finding. ";
            }
            if (profile.memoryConstrained) {
                ss << "Consider memory usage for large graphs. ";
            }
        }

        return ss.str();
    }

    // ================= GENERATE RECOMMENDATION =================
    string generateRecommendation(const vector<StructureScore>& scores) {
        if (scores.empty()) {
            return "No data structures were tested.";
        }

        stringstream ss;
        ss << fixed << setprecision(2);

        const StructureScore& winner = scores[0];

        ss << "\n╔════════════════════════════════════════════════╗\n";
        ss << "║         RECOMMENDATION REPORT                  ║\n";
        ss << "╚════════════════════════════════════════════════╝\n\n";

        ss << "RECOMMENDED DATA STRUCTURE: " << winner.name << "\n";
        ss << "   Overall Score: " << winner.totalScore << "/100\n\n";

        ss << "SCORE BREAKDOWN:\n";
        ss << "   • Time Efficiency:  " << winner.timeScore << "/100\n";
        ss << "   • Space Efficiency: " << winner.spaceScore << "/100\n";
        ss << "   • Suitability:      " << winner.suitabilityScore << "/100\n\n";

        ss << "RATIONALE:\n";
        ss << "   " << winner.reasoning << "\n\n";

        if (scores.size() > 1) {
            ss << "ALTERNATIVES:\n";
            for (size_t i = 1; i < min(size_t(3), scores.size()); i++) {
                ss << "   " << (i+1) << ". " << scores[i].name
                   << " (Score: " << scores[i].totalScore << "/100)\n";
                ss << "      → " << scores[i].reasoning << "\n";
            }
        }

        ss << "\n" << explainChoice(winner);

        return ss.str();
    }

    // ================= EXPLAIN CHOICE =================
    string explainChoice(const StructureScore& winner) {
        stringstream ss;

        ss << "WHY " << winner.name << "?\n\n";

        if (winner.name == "HashMap") {
            ss << "HashMap provides:\n";
            ss << "• O(1) average-case search, insert, and delete\n";
            ss << "• Excellent for key-value lookups\n";
            ss << "• Best when order doesn't matter\n";
            ss << "• Use when: Fast lookups are critical\n";
        }
        else if (winner.name == "BST") {
            ss << "Binary Search Tree provides:\n";
            ss << "• O(log n) operations (when balanced)\n";
            ss << "• Maintains sorted order\n";
            ss << "• Supports range queries efficiently\n";
            ss << "• Use when: You need sorted data or ranges\n";
        }
        else if (winner.name == "Trie") {
            ss << "Trie provides:\n";
            ss << "• O(m) operations where m = string length\n";
            ss << "• Excellent for prefix matching\n";
            ss << "• Perfect for autocomplete features\n";
            ss << "• Use when: Working with strings and prefixes\n";
        }
        else if (winner.name == "Heap") {
            ss << "Heap provides:\n";
            ss << "• O(log n) insert and extract-min/max\n";
            ss << "• O(1) peek at min/max element\n";
            ss << "• Perfect for priority queues\n";
            ss << "• Use when: Need min/max element frequently\n";
        }
        else if (winner.name == "Graph") {
            ss << "Graph provides:\n";
            ss << "• O(1) to O(V+E) operations depending on query\n";
            ss << "• Models relationships between entities\n";
            ss << "• Supports BFS, DFS, shortest path algorithms\n";
            ss << "• Use when: Data has connections/relationships\n";
        }

        return ss.str();
    }

    // ================= COMPARE TWO STRUCTURES =================
    string compareStructures(const StructureScore& s1, const StructureScore& s2) {
        stringstream ss;
        ss << fixed << setprecision(2);

        ss << "\nCOMPARISON: " << s1.name << " vs " << s2.name << "\n\n";

        ss << "Overall Scores:\n";
        ss << "  " << s1.name << ": " << s1.totalScore << "/100\n";
        ss << "  " << s2.name << ": " << s2.totalScore << "/100\n";
        ss << "  Winner: " << (s1.totalScore > s2.totalScore ? s1.name : s2.name) << "\n\n";

        ss << "Time Efficiency:\n";
        ss << "  " << s1.name << ": " << s1.timeScore << "/100\n";
        ss << "  " << s2.name << ": " << s2.timeScore << "/100\n";
        ss << "  Winner: " << (s1.timeScore > s2.timeScore ? s1.name : s2.name) << "\n\n";

        ss << "Space Efficiency:\n";
        ss << "  " << s1.name << ": " << s1.spaceScore << "/100\n";
        ss << "  " << s2.name << ": " << s2.spaceScore << "/100\n";
        ss << "  Winner: " << (s1.spaceScore > s2.spaceScore ? s1.name : s2.name) << "\n\n";

        ss << "Suitability:\n";
        ss << "  " << s1.name << ": " << s1.suitabilityScore << "/100\n";
        ss << "  " << s2.name << ": " << s2.suitabilityScore << "/100\n";
        ss << "  Winner: " << (s1.suitabilityScore > s2.suitabilityScore ? s1.name : s2.name) << "\n";

        return ss.str();
    }

    // ================= SUGGEST WEIGHTS =================
    Weights suggestWeights(const DataAnalyzer::DataProfile& profile) {
        if (profile.speedCritical) {
            return Weights(0.7, 0.2, 0.1); // prioritize speed
        }
        else if (profile.memoryConstrained) {
            return Weights(0.3, 0.6, 0.1); // prioritize memory
        }
        else {
            return Weights(0.4, 0.3, 0.3); // balanced
        }
    }

private:
    Weights defaultWeights;
};

#endif
