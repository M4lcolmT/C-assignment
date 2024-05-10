#include <iostream>
#include <vector>
#include <set>
#include <string>
#include <sstream>
using namespace std;
class Question {
public:
    int id;
    string category;
    string text;
    Vector<string> options;
    string correctAnswers;

    Question(int id, string category, string text, Vector<string> options, string correctAnswers)
        : id(id), category(category), text(text), options(options), correctAnswers(correctAnswers) {}
};