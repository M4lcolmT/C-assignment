#include <iostream>
#include <fstream>
#include <sstream> //parsing strings
#include <string>
#include <vector>
#include <iomanip> //formatting output

using namespace std;

struct Student{
    string name;
    vector<int> scores;
    int totalScore;
    Student* left;
    Student* right;

    Student(string n, vector<int>s) : name(n), scores(s), totalScore(0), left(nullptr), right(nullptr){
        for (int score : scores){
            totalScore += score;
        }
    }
};

//Binary Tree to maintain hierarchy of winners
class BinaryTree {
    private:
    Student* root;

    // Inserting recursive function based on overall score
    void insert(Student*& node, Student* newStudent) {
        if (!node)
            node = newStudent;
        else if (newStudent->totalScore > node->totalScore)
            insert(node->left, newStudent);  // Higher scores go to the left for visual representation
        else
            insert(node->right, newStudent);
    }

    // Function to display the tree in a hierarchical manner
    void display(Student* node, int indent = 0) {
        if (node) {
            display(node->right, indent + 4);
            cout << setw(indent) << node->name << " (" << node->totalScore << ")\n";
            display(node->left, indent + 4);
        }
    }

public:
    BinaryTree() : root(nullptr) {}

    void insertStudent(Student* student) {
        insert(root, student);
    }

    void display() {
        display(root);
    }
};

// Main function for leaderboard management and tree display
int main() {
    vector<Student*> students;
    ifstream file("students.txt");
    string line, name;
    int score1, score2, score3;

    while (getline(file, line)) {
        stringstream ss(line);
        getline(ss, name, ',');
        ss >> score1 >> score2 >> score3;
        students.push_back(new Student(name, { score1, score2, score3 }));
    }

    // Sorting students by total score using simple selection sort
    for (size_t i = 0; i < students.size(); ++i) {
        for (size_t j = i + 1; j < students.size(); ++j) {
            if (students[i]->totalScore < students[j]->totalScore) {
                swap(students[i], students[j]);
            }
        }
    }

    // Displaying the leaderboard
    cout << "Ranking\tStudent\t\tRound 1\tRound 2\tRound 3\tOverall Score\n";
    for (size_t i = 0; i < students.size(); ++i) {
        cout << i + 1 << "\t" << students[i]->name << "\t\t"
            << students[i]->scores[0] << "\t"
            << students[i]->scores[1] << "\t"
            << students[i]->scores[2] << "\t"
            << students[i]->totalScore << "\n";
    }

    // Insert top 15 students into the binary tree for hierarchical display
    BinaryTree tree;
    for (size_t i = 0; i < 15 && i < students.size(); ++i) {
        tree.insertStudent(students[i]);
    }

    cout << "\nHierarchical View of Top Students:\n";
    tree.display();

    // Freeing memory
    for (Student* s : students) {
        delete s;
    }

    return 0;
}
