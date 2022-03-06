//
// Created by alex on 2/23/22.
//

#ifndef PROJET_F209_DATABASE_H
#define PROJET_F209_DATABASE_H

#include <iostream>
#include <fstream>
#include <string>
#include <array>
#include <vector>
#include <sstream>
#include <iterator>


class DatabaseHandler {
private:
    std::array<std::string, 6> string_arr; // permet le parsing du fichier principal
    std::vector<std::string> friendList;   // sous liste d'amis du fichier
    std::vector<std::string> toAddList;    // amis à rajouter
    std::string username;
public:
    // Constructeurs
    DatabaseHandler(const std::string &inputFile);

    // Getters Setters
    std::string getPlayerBoard()const{return string_arr[1];}
    std::string getPlayerName() const{return username;}
    int getWinGames()const{return std::stoi(string_arr[2]);}
    int getLoseGames()const{return std::stoi(string_arr[3]);}
    int getTotalGames()const{return getWinGames()+getLoseGames();}
    std::vector<std::string> getToAddFriendList() const{return toAddList;}
    std::vector<std::string>  getFriendList() const {return friendList;}
    void setRegisteredBoard(const std::string &boardstr){string_arr[1]=boardstr;}
    void hasWin(){string_arr[2] = std::to_string(getWinGames()+1);}
    void hasLose(){string_arr[3] =std::to_string(getLoseGames()+1);}
    void setFriendsList(const std::string &fstr);
    void setToaddList(const std::string &fstr);

    // Méthode "bool"
    int checkPswd(const std::string& input_psw, const std::string& stocked_hash);
    static int isStringValid(const std::string &filepath);
    static bool does_file_exist(const std::string &filename);
    // Méthodes
    void parse(const std::string& file_path, std::array<std::string, 6> * arr_addr);
    static std::string createPsw();
    static std::string createFile(const std::string& filename,const std::string &inputpsw);
    void writeFriends(const std::string &friends_str);
    void writeFriendstoAdd(const std::string &friends_name);
    void transferFriend();
    void listFriends();

    // Méthodes "ask"
    static std::string askFile();
    std::string askPswd();
    void askFriends();


};
#endif //PROJET_F209_DATABASE_H
