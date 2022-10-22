#include "fx.cpp"

// #include <stdlib.h>
// #include <time.h>

#define LED_PIN 1
#define LED_COUNT 144

#define UP 7
#define INTERRUPT 2

#define MATRIX_LEN 12
#define SPACE 4
#define BETWEEN 9
#define BIRD_INIT_X 5

int bird_x = BIRD_INIT_X;
const int bird_y = 1;
volatile int button_pressed = 0;
bool end_game = false;
// volatile int up_pressed = 0;

Adafruit_NeoPixel strip(LED_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800);

int game[MATRIX_LEN][MATRIX_LEN] = {0};
int draw = BETWEEN + 1;
int num_up, num_down;

void set_button_pressed(void) {
	button_pressed = 1;
}

void create_new_obstacle() {
    if(draw == BETWEEN + 1) {
        num_up = random(MATRIX_LEN - SPACE - 1) + 1;
        num_down = MATRIX_LEN - SPACE - num_up;
    } else if(draw < BETWEEN + 1) {
        for(int i=0; i < MATRIX_LEN; i++) game[i][MATRIX_LEN-1] = 0;
        return;
    }

    for(int i=0, cont=1; cont <= num_up; i++, cont++) game[i][MATRIX_LEN-1] = 2;
    for(int i=MATRIX_LEN-1, cont=1; cont <= num_down; i--, cont++) game[i][MATRIX_LEN-1] = 2;
}

bool check_colapse() {
    if(game[bird_x][bird_y] == 2) return true;
    else return false;
}

void process_up() {
    if(digitalRead(UP)) {
        end_game = false;
        bird_x -= 2;
        if(bird_x < 0) {
            end_game = true;
        }
    }

    button_pressed = 0;
}

void process_down() {
    bird_x += 1;
    if(bird_x > MATRIX_LEN-1) {
        end_game = true;
    }
}

void shift_game() {
    for(int i=0; i<MATRIX_LEN; i++) {
        for(int j=0; j<MATRIX_LEN-1; j++) {
            if(game[i][j+1] != 1)
                game[i][j] = game[i][j+1];
        }
    }

    if(check_colapse()) end_game = true;

    create_new_obstacle();

    draw = (draw == BETWEEN+2 ? 1 : draw+1);
}

void draw_game() {
    game[bird_x][bird_y] = 1;
    for(int i=0; i<MATRIX_LEN; i++) {
        for(int j=0; j<MATRIX_LEN ; j++) {
            int led_index = (i % 2 == 0 ? (i*MATRIX_LEN+j) : ((i+1)*MATRIX_LEN-(j+1)));
            if(game[i][j] == 2) {
                strip.setPixelColor(led_index, 0, 255, 0);
            } else if(game[i][j] == 1) {
                strip.setPixelColor(led_index, 255, 0, 0);
            }
        }
    }
    strip.show();
}

void restart_game() {
    strip.clear();
    end_game = true;
    bird_x = BIRD_INIT_X;

    for(int i=0; i<MATRIX_LEN; i++) {
        for(int j=0; j<MATRIX_LEN; j++) {
            game[i][j] = 0;
        }
    }

    game[bird_x][bird_y] = 1;
    draw = BETWEEN + 1;
    draw_game();
}

void setup() {
    pinMode(UP, INPUT);
    // game[6][1] = 1;
    randomSeed(analogRead(0));
    strip.begin();
    strip.show();

    attachInterrupt(digitalPinToInterrupt(INTERRUPT), set_button_pressed, RISING);
    restart_game();
}

void loop() {

    while(end_game) {
        if(button_pressed) {
            process_up();
        }
    }

    while(!end_game) {
        strip.clear();
        shift_game();        
        draw_game();
        delay(400);
        if(button_pressed) {
            process_up();
        } else {
            process_down();
        }
    }

    restart_game();
}
