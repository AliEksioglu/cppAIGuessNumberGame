#include <iostream>
#include <string>
#include <vector>
#include "class/AI.h"
#include "class/Player.h"
#include "class/Gamer.h"
#include "AI.cpp"
#include "Player.cpp"

using namespace std;

std::string guessStringResult(int correctPlace, int diffrentPlace)
{
    return "+" + std::to_string(correctPlace) + " / -" + std::to_string(diffrentPlace);
}

int main()
{
    Logger logger;
    std::vector<Gamer *> gamerList;
    Player *player = new Player();
    AI *ai = new AI();
    //AI *ai2 = new AI();
    Gamer *activePlayer;
    int activePlayerIndex = 0;
    bool finishedGame = false;

    std::string playerName;
    std::cout << "Lutfen Oyuncu isminizi giriniz: ";
    std::getline(std::cin, playerName);
    player->StartGame(playerName);
    ai->StartGame("Yapay Zeka 1");
    //ai2->StartGame("Yapay Zeka 2");

    gamerList.push_back(player);
    gamerList.push_back(ai);
    //gamerList.push_back(ai2);

    std::string guess;
    std::pair<int, int> guessResult;
    std::string message;

    logger.message("\nGizli numaralar Olusturuldu. Oyun Basliyor !! \n", Logger::MessageType::INFO, true);
    do
    {
        activePlayer = gamerList[activePlayerIndex];
        logger.message("\n!!!Sirasi olan oyuncu: " + activePlayer->GamerName, Logger::MessageType::GREEN, true);
        // for (int i = 0; i < gamerList.size(); i++)
        // {
        //     logger.message(gamerList[i]->GamerName + " gizli sayisi: " + gamerList[i]->getSecretNumber(), Logger::MessageType::GREEN, true);
        // }
        guess = activePlayer->getGuess();
        logger.message("(" + activePlayer->GamerName + ")'in tahmini = " + guess + "\n", Logger::MessageType::INFO, true);
        for (int i = 0; i < gamerList.size(); i++)
        {
            if (i == activePlayerIndex)
                continue;
            guessResult = gamerList[i]->GuessResult(guess); // burada ileride belki buradaki ip uclarini bir yere kayit ederiz ne yapti etti yada oyuncuya gostermek icin
            message = "(" + gamerList[i]->GamerName + ")'in: tahmine yaniti ==> " + guessStringResult(guessResult.first, guessResult.second);
            logger.message(message, Logger::MessageType::DEFAULT, true);
            if (guessResult.first == 4)
            {
                finishedGame = true;
                break;
            }

            // AI sinifi nesnesi varsa demekki bu yapay zeka
            if (auto aiPlayer = dynamic_cast<AI *>(activePlayer))
            {
                aiPlayer->ProcessPlayerGuess(guessResult.first, guessResult.second);
            }
        }
        if (!finishedGame)
            activePlayerIndex = (activePlayerIndex + 1) % gamerList.size();
    } while (!finishedGame);

    logger.message("\n\n!KAZANAN OYUNCUMUZ " + activePlayer->GamerName + " tahmin sayisi: " + std::to_string(activePlayer->guessCount) + " Gizli Sayisi: " + activePlayer->getSecretNumber() + "\n", Logger::MessageType::WARN, true);
    logger.message("Diger Yarismacilarin Gizli Sayilari ve kac adet tahminde bulunduklari: \n", Logger::MessageType::DEFAULT, true);

    for (int i = 0; i < gamerList.size(); i++)
    {
        if (i == activePlayerIndex)
            continue;
        logger.message("(" + gamerList[i]->GamerName + ")" + "'in tahmin sayisi: " + std::to_string(gamerList[i]->guessCount) + "/ Gizli Sayisi: " + gamerList[i]->getSecretNumber(), Logger::MessageType::INFO, true);
    }

    return 0;
}
