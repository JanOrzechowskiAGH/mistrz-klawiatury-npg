#include <iostream>
#include "savegame.h"
#include <string>
#include <vector>
#include <fstream>

void save(std::vector<Entry> list, std::string username){
    std::ofstream file_out;
    std::string path = "../saves/" + username + ".savegame";
    file_out.open(path);
    file_out << username << '\n';
    for (auto element : list){
        file_out << element.getTime() << " " << element.getWord() << " \n";
    }

    file_out.close();
}

//Jest jak jest, ważne że działa
void load(std::vector<Entry>& list, std::string& username, std::string path){
    std::ifstream file_in (path);
    if (file_in.is_open()) {
        bool data = false;
        bool name = true;
        char temp_char;
        double elapsed_time;
        std::string word;
        std::string elapsed_time_s;

        while ( file_in ) {
            temp_char = file_in.get();
            if (name) {
                if (temp_char != '\n') {
                    username += std::string(1, temp_char);
                } else {
                    name = false;
                }
            }
            else {
                if (temp_char == ' ') {
                    data = true;
                } else if (temp_char == '\n') {
                    data = false;
                    elapsed_time = std::stod(elapsed_time_s);

                    Entry entry(elapsed_time, word);
                    list.push_back(entry);

                    elapsed_time = 0;
                    elapsed_time_s = "";
                    word = "";
                } else {
                    if (!data) {
                        elapsed_time_s += std::string(1, temp_char);
                    } else {
                        word += std::string(1, temp_char);
                    }
                }

            }
        }

    }
}

    /* Przykład zapisu, najlepiej przy każdym zakończonym słowie tworzyć Entry i dodawać do wektora.
    Entry f1(1.2, "wyindywidualizowany");
    Entry f2(0.5, "rycerz");
    Entry f3(0.6, "smok");
    Entry f4(0.4, "magiczny");
    Entry f5(0.7, "zamek");
    Entry f6(0.5, "skarb");

    std::vector<Entry> list = {f1, f2, f3, f4, f5, f6};

    save(list, "Ai");

    tu przykład odczytu.

    std::vector<Entry> list;
    std::string name;

    load(list, name, "../saves/Ai.savegame");
    double time_ = 0;
    for (auto element : list){
        std::cout << element.getWord() << " " << element.getTime() << " \n";
        time_ += element.getTime();
    }
    std::cout << name;
    */