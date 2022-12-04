#ifndef FLAPPYBIRD_H
#define FLAPPYBIRD_H

#include "Game.h"
#include <M5StickC.h>
#include <EEPROM.h>

const int buttonPin = 2;
// background
const unsigned int BCKGRDCOL = M5.Lcd.color565(138, 235, 244);
// bird
const unsigned int BIRDCOL = M5.Lcd.color565(255, 254, 174);
// pipe
const unsigned int PIPECOL = M5.Lcd.color565(99, 255, 78);
// pipe highlight
const unsigned int PIPEHIGHCOL = M5.Lcd.color565(250, 255, 250);
// pipe seam
const unsigned int PIPESEAMCOL = M5.Lcd.color565(0, 0, 0);
// floor
const unsigned int FLOORCOL = M5.Lcd.color565(246, 240, 163);
// grass (col2 is the stripe color)
const unsigned int GRASSCOL  = M5.Lcd.color565(141, 225, 87);
const unsigned int GRASSCOL2 = M5.Lcd.color565(156, 239, 88);

#define TFTW  80   // screen width
#define TFTH  160  // screen height
#define TFTW2 40   // half screen width
#define TFTH2 80   // half screen height
// game constant
#define SPEED         1
#define GRAVITY       9.8
#define JUMP_FORCE    2.15
#define SKIP_TICKS    20.0  // 1000 / 50fps
#define MAX_FRAMESKIP 5
// bird size
#define BIRDW  8  // bird width
#define BIRDH  8  // bird height
#define BIRDW2 4  // half width
#define BIRDH2 4  // half height
// pipe size
#define PIPEW     15  // pipe width
#define GAPHEIGHT 30  // pipe gap height
// floor size
#define FLOORH 20  // floor height (from bottom of the screen)
// grass size
#define GRASSH 4  // grass height (inside floor, starts at floor y)

#define C0 BCKGRDCOL
#define C1 M5.Lcd.color565(195, 165, 75)
#define C2 BIRDCOL
#define C3 TFT_WHITE
#define C4 TFT_RED
#define C5 M5.Lcd.color565(251, 216, 114)

#define drawPixel(a, b, c)            \
    M5.Lcd.setAddrWindow(a, b, a, b); \
    M5.Lcd.pushColor(c)

// bird structure
static struct BIRD {
    long x, y, old_y;
    long col;
    float vel_y;
} bird;

// pipe structure
static struct PIPES {
    long x, gap_y;
    long col;
} pipes;

class FlappyBird : public Game {
  public:
    FlappyBird();
    virtual void gameLoop();
    virtual void gameInit();
    virtual string getName();

  private:
    void game_init();
    void game_loop();
    void game_over();
    int address, maxScore, score;
    short tmpx, tmpy;

    unsigned int birdcol[128] = {
      C0, C0, C1, C1, C1, C1, C1, C0, C0, C0, C1, C1, C1, C1, C1, C0, C0, C1, C2,
      C2, C2, C1, C3, C1, C0, C1, C2, C2, C2, C1, C3, C1, C0, C2, C2, C2, C2, C1,
      C3, C1, C0, C2, C2, C2, C2, C1, C3, C1, C1, C1, C1, C2, C2, C3, C1, C1, C1,
      C1, C1, C2, C2, C3, C1, C1, C1, C2, C2, C2, C2, C2, C4, C4, C1, C2, C2, C2,
      C2, C2, C4, C4, C1, C2, C2, C2, C1, C5, C4, C0, C1, C2, C2, C2, C1, C5, C4,
      C0, C0, C1, C2, C1, C5, C5, C5, C0, C0, C1, C2, C1, C5, C5, C5, C0, C0, C0,
      C1, C5, C5, C5, C0, C0, C0, C0, C1, C5, C5, C5, C0, C0
    };


};

#endif