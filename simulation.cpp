#include <vector>
#include <iostream>
#include <time.h>
#include <cmath>
class Strategy {
    
    public:

    // default constructor : DO NOT USE
    Strategy(){

    }

    // constructor: 
    // focus is a vector of ints that correspond to the castles to weight heavily
    // focusNums is the number of troops to exclusively allocate to the focused castles
    // min is the minimum number of troops any castle should get
    Strategy(std::vector<int> focus, int focusNums, int min){
        focuses = focus;
        focusNum = focusNums;
        for (int i = 0; i < 10; i++){
            strats.push_back(min);
        }
        totalSoldiers = 100 - 10*min;
        generateStrategy();
    }
    void generateStrategy(){
        int totalWeights = 0;
        for (int i = 0; i < focuses.size(); i++){
            totalWeights+=focuses[i];
            totalWeights++;
        }
        int eachWeight = round(((double)focusNum / (double)totalWeights));
        for (int i = 0; i < focuses.size(); i++){
            strats[focuses[i]] += (eachWeight*(focuses[i]+1));
        }
        totalSoldiers -= focusNum;
        totalSoldiers/=9;
        for (int i = 0; i < 9; i++){
            strats[i] += totalSoldiers;
        }
    }

    void generateVariation(int maxVariation){
        int variation = rand()%maxVariation + 1;
        for (int i = 0; i < focuses.size(); i++){
            int add = rand()%2;
            int partner = rand()%(focuses.size()) + 1;
            if (add == 1){
                if (strats[focuses[(i+partner)%focuses.size()]] >= variation){
                    strats[focuses[i]] += variation;
                    strats[focuses[(i+partner)%focuses.size()]] -= variation;
                }
            }
            else {
                if (strats[focuses[i]] >= variation){
                    strats[focuses[i]] -= variation;
                    strats[focuses[(i+partner)%focuses.size()]] += variation;
                }
            }
        }
    }
    int focusNum;
    int totalSoldiers;
    std::vector<int>strats;
    std::vector<int>focuses;
    std::pair<int, int> decideIfBeats(std::vector<int> FirstStrat, std::vector<int> secondStrat){
        std::pair<int, int> output;
        output.first = 0;
        output.second = 0;
        for (int i = 0; i < 10; i++){
            if (output.first >= 20 || output.second >= 20){
                return output;
            }
            if (FirstStrat[i] > secondStrat[i]){
                output.first+=(i+1);
            }
            else if (secondStrat[i] > FirstStrat[i]){
                output.second+=(i+1);
            }
        }
        return output;
    }
};

int main(){
    srand(time(0));
    std::vector<int> focus;
    //focus.push_back(1);
    //focus.push_back(3);
    //focus.push_back(1);
    //focus.push_back(3);
    focus.push_back(4);
    focus.push_back(5);
    focus.push_back(6);
    
    

    std::cout<<"\n";
    Strategy k(focus, 70, 0);
    for (int i = 0; i < k.strats.size(); i++){
       std::cout<<" "<<k.strats[i];
    }

    static const int arr2[] = {3, 0, 13, 0, 0, 0, 36, 36, 12, 0};
    std::vector<int> SecondStrat (arr2, arr2 + sizeof(arr2) / sizeof(arr2[0]));
    
    static const int arr[] = {3, 12, 0, 0, 0, 0, 38, 37, 10, 0};
    std::vector<int> firstStrat (arr, arr + sizeof(arr) / sizeof(arr[0]));

    int numPoints = 0;
    int numWins = 0;
    int numGames = 0;
    for (int f = 70; f <=90; f++){
        for (int i = 0; i < 10000; i++){
            Strategy k(focus, f, 0);
            for (int j = 0; j < 10; j++){
                k.generateVariation(1);
                std::pair <int, int> result = k.decideIfBeats(SecondStrat, k.strats);
                numPoints += result.first;
                if (result.first > result.second){
                    numWins++;
                }
                numGames++;
            }
        }
    }
    std::cout<<numPoints/numGames<<" "<<(double)numWins/(double)numGames;
   
    
   // std::cout<<k.decideIfBeats(firstStrat, k.strats).first << " " << k.decideIfBeats(firstStrat, k.strats).second;
}

