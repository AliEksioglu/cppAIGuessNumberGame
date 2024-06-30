#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <unordered_set>

using namespace std;

class CorrectPositionDigits
{
private:
    unordered_set<int> correctIndexes = {};
    int beginIndex = 0;
    int beginTempIndex = 1;
    bool isSwap = false;
    pair<int, int> lastResult;

public:
    vector<int> lastGuess;
    CorrectPositionDigits(vector<int> guessNumber)
    {
        lastGuess = guessNumber;
    }

    void Process(int correctPosition, int differentPosition) // Dogru sayilarilarin yerini bulmak icin gerekli olan algoritmamiz
    {

        if (beginTempIndex == 4)
        {
            beginIndex++;
            beginTempIndex = beginIndex + 1;
            Process(correctPosition, differentPosition);
            return;
        }
        if (beginIndex == 0 && lastGuess[beginTempIndex] == 0)
        {
            beginTempIndex++;
            Process(correctPosition, differentPosition);
            return;
        }
        if (!isSwap)
        {
            for (int i = beginTempIndex; i < lastGuess.size(); i++)
            {
                if (Contains(beginIndex, correctIndexes))
                {
                    beginIndex++;
                    beginTempIndex = beginIndex + 1;
                }
                else
                {
                    break;
                }
            }
            for (int i = beginTempIndex; i < lastGuess.size(); i++)
            {
                if (Contains(beginTempIndex, correctIndexes))
                {
                    beginTempIndex++;
                }
                else
                {
                    break;
                }
            }
            SwapNumberPosition();
            isSwap = true;
            lastResult.first = correctPosition;
            lastResult.second = differentPosition;
        }
        else
        {
            isSwap = false;
            if ((correctPosition - lastResult.first) <= 0) //
            {
                SwapNumberPosition(); // Geri koyduk
                beginTempIndex++;
                Process(lastResult.first, lastResult.second);
                return;
            }
            else
            {
                if ((correctPosition - lastResult.first) > 1)
                {
                    correctIndexes.insert(beginIndex);
                    correctIndexes.insert(beginTempIndex);
                }
                lastResult.first = correctPosition;
                lastResult.second = differentPosition;
                beginTempIndex = beginIndex + 1;
                Process(correctPosition, differentPosition);
                return;
            }
        }
    }

private:
    void SwapNumberPosition()
    {
        int temp = lastGuess[beginIndex];
        lastGuess[beginIndex] = lastGuess[beginTempIndex];
        lastGuess[beginTempIndex] = temp;
    }

    bool Contains(int value, unordered_set<int> array)
    {
        return (array.find(value) != array.end());
    }
    bool Contains(int value, std::vector<int> array)
    {
        return (find(array.begin(), array.end(), value) != array.end());
    }
};