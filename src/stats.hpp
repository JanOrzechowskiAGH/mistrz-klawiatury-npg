#ifndef NPG_STATS_HPP
#define NPG_STATS_HPP

#include <string>
#include <utility>
#include <vector>

enum Comparator {
    GameCount,
    HighScore,
    AvgScore
};

class StatsEntry{
public:
    StatsEntry(std::string  username, std::vector<int> score,int games = 0) :
            username_(std::move(username)), games_(games), score_(score) {}

    std::string getUsername() const {return username_;}
    std::vector<int> getScore() const { return score_; }
    int getGameCount() const {return games_;}
    int getHighScore() const;
    int getAvgScore() const;

private:
    std::string username_;
    std::vector<int> score_;
    int games_;
};

StatsEntry getUsersStats(std::string& username);

std::vector<StatsEntry> getMultipleUsersStats(std::vector<std::string>& user_list);

bool compareStatsEntries(const StatsEntry& a, const StatsEntry& b, Comparator parameter);

void sortStatsEntries(std::vector<StatsEntry>& stats, Comparator parameter);


#endif //NPG_STATS_HPP
