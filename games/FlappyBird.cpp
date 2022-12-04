#include "FlappyBird.h"

FlappyBird::FlappyBird() {
  EEPROM.begin(1000);
  address = 0;
  maxScore = EEPROM.readInt(address);
  pinMode(M5_BUTTON_HOME, INPUT);
}

string FlappyBird::getName() { return "Flappy Bird"; }

void FlappyBird::gameInit() {
    M5.Lcd.fillScreen(TFT_BLACK);
    M5.Lcd.fillRect(0, TFTH2 - 10, TFTW, 1, TFT_WHITE);
    M5.Lcd.fillRect(0, TFTH2 + 15, TFTW, 1, TFT_WHITE);
    M5.Lcd.setTextColor(TFT_WHITE);
    M5.Lcd.setTextSize(1);
    // half width - num char * char width in pixels
    M5.Lcd.setCursor(TFTW2 - 15, TFTH2 - 6);
    M5.Lcd.println("FLAPPY");
    M5.Lcd.setTextSize(1);
    M5.Lcd.setCursor(TFTW2 - 15, TFTH2 + 6);
    M5.Lcd.println("-BIRD-");
    M5.Lcd.setTextSize(1);
    M5.Lcd.setCursor(15, TFTH2 - 21);
    M5.Lcd.println("M5StickC");
    M5.Lcd.setCursor(TFTW2 - 40, TFTH2 + 21);
    M5.Lcd.println("please press home");
    while (1) {
        // wait for push button
        if (digitalRead(M5_BUTTON_HOME) == LOW) {
            while (digitalRead(M5_BUTTON_HOME) == LOW)
                ;
            break;
        }
    }

    // clear screen
    M5.Lcd.fillScreen(BCKGRDCOL);
    // reset score
    score = 0;
    // init bird
    bird.x = 30;
    bird.y = bird.old_y = TFTH2 - BIRDH;
    bird.vel_y          = -JUMP_FORCE;
    tmpx = tmpy = 0;
    // generate new random seed for the pipe gape
    randomSeed(analogRead(0));
    // init pipe
    pipes.x     = 0;
    pipes.gap_y = random(20, TFTH - 60);
}

void FlappyBird::game_init() {
    // clear screen
    M5.Lcd.fillScreen(BCKGRDCOL);
    // reset score
    score = 0;
    // init bird
    bird.x = 30;
    bird.y = bird.old_y = TFTH2 - BIRDH;
    bird.vel_y          = -JUMP_FORCE;
    tmpx = tmpy = 0;
    // generate new random seed for the pipe gape
    randomSeed(analogRead(0));
    // init pipe
    pipes.x     = 0;
    pipes.gap_y = random(20, TFTH - 60);
}

void FlappyBird::game_loop() {
    // ===============
    // prepare game variables
    // draw floor
    // ===============
    // instead of calculating the distance of the floor from the screen height
    // each time store it in a variable
    unsigned char GAMEH = TFTH - FLOORH;
    // draw the floor once, we will not overwrite on this area in-game
    // black line
    M5.Lcd.drawFastHLine(0, GAMEH, TFTW, TFT_BLACK);
    // grass and stripe
    M5.Lcd.fillRect(0, GAMEH + 1, TFTW2, GRASSH, GRASSCOL);
    M5.Lcd.fillRect(TFTW2, GAMEH + 1, TFTW2, GRASSH, GRASSCOL2);
    // black line
    M5.Lcd.drawFastHLine(0, GAMEH + GRASSH, TFTW, TFT_BLACK);
    // mud
    M5.Lcd.fillRect(0, GAMEH + GRASSH + 1, TFTW, FLOORH - GRASSH, FLOORCOL);
    // grass x position (for stripe animation)
    long grassx = TFTW;
    // game loop time variables
    double delta, old_time, next_game_tick, current_time;
    next_game_tick = current_time = millis();
    int loops;
    // passed pipe flag to count score
    bool passed_pipe = false;
    // temp var for setAddrWindow
    unsigned char px;

    while (1) {
        loops = 0;
        while (millis() > next_game_tick && loops < MAX_FRAMESKIP) {
            if (digitalRead(M5_BUTTON_HOME) == LOW) {
                // while(digitalRead(M5_BUTTON_HOME) == LOW);
                if (bird.y > BIRDH2 * 0.5) bird.vel_y = -JUMP_FORCE;
                // else zero velocity
                else
                    bird.vel_y = 0;
            }

            // ===============
            // update
            // ===============
            // calculate delta time
            // ---------------
            old_time     = current_time;
            current_time = millis();
            delta        = (current_time - old_time) / 1000;

            // bird
            // ---------------
            bird.vel_y += GRAVITY * delta;
            bird.y += bird.vel_y;

            // pipe
            // ---------------

            pipes.x -= SPEED;
            // if pipe reached edge of the screen reset its position and gap
            if (pipes.x < -PIPEW) {
                pipes.x     = TFTW;
                pipes.gap_y = random(10, GAMEH - (10 + GAPHEIGHT));
            }

            // ---------------
            next_game_tick += SKIP_TICKS;
            loops++;
        }

        // ===============
        // draw
        // ===============
        // pipe
        // ---------------
        // we save cycles if we avoid drawing the pipe when outside the screen

        if (pipes.x >= 0 && pipes.x < TFTW) {
            // pipe color
            M5.Lcd.drawFastVLine(pipes.x + 3, 0, pipes.gap_y, PIPECOL);
            M5.Lcd.drawFastVLine(pipes.x + 3, pipes.gap_y + GAPHEIGHT + 1,
                                 GAMEH - (pipes.gap_y + GAPHEIGHT + 1),
                                 PIPECOL);
            // highlight
            M5.Lcd.drawFastVLine(pipes.x, 0, pipes.gap_y, PIPEHIGHCOL);
            M5.Lcd.drawFastVLine(pipes.x, pipes.gap_y + GAPHEIGHT + 1,
                                 GAMEH - (pipes.gap_y + GAPHEIGHT + 1),
                                 PIPEHIGHCOL);
            // bottom and top border of pipe
            drawPixel(pipes.x, pipes.gap_y, PIPESEAMCOL);
            drawPixel(pipes.x, pipes.gap_y + GAPHEIGHT, PIPESEAMCOL);
            // pipe seam
            drawPixel(pipes.x, pipes.gap_y - 6, PIPESEAMCOL);
            drawPixel(pipes.x, pipes.gap_y + GAPHEIGHT + 6, PIPESEAMCOL);
            drawPixel(pipes.x + 3, pipes.gap_y - 6, PIPESEAMCOL);
            drawPixel(pipes.x + 3, pipes.gap_y + GAPHEIGHT + 6, PIPESEAMCOL);
        }
#if 1
        // erase behind pipe
        if (pipes.x <= TFTW)
            M5.Lcd.drawFastVLine(pipes.x + PIPEW, 0, GAMEH, BCKGRDCOL);
            // M5.Lcd.drawFastVLine(pipes.x, 0, GAMEH, BCKGRDCOL);
            // PIPECOL
#endif
        // bird
        // ---------------
        tmpx = BIRDW - 1;
        do {
            px = bird.x + tmpx + BIRDW;
            // clear bird at previous position stored in old_y
            // we can't just erase the pixels before and after current position
            // because of the non-linear bird movement (it would leave 'dirty'
            // pixels)
            tmpy = BIRDH - 1;
            do {
                drawPixel(px, bird.old_y + tmpy, BCKGRDCOL);
            } while (tmpy--);
            // draw bird sprite at new position
            tmpy = BIRDH - 1;
            do {
                drawPixel(px, bird.y + tmpy, birdcol[tmpx + (tmpy * BIRDW)]);
            } while (tmpy--);
        } while (tmpx--);
        // save position to erase bird on next draw
        bird.old_y = bird.y;

        // grass stripes
        // ---------------
        grassx -= SPEED;
        if (grassx < 0) grassx = TFTW;
        M5.Lcd.drawFastVLine(grassx % TFTW, GAMEH + 1, GRASSH - 1, GRASSCOL);
        M5.Lcd.drawFastVLine((grassx + 64) % TFTW, GAMEH + 1, GRASSH - 1,
                             GRASSCOL2);

        // ===============
        // collision
        // ===============
        // if the bird hit the ground game over
        if (bird.y > GAMEH - BIRDH) break;
        // checking for bird collision with pipe
        if (bird.x + BIRDW >= pipes.x - BIRDW2 &&
            bird.x <= pipes.x + PIPEW - BIRDW) {
            // bird entered a pipe, check for collision
            if (bird.y < pipes.gap_y ||
                bird.y + BIRDH > pipes.gap_y + GAPHEIGHT)
                break;
            else
                passed_pipe = true;
        }
        // if bird has passed the pipe increase score
        else if (bird.x > pipes.x + PIPEW - BIRDW && passed_pipe) {
            passed_pipe = false;
            // erase score with background color
            M5.Lcd.setTextColor(BCKGRDCOL);
            M5.Lcd.setCursor(TFTW2, 4);
            M5.Lcd.print(score);
            // set text color back to white for new score
            M5.Lcd.setTextColor(TFT_WHITE);
            // increase score since we successfully passed a pipe
            score++;
        }

        // update score
        // ---------------
        M5.Lcd.setCursor(2, 4);
        M5.Lcd.print(score);
    }

    // add a small delay to show how the player lost
    delay(1200);
}

void FlappyBird::game_over() {
    M5.Lcd.fillScreen(TFT_BLACK);
    maxScore = EEPROM.readInt(address);

    if (score > maxScore) {
        EEPROM.writeInt(address, score);
        EEPROM.commit();
        maxScore = score;
        M5.Lcd.setTextColor(TFT_RED);
        M5.Lcd.setTextSize(1);
        M5.Lcd.setCursor(0, TFTH2 - 16);
        M5.Lcd.println("NEW HIGHSCORE");
    }

    M5.Lcd.setTextColor(TFT_WHITE);
    M5.Lcd.setTextSize(1);
    // half width - num char * char width in pixels
    M5.Lcd.setCursor(TFTW2 - 25, TFTH2 - 6);
    M5.Lcd.println("GAME OVER");
    M5.Lcd.setTextSize(1);
    M5.Lcd.setCursor(1, 10);
    M5.Lcd.print("score: ");
    M5.Lcd.print(score);
    M5.Lcd.setCursor(5, TFTH2 + 6);
    M5.Lcd.println("press home to play again");
    M5.Lcd.setCursor(1, 21);
    M5.Lcd.print("Max Score:");
    M5.Lcd.print(maxScore);
    while (1) {
        // wait for push button
        if (digitalRead(M5_BUTTON_HOME) == LOW) {
            while (digitalRead(M5_BUTTON_HOME) == LOW)
                ;
            break;
        }
    }

}

void FlappyBird::gameLoop() {
    game_init();
    game_loop();
    game_over();
}