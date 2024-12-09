#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
#include <ctime>

using namespace std;

vector<string> loadWords(const string& fileName) {
    ifstream file(fileName);
    vector<string> words;
    string word;
    while (file >> word) {
        words.push_back(word);
    }
    return words;
}

void loadHighScores(const string& fileName, vector<string>& names, vector<int>& scores) {
    ifstream file(fileName);
    string name;
    int score;
    while (file >> name >> score) {
        names.push_back(name);
        scores.push_back(score);
    }
}

void saveHighScores(const string& fileName, const vector<string>& names, const vector<int>& scores) {
    ofstream file(fileName);
    for (int i = 0; i < names.size(); ++i) {
        file << names[i] << " " << scores[i] << endl;
    }
}

void addWord(const string& fileName, vector<string>& words) {
    ofstream file(fileName); 
    string newWord;
    cout << "I want to add the word: ";
    cin >> newWord;

    words.push_back(newWord); 

    for (const string& word : words) {
        file << word << endl; 
    }

}

void displayHighScores(const vector<string>& names, const vector<int>& scores) {
    cout << endl << "<< High Scores >>" << endl;
    for (int i = 0; i < names.size(); ++i) {
        cout << names[i] << ": " << scores[i] << " points" << endl;
    }
}

int Score(int attemptsLeft) {
    return (attemptsLeft * 100);
}

void playGame(const vector<string>& words, vector<string>& names, vector<int>& scores) {
    if (words.empty()) {
        cout << "No words to play. Please add words to the slowa file." << endl;
        return;
    }

    srand(time(0));
    string word = words[rand() % words.size()];
    string guessedWord(word.size(), '_');
    int attemptsLeft = 6;
    vector<char> wrongGuesses;

    while (attemptsLeft > 0 && guessedWord != word) {
        cout << endl << "Word: " << guessedWord << endl;
        cout << "Attempts Left: " << attemptsLeft << endl;
        cout << "Wrong Guesses: ";
        for (int i = 0; i < wrongGuesses.size(); ++i) 
        {
            cout << wrongGuesses[i] << " ";
        }
        cout << endl << "Enter a letter: ";

        char guess;
        cin >> guess;

        if (word.find(guess) != string::npos) {
            for (int i = 0; i < word.size(); ++i) {
                if (word[i] == guess) guessedWord[i] = guess;
            }
        }
        else {
            --attemptsLeft;
            wrongGuesses.push_back(guess);
        }
    }

    if (guessedWord == word) {
        cout << endl << "Congratulations! You guessed the word: " << word << endl;
        int score = Score(attemptsLeft);
        cout << "Your score: " << score << endl;

        string playerName;
        cout << "Enter your name: ";
        cin >> playerName;

        names.push_back(playerName);
        scores.push_back(score);

        if (names.size() > 10) {
            names.resize(10);
            scores.resize(10);
        }

        saveHighScores("high_scores.txt", names, scores);
    }
    else {
        cout << endl << "Game Over. The word was: " << word << endl;
    }
}

int main() {
    vector<string> words = loadWords("slowa.txt");
    vector<string> names;
    vector<int> scores;
    loadHighScores("high_scores.txt", names, scores);

    int choice;
    do {
        cout << endl << "<< Hangman Game >>" << endl;
        cout << "1. Play Game" << endl << "2. View High Scores" << endl << "3. Add Word" << endl << "4. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
        case 1:
            playGame(words, names, scores);
            break;
        case 2:
            displayHighScores(names, scores);
            break;
        case 3:
            addWord("slowa.txt", words);
            break;
        case 4:
            cout << "Closing" << endl;
            break;
        default:
            cout << "Invalid choice. Try again." << endl;
        }
    } while (choice != 4);

    return 0;
}
