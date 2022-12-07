#include "MenuControl.h"
#include <M5StickC.h>

#define TFTW  80   // screen width
#define TFTH  160  // screen height
#define TFTW2 40   // half screen width
#define TFTH2 80   // half screen height

#define M5_BUTTON_A 39
#define M5_BUTTON_B 37

MenuControl::MenuControl(const string listGames[], int size) {
  for(int i=0; i<size; i++) {
    games.push_back(listGames[i]);
  }

  curr = 0;
  numGames = games.size();
}

int MenuControl::getNumGames() { return numGames; }

void MenuControl::next() {
  curr += 1;
  if(curr == numGames) curr = 0;
}

int MenuControl::loop() {
  while(1) {
    M5.Lcd.fillScreen(BLACK);
    M5.Lcd.setTextColor(TFT_WHITE);
    M5.Lcd.setTextSize(1);
    // half width - num char * char width in pixels
    M5.Lcd.setCursor(0, 10);
    M5.Lcd.println("  Select the\n    game");
    M5.Lcd.fillRect(0, 30, TFTW, 1, WHITE);
    displayGames();
    M5.Lcd.setCursor(0, TFTH - 30);

    while (1) {
      M5.update();
      // Change game selected - Home button
      if(M5.BtnA.wasReleased()) {
        next();
        break;
      }

      // Select game
      if(M5.BtnB.wasReleased()) {
        return curr;
      }
    }
  }

  return -1;
}

void MenuControl::displayGames() {
  int initH = 40;
  M5.Lcd.setCursor(0, initH);
  initH += 5;
  for(int i=0; i<numGames; i++) {
    if(i == curr) { M5.Lcd.print("> "); }
    else { M5.Lcd.print("  "); }

    M5.Lcd.println(games[i].c_str());
    M5.Lcd.println();
    // M5.Lcd.setCursor(0, initH);
    // initH += 5;
  }
}