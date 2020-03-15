#ifndef GAME_CLASS
#define GAME_CLASS

#include <string>
#include <vector>
#include <iostream>
#include <queue>
#include <utility>

class Game {
public:
    // constructors
    Game(int size, int ladderNum, int snakeNum, std::vector<int> &ladders, std::vector<int> &snakes);
    ~Game();

    // member functions
    std::string solve(); // solve the game, return string representing solved output

    friend std::ostream& operator<<(std::ostream& os, const Game& game);
    
private:
    std::string output() const; // returns output after board is solved

    int* snakeStart;
    int* snakeEnd;
    int* ladderStart;
    int* ladderEnd;

    std::queue<int> bfsQueue;
    std::vector<std::pair<int,std::string>> pred;
    std::vector<int> distance;
    std::vector<bool> visited;

    const int gameSize;
    const int numSnakes;
    const int numLadders;
};

#endif