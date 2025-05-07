#include "GameManager.h"

int main(int argc, char const *argv[])
{
    GameManager gm;

    gm.addPlayer(new Player("Joueur 1"));
    gm.addPlayer(new Player("Joueur 2"));
    gm.addPlayer(new Player("Joueur 3"));

    // gm.setupRound();
    // gm.processPredictionsInputs();
    // gm.sortPlayersByPredictions();

    gm.playRound(0);

    getchar();

    return 0;
}
