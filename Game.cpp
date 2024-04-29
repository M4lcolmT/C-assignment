#include <iostream>
#include <fstream> // To read CSV files
#include <string>
using namespace::std

// Call the Question, Student, and Stack classes
// Make linked lists algorithm here

class Game {
private:
    ArrayList<Question> questions;
    LinkedList<Student> students;
    Stack answeredStack;
    Stack unansweredStack;
    Stack discardedStack;

public:
    void prepareGame() {
        loadStudentData();
        // Call function to read question data from csv

        for (const auto& question : questions) {
            unansweredStack.push(question);
        }
    }

    void loadStudentData() {
        ifstream studentFile("students.txt");
        if (studentFile.is_open()) {
            int studentID;
            string studentName;
            while (getline(studentFile, studentID, studentName, ',')) {
                students.insert(Student(studentID, studentName, 0)); 
            }
            studentFile.close();
        } else {
            cout << "unable to open file!";
        }
    }
}; 

int main() { 
    cout << "Jeff";
    return 0;
}