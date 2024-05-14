#include <fstream>
#include <sstream>
#include <iostream>
#include "Vector.hpp"
#include "Student.hpp"
#include "LinkedList.hpp"
using namespace std;

LinkedList<Student> studentList;


void loadStudentData() {
    ifstream file("students.csv");
    if (!file.is_open()) {
        cerr << "Error opening students.csv file." << endl;
        return;
    }

    string line;
    while (getline(file, line)) {
        istringstream iss(line);
        string id, name;
        getline(iss, id, '|');
        getline(iss, name, '|');

        Student student(id, name);

        string questionIdStr, scoreStr;
        while (getline(iss, questionIdStr, '|') && getline(iss, scoreStr, '|')) {
            int questionID, score;
            try {
                questionID = stoi(questionIdStr);
                score = stoi(scoreStr);
                student.updateScore(questionID, score);
            } catch (const invalid_argument& e) {
                cerr << "Invalid value in CSV: " << questionIdStr << " or " << scoreStr << endl;
            }
        }

        studentList.append(student);
    }

    file.close();

    // Print student scores after loading all the data
    for (size_t i = 0; i < studentList.getSize(); i++) {
        studentList[i].printScores();
        cout << endl;
    }
}

int main() {
    loadStudentData();
    cout << "size: " << studentList.getSize() << endl;

    for (int i = 0; i < studentList.getSize(); i++) {
        Student student = studentList[i];
        cout << student.getID() << " " << student.getName() << endl;
        student.printScores();
    }
    return 0;
}