#ifndef GAME_H
#define GAME_H

#include <string>
using std::string;

class Game {
  public:
    virtual void gameLoop() = 0;
    virtual void gameInit() = 0;
    virtual string getName() = 0;
};

#endif