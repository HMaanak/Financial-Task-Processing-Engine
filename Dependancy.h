#pragma once

#include <iostream>

using namespace std;

struct Node {
    int taskId;
    Node* left;
    Node* right;

    Node(int taskid)
        : taskId(taskid),
          left(nullptr),
          right(nullptr) {}
};


class DependencyTree {
private:
    Node* root;

    void removeTree(Node* root) {
        if (root == nullptr)
            return;

        removeTree(root->left);
        removeTree(root->right);

        delete root;
    }

    Node* insertDependency(Node* root, int taskId) {
        if (root == nullptr)
            return new Node(taskId);

        if (taskId < root->taskId) {
            root->left = insertDependency(root->left, taskId);
        }
        else if (taskId > root->taskId) {
            root->right = insertDependency(root->right, taskId);
        }

        return root;
    }

    bool dependencyExist(Node* root, int id) const {
        if (root == nullptr)
            return false;

        if (root->taskId == id)
            return true;

        if (id < root->taskId)
            return dependencyExist(root->left, id);

        return dependencyExist(root->right, id);
    }

    void printTree(Node* root) const {
        if (root == nullptr)
            return;

        printTree(root->left);

        cout << root->taskId << " ";

        printTree(root->right);
    }

    Node* findMin(Node* root) {
        while (root->left != nullptr)
            root = root->left;

        return root;
    }

    Node* deleteNode(Node* root, int targetId, bool& success) {
        if (root == nullptr) {
            success = false;
            return nullptr;
        }

        if (targetId < root->taskId) {
            root->left =
                deleteNode(root->left, targetId, success);
        }
        else if (targetId > root->taskId) {
            root->right =
                deleteNode(root->right, targetId, success);
        }
        else {

            success = true;

            if (root->left == nullptr) {
                Node* temp = root->right;
                delete root;
                return temp;
            }

            if (root->right == nullptr) {
                Node* temp = root->left;
                delete root;
                return temp;
            }

            Node* temp = findMin(root->right);

            root->taskId = temp->taskId;

            bool dummy = false;

            root->right =
                deleteNode(root->right,
                           temp->taskId,
                           dummy);
        }

        return root;
    }

    int height(Node* root) const {
        if (root == nullptr)
            return 0;

        int leftHeight = height(root->left);
        int rightHeight = height(root->right);

        return 1 + max(leftHeight, rightHeight);
    }

    bool checkBalanced(Node* root) const {
        if (root == nullptr)
            return true;

        int leftHeight = height(root->left);
        int rightHeight = height(root->right);

        if (abs(leftHeight - rightHeight) > 1)
            return false;

        return checkBalanced(root->left) &&
               checkBalanced(root->right);
    }

public:

    DependencyTree()
        : root(nullptr) {}

    ~DependencyTree() {
        removeTree(root);
    }

    void insertDependency(int taskId) {
        root = insertDependency(root, taskId);
    }

    bool dependencyExists(int id) const {
        return dependencyExist(root, id);
    }

    void printDependencies() const {
        printTree(root);
        cout << endl;
    }

    bool removeDependency(int id) {
        bool success = false;

        root = deleteNode(root, id, success);

        return success;
    }

    int treeHeight() const {
        return height(root);
    }

    bool isBalanced() const {
        return checkBalanced(root);
    }
};