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

std::vector<Team> DraftParser::ParseTeams(std::string filepath) {
    std::vector<Team> draftOrder;
    std::ifstream pFile(filepath);
    
    if (!pFile.is_open()) {
        std::cerr << "Error: Could not open team needs file!" << std::endl;
        return draftOrder;
    }

    std::string line;
    while (std::getline(pFile, line)) {
        std::stringstream ss(line);
        std::string teamName;
        std::vector<std::string> teamNeeds;

        std::getline(ss, teamName, ',');

        std::string need;
        while (std::getline(ss, need, ',')) {
            if (!need.empty() && need.back() == '\r') {
                need.pop_back();
            }
            teamNeeds.push_back(need);
        }

        Team newTeam(teamName, teamNeeds);
        draftOrder.push_back(newTeam);
    }

    return draftOrder;
}