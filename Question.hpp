#include <iostream>
#include <vector>
#include <set>
#include <string>
#include <sstream>
using namespace std;

class Question {
public:
    int id;
    string text;
    string option1;
    string option2;
    string option3;
    string option4;
    set<char> correctAnswers;    // Correct answer(s) stored as 'a', 'b', 'c', etc.

    Question() : id(0) {}
    
    Question(int id, const string& text, const string& option1, const string& option2, const string& option3,  const string& option4, const set<char>& correctAnswers)
        : id(id), text(text), option1(option1), option2(option2),option3(option3),option4(option4),correctAnswers(correctAnswers) {}

    
};
