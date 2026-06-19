#pragma once

#include <vector>
#include <string>
#include "draftee.h"
#include "team.h"

class Program{
    private:
        std::vector<Draftee> availablePlayers;
        std::vector<Team> draftOrder;
    
    public:
        Program(std::string playersCSV, std::string teamNeedsCSV);
        void RunRedraft();
};