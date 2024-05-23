#include <iostream>
#include "stats.hpp"
#include "savegame.h"
#include <fstream>
#include <vector>
#include <string>
#include <sstream>

// Ogólne to trzeba zrobiś jakąś listę użytkowników
// ale to chyba bedzie tworzone w głównym kodzie gry więc na razie to tak zostawiam
// Tutaj po prostu biorę username, load-uje to co ma zapisane w save-ach i pakuje to do listy którą ty wrzucasz

void get_user_stats(std::vector<StatsEntry>& list, std::string& username){
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

void get_many_users_stats(std::vector<StatsEntry>& list, std::vector<std::string>& user_list){
    for (auto& user : user_list){
        get_user_stats(list, user);
    }
}
