#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <random>
#include <algorithm>

#include "Student.hpp"
#include "Question.hpp"
#include "ArrayList.hpp"
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
    LinkedList<Question> answeredCards;
    Student newStudent;

public:
    void loadStudentData() { // working code - linkedlist for dynamically update the student's score.
        ifstream file("students.csv");
        string line;
        if (!file.is_open()) {
            cerr << "Error opening students.csv file." << endl;
            return;
        }
        while (getline(file, line)) {
            istringstream iss(line);
            string id, name, score;
            getline(iss, id, '|');
            getline(iss, name, '|');
            getline(iss, score, '|');
            Student student(id, name, stoi(score));
            studentList.append(student); 
        }
        file.close();
    }

    void loadQuestionData() { // working code - dynamicArray to store the questions
        ifstream file("questions.csv");
        string line;
        if (!file.is_open()) {
            cerr << "Error opening questions.csv file." << endl;
            return;
        }

        while (getline(file, line)) {
            istringstream iss(line);
            string idStr, questionText, option1, option2, option3, option4, correctAnswer;
            getline(iss, idStr, '|');
            getline(iss, questionText, '|');
            getline(iss, option1, '|');
            getline(iss, option2, '|');
            getline(iss, option3, '|');
            getline(iss, option4, '|');
            getline(iss, correctAnswer, '|');

            int id = stoi(idStr);

            questionList.push_back(Question(id, questionText, option1, option2, option3, option4, correctAnswer));
        }
        file.close();
    }

    void startGame() {
        int choice;
        cout << "     Trivial Flash Card Game     " << endl
        << "<< --------------------------- >>" << endl
        << "Would you like to play" << endl
        << "1. Yes" << endl
        << "2. No" << endl
        << "Enter your choice: ";
        validateInput("playGame", choice);
        if (choice == 1) {
            string id;
            string name;
            cout << "Ready to play? Enter your student details below." << endl
            << "TP number: ";
            cin >> id;
            cout << "Name: ";
            cin >> name;   
            cin.clear();
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Clear the input stream 
            newStudent = Student(id, name, 0);
            studentList.append(newStudent);
            repeatRound();
        } else if (choice == 2) {
            cout << "I guess you are not up for the challenge, pussy...";
        }
    }

    void setUpDecks() { // delegate the questions into unanswered and discarded decks
        random_device rd;
        mt19937 gen(rd());
        
        // Shuffle the vector 
        shuffle(questionList.begin(), questionList.end(), gen); 

        // Add 10 questions from questionList to discardedCards
        for (int i = 0; i < 5 && i < questionList.getSize(); i++) {
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

    // void updateScore() {

    // }
    
    int countCharAnswer(string& formattedUserAnswer, string& formattedCardAnswer) {
        int numCorrect = 0;
        for (char ch : formattedUserAnswer) {
            if (formattedCardAnswer.find(ch) != string::npos) {
                numCorrect++;
            }
        }
        return numCorrect;
    }

    string removeCommas(const string& answer) {
        string result;
        for (char ch : answer) {
            if (ch != ',') {
                result += ch;
            }
        }
        return result;
    }

    void validateInput(const string& inputType, int& choice) { // check user input whether is 1 or 2
        bool validInput = false;
        
        do {
            cin >> choice;
            
            if (choice == 1 || choice == 2) {
                validInput = true;
            } else {
                if (inputType == "chooseQuestion") {
                    cout << "Invalid input! Please enter 1 for discarded or 2 for unanswered questions: ";
                } else if (inputType == "answerQuestion") {
                    cout << "Invalid input! Please enter 1 to accept or 2 to decline: ";
                } else if (inputType == "playGame") {
                    cout << "Invalid input! Please enter 1 for YES or 2 for NO: ";
                } else if (inputType == "viewRanking") {
                    cout << "Invalid input! Please enter 1 to view leaderboard or 2 to view hierarchy: ";
                }
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }
        } while (!validInput);
    }


    void answerDiscardedQuestion() {
        Question card = discardedCards.pop();
        cout << "Question " << card.id << ": " << card.text << endl
            << card.option1 << endl
            << card.option2 << endl
            << card.option3 << endl
            << card.option4 << endl;
        int choice;
        cout << "Do you accept the question? If you decline, you will receive 0 score for this round..." << endl
            << "1. Accept" << endl
            << "2. Decline" << endl
            << "Enter your choice: ";
        validateInput("answerQuestion", choice); 
        if (choice == 1) {
            string answer;
            cout << "Enter your answer (e.g., a/b,c/b,c,d): ";
            cin >> answer;
            // Remove commas from both correct and user answers for comparison
            string formattedUserAnswer = removeCommas(answer);
            string formattedCardAnswer = removeCommas(card.correctAnswers);
            int numCorrect = countCharAnswer(formattedUserAnswer, formattedCardAnswer);
            int questionScore = numCorrect * 5;

            if (numCorrect == formattedCardAnswer.length()) {
                cout << "Correct answer! Well done!" << endl;
                cout << "Score for this question: " << questionScore << endl; 
            } else if (numCorrect > 0) {
                cout << "Partially correct. " << numCorrect << " out of " << formattedCardAnswer.length() << " correct." << endl;
                cout << "Score for this question: " << questionScore << endl; 
            } else {
                cout << "Incorrect answer. Correct answer was: " << formattedCardAnswer << endl;
                cout << "Score for this question: 0" << endl; 
            }

            updateScore(newStudent, questionScore, false);

        } else if (choice == 2) {
            cout << "Question declined. No score awarded for this round." << endl;
            updateScore(newStudent, 0, false);
            // Put back discarded stack
        }
        putBackCard(card);
    }



    void answerUnansweredQuestion() { // pop top question from unanswered stack and ask for answer confirmation
        Question card = unansweredCards.pop();
        cout << "Question " << card.id << ": " <<
        card.text << endl <<
        card.option1 << endl <<
        card.option2 << endl <<
        card.option3 << endl <<
        card.option4 << endl;
        int choice;
        cout << "Do you accept the question? If you decline, you will receive 0 score for this round..." << endl
        << "1. Accept" << endl
        << "2. Decline" << endl
        << "Enter your choice: ";
        validateInput("answerQuestion", choice); 
        if (choice == 1) {
            string answer;
            cout << "Enter your answer (e.g., a/b,c/b,c,d): ";
            cin >> answer;

            // Remove commas from both correct and user answers for comparison
            string formattedUserAnswer = removeCommas(answer);
            string formattedCardAnswer = removeCommas(card.correctAnswers);
            int numCorrect = countCharAnswer(formattedUserAnswer, formattedCardAnswer);
            int questionScore = numCorrect * 5;

            if (numCorrect == formattedCardAnswer.length()) {
                cout << "Correct answer! Well done!" << endl;
                cout << "Score for this question: " << questionScore << endl; 
            } else if (numCorrect > 0) {
                cout << "Partially correct. " << numCorrect << " out of " << formattedCardAnswer.length() << " correct." << endl;
                cout << "Score for this question: " << questionScore << endl; 
            } else {
                cout << "Incorrect answer. Correct answer was: " << formattedCardAnswer << endl;
                cout << "Score for this question: 0" << endl; 
            }

            updateScore(newStudent, questionScore, false);

        } else if (choice == 2) {
            cout << "Question declined. No score awarded for this round." << endl;
            updateScore(newStudent, 0, false);
        } 
        putBackCard(card);
    }

    void chooseQuestion() { // user choose discarded or unanswered question
        int choice;
        cout << "Would you like to choose a Discarded/Unanswered question?" << endl <<
        "1. Discarded" << endl <<
        "2. Unanswered" << endl <<
        "Enter your choice: ";
        validateInput("chooseQuestion", choice); 
        if (choice == 1) {
            answerDiscardedQuestion();
        } else if (choice == 2) {
            answerUnansweredQuestion();
        } 
    } 

    void putBackCard(Question answeredCard) { // untested - put back card after round ends
        if (discardedCards.getSize() != 10) {
            discardedCards.push(answeredCard); // stack
        } else {
            answeredCards.prepend(answeredCard); // linkedlist
        }
    }

    void viewScoreboard() { // prompt user to select view leaderboard/hierarchy
        int choice;
        cout << "View Score:" << endl 
        << "1. Leaderboard" << endl 
        << "2. Rank hierarchy" << endl 
        << "Enter your choice: ";
        validateInput("viewRanking", choice);
        if (choice == 1) {
            //showLeaderboard();
        } else if (choice == 2) {
            //showhierarchy();
        } 
    }

    void repeatRound() { // 3 rounds then calculate the total score for each student
        for (size_t i = 1; i < 4; i++)
        {
            cout << "Round " << i << ":" << endl;
            chooseQuestion();
        }
        // temporary code to show student list
        for (int i = 0; i < studentList.getSize(); i++) {
            Student student = studentList[i];
            cout << "Student ID: " << student.id << ", Name: " << student.name << ", Score: " << student.score << endl;
        }
        // viewScoreboard();
    }
};

int main() {
    Game game;
    game.loadStudentData();
    game.loadQuestionData();
    game.setUpDecks();
    game.startGame();
    return 0;
}
