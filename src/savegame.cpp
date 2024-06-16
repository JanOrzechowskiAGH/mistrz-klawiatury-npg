#include <iostream>
#include "savegame.h"
#include <string>
#include <vector>
#include <fstream>
#include <filesystem>

void load(std::vector<User>& users){
    std::string path = "../saves/";
    for (const auto & file : std::filesystem::directory_iterator(path)) {

        std::ifstream file2 (file.path());
        int lines = (int) std::count(std::istreambuf_iterator<char>(file2),
                                     std::istreambuf_iterator<char>(), '\n') + 1;
        char temp_char;
        std::string username;
        std::string score_s;
        std::vector<int> scores;
        int games = 0;
        int score;
        int line = 0;
        std::ifstream file_in (file.path());
        while ( file_in ) {
            temp_char =  (char) file_in.get();
            if(line == 0) {
                if (temp_char == '\n') {
                    line++;
                } else {
                    username += std::string(1, temp_char);
                }
            }
            else if( line < lines){
                if (temp_char == '\n') {
                    games++;
                    score = std::stoi(score_s);
                    scores.push_back(score);
                    score_s = "";
                    line++;
                } else {
                    score_s += std::string(1, temp_char);
                }
            }
        }
        User new_user = User(username, scores, games);
        users.push_back(new_user);
        file_in.close();
    }
}
void save(std::string& username, int& score){
    std::filesystem::create_directory("../saves");
    std::string path = "../saves/" + username + ".savegame";
    std::ifstream file_in;
    file_in.open(path);
    if(file_in){
        file_in.close();
        std::ofstream file_out;
        file_out.open(path, std::ios::app); // append instead of overwrite
        file_out << score << "\n";
        file_out.close();
    }
    else {
        file_in.close();
        std::ofstream file_out;
        file_out.open(path);
        file_out << username << "\n";
        file_out << score << "\n";
        file_out.close();
    }

}
