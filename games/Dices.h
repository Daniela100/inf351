#ifndef DICES_H
#define DICES_H

#include "Game.h"

class Dices : public Game {
    public:
        Dices();
        int dot[6][6][2]{
                                {{35, 35}},
                                {{15, 15}, {55, 55}},
                                {{15, 15}, {35, 35}, {55, 55}},
                                {{15, 15}, {15, 55}, {55, 15}, {55, 55}},
                                {{15, 15}, {15, 55}, {35, 35}, {55, 15}, {55, 55}},
                                {{15, 15}, {15, 35}, {15, 55}, {55, 15}, {55, 35}, {55, 55}},
                            };

        float accX;
        float accY;
        float accZ;

        int selectedDice;
        int button;
        int cur_value   ;
        int num1        ;
        int num2        ;

        virtual void gameLoop();
        virtual string getName();
        virtual void gameInit();
        
    private:
        int DOT_SIZE;
        void draw_dice(int16_t x, int16_t y, int n);
};

#endif