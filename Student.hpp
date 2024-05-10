#include <string>
using namespace std;

struct Student {
    string id;
    string name;
    int score;

    Student(string tpNum = "", string n = "", int sc = 0) : id(tpNum), name(n), score(sc) {}
};


void updateScore(Student& student, int questionScore, bool isDiscarded) {
    if (isDiscarded) {
        student.score += static_cast<int>(questionScore * 0.8);  // 80% of the original score
    } else {
        student.score += questionScore;  // Full score
    }
}
