#include <M5StickC.h>
#include <Preferences.h>
#include <SPIFFS.h>
#include <string>

String file_path = "/M5Stack/";
bool SPIFFS_FORMAT = false;

bool error = false, send = false, start = false;

int check_num_files() {
  if(SPIFFS.begin()) {
    for(int index=0 ; true ; index++) {
      String file_path_index = file_path + String(index) + ".txt";
      if(!SPIFFS.exists(file_path_index)) return index - 1;
    }
  }
}

void setup() {
  // put your setup code here, to run once:
  M5.begin();
  M5.Lcd.setRotation(1);
  M5.IMU.Init();
  M5.Lcd.setTextColor(WHITE);
  Serial.begin(9600);
  // preferences.begin("my-app", false);
  // preferences.putUInt("index", 0);
  // preferences.end();

  if (SPIFFS_FORMAT) {
    SPIFFS.format();
  }
}

void loop() {

  M5.Lcd.fillScreen(BLACK);
  M5.Lcd.fillCircle(80, 40, 10, RED);
  while(!send) {
    M5.Lcd.setCursor(0, 5);
    if(!error) {
      M5.Lcd.print("  Aperte o botao home para\n  iniciar a tranferencia");
      // wait for push button HOME
      if(digitalRead(M5_BUTTON_HOME) == LOW) {
        while(digitalRead(M5_BUTTON_HOME) == LOW)
          ;      
        send = true;
        // Serial.println("Botao pressionado");
        // send = false;
        break;
      }
    }
  }

  delay(1000);

  if(send) {
    int max = check_num_files();
    M5.Lcd.fillScreen(BLACK);
    M5.Lcd.fillCircle(80, 40, 10, GREEN);
    for(int i=0; i <= max; i++) {
      String file_name = String(i) + ".txt";
      // M5.Lcd.fillScreen(BLACK);
      // M5.Lcd.setCursor(20, 40);
      // M5.Lcd.println("Enviando arquivo:");
      // M5.Lcd.setCursor(20, 40);
      // M5.Lcd.print(file_name);
      String file_id = "f," + file_name;
      Serial.println(file_id);
      delay(500);
      String file_path_index = file_path + file_name;
      File dataFile = SPIFFS.open(file_path_index);
      String line = String(dataFile.readString());
      Serial.println(line);
      delay(500);
    }
    M5.Lcd.fillScreen(BLACK);
    M5.Lcd.setCursor(20, 40);
    M5.Lcd.println("Todos os arquivos foram enviados!");   
    Serial.println("END");
    send = false;
  }
}
