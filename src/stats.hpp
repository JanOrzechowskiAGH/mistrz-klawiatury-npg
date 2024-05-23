#ifndef NPG_STATS_HPP
#define NPG_STATS_HPP

#include <cstdlib>
#include <string>
#include <utility>
#include <vector>
#include <fstream>

class StatsEntry {
public:
    StatsEntry(std::string username, int num_games = 1, int num_char = 0, double playtime = 0) :
            username_(username), num_games_(num_games), num_char_(num_games), playtime_(playtime) {}

    std::string getUsername() const {return username_;}
    int getNumGames() const {return num_games_;}
    int getNumChars() const {return num_char_;}
    double getPlaytime() const {return playtime_;}
    double getCharPerS() const {return (double)num_char_/playtime_;}



    void add_to_playtime(double time){ playtime_+= time; }
    void add_to_chars(int number){ num_char_+= number; }
    void add_game_number(){ num_games_++; }

private:
    std::string username_;
    int num_games_;
    int num_char_;
    double playtime_;
};

#endif //NPG_STATS_HPP
