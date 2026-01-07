#ifndef TRIE_H
#define TRIE_H

#include <iostream>
#include <unordered_map>
#include <vector>
#include <string>
#include <stdexcept>

using namespace std;

class TrieNode {
public:
    unordered_map<char, TrieNode*> children;
    bool isEndOfWord;

    TrieNode() : isEndOfWord(false) {}
};

class Trie {
private:
    TrieNode* root;
    int wordCount;
    size_t memoryUsed;

    // helper for insertion
    void insertHelper(TrieNode* node, const string& word, int index) {
        if (index == word.length()) {
            if (!node->isEndOfWord) {
                node->isEndOfWord = true;
                wordCount++;
            }
            return;
        }

        char ch = word[index];
        if (node->children.find(ch) == node->children.end()) {
            node->children[ch] = new TrieNode();
            memoryUsed += sizeof(TrieNode);
        }

        insertHelper(node->children[ch], word, index + 1);
    }

    // helper for search
    bool searchHelper(TrieNode* node, const string& word, int index) const {
        if (!node)
            return false;
        if (index == word.length())
            return node->isEndOfWord;

        char ch = word[index];
        if (node->children.find(ch) == node->children.end())
            return false;

        return searchHelper(node->children.at(ch), word, index + 1);
    }

    // helper for deletion
    bool removeHelper(TrieNode* node, const string& word, int index) {
        if (!node)
            return false;

        if (index == word.length()) {
            if (!node->isEndOfWord)
                return false;

            node->isEndOfWord = false;
            wordCount--;
            return node->children.empty();
        }

        char ch = word[index];
        if (node->children.find(ch) == node->children.end())
            return false;

        bool shouldDelete = removeHelper(node->children[ch], word, index + 1);

        if (shouldDelete) {
            delete node->children[ch];
            node->children.erase(ch);
            memoryUsed -= sizeof(TrieNode);
        }

        return node->children.empty() && !node->isEndOfWord;
    }

    // collect all words
    void collectWords(TrieNode* node, string current, vector<string>& result) const {
        if (!node)
            return;

        if (node->isEndOfWord)
            result.push_back(current);

        for (auto& pair : node->children) {
            collectWords(pair.second, current + pair.first, result);
        }
    }

    // free memory
    void freeTrie(TrieNode* node) {
        if (!node)
            return;
        for (auto& pair : node->children)
            freeTrie(pair.second);
        delete node;
    }

public:
    Trie() : wordCount(0), memoryUsed(sizeof(TrieNode)) {
        root = new TrieNode();
    }

    ~Trie() {
        freeTrie(root);
    }

    void insert(const string& word) {
        if (word.empty())
            throw invalid_argument("Empty word not allowed");
        insertHelper(root, word, 0);
    }

    bool search(const string& word) const {
        return searchHelper(root, word, 0);
    }

    void remove(const string& word) {
        removeHelper(root, word, 0);
    }

    vector<string> getAllWords() const {
        vector<string> result;
        collectWords(root, "", result);
        return result;
    }

    bool startsWith(const string& prefix) const {
        TrieNode* node = root;
        for (char ch : prefix) {
            if (node->children.find(ch) == node->children.end())
                return false;
            node = node->children[ch];
        }
        return true;
    }

    int size() const {
        return wordCount;
    }

    bool isEmpty() const {
        return wordCount == 0;
    }

    size_t estimateMemory() const {
        return memoryUsed;
    }
};

#endif
