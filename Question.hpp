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
    string correctAnswers;   

    Question() : id(0) {}
    
    Question(int id, const string& text, const string& option1, const string& option2, const string& option3,  const string& option4, const string& correctAnswers)
        : id(id), text(text), option1(option1), option2(option2),option3(option3),option4(option4),correctAnswers(correctAnswers) {}

    
};
