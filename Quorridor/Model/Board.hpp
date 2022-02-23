#ifndef BOARD_HPP
#define BOARD_HPP

#include "MotherCell.hpp"
#include "Player.hpp"
#include "Position.hpp"
#include <string>
#include <array>
#include <memory>

#include "iostream"


class Board{
    private:
        int size=9;
        int boardSize;
        
        std::vector<std::vector< std::shared_ptr<MotherCell> > > matrix;

        std::vector<std::shared_ptr<Player>> players;
        int currentPlayer=0;
    public:
        explicit Board(int size=9);
        void bindCells();
        std::vector<std::vector< std::shared_ptr<MotherCell> > > getMatrix() {return matrix;}
        int getBoardSize() const {return boardSize;}
        void newGame();
        void ExecuteMove(std::string& input);
        bool checkInput(std::string &input);
        bool checkPos(Position pos) const;
        std::vector<std::shared_ptr<Player>> getPlayers(){return players;};
        
};

#endif