#include <M5StickC.h>
#include <string>

// ------------------ VARIÁVEIS QUE PODEM SER ALTERADAS -----------------
// Tempo de coleta de dados (em minutos)
int RECORD_TIME = 1;
// Intervalo de tempo para coletar os dados (milisegundos)
int GAP = 500;
// ----------------------------------------------------------------------

float accX = 0.0f;
float accY = 0.0f;
float accZ = 0.0f;

float gyroX = 0.0f;
float gyroY = 0.0f;
float gyroZ = 0.0f;

float pitch = 0.0f;
float roll  = 0.0f;
float yaw   = 0.0f;

bool start;
bool rec = true;
int RECORD_TIME_MS = RECORD_TIME * 1000 * 60;
int count_rec_time = 0;
int delay_gap = GAP / 2;

float data[9];

void setup() {
  // put your setup code here, to run once:
  M5.begin();
  M5.Lcd.setRotation(3);
  M5.IMU.Init();
  M5.Lcd.setTextColor(WHITE);
  M5.Lcd.fillCircle(80, 40, 10, RED);
  start = false;
}

// Protótipos
void get_data();
String display_data();


void loop() {
  M5.update();

  while(!start) {
    M5.Lcd.setCursor(0, 5);
    M5.Lcd.print("  Aperte o botao home\n  para iniciar");
    // wait for push button HOME
    if(digitalRead(M5_BUTTON_HOME) == LOW) {
      while(digitalRead(M5_BUTTON_HOME) == LOW)
        ;      
      start = true;
      rec = true;
      count_rec_time = 0;
      break;
    }
  }
  
  if(start) {
    while(count_rec_time <= RECORD_TIME_MS) {
      if(rec) {
        get_data();
        String line = display_data();
        M5.Lcd.fillCircle(120, 60, 10, RED);   
        rec = false;
      } else {
        rec = true;
        M5.Lcd.fillCircle(120, 60, 10, BLACK);
      }
        
      count_rec_time += delay_gap;

      delay(delay_gap);
    }
      
    start = false;
    M5.Lcd.fillScreen(BLACK);
    M5.Lcd.fillCircle(80, 40, 10, RED);
    M5.Lcd.setCursor(0, 10);      
  }
}

void get_data() {
  M5.IMU.getAccelData(&accX, &accY, &accZ);
  M5.IMU.getGyroData(&gyroX, &gyroY, &gyroZ);
  M5.IMU.getAhrsData(&pitch, &roll, &yaw);

  data[0] = accX; data[1] = accY; data[2] = accZ;
  data[3] = gyroX; data[4] = gyroY; data[5] = gyroZ;
  data[6] = pitch; data[7] = roll; data[8] = yaw;
}

String display_data() {
  M5.Lcd.fillCircle(120, 60, 10, RED);
  M5.Lcd.fillScreen(BLACK);    
  M5.Lcd.setCursor(0, 5);
  M5.Lcd.println(" Acc");
  M5.Lcd.printf(" x: %.1f y: %.1f z: %.1f\n", data[0], data[1], data[2]);
  M5.Lcd.println(" Gyro");
  M5.Lcd.printf(" x: %.1f y: %.1f z: %.1f\n", data[3], data[4], data[5]);
  M5.Lcd.printf(" pitch: %5.2f\n roll: %5.2f\n yaw: %5.2f\n", data[6], data[7], data[8]);
  M5.Lcd.printf(" Time: %d ms", count_rec_time);

  String data_line = "";
  for(int i=0; i<9; i++) {
    String s_data = String(data[i]);
    String aux = (i == 8 ? "?" : ",");
    data_line += s_data + aux;
  }

  return data_line;
}