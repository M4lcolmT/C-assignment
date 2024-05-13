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
        Vector<string> fields;
        string field;

        while (getline(iss, field, '|')) {
            fields.push_back(field);
        }

        if (fields.getSize() < 7) {
            cerr << "Invalid line in CSV: " << line << endl;
            continue;
        }

        string id = fields[0];
        string name = fields[1];
        Student student(id, name);

        for (int i = 2; i < fields.getSize(); i += 2) {
            int questionID = stoi(fields[i]);
            int score = stoi(fields[i + 1]);
            student.updateScore(questionID, score);
        }

        studentList.append(student);
    }
    file.close();
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