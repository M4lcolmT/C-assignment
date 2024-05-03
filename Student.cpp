#include <iostream>
#include <string>

struct Student {
    std::string name;
    int studentID;
    int score;

    Student(std::string n, int id) : name(n), studentID(id), score(0) {}
};

void updateScore(Student& student, int questionScore, bool isDiscarded) {
    if (isDiscarded) {
        student.score += static_cast<int>(questionScore * 0.8);  // 80% of the original score
    } else {
        student.score += questionScore;  // Full score
    }
}

int main() {
    Student melinda("Melinda", 12345);
    return 0;
}
