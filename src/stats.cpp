#include "stats.hpp"
#include "savegame.h"
#include <vector>
#include <sstream>
#include <algorithm>

float StatsEntry::getAvgScore() const {
    float sum = 0;
    for (auto i: score_){
        sum += i;
    }
    return games_>0 ? sum/(float)games_ : 0;
}

int StatsEntry::getHighScore() const {
    int highest = 0;
    for (auto i: score_){
        if (i>highest){
            highest = i;
        }
    }
    return highest;
}

std::vector<StatsEntry> getUsersStats(){
    std::vector<User> users;
    std::vector<StatsEntry> users_stats;
    load(users);
    for (const auto& user: users){
        StatsEntry tmp(user.GetUserName(), user.getScore(), user.getGameCount());
        users_stats.push_back(tmp);
    }
    return users_stats;
}

bool compareStatsEntries(const StatsEntry& a, const StatsEntry& b, Comparator parameter){
    switch (parameter) {
        case GameCount:
            return a.getGameCount() > b.getGameCount();
        case HighScore:
            return a.getHighScore() > b.getHighScore();
        case AvgScore:
            return a.getAvgScore() > b.getAvgScore();
        default:
            return false;
    }
}


void sortStatsEntries(std::vector<StatsEntry>& stats, Comparator parameter){
    std::sort(stats.begin(), stats.end(), [&parameter](const StatsEntry& a, const StatsEntry& b) {
        return compareStatsEntries(a, b, parameter);
    });
}