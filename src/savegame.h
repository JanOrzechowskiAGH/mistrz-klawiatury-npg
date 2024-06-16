#ifndef SAVEGAME_H
#define SAVEGAME_H
#include <cstdlib>
#include <string>
#include <string>
#include <vector>
#include <fstream>

void GetUserList(std::vector<std::string>& list);

void save(std::string username, double time,  int score1, int score2);

#endif //SAVEGAME_H
