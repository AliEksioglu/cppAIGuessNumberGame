#ifndef AI_H
#define AI_H

#include "Gamer.h"
#include "../CorrectPositionDigits.cpp"
#include "../FindDigits.cpp"

#include <algorithm>
#include <random>
#include <vector>

class AI : public Gamer 
{
public:
    virtual ~AI() {}
    void StartGame(const std::string &gamerName) override;
    std::string getGuess() override;
    std::pair<int, int> GuessResult(const std::string &guess) override;
    void ProcessPlayerGuess(const int &correctPlace, const int &differentPlace);
    std::vector<int> lastGuess = {};
protected:
    std::string GenerateNumber();
    void GenerateSecretNumber() override;
    std::vector<std::string> allNumbers = {"0", "1", "2", "3", "4", "5", "6", "7", "8", "9"};

private: // Yapay zeka sayiyi tahmin etmesi icin gerekli olan degiskenlerimiz

    FindDigits *find_digits = new FindDigits({});   //Gizli Sayidaki numaralari bulmasi icin gereken kod
    CorrectPositionDigits *correct_digits = new CorrectPositionDigits({});  //Dogru sayilari bulduktan sonra onlarin yerini bulmasi icin gereken kod
    bool Contains(int value, std::set<int> array)
    {
        return (array.find(value) != array.end());
    }
    bool Contains(int value, std::vector<int> array)
    {
        return (std::find(array.begin(), array.end(), value) != array.end());
    }
};

#endif