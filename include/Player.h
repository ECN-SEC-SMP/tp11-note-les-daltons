#ifndef PLAYER_H
#define PLAYER_H

#include <string>

class Player
{
private:
    std::string name;
    int prediction;
    int nbMoves;
    int nbRoundsPlayed;
    int score;

public:
    /* Constructors */
    Player(std::string name);

    /* Getters */
    std ::string getName();
    int getPrediction();
    int getNbMoves();
    int getRoundsPlayed();
    int getScore();

    /* Setters */
    void setPrediction(int prediction);

    /* Methods */
    void incrementMoves();
    void incrementRoundsPlayed();
    void incrementScore(int points = 1);
};

#endif // PLAYER_H