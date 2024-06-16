#ifndef SAVEGAME_H
#define SAVEGAME_H
#include <cstdlib>
#include <string>
#include <string>
#include <vector>
#include <fstream>

class User{
public:
    User(std::string UserName, std::vector<int> score, int gameCount) : score_(score), gameCount_(gameCount), UserName_(UserName) {}
    std::vector<int> getScore() const { return score_; }
    int getGameCount() const { return gameCount_; }
    std::string GetUserName () const { return UserName_; }
private:
    std::vector<int> score_;
    int gameCount_;
    std::string UserName_;
};

void save(std::string& username, int& score);

void load(std::vector<User>& users);

#endif //SAVEGAME_H
