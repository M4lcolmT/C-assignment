#ifndef GAME_HPP
#define GAME_HPP

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <random>
#include <iomanip>
#include <algorithm>
#include <queue>

#include "Student.hpp"
#include "Question.hpp"
#include "LinkedList.hpp"
#include "Vector.hpp"
#include "Stack.hpp"
#include "Tree.hpp"
#include "DoublyLinkedList.hpp"
#include "ArrayList.hpp"
using namespace std;


class Game {
private:
    DoublyLinkedList<Student> studentList;
    Vector<Question> questionList; // decide should use linkedlist or what...
    Stack<Question, 5> discardedCards;
    Stack<Question, 295> unansweredCards;
    LinkedList<Question> answeredCards;
    Student* newStudent;

public:
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
        // for (int i = 0; i < studentList.getSize(); i++) {
        //     Student student = studentList[i];
        //     student.printScores();
        // }
    }

    void loadQuestionData() {
        ifstream file("questions.csv");
        string line;
        if (!file.is_open()) {
            cerr << "Error opening questions.csv file." << endl;
            return;
        }

        while (getline(file, line)) {
            istringstream iss(line);
            string idStr, category, questionText, correctAnswer;
            LinkedList<string> options;

            getline(iss, idStr, '|');
            getline(iss, category, '|');
            getline(iss, questionText, '|');

            string option;
            while (getline(iss, option, '|')) {
                options.append(option);
            }

            // Extract the correct answer from the options list
            correctAnswer = options.popBack();

            int id = stoi(idStr);

            questionList.push_back(Question(id, category, questionText, options, correctAnswer));
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
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clear the input stream
            
            newStudent = new Student(id, name);
            repeatRound();
        }
        else if (choice == 2) {
            cout << "I guess you are not up for the challenge, pussy...";
        }
    }


    void setUpDecks() { // delegate the questions into unanswered and discarded decks
        random_device rd;
        mt19937 gen(rd());
        
        // Shuffle the vector 
        shuffle(questionList.begin(), questionList.end(), gen); 

        // Add 5 questions from questionList to discardedCards
        for (int i = 0; i < 5 && i < questionList.getSize(); i++) {
            discardedCards.push(questionList[i]);
        }
        cout << "total count: " << questionList.getSize() << endl;
        cout << "discarded count: " << discardedCards.getSize() << endl;

        // Add remaining questions from questionList to unansweredCards
        for (int i = 5; i < questionList.getSize(); i++) {
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


    void answerDiscardedQuestion(Question card) {
        cout << "Question " << card.id << ": " << card.text << endl;
        for (size_t i = 0; i < card.options.getSize(); i++) {
            cout << card.options[i] << endl;
        }
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
            int questionScore = (numCorrect * 5) * 0.8;

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
            newStudent -> updateScore(card.id, questionScore);

        } else if (choice == 2) {
            cout << "Question declined. No score awarded for this round." << endl;
            newStudent -> updateScore(card.id, 0);
            // Put back discarded stack
        }
        putBackCard(card);
    }



    void answerUnansweredQuestion() {
        Question card = unansweredCards.pop();
        cout << "Question " << card.id << ": " << card.text << endl;
        for (size_t i = 0; i < card.options.getSize(); i++) {
            cout << card.options[i] << endl;
        }
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
            newStudent -> updateScore(card.id, questionScore);

        } else if (choice == 2) {
            cout << "Question declined. No score awarded for this round." << endl;
            newStudent -> updateScore(card.id, 0);
        }
        putBackCard(card);
    }

    void chooseQuestion() { // user choose discarded or unanswered question
        cout << "Here is a sneak peek of the discarded question ;)" << endl
        << "if you choose a discarded question, you only receive 80 percent of the total marks..." << endl;
        Question discardedCard = discardedCards.pop(); 
        cout << "Discarded Question: " << discardedCard.text << endl;
        int choice;
        cout << "Would you like to choose a Discarded/Unanswered question?" << endl <<
        "1. Discarded" << endl <<
        "2. Unanswered" << endl <<
        "Enter your choice: ";
        validateInput("chooseQuestion", choice); 
        if (choice == 1) {
            answerDiscardedQuestion(discardedCard);
        } else if (choice == 2) {
            answerUnansweredQuestion();
        } 
    } 

    void putBackCard(Question answeredCard) { // logic not set yet, how does the discarded cards work?
        answeredCards.prepend(answeredCard);
        cout << "Unanswered cards length: " << unansweredCards.getSize() << endl;
        cout << "Discarded cards length: " << discardedCards.getSize() << endl;
        cout << "Answered cards length: " << answeredCards.getSize() << endl;
        if (discardedCards.getSize() != 5) {
            Question q = unansweredCards.pop();
            discardedCards.push(q);
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
            showLeaderboard();
        } else if (choice == 2) {
            showHierarchy();
        } 
    }

    void repeatRound() { // 3 rounds then calculate the total score for each student
        for (size_t i = 1; i < 4; i++)
        {
            cout << "Round " << i << ":" << endl;
            chooseQuestion();
            cout << "round total score: " << newStudent -> getTotalScore() << endl;
            
        }
        newStudent -> printScores();
        viewScoreboard();
    }


    void showLeaderboard() {
    char sortOrder;
    cout << "Select sort order: [A]scending or [D]escending: ";
    cin >> sortOrder;

    if (sortOrder == 'A' || sortOrder == 'a') {
        studentList.sort([](const Student& a, const Student& b) {
            return a.getTotalScore() < b.getTotalScore(); // Ascending order
        });
    } else {
        studentList.sort([](const Student& a, const Student& b) {
            return a.getTotalScore() > b.getTotalScore(); // Descending order
        });
    }

    const int pageSize = 20;  // Number of students per page
    int totalPages = (studentList.getSize() + pageSize - 1) / pageSize;
    int currentPage = 0;

    while (true) {
        int start = currentPage * pageSize;
        int end = min(start + pageSize, studentList.getSize());

        cout << "\nLeaderboard - Page " << (currentPage + 1) << " of " << totalPages << ":\n";
        cout << setw(10) << left << "Rank"
            << setw(15) << left << "ID"
            << setw(25) << left << "Name"
            << setw(15) << left << "R1 (QID:Score)"
            << setw(15) << left << "R2 (QID:Score)"
            << setw(15) << left << "R3 (QID:Score)"
            << setw(15) << left << "Total Score" << endl;
        cout << "-------------------------------------------------------------------------------------------------------------------\n";

        for (int i = start; i < end; i++) {
            Student student = studentList.get(i);
            cout << setw(10) << left << (i + 1)
                << setw(15) << left << student.getID()
                << setw(25) << left << student.getName();

            LinkedList<Score> scores = student.getScores();
            for (int round = 0; round < 3; round++) {
                if (round < scores.getSize()) {
                    Score score = scores[round];
                    cout << setw(15) << left << score.getQuestionID() << ":" << score.getScore();
                } else {
                    cout << setw(15) << left << "N/A";
                }
            }

            cout << setw(15) << left << student.getTotalScore() << endl;
        }

        // Navigation
        cout << "\nNavigation: [N]ext page, [P]revious page, [S]earch, [E]xit\n";
        cout << "Enter choice: ";
        char choice;
        cin >> choice;

        if (choice == 'N' || choice == 'n') {
            if (currentPage < totalPages - 1) {
                currentPage++;
            } else {
                cout << "This is the last page.\n";
            }
        } else if (choice == 'P' || choice == 'p') {
            if (currentPage > 0) {
                currentPage--;
            } else {
                cout << "This is the first page.\n";
            }
        } else if (choice == 'S' || choice == 's') {
            searchStudent();
        } else if (choice == 'E' || choice == 'e') {
            break;
        }
    }
}


    void showHierarchy() {
        studentList.sort([](const Student& a, const Student& b) {
            return a.getTotalScore() > b.getTotalScore(); 
        });

        int topSize = min(studentList.getSize(), 30);
        ArrayList<Student> top30List;
        for (int i = 0; i < topSize; ++i) {
            top30List.add(studentList.get(i));
        }

        Tree tree;
        tree.buildTree(top30List);

        cout << "Displaying hierarchy of top 30 students:" << endl;
        tree.displayHorizontalTree();

        while (true) {
            cout << "\nOptions: [B]ack to Scoreboard, [C]heck student ID, [E]xit\n";
            cout << "Enter choice: ";
            char choice;
            cin >> choice;

            if (choice == 'B' || choice == 'b') {
                viewScoreboard();
                break;
            } else if (choice == 'C' || choice == 'c') {
                string searchID;
                cout << "Enter the student ID to check if they are in the top 30: ";
                cin >> searchID;

                TreeNode* foundStudent = tree.find(searchID);
                if (foundStudent) {
                    cout << "Student " << searchID << " is in the top 30 winners!" << endl;
                } else {
                    // Check if the ID exists in the overall student list
                    Student* student = studentList.search(searchID);
                    if (student) {
                        cout << "Student " << searchID << " exists but is not in the top 30 winners." << endl;
                    } else {
                        cout << "Student ID " << searchID << " is invalid." << endl;
                    }
                }
            } else if (choice == 'E' || choice == 'e') {
                viewScoreboard();
            } else {
                cout << "Invalid choice! Please enter B, C, or E." << endl;
                cin.clear();// Clear the error flag on cin
                cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discard the invalid input
            }
        }
    }
    
    void searchStudent() { // working code!
        string studentID;
        cout << "Enter the student number to search: ";
        cin >> studentID;

        Student* student = studentList.search(studentID);
        if (student) {
            cout << "\nStudent found:\n";
            cout << setw(15) << left << "ID"
                    << setw(25) << left << "Name"
                    << setw(15) << left << "Total Score" << endl;
            cout << "---------------------------------------------------\n";
            cout << setw(15) << left << student->getID()
                    << setw(25) << left << student->getName()
                    << setw(15) << left << student->getTotalScore() << endl;
        } else {
            cout << "Student with ID " << studentID << " not found." << endl;
            }
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

#endif