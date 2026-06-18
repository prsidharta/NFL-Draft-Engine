#pragma once

#include <string>
#include <cmath>

struct Draftee{
    std::string dName;
    std::string dPosition;
    int dPick;
    std::string dTeam;

    double actualValue;
    double expectedValue;
    double valueDelta;

    Draftee();
    Draftee(std::string dName, std::string dPosition, int dPick, std::string dTeam, double actualValue);
    double FindExpectedValue(int dPick);
};