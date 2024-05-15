#include <string>
#include "Vector.hpp"
using namespace std;

struct Score {
    int questionID;
    int score;

    Score() : questionID(0), score(0) {}
    Score(int id, int s) : questionID(id), score(s) {}
};

class Student {
private:
    string id;
    string name;
    Vector<Score> roundScores;
    int totalScore;

public:
    Student(string tpNum = "", string n = "") : id(tpNum), name(n), roundScores(), totalScore(0) {}
    
    void updateScore(int questionID, int score) {
        roundScores.push_back(Score(questionID, score));
        totalScore += score;
    }

    string getID() {
        return id;
    }

    string getName() const {
        return name;
    }

    Vector<Score> getScores() {
        return roundScores;
    }

    int getTotalScore() const {
        return totalScore;
    }

    void printScores() {
        cout << id << " " << name << endl;
        for (size_t i = 0; i < roundScores.getSize(); i++) {
            cout << "Question ID: " << roundScores[i].questionID << ", Score: " << roundScores[i].score << endl;
        }
        cout << "Your total score is: " << totalScore << endl;
    }
};
