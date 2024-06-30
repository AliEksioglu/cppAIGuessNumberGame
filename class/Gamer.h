#ifndef GAMER_H
#define GAMER_H

#include <iostream>
#include <utility>
#include <string>
#include <set>

#include "Logger.h"

class Gamer
{

private:
    std::string secretNumber; // Bilinmesi gereken numaraya disaridan erisimi engellenmesi icin

public:
    std::string GamerName;
    virtual ~Gamer() {}
    virtual std::string getGuess() = 0;
    virtual std::pair<int, int> GuessResult(const std::string &guess) = 0; // Burada std::pair kullanmamin nedeni 2 adet tahmin sonucu dondurmem gerekiyor ve yapay zeka bu sonuclara gore farkli
    virtual void StartGame(const std::string &gamerName) = 0;
    int guessCount = 0;
    // davranislar sergileyebilir

    std::string getSecretNumber() const { return secretNumber; } // okunmasi icin kullanildiginde degistirilmesin diye const kullandim

    // bu da secretNumber atamasi yapmak icin
    void setSecretNumber(const std::string &number)
    {
        this->secretNumber = number;
    }

protected:
    // Burada asinda kullanicini verdigi ipucu dogrumu kontrolu yapiliyor ama ayni zamanda
    // Bu kodu AI dogru yaniti vermek icinde kullaniyor
    Logger logger;
    virtual void GenerateSecretNumber() = 0;

    std::pair<int, int> correctGuessResult(const std::string &guess)
    {
        int correctPlace = 0, differentPlace = 0;
        std::string secretNumber = getSecretNumber();
        int size = secretNumber.length();
        for (int i = 0; i < size; i++)
        {
            // Burada tahminin sonucu hesapliyoruz
            if (secretNumber[i] == guess[i])
            {
                correctPlace++;
                continue;
            }
            else if (secretNumber.find(guess[i]) != std::string::npos)
            {
                differentPlace++;
                continue;
            }
        }

        return std::make_pair(correctPlace, differentPlace);
    };
};

#endif