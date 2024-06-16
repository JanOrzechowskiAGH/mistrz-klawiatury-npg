#ifndef SAVEGAME_H
#define SAVEGAME_H
#include <cstdlib>
#include <string>
#include <string>
#include <vector>
#include <fstream>

class User{
public:
    User(std::string UserName, int score) : score_(score), UserName_(std::move(UserName)) {}
    int getScore() const { return score_; }
    std::string GetUserName () const { return UserName_; }
private:
    int score_;
    std::string UserName_;
};

void save(std::string& username, int& score);

void load(std::vector<User>& users);

#endif //SAVEGAME_H
