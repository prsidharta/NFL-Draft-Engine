#include "draftee.h"

Draftee::Draftee() {
    dPick = 0;
    actualValue = 0.0;
    expectedValue = 0.0;
    valueDelta = 0.0;
}

Draftee::Draftee(std::string dName, std::string dPosition, int dPick, std::string dTeam, double actualValue) {
    this->dName = dName;
    this->dPosition = dPosition;
    this->dPick = dPick;
    this->dTeam = dTeam;
    
    this->actualValue = actualValue;
    this->expectedValue = FindExpectedValue(this->dPick);
    this->valueDelta = this->actualValue - this->expectedValue;
}

double Draftee::FindExpectedValue(int dPick) {
    double alpha = 75.0;
    double decayRate = 0.02;

    return alpha * std::exp(-(decayRate) * (dPick - 1));
}