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
void save(std::string username, int score){
    std::filesystem::create_directory("../saves");
                }
            }
            else if (line == 2) {
                if (temp_char == '\n') {
    std::string path = "../saves/" + username + ".savegame";
    std::ofstream file_out;
    file_out.open(path);
    file_out << username << "\n";
    file_out << score << "\n";
    file_out.close();
}