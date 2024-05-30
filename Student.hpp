#pragma once

#include <string>
#include "LinkedList.hpp"
using namespace std;

struct Score {
    int questionID;
    int score;

    Score() : questionID(0), score(0) {}
    Score(int id, int s) : questionID(id), score(s) {}

    int getQuestionID() const {
        return questionID;
    }

    int getScore() const {
        return score;
    }
};

class Student {
private:
    string id;
    string name;
    LinkedList<Score> roundScores;
    int totalScore;

public:
    Student(string tpNum = "", string n = "") : id(tpNum), name(n), roundScores(), totalScore(0) {}
    
    // to update the student score struct with question id and round score
    void updateScore(int questionID, int score) { 
        roundScores.append(Score(questionID, score));
        totalScore += score;
    }

    string getID() {
        return id;
    }

    string getName() const {
        return name;
    }

    LinkedList<Score> getScores() const{
        return roundScores;
    }

    int getTotalScore() const {
        return totalScore;
    }

    void printScores() {
        cout << id << " " << name << endl;
        for (size_t i = 0; i < roundScores.getSize(); i++) {
            cout << "Question ID: " << roundScores.get(i).questionID << ", Score: " << roundScores.get(i).score << endl;
        }
        cout << "Your total score is: " << totalScore << endl;
    }
};
