#ifndef NPG_STATS_HPP
#define NPG_STATS_HPP

#include <cstdlib>
#include <string>
#include <utility>
#include <vector>
#include <fstream>
/*
No mam nadzieje że to działa xdd
Myślę że wystarczy wyświtlić coś w tym stylu:
 Userame Num_of_games Play_Time Char_per_s Avg_Errors
*/

class StatsEntry{
public:
    StatsEntry(std::string& username, int games = 0, int num_char = 0, double playtime = 0, int backspaces = 0, int errors = 0) :
            username_(username), games_(games), char_(num_char), playtime_(playtime), backspaces_(backspaces), errors_(errors) {}

    std::string getUsername() const {return username_;}
    int getNumGames() const {return games_;}
    int getNumChars() const {return char_;}
    double getPlaytime() const {return playtime_;}
    int getBackspaces() const {return backspaces_;}
    int getErrors() const {return errors_;}

    double getCharPerS() const {return (double)char_ / playtime_;}
    double getAvgBackspaces() const {return (double)backspaces_/games_;}
    double getAvgErrors() const {return (double)errors_/games_;}

    void add_playtime(double time){playtime_+= time;}
    void add_chars(int number){char_+= number;}
    void add_game_number(){games_++;}
    void add_backspaces(int number){backspaces_+= number;}
    void add_errors(int number){errors_+= number;}



private:
    std::string username_;
    int games_;
    int char_;
    int backspaces_;
    int errors_;
    double playtime_;
};

void get_user_stats(std::vector<StatsEntry>& list, std::string& username);

void get_many_users_stats(std::vector<StatsEntry>& list, std::vector<std::string>& user_list);

#endif //NPG_STATS_HPP
