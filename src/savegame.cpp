#include <iostream>
#include "savegame.h"
#include <string>
#include <vector>
#include <fstream>
#include <filesystem>

void GetUserList(std::vector<std::string>& list){
    std::string path = "../saves/";
    for (const auto & file : std::filesystem::directory_iterator(path)) {
        std::ifstream file_in (file.path());
        char temp_char;
        std::string username;
        while ( file_in ) {
            temp_char =  (char) file_in.get();
            if (temp_char == '\n') {
                list.push_back(username);
                break;
            }
            else{
                username += std::string(1, temp_char);
            }
        }
        file_in.close();
    }
}
int load(std::string& username, std::string path, double& time,  int& score1, int& score2){
    std::filesystem::create_directory("../saves");
    std::ifstream file_in (path);
    if (file_in.is_open()) {
        int line = 0;
        char temp_char;

        std::string elapsed_time_s;
        std::string score1_s;
        std::string score2_s;
        while ( file_in ) {

            temp_char = file_in.get();
            if (line == 0) {
                if (temp_char == '\n') {
                    line++;
                }
                else{
                    username += std::string(1, temp_char);
                }
            }
            else if (line == 1) {
                if (temp_char == '\n') {
                    line++;
                    time = std::stod(elapsed_time_s);
                }
                else{
                    elapsed_time_s += std::string(1, temp_char);
                }
            }
            else if (line == 2) {
                if (temp_char == '\n') {
                    line++;
                    score1 = std::stoi(score1_s);
                }
                else{
                    score1_s += std::string(1, temp_char);
                }
            }
            else if (line == 3) {
                if (temp_char == '\n') {
                    score2 = std::stoi(score2_s);
                    return 1;
                }
                else{
                    score2_s += std::string(1, temp_char);
                }
            }
        }
    } else{
        return 0;
    }
}
void save(std::string username, double time,  int score1, int score2){
    std::filesystem::create_directory("../saves");
    std::string saveUser;
    int saveScore = 0;
    double saveTime = 0;
    int saveScore2 = 0;

    if(load(saveUser, "../saves/Marta.savegame", saveTime, saveScore, saveScore2)) { //overwrite
        if(score1 == -1){
            score1 = saveScore;
        }
        if(score2 == -1) {
            score2 = saveScore2;
        }
    }
    else{ //create new
        if(score1 == -1){
            score1 = 0;
        }
        if(score2 == -1) {
            score2 = 0;
        }
    }
    std::string path = "../saves/" + username + ".savegame";
    std::ofstream file_out;
    file_out.open(path);
    file_out << username << "\n";
    file_out << time << "\n";
    file_out << score1 << "\n";
    file_out << score2 << "\n";
    file_out.close();
}