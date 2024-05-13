#include <string>
#include "Vector.hpp"
using namespace std;

class Student {
private:
    string id;
    string name;
    Vector<int> roundScores;
    int totalScore;

public:
    Student(string tpNum = "", string n = "") : id(tpNum), name(n), roundScores(), totalScore(0) {}
    
    void updateScore(int questionID, int score) {
        roundScores.push_back(score);
        totalScore += score;
    }

    string getID() {
        return id;
    }

    string getName() {
        return name;
    }

    Vector<int> getScores() {
        return roundScores;
    }

    int getTotalScore() {
        return totalScore;
    }

    void printScores() {
        cout << "Scores for student " << name << " (ID: " << id << "):" << endl;
        for (size_t i = 0; i < roundScores.getSize(); i++) {
            cout << "Round " << i + 1 << ": " << roundScores[i] << endl;
        }
        cout << "Total score: " << totalScore << endl;
    }
};

