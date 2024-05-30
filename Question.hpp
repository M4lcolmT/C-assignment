#pragma once

#include <iostream>
#include <string>
#include "LinkedList.hpp"
using namespace std;

class Question {
public:
    int id;
    string category;
    string text;
    LinkedList<string> options;
    string correctAnswers;

    Question() : id(0) {}

    Question(int id, string category, string text, LinkedList<string> options, string correctAnswers)
        : id(id), category(category), text(text), options(options), correctAnswers(correctAnswers) {}
};
