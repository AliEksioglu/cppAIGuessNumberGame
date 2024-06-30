#include <iostream>
#include <string>
#include <vector>
#include "class/AI.h"
#include "class/Player.h"
#include "class/Gamer.h"
#include "AI.cpp"
#include "Player.cpp"
#include "FindDigits.cpp"
#include "CorrectPositionDigits.cpp"

using namespace std;

std::string guessStringResult(int correctPlace, int diffrentPlace)
{
    return "+" + std::to_string(correctPlace) + " / -" + std::to_string(diffrentPlace);
}

int main()
{
    AI *ai = new AI();
    for (int i = 0; i < 10; i++)
    {
        ai->StartGame("YP");
        std::string _firstGuess = ai->getGuess();
        std::vector<int> firstGuess;
        std::pair<int, int> result;

        for (char number : _firstGuess)
        {
            int num = number - '0';
            firstGuess.push_back(num);
        }
        FindDigits *find_digit = new FindDigits(firstGuess);
        result = ai->GuessResult(_firstGuess);
        cout << "!!!İlk Tahmin " + _firstGuess + " Gizli Sayimiz: " + ai->getSecretNumber()  << endl;
        while ((result.first + result.second) < 4)
        {
            find_digit->Process(result.first, result.second);
            _firstGuess = "";
            for (int number : find_digit->startGuess)
            {
                _firstGuess += to_string(number);
            }
            // cout << "Gizli Sayi: " + ai->getSecretNumber() + " / Tahmin: " + _firstGuess + " / Yanit: +" + to_string(result.first) + " / -" + to_string(result.second) << endl;
            result = ai->GuessResult(_firstGuess);
        }

        cout << _firstGuess + " - yanit: +" + to_string(result.first) + " / -" + to_string(result.second) << endl;
        CorrectPositionDigits *correct_digit = new CorrectPositionDigits(find_digit->startGuess);
        while ((result.first) < 4)
        {
            correct_digit->Process(result.first, result.second);
            _firstGuess = "";
            for (int number : correct_digit->lastGuess)
            {
                _firstGuess += to_string(number);
            }
            result = ai->GuessResult(_firstGuess);
        }
        cout << "Bulundu sayilar: " + _firstGuess + "   secret number: " + ai->getSecretNumber() << endl;
    }
}