#pragma once

#include <string>
#include <vector>
#include <draftee.h>
#include <team.h>

class DraftParser{
    public:
        static std::vector<Draftee> ParseCSV(std::string filepath);
        static std::vector<Team> ParseTeams(std::string filepath);
};

