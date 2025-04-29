#include "player.h"

/* Constructors */
Player::Player(std::string nom) {
    this->nom = nom;
    this->prediction = 0;
    this->score = 0;
}

/* Getters */
std::string Player::getName(){
    return this->nom ;
}

int Player::getPrediction(){
    return this->prediction ;
}

int Player::getScore(){
    return this->score ;
}

/* Setters */
void Player::setPrediction(int prediction){
    this->prediction = prediction;
}


/* Methods */
void Player::incrementScore(int point = 1){
    this->score += point;
}
