#include <M5StickC.h>
// #include <string>

// include games
#include "Dices.h"
#include "FlappyBird.h"
#include "WatchInvaders.h"

// Abstract class
#include "Game.h"

#include "MenuControl.h"
// FlappyBird derived;
// Game *game;
bool initGame = false;

string games[] = {
  "Dices",
  "Flappy Bird",
  "Watch Invaders"
};

// Define games class
Game *game;
Dices dices;
FlappyBird flappyBird;
WatchInvaders watchInvaders;

int numGames = 3;
int gameSelected = -1;

MenuControl menu = MenuControl(games, numGames);

void setGame();

void setup() {
  M5.begin();
  flappyBird = FlappyBird();
  dices = Dices();
  watchInvaders = WatchInvaders();
  initGame = false;
  // Serial.begin(9600);
  // game = Game();
}

void loop() {
  if(!initGame) {
    gameSelected = menu.loop();
  }

  if(gameSelected > -1 && !initGame) {
    setGame();
    game->gameInit();
    initGame = true;
  }

  if(initGame) {
    game->gameLoop();
  }
}

void setGame() {
  switch (gameSelected) {
    case 0:
      game = &dices;
      break;

    case 1:
      game = &flappyBird;
      break;

    case 2:
      game = &watchInvaders;
      break;
    
    default:
      break;
  }
}