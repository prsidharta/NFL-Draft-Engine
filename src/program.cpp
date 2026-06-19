#include "program.h"
#include "draftparser.h"

#include <iostream>
#include <algorithm>

Program::Program(std::string playersCSV, std::string teamNeedsCSV){
    availablePlayers = DraftParser::ParseCSV(playersCSV);
    draftOrder = DraftParser::ParseTeams(teamNeedsCSV); 
}

