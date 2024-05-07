#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <random>
#include <algorithm>

#include "Student.hpp"
#include "Question.hpp"
#include "LinkedList.hpp"
#include "Vector.hpp"
#include "Stack.hpp"
using namespace std;

class Game {
private:
    LinkedList<Student> studentList;
    Vector<Question> questionList; 
    Stack<Question, 10> discardedCards;
    Stack<Question, 290> unansweredCards;

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

            questionList.push_back(Question(id, questionText, option1, option2, option3, option4, correctAnswers));
        }
        file.close();
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

    void setUpDecks() { // delegate the questions into unanswered and discarded decks
        random_device rd;
        mt19937 gen(rd());
        
        // Shuffle the vector 
        shuffle(questionList.begin(), questionList.end(), gen); 

        // Add 10 questions from questionList to discardedCards
        for (int i = 0; i < 10 && i < questionList.getSize(); i++) {
            discardedCards.push(questionList[i]);
        }

        cout << "total count: " << questionList.getSize() << endl;
        cout << "discarded count: " << discardedCards.getSize() << endl;

        // Add remaining questions from questionList to unansweredCards
        for (int i = 10; i < questionList.getSize(); i++) {
            unansweredCards.push(questionList[i]);
        }

        cout << "unanswered count: " << unansweredCards.getSize() << endl;
    }

    void answerDiscardedQuestion() { // pop top question from discarded stack and ask for answer confirmation
        Question card = discardedCards.pop();
        cout << "Question " << card.id << ": " << card.text << endl <<
        card.option1 << endl <<
        card.option2 << endl <<
        card.option3 << endl <<
        card.option4 << endl;
        cout << "Do you accept the question? If you decline, you will receive 0 score for this round... (1 for accept, 2 for decline): ";
        int choice;
        cin >> choice;
        if (choice == 1) {
            string answer;
            cout << "Enter your answer (a/b/c/d): ";
            cin >> answer;
        } else if (choice == 2) {
            // update student's round score to 0 (score + 0)
        } else {
            cout << "Invalid input!";
        }
    }

    void answerUnansweredQuestion() { // pop top question from unanswered stack and ask for answer confirmation
        Question card = unansweredCards.pop();
        cout << "Question " << card.id << ": " <<
        card.text << endl <<
        card.option1 << endl <<
        card.option2 << endl <<
        card.option3 << endl <<
        card.option4 << endl;
        cout << "Do you accept the question? If you decline, you will receive 0 score for this round..." << endl <<
        "(1 for accept, 2 for decline)";
        int choice;
        cin >> choice;
        if (choice == 1) {
            string answer;
            cout << "Enter your answer (a/b/c/d): ";
            cin >> answer;
        } else if (choice == 2) {
            // update student's round score to 0 (score + 0)
        } else {
            cout << "Invalid input!";
        }
    }

    void chooseQuestion() { // user choose discarded or unanswered question
        cout << "Would you like to choose a Discarded/Unanswered question? (1 for discarded, 2 for unanswered): ";
        int choice;
        cin >> choice;
        if (choice == 1) {
            answerDiscardedQuestion();
        } else if (choice == 2) {
            answerUnansweredQuestion();
        } else {
            cout << "Invalid input!";
        }
    } 
};

int main() {
    Game game;
    game.loadQuestionData();
    game.setUpDecks();
    game.chooseQuestion();
    return 0;
}
