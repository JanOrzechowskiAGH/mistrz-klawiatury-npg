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
    for (auto& element : list){
        file_out << element.getTime() << " " << element.getBackspaces() << " " << element.getErrors()<< " " << element.getWord() << " \n";
    }

    file_out.close();
}

//Jest jak jest, ważne że działa
void load(std::vector<Entry>& list, std::string& username, std::string path){
    std::ifstream file_in (path);
    if (file_in.is_open()) {
        int pos = -1;
        char temp_char;
        double elapsed_time;
        int errors;
        int backspaces;

        std::string word;
        std::string elapsed_time_s;
        std::string backspaces_s;
        std::string errors_s;
        while ( file_in ) {

            temp_char = file_in.get();
            if (pos == -1) {
                if (temp_char == '\n') {
                    pos = 0;
                }
                else{
                    username += std::string(1, temp_char);
                }
            }
            else if (pos == 0) {
                if (temp_char == ' ') {
                    pos = 1;
                    elapsed_time = std::stod(elapsed_time_s);
                }
                else{
                    elapsed_time_s += std::string(1, temp_char);
                }
            }
            else if(pos == 1){

                if (temp_char == ' ') {
                    pos = 2;
                    backspaces = std::stoi(backspaces_s);
                }
                else{
                    backspaces_s += std::string(1, temp_char);
                }
            }
            else if(pos == 2){
                if (temp_char == ' ') {
                    pos = 3;
                    errors = std::stoi(errors_s);
                }
                else{
                    errors_s += std::string(1, temp_char);
                }
            }
            else{
                if (temp_char != '\n') {
                    word += std::string(1, temp_char);
                } else {
                    Entry entry(elapsed_time, backspaces, errors, word);
                    list.push_back(entry);
                    elapsed_time = 0;
                    elapsed_time_s = "";
                    errors = 0;
                    errors_s = "";
                    backspaces = 0;
                    backspaces_s = "";
                    word = "";
                    pos = 0;
                }
            }
        }

    }
}

    /* Przykład zapisu, najlepiej przy każdym zakończonym słowie tworzyć Entry i dodawać do wektora.
    Entry f1(1.2, 2, 2, "wyindywidualizowany");
    Entry f2(0.5, 1, 1, "rycerz");
    Entry f3(0.6, 4, 5, "smok");
    Entry f4(0.4, 2, 6, "magiczny");
    Entry f5(0.7, 8, 9, "zamek");
    Entry f6(0.5, 10, 8, "skarb");

    std::vector<Entry> list = {f1, f2, f3, f4, f5, f6};

    save(list, "ChatGPT");

    tu przykład odczytu.

    std::vector<Entry> list;
    std::string name;

    load(list, name, "../saves/ChatGPT.savegame");
    for (auto element : list){
        std::cout << element.getWord() << " ";
        std::cout << element.getErrors() << " ";
        std::cout << element.getBackspaces() << " ";
        std::cout << element.getTime();
        std::cout << "\n";
    }
    std::cout << name;
    */