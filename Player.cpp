
#include "class/Player.h"

void Player::StartGame(const std::string &gamerName)
{
    GamerName = gamerName;
    Player::guessCount = 0;
    GenerateSecretNumber();
}

void Player::GenerateSecretNumber()
{
    std::string number;

    do
    {
        std::cout << "Lutfen Rakamlari farkli 4 basamakli Gizli numaranizi giriniz: ";
        std::cin >> number;
    } while (!isValidNumber(number));

    // Gizli sayıyı ayarla
    Player::setSecretNumber(number);
}

std::pair<int, int> Player::GuessResult(const std::string &guess)
{
    int correctPlace, differentPlace = 0;
    int secretNumberLength = getSecretNumber().length();
    std::string answer;
    logger.message("Gizli Sayin: "+ getSecretNumber() + " (Ip uclarinizi yazarken '+' ve '-' ifadeler gelicek onlarin sayisini belirtiniz)", Logger::MessageType::WARN, true);
    int tempNumber = 0;
    bool changeGuess = false;
    do // Buradaki do-while fonksiyonu kullanicinin ip ucunu vermesi icin bir dongu olusturuyor
    {
        if (!changeGuess)
        {
            std::cout << "+: ";
        }
        else
        {
            std::cout << "-: ";
        }
        std::cin >> answer;
        tempNumber = std::stoi(answer); // girilen
        if (!isNumber(answer) || answer.length() != 1)
        {
            logger.message("Lutfen sadece rakam giriniz", Logger::MessageType::WARN, true);
            continue;
        }
        else if (tempNumber > secretNumberLength)
        {
            logger.message("Ip uclarinizin toplami tutulan sayilarin basamak sayisindan fazla olamaz", Logger::MessageType::WARN, true);
        }
        else
        {
            if (!changeGuess)
            {
                correctPlace = tempNumber;
                changeGuess = true;
                continue;
            }
            differentPlace = tempNumber;
        }

        std::pair<int, int> result = Gamer::correctGuessResult(guess); // burada kullanicinin verdigi ip uclari yanlis olup olmadiginin kontrolu yapiliyor
        if (result.first != correctPlace || result.second != differentPlace)
        {
            logger.message("Ip uclarinizin yanlis lutfen kontrol edip tekrar veriniz", Logger::MessageType::WARN, true);
            logger.message("Tuttugun numara: " + getSecretNumber() + " / Yapay Zeka tahmini: " + guess, Logger::MessageType::INFO, true);
            correctPlace, differentPlace = 0;
            changeGuess = false;
            continue;
        }
        break;
    } while (true);
    std::cout << "\n";
    return std::make_pair(correctPlace, differentPlace); // burada make_pair kullanarak 2 adet ciktiyi verebiliyoruz
}

bool Player::isNumber(const std::string &value) const
{
    bool isValid = true;
    for (char c : value)
    {
        if (!std::isdigit(c))
        {
            isValid = false;
            break;
        }
    }
    return isValid;
}

std::string Player::getGuess()
{
    std::string number;

    // Burada gene secret number olustururken ki gibi kullaniciden gelen tahminlerin de kurala uygun 4 basamakli bir sayi olması gerekir
    do
    {
        logger.message("Tahmininizi yaziniz: ", Logger::MessageType::INFO, false);
        std::cin >> number;
    } while (!isValidNumber(number));
    guessCount++;
    return number;
}

// Girilecek olan inputlarin rakamlari farkli 4 basamakli 0 ile baslamayacak olan bir sayi kontrol fonksiyonu
bool Player::isValidNumber(const std::string &number) const
{
    // Girilen input degerinin belirtilen uzunluga esit olup olmadigi kontrol ediliyor
    if (number.length() != 4)
    {
        logger.message("Hatali giris! Sayi 4 basamakli olmali.", Logger::MessageType::WARN, true);
        return false;
    }
    else if (number[0] == '0') // Girilen sayi 0 ile basliyor mu kontrolu
    {
        logger.message("Hatali giris! Sayiniz 0 ile baslayamaz", Logger::MessageType::WARN, true);
        return false;
    }

    std::set<char> seenDigits; // Bu kume oldugu icin sadece benzersiz elemanlar olabilir ayni eleman olamaz yani icerisinde ondan kullanildi
    for (char digit : number)
    {
        if (!isdigit(digit))
        {
            logger.message("Hatali giris! sadece 4 basamakli tam sayi girmeniz gerekiyor", Logger::MessageType::WARN, true);
            return false;
        }
        else if (seenDigits.count(digit) > 0)
        {
            logger.message("Hatali giris! Rakamlar birbirinden farkli ve sayisal olmali.", Logger::MessageType::WARN, true);
            return false;
        }
        seenDigits.insert(digit);
    }

    return true;
}