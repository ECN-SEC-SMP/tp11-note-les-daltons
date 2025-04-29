#ifndef PLAYER_H
#define PLAYER_H

#include <string>

class Player {
protected:
 std::string nom ;
 int prediction ;
 int score ;

public:

/* Constructors */
 Player(std::string nom);

 /* Getters */
 std :: string getName();
 int getPrediction();
 int getScore();

/* Setters */
void setPrediction(int prediction);

/* Methods */
void incrementScore (int score);

} ;

#endif // PLAYER_H