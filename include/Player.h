#ifndef PLAYER_H
#define PLAYER_H

#include <string>

class Player
{
private:
    std::string name;
    int prediction;
    int score;

public:
    /* Constructors */
    Player(std::string name);

    /* Getters */
    std ::string getName();
    int getPrediction();
    int getScore();

    /* Setters */
    void setPrediction(int prediction);

    /* Methods */
    void incrementScore(int score);
};

#endif // PLAYER_H