//
// Created by Antek Pater on 04/06/2024.
//

#ifndef NPG_FRAZY_H
#define NPG_FRAZY_H
#include <vector>
#include <string>

std::vector<std::string> generatePhrases();
void savePhrasesToFile(const std::vector<std::string>& phrases, const std::string& filename);
std::string getRandomPhrase(const std::vector<std::string>& phrases);

#endif
#endif //NPG_FRAZY_H
