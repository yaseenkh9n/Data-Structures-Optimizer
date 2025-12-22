#ifndef BST_H
#define BST_H

#include <iostream>
#include <stdexcept>
#include <vector>
#include <cmath>
#include <Queue.h>

using namespace std;

template <typename T>
class Node {
public:
    T data;
    Node* left;
    Node* right;
    int height;

    Node(T val){
        data = val;
        left = nullptr;
        right = nullptr;
        height = 0;
    }
};

template <typename T>
class BST {
    Node<T>* root;
    int nodeCount;

    Node<T>* insert(Node<T>* node, T val) {
        if (!node) {
            nodeCount++;
            return new Node<T>(val);
        }
        if (val > node->data)
            node->right = insert(node->right, val);
        else
            node->left = insert(node->left, val);

        node->height = max(height(node->left), height(node->right)) + 1;
        return node;
    }

    Node<T>* search(Node<T>* node, T target) {
        if(!node || node->data == target) return node;
        if(target > node->data)
            return search(node->right, target);
        return search(node->left, target);
    }

    Node<T>* remove(Node<T>* node, T val){
        if (!node) return nullptr;

        if(val < node->data){
            node->left = remove(node->left, val);
        }
        else if(val > node->data){
            node->right = remove(node->right, val);
        }
        else {
            if(!node->left && !node->right){
                delete node;
                nodeCount--;
                return nullptr;
            }
            else if(!node->left || !node->right){
                Node<T>* child = (node->left) ? node->left : node->right;
                delete node;
                nodeCount--;
                return child;
            }
            else {
                Node<T>* successor = node->right;
                while(successor->left) successor = successor->left;
                node->data = successor->data;
                node->right = remove(node->right, successor->data);
            }
        }

        node->height = max(height(node->left), height(node->right)) + 1;
        return node;
    }

    int height(Node<T>* node){
        if (!node) return -1;
        return node->height;
    }

    bool isBalance(Node<T>* node){
        if (!node) return true;
        int leftHeight = height(node->left);
        int rightHeight = height(node->right);
        if(abs(leftHeight - rightHeight) > 1) return false;
        return isBalance(node->left) && isBalance(node->right);
    }

    void inOrder(Node<T>* node, vector<T>& result) {
        if (!node) return;
        inOrder(node->left, result);
        result.push_back(node->data);
        inOrder(node->right, result);
    }

    void preOrder(Node<T>* node, vector<T>& result) {
        if (!node) return;
        result.push_back(node->data);
        preOrder(node->left, result);
        preOrder(node->right, result);
    }

    void postOrder(Node<T>* node, vector<T>& result) {
        if (!node) return;
        postOrder(node->left, result);
        postOrder(node->right, result);
        result.push_back(node->data);
    }

    void levelOrder(Node<T>* node, vector<T>& result) {
        if(!node) return;
        Queue<Node<T>*> q;
        q.enqueue(node);
        while(!q.isEmpty()){
            Node<T>* curr = q.frontValue();
            q.dequeue();
            result.push_back(curr->data);
            if(curr->left) q.enqueue(curr->left);
            if(curr->right) q.enqueue(curr->right);
        }
    }

public:
    BST() {
        root = nullptr;
        nodeCount = 0;
    }

    ~BST() {
        while(root) remove(root->data);
    }

    void insert(T val) {
        root = insert(root, val);
    }

    bool searchValue(T target){
        return search(root, target) != nullptr;
    }

    void remove(T val){
        root = remove(root, val);
    }

    vector<T> inOrder() {
        vector<T> result;
        inOrder(root, result);
        return result;
    }

    vector<T> preOrder() {
        vector<T> result;
        preOrder(root, result);
        return result;
    }

    vector<T> postOrder() {
        vector<T> result;
        postOrder(root, result);
        return result;
    }

    vector<T> levelOrder() {
        vector<T> result;
        levelOrder(root, result);
        return result;
    }

    vector<T> rangeQuery(T minVal, T maxVal){
        vector<T> result;
        vector<T> all = inOrder();
        for(auto val : all){
            if(val >= minVal && val <= maxVal)
                result.push_back(val);
        }
        return result;
    }

    int height(){
        return height(root);
    }

    int countNodes(){
        return nodeCount;
    }

    bool isBalance(){
        return isBalance(root);
    }

    T sumOfNodes(Node<T>* node){
        if(!node) return 0;
        return sumOfNodes(node->left) + sumOfNodes(node->right) + node->data;
    }

    T sumOfNodes(){
        return sumOfNodes(root);
    }

    T findMax(){
        if(!root) throw runtime_error("Tree is empty!");
        Node<T>* curr = root;
        while(curr->right) curr = curr->right;
        return curr->data;
    }

    T findMin(){
        if(!root) throw runtime_error("Tree is empty!");
        Node<T>* curr = root;
        while(curr->left) curr = curr->left;
        return curr->data;
    }
};

#endif
