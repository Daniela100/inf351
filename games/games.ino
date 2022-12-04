#include <M5StickC.h>
// #include "Dices.h"
#include "FlappyBird.h"
#include "Game.h"

FlappyBird derived;
Game *game;
bool initGame = false;

void setup() {
  M5.begin();
  derived = FlappyBird();
  initGame = false;
  // Serial.begin(9600);
  // game = Game();
}

void loop() {
  if(!initGame) {
    game = &derived;
    game->gameInit();
    initGame = true;
  }
  // Serial.println(game->getName().c_str());
  game->gameLoop();
}