#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <unordered_set>

using namespace std;

class FindDigits
{
private:
    unordered_set<int> badNumbersHash = {};    // Bulunacak sayida olmayan rakamlar
    unordered_set<int> correctNumberHash = {}; // Bulunacak sayida olan sayilar
    pair<int,int> matchResult;
    int resultSum = 0;
    int matchResultSum = 0;
    int index = 0;
    int j = 0;
    int indexCacheValue = 0;
    bool sorguBekleniyor = false;

public:
    vector<int> startGuess;
    FindDigits(vector<int> guessNumber)
    {
        startGuess = guessNumber;
    }

    void Process(int correctPosition, int differentPosition)
    {
        // if((correctPosition+differentPosition)){
        //     for(int i = 0; i < startGuess.size() ; i++){
        //         badNumbersHash.insert(startGuess[i]);
        //     }
        // }
        if(j > 9 ){
            j = 0;
            index++;
        }
        if (!sorguBekleniyor)
        {
            indexCacheValue = startGuess[index];
            if (
                indexCacheValue == j || Contains(j, startGuess) || Contains(j, badNumbersHash) || Contains(j, correctNumberHash))
            {
                j++;
                Process(correctPosition, differentPosition);
                return;
            }
            startGuess[index] = j;
            matchResult.first = correctPosition;
            matchResult.second = differentPosition;
            matchResultSum = correctPosition + differentPosition;
            sorguBekleniyor = true;

        }else{
            sorguBekleniyor = false;
            resultSum = correctPosition + differentPosition;
            if(resultSum < matchResultSum){
                badNumbersHash.insert(j);
                correctNumberHash.insert(indexCacheValue);
                startGuess[index] = indexCacheValue;
                j=0;
                index++;
                Process(matchResult.first,matchResult.second);
                return;
            }else if(resultSum > matchResultSum){
                correctNumberHash.insert(j);
                matchResult.first = correctPosition;
                matchResult.second = differentPosition;
                j=0;
                index++;
                Process(matchResult.first,matchResult.second);
                return;
            }
            Process(matchResult.first,matchResult.second);
        }
    }


private:
    bool Contains(int value, unordered_set<int> array)
    {
        return (array.find(value) != array.end());
    }
    bool Contains(int value, std::vector<int> array)
    {
        return (find(array.begin(), array.end(), value) != array.end());
    }
};