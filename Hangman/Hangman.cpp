#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <string>
#include <vector>

#define MAX_ATTEMPTS 6

using namespace std;

class HangmanGame {
public:
    HangmanGame() {
        srand(static_cast<unsigned int>(time(nullptr)));
        secretWord = getRandomWord();
        currentWord = string(secretWord.length(), '_');
        attemptsLeft = MAX_ATTEMPTS;
    }

    void play() {
        cout << "Welcome to Hangman!\nCategory: Fruits\nYou have " << attemptsLeft << " attempts to guess the fruit name.\n";
        
        while (attemptsLeft > 0) {
            displayGameInfo();
            char guess;
            cout << "Guess a letter: ";
            cin >> guess;

            if (!isalpha(guess)) {
                cout << "Please enter a valid letter.\n";
                continue;
            }

            guess = tolower(guess);
            if (alreadyGuessed(guess)) {
                cout << "You've already guessed that letter.\n";
            } else {
                guessedLetters.push_back(guess);
                if (updateCurrentWord(guess)) {
                    cout << "Good guess!\n\n";
                    if (currentWord == secretWord) {
                        displayGameInfo();
                        cout << "Congratulations! You guessed the word: " << secretWord << endl;
                        return;
                    }
                } else {
                    cout << "Incorrect guess.\n";
                    attemptsLeft--;
                    drawHangman(attemptsLeft);
                }
            }
        }

        cout << "The word was: " << secretWord << endl;
    }

private:
    string secretWord, currentWord;
    int attemptsLeft;
    vector<char> guessedLetters;

    string getRandomWord() {
        vector<string> words = {"apple", "banana", "cherry", "grape", "kiwi"};
        return words[rand() % words.size()];
    }

    bool alreadyGuessed(char letter) {
        return find(guessedLetters.begin(), guessedLetters.end(), letter) != guessedLetters.end();
    }

    bool updateCurrentWord(char letter) {
        bool correctGuess = false;
        for (size_t i = 0; i < secretWord.length(); i++) {
            if (secretWord[i] == letter) {
                currentWord[i] = letter;
                correctGuess = true;
            }
        }
        return correctGuess;
    }

    void displayGameInfo() {
        cout << "\nWord: " << currentWord << "\nChances: " << attemptsLeft << "\nGuessed letters: ";
        for (char letter : guessedLetters) cout << letter << ' ';
        cout << endl;
    }

    void drawHangman(int attemptsLeft) {
        const vector<string> hangmanStages = {
        "_________\n  |     |\n  |     O\n  |\n  |\n  |\n  |\n =============== \n",
        "_________\n  |     |\n  |     O\n  |     |\n  |\n  |\n  |\n =============== \n",
        "_________\n  |     |\n  |     O\n  |    /|\n  |\n  |\n  |\n =============== \n",
        "_________\n  |     |\n  |     O\n  |    /|\\ \n  |\n  |\n  |\n =============== \n",
        "_________\n  |     |\n  |     O\n  |    /|\\ \n  |    /\n  |\n  |\n =============== \n",
        "_________\n  |     |\n  |     O\n  |    /|\\   YOU HAVE FAILED!!  \n  |    / \\ \n  |\n  |\n =============== \n",
        };
        cout << hangmanStages[MAX_ATTEMPTS - attemptsLeft - 1];
    }
};

int main() {
     srand(static_cast<unsigned int>(time(nullptr))); //seeding rng
    HangmanGame game;
    game.play();
    return 0;
}
