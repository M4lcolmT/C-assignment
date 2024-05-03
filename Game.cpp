#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

class Game {
private:
    struct Student {
        int id;
        string name;
        int score;
    };

    struct Question {
        int id;
        string question;
        string answer;
    };

    vector<Student> studentList;

public:
    void prepareGame() {
        loadStudentData();
        loadQuestionData();
        // Actions:
        // setDiscardedCards() => select 5/10 random questions (straight-forward & revealed) from questionList and add into discardedCards stack
        // setUnansweredCards() => add the leftover 295/290 ques (multi-answer & hidden) into the unansweredCards stack
        // chooseQues() => user choose unanswered or discarded (1/2)
        // acceptQues() => user choose accept or decline (Yes/No)
        // answerQues() => prompt user input
        // scoreUnansweredQues() => compare user input with question's data answer and score based on (incorrect, partially correct, and correct)
        // scoreDiscardedQues() => compare user input with question's data answer and score based on (incorrect and correct - 80% only)
        // updateScore() => update the student's total score after each round
        // checkDiscardedStack() => check if discardedStack is 5/10 cards (max size). 
        // insertDiscardedQues() => insert answered card at the bottom of discardedCards stack
        // insertAnsweredQues() => insert answered card at the top of answeredCards stack

        // Phases: 
        // 1. Setup decks: setDiscardedCards() + setUnansweredCards() #user can only pick the top card 
        // 2. Answer ques: chooseQues() => acceptQues() => if accepted, answerQues() + scoreUnansweredQues()/scoreDiscardedQues() || if declined, chooseQues() => updateScore()
        // 3. Put back cards: checkDiscardedStack() => if full, insertAnsweredQues() || if have space, insertDiscardedQues()
        // 4. Repeat 2 & 4 for 2 rounds
        // 5. Show results: display leaderboard + hierachy

        // for (const auto& question : questions) {
        //     unansweredStack.push(question);
        // }
    }

    void loadStudentData() { // working code!
        ifstream file("students.csv");
        string line;
        while (getline(file, line)) {
            istringstream iss(line);
            Student student;
            string id, name, score;
            getline(iss, id, '|');
            getline(iss, name, '|');
            getline(iss, score, '|');
            student.id = stoi(id);
            student.name = name;
            student.score = stoi(score);
            studentList.push_back(student); //Implement once done arraylist algorithm
        }
        file.close();
        for (auto& student : studentList) {
            cout << "ID: " << student.id << ", Name: " << student.name << ", Score: " << student.score << endl;
        }
    }

    void loadQuestionData() { // waiting for question struct...
        ifstream file("questions.csv");
        string line;
        while (getline(file, line)) {
            istringstream iss(line);
            Student student;
            string id, name, score;
            getline(iss, id, '|');
            getline(iss, name, '|');
            getline(iss, score, '|');
            student.id = stoi(id);
            student.name = name;
            student.score = stoi(score);
            studentList.push_back(student); //Implement once done arraylist algorithm
        }
        file.close();
        for (auto& student : studentList) {
            cout << "ID: " << student.id << ", Name: " << student.name << ", Score: " << student.score << endl;
        }
    }
};

int main() {
    return 0;
}
