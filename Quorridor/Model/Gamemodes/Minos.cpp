#include "Minos.hpp"

const std::string DIRECTION = "HV";

void MinosGame::start() {
    int player = 0;
    int nplayer = model->getNplayer(); 
    inputFormat();
    createLabyrinth();
    while(!model->isEnd()){
        std::cout<<"Player " + std::to_string(player+1) + "'s moves : "<<std::endl;
        std::string input = getInput();
        
        if(checkInput(input, player)){
            player=(player+1)%nplayer;
            if (player == 0) {
                destroyLabyrinth();
                createLabyrinth();
            }
        }
        else inputFormat();
        view->printBoard();
    }
    std::cout << "Player "<< (player-1)%nplayer << " has won"<< std::endl;
}


void MinosGame::createLabyrinth() {
    while (wallsToPlace != 0) {
        Position position = Position((rand() % model->getBoardSize()), (rand() % model->getBoardSize())) * 2;
        std::string direction = std::string(1, DIRECTION[rand() % 2]);
        if (model->checkWall(direction, position)) {
            model->placeWall(direction, position);
            wallsToPlace --;
            placedWallsDirections.push(direction);
            placedWalls.push(position);
        }
    }
}

void MinosGame::destroyLabyrinth() {
    for (int i = 0; i < wallsToDestroy; i++) {
        std::string direction = placedWallsDirections.top();
        placedWallsDirections.pop();
        Position position = placedWalls.top();
        placedWalls.pop();
        model->destroyWall(direction, position);
    }
}