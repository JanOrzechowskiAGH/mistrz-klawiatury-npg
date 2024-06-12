#include <iostream>
#include "stats.hpp"
#include "savegame.h"
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>
#include <filesystem>

// Ogólne to trzeba zrobiś jakąś listę użytkowników     <- Funkcja zrobiona, teraz trzeba jakoś ją użyć
// ale to chyba bedzie tworzone w głównym kodzie gry więc na razie to tak zostawiam
// Tutaj po prostu biorę username, load-uje to co ma zapisane w save-ach i pakuje to do listy którą ty wrzucasz

void getUserStats(std::vector<StatsEntry>& list, std::string& username){
    std::vector<Entry> temp;
    std::string path = "../saves/" + username + ".savegame";
    load(temp, username, path);

    StatsEntry userstats(username);
    for (const auto& element : temp){
        userstats.add_game_number();
        userstats.add_playtime(element.getTime());
        userstats.add_backspaces(element.getBackspaces());
        userstats.add_errors(element.getErrors());
        userstats.add_chars((int)element.getWord().length());
    }

    list.push_back(userstats);
}

void getMultipeUsersStats(std::vector<StatsEntry>& list, std::vector<std::string>& user_list){
    for (auto& user : user_list){
        getUserStats(list, user);
    }
}

// Switch nie działa dla std::string więc jest else if
bool compareByParameter(const StatsEntry& a, const StatsEntry& b, const std::string& parameter) {
    if (parameter == "Games") {
        return a.getNumGames() < b.getNumGames();
    } else if (parameter == "Chars") {
        return a.getNumChars() < b.getNumChars();
    } else if (parameter == "Playtime") {
        return a.getPlaytime() < b.getPlaytime();
    } else if (parameter == "Backspaces") {
        return a.getBackspaces() < b.getBackspaces();
    } else if (parameter == "Errors") {
        return a.getErrors() < b.getErrors();
    } else if (parameter == "CharPerS") {
        return a.getCharPerS() < b.getCharPerS();
    } else if (parameter == "AvgBackspaces") {
        return a.getAvgBackspaces() < b.getAvgBackspaces();
    } else if (parameter == "AvgErrors") {
        return a.getAvgErrors() < b.getAvgErrors();
    } else {
        throw std::invalid_argument("Invalid sorting parameter");
    }

}

void sortStatsEntries(std::vector<StatsEntry>& stats, const std::string& parameter) {
    std::sort(stats.begin(), stats.end(), [&parameter](const StatsEntry& a, const StatsEntry& b) {
        return compareByParameter(a, b, parameter);
    });
}

void GetUserList(std::vector<std::string>& list){
    std::string path = "../saves/";
    std::filesystem::create_directory("../saves");
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