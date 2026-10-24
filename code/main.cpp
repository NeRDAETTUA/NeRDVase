#include <Arduino.h>
#include <LCD_NeRD_Vase.h>
#include <HWSensor.h>

#define SOIL_PIN 27
#define SOIL_THRESHOLD 20

#define MOTOR_PIN 26

uint8_t humLevel;

HWSensor soilSensor;

void setup() {

  soilSensor.begin();
  pinMode(MOTOR_PIN, OUTPUT);

  lcd.init();

  Serial.begin(115200);
}

void loop() {
  
  humLevel =  soilSensor.lerPercentagem();
  printvar("Humidade (%)", humLevel);
  checkstate(100, SOIL_THRESHOLD, humLevel);

  if(soilSensor.precisaRega(SOIL_THRESHOLD)) {    //caso o nivel esteja abaixo do desejado
    digitalWrite(MOTOR_PIN, HIGH);
  }
  else if(soilSensor.lerPercentagem() > 35) {     //caso o nivel de humidade atinja um nivel folgado
    digitalWrite(MOTOR_PIN, LOW);
  }
  delay(500);
}


