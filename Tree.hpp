#ifndef TREE_HPP
#define TREE_HPP

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <random>
#include <iomanip>
#include <algorithm>

#include "Student.hpp"
#include "Queue.hpp"
#include "ArrayList.hpp"
using namespace std;

class TreeNode {
public:
    Student student;
    TreeNode* left;
    TreeNode* right;

    TreeNode(const Student& student) : student(student), left(nullptr), right(nullptr) {}
};

class Tree {
private:
    TreeNode* root;

    void displayTree(TreeNode* root) const {
        if (!root) return;

        Queue<TreeNode*> q;
        q.push(root);

        int level = 0;
        while (!q.isEmpty()) {
            int count = q.getSize();
            cout << "Level " << level++ << ": ";
            while (count--) {
                TreeNode* node = q.getFront();
                q.pop();
                cout << node->student.getName() << " (" << node->student.getTotalScore() << ") ";
                if (node->left) q.push(node->left);
                if (node->right) q.push(node->right);
            }
            cout << endl;
        }
    }

    void displayHorizontalTree(TreeNode* root, ostream& out) const {
        if (!root) return;

        Queue<TreeNode*> q;
        q.push(root);

        LinkedList<LinkedList<TreeNode*>> levels;
        while (!q.isEmpty()) {
            int count = q.getSize();
            LinkedList<TreeNode*> level;
            while (count--) {
                TreeNode* node = q.getFront();
                q.pop();
                level.append(node);
                if (node) {
                    q.push(node->left);
                    q.push(node->right);
                } else {
                    q.push(nullptr);
                    q.push(nullptr);
                }
            }
            bool allNull = true;
            for (size_t i = 0; i < level.getSize(); ++i) {
                if (level[i] != nullptr) {
                    allNull = false;
                    break;
                }
            }
            if (allNull) break;
            levels.append(level);
        }

        // Center the root node
        out << "                                                                                                                       " << root->student.getName() << " (" << root->student.getTotalScore() << ")\n";

        // Level 1
        if (root->left || root->right) {
            out << "                                                                                                                            |\n";
            out << "                                                                                                                            |\n";
            out << "                                                           +----------------------------------------------------------------+-------------------------------------------------------------------+\n";
            out << "                                                           |                                                                                                                                    |\n";
            out << "                                                       " << (root->left ? root->left->student.getName() + " (" + to_string(root->left->student.getTotalScore()) + ")" : "                         ")
                << "                                                                                                                           " << (root->right ? root->right->student.getName() + " (" + to_string(root->right->student.getTotalScore()) + ")" : "                         ") << "\n";
        }

        // Level 2
        if ((root->left && (root->left->left || root->left->right)) || (root->right && (root->right->left || root->right->right))) {
            out << "                                                           |                                                                                                                                    |\n";
            out << "                                                           |                                                                                                                                    |\n";
            out << "                               +-----------------------------+--------------------------------+                                                                 +-------------------------------+----------------------------------+\n";
            out << "                               |                                                              |                                                                 |                                                                  |\n";
            out << "                            " << (root->left && root->left->left ? root->left->left->student.getName() + " (" + to_string(root->left->left->student.getTotalScore()) + ")" : "           ")
                << "                                                    " << (root->left && root->left->right ? root->left->right->student.getName() + " (" + to_string(root->left->right->student.getTotalScore()) + ")" : "           ")
                << "                                                         " << (root->right && root->right->left ? root->right->left->student.getName() + " (" + to_string(root->right->left->student.getTotalScore()) + ")" : "           ")
                << "                                                      " << (root->right && root->right->right ? root->right->right->student.getName() + " (" + to_string(root->right->right->student.getTotalScore()) + ")" : "           ") << "\n";
        }

        // Level 3
        if ((root->left && root->left->left && (root->left->left->left || root->left->left->right)) ||
            (root->left && root->left->right && (root->left->right->left || root->left->right->right)) ||
            (root->right && root->right->left && (root->right->left->left || root->right->left->right)) ||
            (root->right && root->right->right && (root->right->right->left || root->right->right->right))) {
            out << "              +----------------+---------------+                               +--------------+--------------+                                 +----------------+----------------+                                 +---------------+----------------+\n";
            out << "           " << (root->left && root->left->left && root->left->left->left ? root->left->left->left->student.getName() + " (" + to_string(root->left->left->left->student.getTotalScore()) + ")" : "                    ")
                << "                    " << (root->left && root->left->left && root->left->left->right ? root->left->left->right->student.getName() + " (" + to_string(root->left->left->right->student.getTotalScore()) + ")" : "                      ")
                << "                      " << (root->left && root->left->right && root->left->right->left ? root->left->right->left->student.getName() + " (" + to_string(root->left->right->left->student.getTotalScore()) + ")" : "                      ")
                << "                    " << (root->left && root->left->right && root->left->right->right ? root->left->right->right->student.getName() + " (" + to_string(root->left->right->right->student.getTotalScore()) + ")" : "                      ")
                << "                      " << (root->right && root->right->left && root->right->left->left ? root->right->left->left->student.getName() + " (" + to_string(root->right->left->left->student.getTotalScore()) + ")" : "                      ")
                << "                          " << (root->right && root->right->left && root->right->left->right ? root->right->left->right->student.getName() + " (" + to_string(root->right->left->right->student.getTotalScore()) + ")" : "                      ")
                << "                      " << (root->right && root->right->right && root->right->right->left ? root->right->right->left->student.getName() + " (" + to_string(root->right->right->left->student.getTotalScore()) + ")" : "                      ")
                << "                       " << (root->right && root->right->right && root->right->right->right ? root->right->right->right->student.getName() + " (" + to_string(root->right->right->right->student.getTotalScore()) + ")" : "                      ") << "\n";
        }

        // Level 4
        if ((root->left && root->left->left && root->left->left->left && (root->left->left->left->left || root->left->left->left->right)) ||
            (root->left && root->left->left && root->left->left->right && (root->left->left->right->left || root->left->left->right->right)) ||
            (root->left && root->right && root->right->left && (root->right->left->left || root->right->left->right)) ||
            (root->left && root->right && root->right->right && (root->right->right->left || root->right->right->right))) {
            out << "     +--------+---------+             +--------+---------+            +--------+---------+          +--------+---------+              +--------+---------+              +--------+---------+              +--------+---------+               +------+-------+\n";
            out << "     |                  |             |                  |            |                  |          |                  |              |                  |              |                  |              |                  |               |               \n";
            out << (root->left && root->left->left && root->left->left->left && root->left->left->left->left ? root->left->left->left->left->student.getName() + " (" + to_string(root->left->left->left->left->student.getTotalScore()) + ")" : "           ")
                << "     " << (root->left && root->left->left && root->left->left->left && root->left->left->left->right ? root->left->left->left->right->student.getName() + " (" + to_string(root->left->left->left->right->student.getTotalScore()) + ")" : "           ")
                << "     " << (root->left && root->left->left && root->left->left->right && root->left->left->right->left ? root->left->left->right->left->student.getName() + " (" + to_string(root->left->left->right->left->student.getTotalScore()) + ")" : "           ")
                << "        " << (root->left && root->left->left && root->left->left->right && root->left->left->right->right ? root->left->left->right->right->student.getName() + " (" + to_string(root->left->left->right->right->student.getTotalScore()) + ")" : "           ")
                << "    " << (root->left && root->left->right && root->left->right->left && root->left->right->left->left ? root->left->right->left->left->student.getName() + " (" + to_string(root->left->right->left->left->student.getTotalScore()) + ")" : "           ")
                << "    " << (root->left && root->left->right && root->left->right->left && root->left->right->left->right ? root->left->right->left->right->student.getName() + " (" + to_string(root->left->right->left->right->student.getTotalScore()) + ")" : "           ")
                << "    " << (root->left && root->left->right && root->left->right->right && root->left->right->right->left ? root->left->right->right->left->student.getName() + " (" + to_string(root->left->right->right->left->student.getTotalScore()) + ")" : "           ")
                << "     " << (root->left && root->left->right && root->left->right->right && root->left->right->right->right ? root->left->right->right->right->student.getName() + " (" + to_string(root->left->right->right->right->student.getTotalScore()) + ")" : "           ")
                << "     " << (root->right && root->right->left && root->right->left->left && root->right->left->left->left ? root->right->left->left->left->student.getName() + " (" + to_string(root->right->left->left->left->student.getTotalScore()) + ")" : "           ")
                << "       " << (root->right && root->right->left && root->right->left->left && root->right->left->left->right ? root->right->left->left->right->student.getName() + " (" + to_string(root->right->left->left->right->student.getTotalScore()) + ")" : "           ")
                << "   " << (root->right && root->right->left && root->right->left->right && root->right->left->right->left ? root->right->left->right->left->student.getName() + " (" + to_string(root->right->left->right->left->student.getTotalScore()) + ")" : "           ")
                << "        " << (root->right && root->right->left && root->right->left->right && root->right->left->right->right ? root->right->left->right->right->student.getName() + " (" + to_string(root->right->left->right->right->student.getTotalScore()) + ")" : "           ")
                << "     " << (root->right && root->right->right && root->right->right->left && root->right->right->left->left ? root->right->right->left->left->student.getName() + " (" + to_string(root->right->right->left->left->student.getTotalScore()) + ")" : "           ")
                << "         " << (root->right && root->right->right && root->right->right->left && root->right->right->left->right ? root->right->right->left->right->student.getName() + " (" + to_string(root->right->right->left->right->student.getTotalScore()) + ")" : "           ")
                << "    " << (root->right && root->right->right && root->right->right->right && root->right->right->right->left ? root->right->right->right->left->student.getName() + " (" + to_string(root->right->right->right->left->student.getTotalScore()) + ")" : "           ")
                << "    " << (root->right && root->right->right && root->right->right->right && root->right->right->right->right ? root->right->right->right->right->student.getName() + " (" + to_string(root->right->right->right->right->student.getTotalScore()) + ")" : "           ") << "\n";
        }
    }

    void deleteTree(TreeNode* node) {
        if (node == nullptr) return;
        deleteTree(node->left);
        deleteTree(node->right);
        delete node;
    }

    TreeNode* find(TreeNode* node, const string& id) const {
        if (node == nullptr)
            return nullptr;
        if (id == node->student.getID())
            return node;
        if (id < node->student.getID())
            return find(node->left, id);
        return find(node->right, id);
    }

public:
    Tree() : root(nullptr) {}
    ~Tree() {
        deleteTree(root);
    }

    TreeNode* find(const string& id) const {
        return find(root, id);
    }

    void buildTree(ArrayList<Student>& students) {
        if (students.getSize() == 0) return;
        root = new TreeNode(students.get(0));

        queue<TreeNode*> q;
        q.push(root);
        size_t index = 1;

        while (!q.empty() && index < students.getSize()) {
            TreeNode* current = q.front();
            q.pop();

            if (index < students.getSize()) {
                current->left = new TreeNode(students.get(index++));
                q.push(current->left);
            }

            if (index < students.getSize()) {
                current->right = new TreeNode(students.get(index++));
                q.push(current->right);
            }
        }
    }

    void displayTree() const {
        displayTree(root);
    }

    void displayHorizontalTree() const {
        displayHorizontalTree(root, cout);
    }
};

#endif
