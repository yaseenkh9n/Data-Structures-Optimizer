#ifndef DATAANALYZER_H
#define DATAANALYZER_H

#include <vector>
#include <set>
#include <numeric>
#include <algorithm>
#include <string>
#include <iostream>

class DataAnalyzer {
public:

    // ================= DATA PROFILE =================
    struct DataProfile {
        size_t dataSize;
        std::string dataType;
        bool isSorted;
        bool hasPattern;
        size_t uniqueElements;
        bool hasDuplicates;
        double averageValue;
        double averageStringLength;

        // user intent flags
        bool needsRangeQueries;
        bool needsPrefixSearch;
        bool needsPriorityQueue;
        bool memoryConstrained;
        bool speedCritical;

        // graph-related flags
        bool hasRelationships;
        bool needsConnectivity;
    };

    // ================= INTEGER DATA =================
    DataProfile analyzeIntegerData(const std::vector<int>& data) {
        DataProfile profile{};
        profile.dataSize = data.size();
        profile.dataType = "integer";

        if (data.empty()) {
            return profile;
        }

        profile.isSorted = isSorted(data);
        profile.hasPattern = hasSequentialPattern(data);
        profile.uniqueElements = countUnique(data);
        profile.hasDuplicates = (profile.uniqueElements < profile.dataSize);

        double sum = std::accumulate(data.begin(), data.end(), 0.0);
        profile.averageValue = sum / data.size();
        profile.averageStringLength = 0;

        initUserFlags(profile);
        return profile;
    }

    // ================= STRING DATA =================
    DataProfile analyzeStringData(const std::vector<std::string>& data) {
        DataProfile profile{};
        profile.dataSize = data.size();
        profile.dataType = "string";

        if (data.empty()) {
            return profile;
        }

        profile.isSorted = isSorted(data);
        profile.uniqueElements = countUnique(data);
        profile.hasDuplicates = (profile.uniqueElements < profile.dataSize);

        double totalLength = 0;
        for (const auto& str : data) {
            totalLength += str.length();
        }
        profile.averageStringLength = totalLength / data.size();
        profile.averageValue = profile.averageStringLength;

        // pattern: same starting character
        profile.hasPattern = false;
        if (!data[0].empty()) {
            char firstChar = data[0][0];
            bool sameStart = true;
            for (const auto& str : data) {
                if (str.empty() || str[0] != firstChar) {
                    sameStart = false;
                    break;
                }
            }
            profile.hasPattern = sameStart;
        }

        initUserFlags(profile);
        return profile;
    }

    // ================= DOUBLE DATA =================
    DataProfile analyzeDoubleData(const std::vector<double>& data) {
        DataProfile profile{};
        profile.dataSize = data.size();
        profile.dataType = "double";

        if (data.empty()) {
            return profile;
        }

        profile.isSorted = isSorted(data);
        profile.hasPattern = hasSequentialPattern(data);
        profile.uniqueElements = countUnique(data);
        profile.hasDuplicates = (profile.uniqueElements < profile.dataSize);

        double sum = std::accumulate(data.begin(), data.end(), 0.0);
        profile.averageValue = sum / data.size();
        profile.averageStringLength = 0;

        initUserFlags(profile);
        return profile;
    }

    // ================= PRINT =================


    // ================= TO STRING =================
    std::string profileToString(const DataProfile& profile) {
        std::string out;
        out += "=== Data Profile ===\n";
        out += "Size: " + std::to_string(profile.dataSize) + "\n";
        out += "Type: " + profile.dataType + "\n";
        out += "Sorted: " + std::string(profile.isSorted ? "Yes\n" : "No\n");
        out += "Has Pattern: " + std::string(profile.hasPattern ? "Yes\n" : "No\n");
        out += "Unique Elements: " + std::to_string(profile.uniqueElements) + "\n";
        out += "Has Duplicates: " + std::string(profile.hasDuplicates ? "Yes\n" : "No\n");

        if (profile.dataType != "string") {
            out += "Average Value: " + std::to_string(profile.averageValue) + "\n";
        } else {
            out += "Avg String Length: " + std::to_string(profile.averageStringLength) + "\n";
        }
        return out;
    }

private:

    // ================= HELPER FUNCTIONS=================
    template <typename T>
    bool isSorted(const std::vector<T>& data) {
        return std::is_sorted(data.begin(), data.end());
    }

    template <typename T>
    bool hasSequentialPattern(const std::vector<T>& data) {
        if (data.size() < 2) return false;
        for (size_t i = 1; i < data.size(); i++) {
            if (data[i] != data[i - 1] + 1) {
                return false;
            }
        }
        return true;
    }

    template <typename T>
    size_t countUnique(const std::vector<T>& data) {
        std::set<T> s(data.begin(), data.end());
        return s.size();
    }

    void initUserFlags(DataProfile& profile) {
        profile.needsRangeQueries = false;
        profile.needsPrefixSearch = false;
        profile.needsPriorityQueue = false;
        profile.memoryConstrained = false;
        profile.speedCritical = false;
        profile.hasRelationships = false;
        profile.needsConnectivity = false;
    }
};

#endif
