// #ifndef LEADERBOARD_HPP
// #define LEADERBOARD_HPP

// #include <vector>
// #include <algorithm>
// #include <iomanip>
// #include <queue>
// #include <iostream>
// #include <string>
// #include <cmath>
// #include "Student.hpp"

// using namespace std;

// // TreeNode structure for the binary search tree
// struct TreeNode {
//     Student student;
//     TreeNode* left;
//     TreeNode* right;

//     TreeNode(const Student& s) : student(s), left(nullptr), right(nullptr) {}
// };

// // Binary Search Tree class
// class BinarySearchTree {
// private:
//     TreeNode* root;

//     void printSpaces(int n, ostream& out) const {
//         for (int i = 0; i < n; ++i) {
//             out << ' ';
//         }
//     }

//     void displayTree(TreeNode* root, ostream& out) const {
//         if (!root) {
//             cerr << "Error: Root is null." << endl;
//             return;
//         }


//         // Level 0
//         out << "                                                                                                                       " << root->student.getName() << " (" << root->student.getTotalScore() << ")\n";

//         // Level 1
//         if (root->left || root->right) {
//             out << "                                                                                                                            |\n";
//             out << "                                                                                                                            |\n";
//             out << "                                                           +----------------------------------------------------------------+-------------------------------------------------------------------+\n";
//             out << "                                                           |                                                                                                                                    |\n";
//             out << "                                                       " << (root->left ? root->left->student.getName() + " (" + to_string(root->left->student.getTotalScore()) + ")" : "                         ")
//                 << "                                                                                                                           " << (root->right ? root->right->student.getName() + " (" + to_string(root->right->student.getTotalScore()) + ")" : "                         ") << "\n";
//         }
//         else {
//             cerr << "Error: Both children in level 1 are null." << endl;
//             return;
//         }

//         // Level 2
//         if ((root->left && (root->left->left || root->left->right)) || (root->right && (root->right->left || root->right->right))) {
//             out << "                                                           |                                                                                                                                    |\n";
//             out << "                                                           |                                                                                                                                    |\n";
//             out << "                               +-----------------------------+--------------------------------+                                                                 +-------------------------------+----------------------------------+\n";
//             out << "                               |                                                              |                                                                 |                                                                  |\n";
//             out << "                            " << (root->left && root->left->left ? root->left->left->student.getName() + " (" + to_string(root->left->left->student.getTotalScore()) + ")" : "           ")
//                 << "                                                    " << (root->left && root->left->right ? root->left->right->student.getName() + " (" + to_string(root->left->right->student.getTotalScore()) + ")" : "           ")
//                 << "                                                         " << (root->right && root->right->left ? root->right->left->student.getName() + " (" + to_string(root->right->left->student.getTotalScore()) + ")" : "           ")
//                 << "                                                      " << (root->right && root->right->right ? root->right->right->student.getName() + " (" + to_string(root->right->right->student.getTotalScore()) + ")" : "           ") << "\n";
//         }
//         else {
//             cerr << "Error: One of the children in level 2 is null." << endl;
//             return;
//         }

//         // Level 3
//         if ((root->left && root->left->left && (root->left->left->left || root->left->left->right)) ||
//             (root->left && root->left->right && (root->left->right->left || root->left->right->right)) ||
//             (root->right && root->right->left && (root->right->left->left || root->right->left->right)) ||
//             (root->right && root->right->right && (root->right->right->left || root->right->right->right))) {
//             out << "              +----------------+---------------+                               +--------------+--------------+                                 +----------------+----------------+                                 +---------------+----------------+\n";
//             out << "           " << (root->left && root->left->left && root->left->left->left ? root->left->left->left->student.getName() + " (" + to_string(root->left->left->left->student.getTotalScore()) + ")" : "                    ")
//                 << "                    " << (root->left && root->left->left && root->left->left->right ? root->left->left->right->student.getName() + " (" + to_string(root->left->left->right->student.getTotalScore()) + ")" : "                      ")
//                 << "                      " << (root->left && root->left->right && root->left->right->left ? root->left->right->left->student.getName() + " (" + to_string(root->left->right->left->student.getTotalScore()) + ")" : "                      ")
//                 << "                    " << (root->left && root->left->right && root->left->right->right ? root->left->right->right->student.getName() + " (" + to_string(root->left->right->right->student.getTotalScore()) + ")" : "                      ")
//                 << "                      " << (root->right && root->right->left && root->right->left->left ? root->right->left->left->student.getName() + " (" + to_string(root->right->left->left->student.getTotalScore()) + ")" : "                      ")
//                 << "                          " << (root->right && root->right->left && root->right->left->right ? root->right->left->right->student.getName() + " (" + to_string(root->right->left->right->student.getTotalScore()) + ")" : "                      ")
//                 << "                      " << (root->right && root->right->right && root->right->right->left ? root->right->right->left->student.getName() + " (" + to_string(root->right->right->left->student.getTotalScore()) + ")" : "                      ")
//                 << "                       " << (root->right && root->right->right && root->right->right->right ? root->right->right->right->student.getName() + " (" + to_string(root->right->right->right->student.getTotalScore()) + ")" : "                      ") << "\n";
//         }

//         // Level 4
//         if ((root->left && root->left->left && root->left->left->left && (root->left->left->left->left || root->left->left->left->right)) ||
//             (root->left && root->left->left && root->left->left->right && (root->left->left->right->left || root->left->left->right->right)) ||
//             (root->left && root->left->right && root->left->right->left && (root->left->right->left->left || root->left->right->left->right)) ||
//             (root->left && root->left->right && root->left->right->right && (root->left->right->right->left || root->left->right->right->right)) ||
//             (root->right && root->right->left && root->right->left->left && (root->right->left->left->left || root->right->left->left->right)) ||
//             (root->right && root->right->left && root->right->left->right && (root->right->left->right->left || root->right->left->right->right)) ||
//             (root->right && root->right->right && root->right->right->left && (root->right->right->left->left || root->right->right->left->right)) ||
//             (root->right && root->right->right && root->right->right->right && (root->right->right->right->left || root->right->right->right->right))) {
//             out << "     +--------+---------+             +--------+---------+            +--------+---------+          +--------+---------+              +--------+---------+              +--------+---------+              +--------+---------+               +------+-------+\n";
//             out << "     |                  |             |                  |            |                  |          |                  |              |                  |              |                  |              |                  |               |               \n";
//             out << (root->left && root->left->left && root->left->left->left && root->left->left->left->left ? root->left->left->left->left->student.getName() + " (" + to_string(root->left->left->left->left->student.getTotalScore()) + ")" : "           ")
//                 << "     " << (root->left && root->left->left && root->left->left->left && root->left->left->left->right ? root->left->left->left->right->student.getName() + " (" + to_string(root->left->left->left->right->student.getTotalScore()) + ")" : "           ")
//                 << "     " << (root->left && root->left->left && root->left->left->right && root->left->left->right->left ? root->left->left->right->left->student.getName() + " (" + to_string(root->left->left->right->left->student.getTotalScore()) + ")" : "           ")
//                 << "        " << (root->left && root->left->left && root->left->left->right && root->left->left->right->right ? root->left->left->right->right->student.getName() + " (" + to_string(root->left->left->right->right->student.getTotalScore()) + ")" : "           ")
//                 << "    " << (root->left && root->left->right && root->left->right->left && root->left->right->left->left ? root->left->right->left->left->student.getName() + " (" + to_string(root->left->right->left->left->student.getTotalScore()) + ")" : "           ")
//                 << "    " << (root->left && root->left->right && root->left->right->left && root->left->right->left->right ? root->left->right->left->right->student.getName() + " (" + to_string(root->left->right->left->right->student.getTotalScore()) + ")" : "           ")
//                 << "    " << (root->left && root->left->right && root->left->right->right && root->left->right->right->left ? root->left->right->right->left->student.getName() + " (" + to_string(root->left->right->right->left->student.getTotalScore()) + ")" : "           ")
//                 << "     " << (root->left && root->left->right && root->left->right->right && root->left->right->right->right ? root->left->right->right->right->student.getName() + " (" + to_string(root->left->right->right->right->student.getTotalScore()) + ")" : "           ")
//                 << "     " << (root->right && root->right->left && root->right->left->left && root->right->left->left->left ? root->right->left->left->left->student.getName() + " (" + to_string(root->right->left->left->left->student.getTotalScore()) + ")" : "           ")
//                 << "       " << (root->right && root->right->left && root->right->left->left && root->right->left->left->right ? root->right->left->left->right->student.getName() + " (" + to_string(root->right->left->left->right->student.getTotalScore()) + ")" : "           ")
//                 << "   " << (root->right && root->right->left && root->right->left->right && root->right->left->right->left ? root->right->left->right->left->student.getName() + " (" + to_string(root->right->left->right->left->student.getTotalScore()) + ")" : "           ")
//                 << "        " << (root->right && root->right->left && root->right->left->right && root->right->left->right->right ? root->right->left->right->right->student.getName() + " (" + to_string(root->right->left->right->right->student.getTotalScore()) + ")" : "           ")
//                 << "     " << (root->right && root->right->right && root->right->right->left && root->right->right->left->left ? root->right->right->left->left->student.getName() + " (" + to_string(root->right->right->left->left->student.getTotalScore()) + ")" : "           ")
//                 << "         " << (root->right && root->right->right && root->right->right->left && root->right->right->left->right ? root->right->right->left->right->student.getName() + " (" + to_string(root->right->right->left->right->student.getTotalScore()) + ")" : "           ")
//                 << "    " << (root->right && root->right->right && root->right->right->right && root->right->right->right->left ? root->right->right->right->left->student.getName() + " (" + to_string(root->right->right->right->left->student.getTotalScore()) + ")" : "           ")
//                 << "    " << (root->right && root->right->right && root->right->right->right && root->right->right->right->right ? root->right->right->right->right->student.getName() + " (" + to_string(root->right->right->right->right->student.getTotalScore()) + ")" : "           ") << "\n";
//         }
//         else {
//             cerr << "Error: One of the children in level 4 is null." << endl;
//             return;
//         }
//     }

// public:
//     BinarySearchTree() : root(nullptr) {}

//     void buildSpecificTree(vector<TreeNode*>& nodes) {
//         if (nodes.size() < 30) return;

//         root = nodes[0]; // Victoria (54)

//         // Level 1
//         if (nodes.size() > 1) root->left = nodes[1]; // Jeff (52)
//         if (nodes.size() > 2) root->right = nodes[2]; // Camila (50)

//         // Level 2
//         if (nodes.size() > 3) root->left->left = nodes[3]; // Zoe (50)
//         if (nodes.size() > 4) root->left->right = nodes[4]; // Joseph (50)
//         if (nodes.size() > 5) root->right->left = nodes[5]; // Natalie (50)
//         if (nodes.size() > 6) root->right->right = nodes[6]; // Anthony (50)

//         // Level 3
//         if (nodes.size() > 7) root->left->left->left = nodes[7]; // Paisley (50)
//         if (nodes.size() > 8) root->left->left->right = nodes[8]; // Kaylee (50)
//         if (nodes.size() > 9) root->left->right->left = nodes[9]; // Ethan (50)
//         if (nodes.size() > 10) root->left->right->right = nodes[10]; // Sofia (50)
//         if (nodes.size() > 11) root->right->left->left = nodes[11]; // Grace (48)
//         if (nodes.size() > 12) root->right->left->right = nodes[12]; // Henry (48)
//         if (nodes.size() > 13) root->right->right->left = nodes[13]; // Mateo (48)
//         if (nodes.size() > 14) root->right->right->right = nodes[14]; // Jack (48)

//         // Level 4
//         if (nodes.size() > 15) root->left->left->left->left = nodes[15]; // Isabella (48)
//         if (nodes.size() > 16) root->left->left->left->right = nodes[16]; // Samuel (48)
//         if (nodes.size() > 17) root->left->left->right->left = nodes[17]; // Avery (48)
//         if (nodes.size() > 18) root->left->left->right->right = nodes[18]; // Ellie (48)
//         if (nodes.size() > 19) root->left->right->left->left = nodes[19]; // Penelope (48)
//         if (nodes.size() > 20) root->left->right->left->right = nodes[20]; // Carter (46)
//         if (nodes.size() > 21) root->left->right->right->left = nodes[21]; // Sophia (46)
//         if (nodes.size() > 22) root->left->right->right->right = nodes[22]; // Charles (46)
//         if (nodes.size() > 23) root->right->left->left->left = nodes[23]; // Aubrey (46)
//         if (nodes.size() > 24) root->right->left->left->right = nodes[24]; // Theodore (46)
//         if (nodes.size() > 25) root->right->left->right->left = nodes[25]; // Harper (46)
//         if (nodes.size() > 26) root->right->left->right->right = nodes[26]; // Levi (46)
//         if (nodes.size() > 27) root->right->right->left->left = nodes[27]; // Owen (46)
//         if (nodes.size() > 28) root->right->right->left->right = nodes[28]; // Elizabeth (46)
//         if (nodes.size() > 29) root->right->right->right->left = nodes[29]; // Nathan (46)
//     }

//     void display() const {
//         displayTree(root, cout);
//     }
// };

// class Leaderboard {
// public:
//     static void sortStudentsByScore(vector<Student>& students) {
//         sort(students.begin(), students.end(), [](const Student& a, const Student& b) {
//             return a.getTotalScore() > b.getTotalScore();
//             });
//     }

//     static void showLeaderboard(vector<Student>& students) {
//         sortStudentsByScore(students);

//         cout << "Leaderboard:\n";
//         cout << setw(10) << left << "Rank"
//             << setw(15) << left << "ID"
//             << setw(25) << left << "Name"
//             << setw(15) << left << "Total Score" << endl;
//         cout << "---------------------------------------------------------\n";

//         for (size_t i = 0; i < students.size(); ++i) {
//             cout << setw(10) << left << (i + 1)
//                 << setw(15) << left << students[i].getID()
//                 << setw(25) << left << students[i].getName()
//                 << setw(15) << left << students[i].getTotalScore() << endl;
//         }
//     }

//     static void showHierarchy(vector<Student>& students) {
//         sortStudentsByScore(students);

//         vector<Student> top30(students.begin(), students.begin() + min(30, static_cast<int>(students.size())));
//         vector<TreeNode*> nodes;
//         for (const Student& student : top30) {
//             nodes.push_back(new TreeNode(student));
//         }

//         BinarySearchTree bst;
//         bst.buildSpecificTree(nodes);

//         cout << "Top 30 Hierarchical Chart:\n";
//         bst.display();
//     }
// };

// #endif
