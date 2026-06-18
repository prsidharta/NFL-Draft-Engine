#include "Team.h"

Team::Team(){}

Team::Team(std::string teamName, std::vector<std::string> teamNeeds){
    this->teamName = teamName;
    this->teamNeeds = teamNeeds;
}

bool Team::TeamNeedsPosition(std::string targetPosition){
    for (int i = 0; i < teamNeeds.size(); i++){
        if (targetPosition == teamNeeds[i]){
            return true;
        }
    }
    return false;
}

void Team::TeamFulfillNeed(std::string draftedPosition){
    for (auto it = teamNeeds.begin(); it != teamNeeds.end(); ++it){
        if (*it == draftedPosition){
            teamNeeds.erase(it);
            break;
        }
    }
}