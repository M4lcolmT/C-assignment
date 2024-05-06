#include <string>
using namespace std;

struct Student {
    string name;
    int id;
    int score;

    Student(std::string n = "", int sid = 0, int sc = 0) : name(n), id(sid), score(sc) {}
};

void updateScore(Student& student, int questionScore, bool isDiscarded) {
    if (isDiscarded) {
        student.score += static_cast<int>(questionScore * 0.8);  // 80% of the original score
    } else {
        student.score += questionScore;  // Full score
    }
}
