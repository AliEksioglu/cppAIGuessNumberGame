#ifndef PLAYER_H
#define PLAYER_H

#include "Gamer.h"

class Player : public Gamer
{
public:
    virtual ~Player() {}
    void StartGame(const std::string &gamerName) override;
    std::string getGuess() override;
    std::pair<int, int> GuessResult(const std::string &guess) override;


protected:
    void GenerateSecretNumber() override;

private:
    bool isNumber(const std::string &number) const;
    bool isValidNumber(const std::string &number) const; // Rakamlari farkli 4 basamakli bir input alabilmek icin kontrol fonksiyonu
};

#endif