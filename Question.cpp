#include <iostream>
#include <vector>
#include <set>
#include <string>
#include <sstream>

class Question {
public:
    int id;
    std::string text;
    std::vector<std::string> options; // Options for answers
    std::set<char> correctAnswers;    // Correct answer(s) stored as 'a', 'b', 'c', etc.

    Question(int id, const std::string& text, const std::vector<std::string>& options, const std::set<char>& correctAnswers)
        : id(id), text(text), options(options), correctAnswers(correctAnswers) {}

    // Calculate the score for the given answers
    int calculateScore(const std::string& answers, int baseScore) {
        std::set<char> userAnswers;
        std::istringstream answerStream(answers);
        char answer;
        while (answerStream >> answer) {
            if (answerStream.peek() == ',') answerStream.ignore();
            userAnswers.insert(answer);
        }

        if (userAnswers == correctAnswers) {
            return baseScore; // Full score for fully correct answers
        } else {
            int correctCount = 0;
            for (char ans : userAnswers) {
                if (correctAnswers.find(ans) != correctAnswers.end()) {
                    correctCount++;
                }
            }
            if (correctCount > 0 && correctCount < correctAnswers.size()) {
                return baseScore / 2; // 50% score if only part of the answers are correct
            }
        }
        return 0; // No score for incorrect answers
    }
};
