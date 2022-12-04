#include "Dices.h"
#include <M5StickC.h>

Dices::Dices() {
  accX = 0;
  accY = 0;
  accZ = 0;

  selectedDice = -1;
  button       = 37;
  cur_value    = 0;
  num1         = 1;
  num2         = 1;

  DOT_SIZE = 6;
}

string Dices::getName() {
  return "Dices";
}

void Dices::gameInit() {
  M5.Lcd.setRotation(1);
  M5.Lcd.fillScreen(TFT_GREEN);

  M5.Lcd.setTextColor(TFT_BLACK);  // Adding a background colour erases
                           // previous text automatically

  M5.Lcd.setCursor(10, 30);
  M5.Lcd.setTextSize(3);
  M5.Lcd.print("SHAKE ME");
  delay(1000);
  pinMode(button, INPUT);
  M5.IMU.Init();
  Serial.begin(9600);
  Serial.println(0);
}

void Dices::draw_dice(int16_t x, int16_t y, int n) {
  selectedDice = 0;
  M5.Lcd.fillRect(x, y, 70, 70, WHITE);

  for(int d=0; d<6; d++) {
    if(dot[n][d][0] > 0) {
      M5.Lcd.fillCircle(x + dot[n][d][0], y + dot[n][d][1], DOT_SIZE, TFT_BLACK);
    }
  }
}

void Dices::gameLoop() {
  Serial.println(1);
  while (1) {
    if (selectedDice >= 0) {
      cur_value = digitalRead(button);
      if (cur_value == 0) {
        while (cur_value == 0) {
          delay(200);
          cur_value = digitalRead(button);
        }

        if (selectedDice == 0) {
          selectedDice = 1;
          M5.Lcd.drawRect(3, 3, 73, 73, BLUE);
          M5.Lcd.drawRect(2, 2, 75, 75, BLUE);
          M5.Lcd.setCursor(11, 1);
          M5.Lcd.setTextSize(1);
            // M5.Lcd.print("selected 1");
          return;
        } else if (selectedDice == 1) {
          selectedDice = 2;
          M5.Lcd.drawRect(83, 3, 73, 73, BLUE);
          M5.Lcd.drawRect(82, 2, 75, 75, BLUE);
          M5.Lcd.drawRect(3, 3, 73, 73, TFT_GREEN);
          M5.Lcd.drawRect(2, 2, 75, 75, TFT_GREEN);
          M5.Lcd.setCursor(11, 1);
          M5.Lcd.setTextSize(1);
            // M5.Lcd.print("selected 2");
          return;
        } else if (selectedDice == 2) {
          selectedDice = 0;
          M5.Lcd.drawRect(83, 3, 73, 73, TFT_GREEN);
          M5.Lcd.drawRect(82, 2, 75, 75, TFT_GREEN);
          M5.Lcd.drawRect(3, 3, 73, 73, TFT_GREEN);
          M5.Lcd.drawRect(2, 2, 75, 75, TFT_GREEN);
          M5.Lcd.setCursor(11, 1);
          M5.Lcd.setTextSize(1);
            // M5.Lcd.print("selected 0");
          return;
        }
      }
    }
    Serial.println(2);
    M5.IMU.getAccelData(&accX, &accY, &accZ);
    if (accX > 1.5 || accY > 1.5) {
      break;
    }
  }

  M5.Lcd.fillScreen(TFT_GREEN);

  // Draw first dice
  if (selectedDice != 1) {
    num1 = random(0, 6);
  }
  // Draw second dice
  if (selectedDice != 2) {
    num2 = random(0, 6);
  }
  delay(500);  // A little delay to increase suspense :-D
  draw_dice(5, 5, num1);
  delay(500);  // A little delay to increase suspense :-D
  draw_dice(85, 5, num2);
}