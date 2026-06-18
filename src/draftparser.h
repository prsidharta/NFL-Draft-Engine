#pragma once

#include <string>
#include <vector>
#include <draftee.h>

class DraftParser{
    public:
        static std::vector<Draftee> ParseCSV(std::string filepath);
};