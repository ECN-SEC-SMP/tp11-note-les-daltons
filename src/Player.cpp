#include "Player.h"

/* Constructors */
Player::Player(std::string name)
{
    this->name = name;
    this->prediction = 0;
    this->score = 0;
}

/* Getters */
std::string Player::getName()
{
    return this->name;
}

int Player::getPrediction()
{
    return this->prediction;
}

int Player::getScore()
{
    return this->score;
}

/* Setters */
void Player::setPrediction(int prediction)
{
    this->prediction = prediction;
}

/* Methods */
void Player::incrementScore(int points)
{
    this->score += points;
}
