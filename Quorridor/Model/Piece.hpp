#ifndef PIECE_HPP
#define PIECE_HPP

#include "Position.hpp"
#include <memory>
#include <utility>
#include <vector>
#include <iostream>
#include <string>

class Piece {
protected:
    Position position; 
public: 
    Piece(Position position ): position{position} {}
    Position getPos() {return position;}
    void setPos(Position pos) {position = pos;}

    virtual std::vector<std::shared_ptr<Piece>> getTriplet()=0;
    virtual int getID() =0;     

    virtual std::string wallD()=0;
    virtual bool isWall() =0; 

    virtual ~Piece(){} 
};


class Wall : public Piece{
private:
    //Position position; 
    std::string direction;
    // Fausse virtuelle pour permettre la configuration OOP de la classe DestruQtionWall
    virtual std::vector<std::shared_ptr<Piece>> getTriplet() override {std::vector<std::shared_ptr<Piece>> empty_list; return empty_list;}; 
    
public:
    Wall(Position position, std::string direction): Piece(position), direction(std::move(direction)) {};
    
    int getID() override {return 10;}

    std::string wallD() override {return direction;}
    bool isWall() override {return true;} 

    virtual ~Wall() {}
}; 

class Pawn : public Piece{
    //Position position;
    int id; //Joueur auquel appartient le pion
    // Fausse virtuelle pour permettre la configuration OOP de la classe DestruQtionWall
    virtual std::vector<std::shared_ptr<Piece>> getTriplet() override {std::vector<std::shared_ptr<Piece>> empty_list; return empty_list;}; 
public: 
    Pawn(Position position, int id): Piece(position), id(id) {}
    
    int getID() override {return id;}
    
    std::string wallD() override {return nullptr;}
    bool isWall() override {return false;} 
}; 

#endif 