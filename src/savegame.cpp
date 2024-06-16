#include <iostream>
#include "savegame.h"
#include <string>
#include <vector>
#include <fstream>
#include <filesystem>

void load(std::vector<User>& users){
    std::string path = "../saves/";
    for (const auto & file : std::filesystem::directory_iterator(path)) {
        std::ifstream file_in (file.path());
        char temp_char;
        std::string username;
        std::string score_s;
        int score;
        int line = 0;
        while ( file_in ) {
            temp_char =  (char) file_in.get();
            if(line == 0) {
                if (temp_char == '\n') {
                    line++;
                } else {
                    username += std::string(1, temp_char);
                }
            }
            else{
                if (temp_char == '\n') {
                    score = std::stoi(score_s);
                    User new_user = User(username, score);
                    users.push_back(new_user);
                    username = "";
                    score = 0;
                } else {
                    score_s += std::string(1, temp_char);
                }
            }
        }
        file_in.close();
    }
}
void save(std::string& username, int& score){
    std::filesystem::create_directory("../saves");
    std::string path = "../saves/" + username + ".savegame";
    std::ofstream file_out;
    file_out.open(path);
    file_out << username << "\n";
    file_out << score << "\n";
    file_out.close();
}
