#include "Player.h"

/* Constructors */
Player::Player(std::string name)
{
    this->name = name;
    this->prediction = 0;
    this->nbMoves = 0;
    this->nbRoundsPlayed = 0;
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

int Player::getNbMoves()
{
    return this->nbMoves;
}

int Player::getRoundsPlayed()
{
    return this->nbRoundsPlayed;
}

int Player::getScore()
{
    return this->score;
}

/* Setters */
void Player::setPrediction(int prediction)
{
    this->prediction = prediction;
    if (this->prediction < 0)
        this->prediction = 0;
}

/* Methods */
void Player::incrementMoves()
{
    this->nbMoves++;
}

void Player::incrementRoundsPlayed()
{
    this->nbRoundsPlayed++;
}

void Player::incrementScore(int points)
{
    this->score += points;
    if (this->score < 0)
    {
        this->score = 0;
    }
}

void Player::resetMoves()
{
    this->nbMoves = 0;
}

void Player::reset()
{
    this->nbMoves = 0;
    this->nbRoundsPlayed = 0;
    this->prediction = 0;
    this->score = 0;
}