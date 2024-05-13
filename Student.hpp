#include <string>
#include "ArrayList.hpp"
using namespace std;

struct Score {
    int questionID;
    int score;

    Score() : questionID(0), score(0) {}  // Default constructor
    Score(int id, int score = 0) : questionID(id), score(score) {}
};

class Student {
private:
    string id;
    string name;
    ArrayList<Score> roundScores;

public:
    Student(string tpNum = "", string n = "") : id(tpNum), name(n), roundScores() {}
    
    void updateScore(int questionID, int questionScore) {
        Score roundScore = Score(questionID, questionScore);
        roundScores.add(roundScore);
    }

    string getID() {
        return id;
    }

    string getName() {
        return name;
    }

    ArrayList<Score> getScores() {
        return roundScores;
    }

    void printScores() {
        int totalScore = 0; // Corrected variable name
        for (int i = 0; i < roundScores.getSize(); i++) {
            Score score = roundScores[i];
            totalScore += score.score; 
            cout << "Question ID: " << score.questionID << ", Score: " << score.score << endl;
        }
        cout << "Your total score is: " << totalScore << endl;
    }
};
