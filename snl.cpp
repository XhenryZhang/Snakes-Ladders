// snl.cpp
// Driver class
// Author: Xinyi Zhang, 3/17/2020

#include "game.h"
#include <iostream>
#include <string>
#include <sstream>
#include <vector>

int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cout << "Usage: ./snl.out" << "<string representing number of games to solve, newline, N, L, S count, newline, then ladder, snake, newline, etc.>" << std::endl;
        exit(1);
    }

    std::string input = argv[1];
    std::string command = "";
    std::string med = "";
    std::string first(1, input[0]);
    int numGames = std::stoi(first); // extract number of game
    // std::cout << numGames << std::endl;
    std::vector<Game*> gameList; // calls default constructor for Game class

    if (numGames != 0) {
        input = input.substr(2);
    }

    int inputIndex = 0;
    // std::cout << input << std::endl;
    // parse input, each separated by newline
    for (int i = 0; i < numGames; i++) {
        int boardSize;
        int ladderNum;
        int snakeNum;
        std::vector<int> ladders;
        std::vector<int> snakes;
        for (int j = 0; j < 3; j++) {
            while (inputIndex != input.length() && input[inputIndex] != '\n') {
                command += input[inputIndex];
                inputIndex++; // inputIndex is newline sequence
            }

            // std::cout << command << std::endl;

            if (!(i == numGames - 1 && j == 2)) {
                inputIndex++; // go to next line
            }
            
            command += ' ';
            std::stringstream parser(command);
            std::vector<int> seq;
            while(getline(parser, med, ' ')) {
                seq.push_back(std::stoi(med));
            }

            if (j == 0) {
                // set lengths of snake and ladder array of i
                boardSize = seq[0] * seq[0];
                ladderNum = seq[1];
                snakeNum = seq[2];
            }else if (j == 1) {
                // modify adjacency list of game ladder
                ladders = seq;
            }else if (j == 2) {
                // modify adjacency list of game snake
                snakes = seq;
            }

            command = "";
        }
        Game* myGame = new Game(boardSize, ladderNum, snakeNum, ladders, snakes);
        gameList.push_back(myGame);
    }

    for (int i = 0; i < gameList.size(); i++) {
        std::cout << "Board Game #" << i + 1 << ":" << std::endl;
        std::cout << gameList[i]->solve();
        delete gameList[i];
    }

    return 0;
}