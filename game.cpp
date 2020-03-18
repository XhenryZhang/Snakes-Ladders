// game.cpp
// Implements class Game
// Author: Xinyi Zhang - 3/17/2020

#include "game.h"
#include <iostream>
#include <stack>

// constructors
Game::Game(int size, int ladderNum, int snakeNum, std::vector<int> &ladders, std::vector<int> &snakes) : gameSize(size), numLadders(ladderNum), numSnakes(snakeNum){
    snakeStart = new int[snakeNum];
    snakeEnd = new int[snakeNum];
    ladderStart = new int[ladderNum];
    ladderEnd = new int[ladderNum];

    // update ladder info
    for (int i = 0; i < ladders.size(); i+=2) {
        ladderStart[i/2] = ladders[i];
        ladderEnd[i/2] = ladders[i+1];
    }

    // update snake info
    for (int i = 0; i < snakes.size(); i+=2) {
        snakeStart[i/2] = snakes[i];
        snakeEnd[i/2] = snakes[i+1];
    }

    for (int i = 0; i < gameSize + 1; i++) {
        visited.push_back(false);
        distance.push_back(gameSize + 1);
        pred.push_back(std::make_pair(-1, " "));
    }
}

// make check for ladder and snakes helper methods

std::string Game::solve() {
    int destination = gameSize;
    visited[1] = true;
    distance[1] = 0;

    bool firstLadder = false;
    int nextMove = 1;
    // check for ladder at position 1
    checkLadderSnake(nextMove, 1, true, firstLadder);

    if (!firstLadder) {
        bfsQueue.push(1);
    }else {
        bfsQueue.push(nextMove);

        if (nextMove == destination) {
            return output();
        }
    }

    while(!bfsQueue.empty()) {
        int currentVertex = bfsQueue.front();
        bfsQueue.pop();
        for (int i = 6; i >= 1; i--) { // throw the dice
            nextMove = currentVertex + i;
            if (nextMove <= gameSize && visited[nextMove] == false) {
                visited[nextMove] = true;
                distance[nextMove] = distance[currentVertex] + 1;
                pred[nextMove] = std::make_pair(currentVertex, " ");

                // check for ladder and snake
                checkLadderSnake(nextMove, currentVertex, false, firstLadder);
                // checkSnake(nextMove, currentVertex, false);

                if (nextMove == destination) {
                    return output();
                }
            }
        }
    }

    return "cannot solve board!";
}

Game::~Game() {
    delete [] snakeStart;
    delete [] snakeEnd;
    delete [] ladderStart;
    delete [] ladderEnd;
}

// private member
void Game::checkLadderSnake(int &nextMove, int currentVertex, bool chain, bool &firstLadder) {
    bool ladderFound;
    bool ladderPresent = false;
    bool snakeFound;
    bool snakePresent = false;
    int temp = nextMove;

    for (int i = 0; i < numLadders; i++) { // loop through list of ladders
        ladderFound = false;
        if (temp == ladderStart[i]) {
            ladderFound = true;
            ladderPresent = true;
            // case if first square is ladder
            if (nextMove == 1) {
                firstLadder = true;
                distance[currentVertex]--; // subtract, not in chain, but no step is made from a previous move
            }

            nextMove = ladderEnd[i];
            
            if (chain) {
                pred[nextMove] = std::make_pair(ladderStart[i], " " + std::to_string(ladderStart[i]) + "+");
            }else {
                pred[nextMove] = std::make_pair(ladderStart[i], "+");
            }

            distance[nextMove] = distance[currentVertex] + 1;
            visited[nextMove] = true;
        }

        if (ladderFound) { // if ladder is found, check ending point to see if it's a ladder or a snake
            checkLadderSnake(nextMove, nextMove, true, firstLadder);
        }
    }

    if (!ladderPresent) { // checks if current index is snake
        for (int i = 0; i < numSnakes; i++) {
            snakeFound = false;
            if (temp == snakeStart[i]) {
                snakePresent = true;
                snakeFound = true;

                nextMove = snakeEnd[i];

                if (chain) {
                    pred[nextMove] = std::make_pair(snakeStart[i], " " + std::to_string(snakeStart[i]) + "-");
                }else {
                    pred[nextMove] = std::make_pair(snakeStart[i], "-");
                }

                distance[nextMove] = distance[currentVertex] + 1;
                visited[nextMove] = true;
            }

            if (snakeFound) {
                bool placeHolder = true;
                checkLadderSnake(nextMove, nextMove, true, placeHolder);
            }
        }
    }

    if (!ladderPresent && !snakePresent) {
        bfsQueue.push(nextMove);
    }
}

std::string Game::output() const {
    std::string output = "";
    output += std::to_string(distance[gameSize]);
    output += '\n';

    std::stack<std::pair<int, std::string>> moveSequence;
    std::pair<int, std::string> top = std::make_pair(gameSize, "");
    moveSequence.push(top);

    int currentVertex = gameSize;
    
    while (currentVertex != 1) {
        moveSequence.push(pred[currentVertex]);
        currentVertex = pred[currentVertex].first;
    }

    while(!moveSequence.empty()) {
        std::pair<int, std::string> curMove= moveSequence.top();
        output += std::to_string(curMove.first) + curMove.second;
        moveSequence.pop();
    }

    output += '\n';
    return output;
}

// friend
std::ostream& operator<<(std::ostream& os, const Game& game) {
    int boardSize = game.gameSize;
    std::string snakes;
    std::string ladders;
    for (int i = 0; i < game.numLadders; i++) {
        ladders = ladders + std::to_string(game.ladderStart[i]) + ' ' + std::to_string(game.ladderEnd[i]) + ' ';
    }

    for (int i = 0; i < game.numSnakes; i++) {
        snakes = snakes + std::to_string(game.snakeStart[i]) + ' ' + std::to_string(game.snakeEnd[i]) + ' ';
    }

    os << "Game size: " << boardSize << std::endl;
    os << "ladders: " << ladders << std::endl;
    os << "snakes: " << snakes << std::endl;
    return os;
}