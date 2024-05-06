

// Game.hpp
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include "Student.hpp"
#include "Question.hpp"
#include "LinkedList.hpp"
#include "DynamicArray.hpp"
using namespace std;

class Game {
private:
    LinkedList<Student> studentList;
    DynamicArray<Question> questionList; // not sure if we wanted to use rigid array list or dynamic


public:
    void loadStudentData() { // working code - linkedlist for dynamically update the student's score.
        ifstream file("students.csv");
        string line;
        while (getline(file, line)) {
            istringstream iss(line);
            string id, name, score;
            getline(iss, id, '|');
            getline(iss, name, '|');
            getline(iss, score, '|');
            Student student(name, stoi(id), stoi(score));
            studentList.append(student); 
        }
        file.close();
        for (int i = 0; i < studentList.getSize(); i++) {
            Student& student = studentList[i];
            cout << "Student ID: " << student.id << ", Name: " << student.name << ", Score: " << student.score << endl;
        }
    }

    void loadQuestionData() { // working code - dynamicArray to store the questions
        ifstream file("questions.csv");
        string line;
        if (!file.is_open()) {
            cerr << "Error opening question.csv file." << endl;
            return;
        }

        while (getline(file, line)) {
            istringstream iss(line);
            string idStr, questionText, option1, option2, option3, option4, correctAnswerStr;
            getline(iss, idStr, '|');
            getline(iss, questionText, '|');
            getline(iss, option1, '|');
            getline(iss, option2, '|');
            getline(iss, option3, '|');
            getline(iss, option4, '|');
            getline(iss, correctAnswerStr, '|');

            int id = stoi(idStr);
            set<char> correctAnswers;
            parseAnswers(correctAnswers, correctAnswerStr);

            questionList.add(Question(id, questionText, option1, option2, option3, option4, correctAnswers));
        }
        file.close();
        for (int i = 0; i < questionList.getSize() - 290; i++) {
            Question& question = questionList[i];
            cout << "Question ID: " << question.id << endl <<
            question.text << endl <<
            question.option1 << endl <<
            question.option2 << endl <<
            question.option3 << endl <<
            question.option4 << endl;
        }
    }

    void parseAnswers(set<char>& correctAnswers, const string& correctAnswerStr) { // untested
        istringstream answerStream(correctAnswerStr);
        char answer;
        while (answerStream >> answer) {
            correctAnswers.insert(answer);
            if (answerStream.peek() == ',' || answerStream.peek() == ' ') {
                answerStream.ignore();  // Ignore the delimiter (comma or space)
            }
        }
    }
};

int main() {
    Game game;
    // game.loadQuestionData();
    return 0;
}
