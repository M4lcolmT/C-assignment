#ifndef QUESTION_HPP
#define QUESTION_HPP

#include <iostream>
#include <string>
#include "Vector.hpp"

class Question {
public:
    int id;
    std::string category;
    std::string text;
    Vector<std::string> options;
    std::string correctAnswers;

    Question() : id(0) {}

    Question(int id, std::string category, std::string text, Vector<std::string> options, std::string correctAnswers)
        : id(id), category(category), text(text), options(options), correctAnswers(correctAnswers) {}
};

#endif