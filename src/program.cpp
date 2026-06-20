#include "program.h"
#include "draftparser.h"

#include <iostream>
#include <algorithm>
#include <unordered_map>
#include <unordered_set>

Program::Program(std::string playersCSV, std::string teamNeedsCSV){
    availablePlayers = DraftParser::ParseCSV(playersCSV);
    draftOrder = DraftParser::ParseTeams(teamNeedsCSV); 
}

void Program::RunRedraft(){
    std::sort(availablePlayers.begin(), availablePlayers.end(), [](const Draftee& a, const Draftee& b) {
        return a.actualValue > b.actualValue;
    }); 

    std::unordered_map<std::string, std::vector<Draftee>> draftBoard;
    std::unordered_set<std::string> draftedNames;
    int bpaIndex = 0;

    for (int i = 0; i < availablePlayers.size(); i++){
        std::string pos = availablePlayers[i].dPosition;
        draftBoard[pos].push_back(availablePlayers[i]);
    }

    int currentPick = 1;

    for (int i = 0; i < draftOrder.size(); i++){
        bool foundPlayer = false;

        while (bpaIndex < availablePlayers.size() && draftedNames.count(availablePlayers[bpaIndex].dName) > 0){
            bpaIndex++;
        }
        Draftee currentBPA = availablePlayers[bpaIndex];

        for (int j = 0; j < draftOrder[i].teamNeeds.size(); j++){
            std::string need = draftOrder[i].teamNeeds[j];

            if (draftBoard.count(need) > 0 && !draftBoard[need].empty()){

                //Empty players in needs folder that already are drafted, continue onto next need if all needs are drafted
                while (!draftBoard[need].empty() && draftedNames.count(draftBoard[need][0].dName) > 0){
                    draftBoard[need].erase(draftBoard[need].begin());
                }
                if (draftBoard[need].empty()){
                    continue;
                }

                Draftee draftedPlayer = draftBoard[need][0];

                double gap = currentBPA.actualValue - draftedPlayer.actualValue;
                double threshold = 15.0 - (j * 5.0);

                if (gap <= threshold){

                    std::cout << draftOrder[i].teamName << " selects " << draftedPlayer.dName << " at pick " << currentPick << "\n";

                    draftedNames.insert(draftedPlayer.dName);
                    draftBoard[need].erase(draftBoard[need].begin());

                    foundPlayer = true;
                    break;
                }
            }
        }

        if (!foundPlayer){
            std::cout << draftOrder[i].teamName << " selects " << currentBPA.dName << " at pick " << currentPick << "\n";
            draftedNames.insert(currentBPA.dName);
        }
        currentPick++;
    }
}
