#include "draftparser.h"

#include <fstream>
#include <sstream>
#include <iostream>

std::vector<Draftee> DraftParser::ParseCSV(std::string filepath){
    std::vector<Draftee> draftClass;

    std::ifstream pFile(filepath);
    if (!pFile.is_open()){
        return draftClass;
    }
    std::string line;
    std::getline(pFile, line);
    while (std::getline(pFile, line)){
        std::stringstream ss(line);
        std::string pickStr, team, name, pos, avStr;

        std::getline(ss, pickStr, ',');
        std::getline(ss, team, ',');
        std::getline(ss, name, ',');
        std::getline(ss, pos, ',');
        std::getline(ss, avStr, ',');

        int pickNum = std::stoi(pickStr);
        double actualValue = std::stod(avStr);
        
        Draftee newPlayer(name, pos, pickNum, team, actualValue);
        draftClass.push_back(newPlayer);
    }

    return draftClass;
}