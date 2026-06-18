#pragma once

#include <string>
#include <vector>
#include "draftee.h"

class Team{
    public:
        std::string teamName;
        std::vector<std::string> teamNeeds;
        std::vector<Draftee> teamDraft;

    Team();
    Team(std::string name, std::vector<std::string> teamNeeds);

    bool TeamNeedsPosition(std::string targetPosition);
    void TeamFulfillNeed(std::string draftedPosition);
};