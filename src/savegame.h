#ifndef SAVEGAME_H
#define SAVEGAME_H
#include <cstdlib>
#include <string>
#include <string>
#include <vector>
#include <fstream>

class Entry {
public:
    Entry(double elapsed_time, int backspaces, int errors, std::string word) : elapsed_time_(elapsed_time), backspaces_(backspaces), errors_(errors), word_(word) {}
    double getTime() const { return elapsed_time_; }
    int getBackspaces() const { return backspaces_; }
    int getErrors() const { return errors_; }
    std::string getWord() const { return word_; }
private:
    double elapsed_time_;
    int backspaces_;
    int errors_;
    std::string word_;
};


void save(std::vector<Entry> list, std::string username);

void load(std::vector<Entry>& list, std::string& username, std::string path);

#endif //SAVEGAME_H
