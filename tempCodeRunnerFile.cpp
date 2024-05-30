    for (size_t i = 1; i < 4; i++) {
            cout << endl << "ROUND " << i << ":" << endl;
            chooseQuestion();

            cout << "Discarded Questions:" << endl;
            discardedCards.printQueue();

            cout << endl;
        }

        // newStudent->printScores();
        cout << endl << "Congratulations!!! Would you like to see how well you did ;) ?" << endl;
        studentList.append(*newStudent);
        viewScoreboard();
    }