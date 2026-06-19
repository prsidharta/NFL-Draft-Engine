
/**
 * NFL Draft Valuation and Re-Draft Engine
 * 1. Parse historical NFL draft data, pre-draft evaluations, and team needs from specific years
 * 2. Calculate expected value for every draftee and draft number
 * 3. Calculate actual value of every draftee based off NFL career
 * 4. Create a Re-Draft that simulates an optimal NFL draft based on actual value and historical team needs
 * 
 */

#include "program.h"
#include <iostream>
#include <string>

int main(){

    std::string year;
    std::cout << "Enter the Draft Year you wish to simulate: "  << "\n";
    std::cin >> year;

    std::string draftPath = "data/" + year + "_draft.csv";
    std::string needsPath = "data/" + year + "_draft.csv";

    Program myProgram(draftPath, needsPath);

    return 0;
}