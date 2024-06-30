#include "class/AI.h"

void AI::StartGame(const std::string &gamerName) // Burada tekrar oynamak icin butun degerleri baslangic degerine esitliyoruz herseyi temizliyoruz
{
  AI::lastGuess.clear();
  AI::GamerName = gamerName;
  AI::guessCount = 0;

  GenerateSecretNumber();
}

void AI::GenerateSecretNumber()
{
  std::string secret_number = GenerateNumber();
  Gamer::setSecretNumber(secret_number);
}

std::pair<int, int> AI::GuessResult(const std::string &guess)
{
  return Gamer::correctGuessResult(guess);
}

std::string AI::getGuess()
{
  if (AI::lastGuess.size() == 0) // İlk tahmini olustururken bunu kullaniyoruz digerlerinde zaten tahminimiz var ve degistiriliyor
  {
    std::string firstGuess = GenerateNumber();
    for (char number : firstGuess)
    {
      int num = number - '0';
      AI::lastGuess.push_back(num);
    }
    if (!Contains(0, lastGuess)) // Biraz uzun anlatirim sorulursa
    {
      std::string generated_number;
      std::random_device rd;
      std::mt19937 generator(rd());
      std::uniform_int_distribution<int> distribution(1, 3);
      int random_index = distribution(generator);

      lastGuess[random_index] = 0;
    }
    if (find_digits->startGuess.size() == 0)
    {
      find_digits->startGuess = lastGuess;
    }
  }
  std::string guess = "";
  for (int number : AI::lastGuess)
  {
    guess += std::to_string(number);
  }
  AI::guessCount++;
  return guess;
}

void AI::ProcessPlayerGuess(const int &correctPlace, const int &differentPlace)
{
  if ((correctPlace + differentPlace) == getSecretNumber().size())
  {
    if (correct_digits->lastGuess.size() == 0)
    {
      correct_digits->lastGuess = lastGuess;
    }
    correct_digits->Process(correctPlace, differentPlace);
    lastGuess = correct_digits->lastGuess;
  }
  else
  {
    find_digits->Process(correctPlace, differentPlace);
    lastGuess = find_digits->startGuess;
  }
}

std::string AI::GenerateNumber()
{
  std::string generated_number;
  std::random_device rd;
  std::mt19937 generator(rd());
  std::vector<std::string> available_digits = allNumbers; // Burada olasi sayilar dizisini kopyaliyoruz bunlar arasindan olusturacak

  auto it = std::find(available_digits.begin(), available_digits.end(), "0"); // burasi muhtemel sayilarda eger 0 varsa once o 0 numarasini cikarmamiz gerekiyor cunku ilk eleman 0 olamaz
  if (it != available_digits.end())                                           // Burada ilk basta 0 i cikartip ilk rakami random seciyoruz sonra 0 i geri ekleyip diger rakamlari asagidaki for da yaziyoruz
  {
    available_digits.erase(it);
    std::uniform_int_distribution<int> distribution(0, available_digits.size() - 1);
    int random_index = distribution(generator);
    generated_number += available_digits[random_index];
    available_digits.erase(available_digits.begin() + random_index);
    available_digits.push_back("0");
  }

  for (int i = 1; i < 4; ++i)
  {
    std::uniform_int_distribution<int> distribution(0, available_digits.size() - 1);
    int random_index = distribution(generator);
    generated_number += available_digits[random_index];
    available_digits.erase(available_digits.begin() + random_index);
  }
  return generated_number;
}
