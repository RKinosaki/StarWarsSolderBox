#include <Arduino.h>
#include <config.h>
#include <ESP32Servo.h>
#include <sv1_setpoints.h>
#include <sv2_setpoints.h>
#include <Adafruit_INA219.h>
#include <Wire.h>

Servo sv1;
Servo sv2;
Adafruit_INA219 ina;
float voltage;
float cellVoltage;
float cellCurrent;

void setup() {
  Wire.begin(0, 1);
  Serial.begin(115200);


  delay(100);
  if(!ina.begin()){
    Serial.write("Current Sensor Initialisation Error!");
    while (1){
      delay(10);
    }
  } 

  ina.setCalibration_16V_400mA();

  delay(2000);


  ESP32PWM::allocateTimer(0);
  ESP32PWM::allocateTimer(1);
  ESP32PWM::allocateTimer(2);
  ESP32PWM::allocateTimer(3);
  sv1.setPeriodHertz(50);
  sv2.setPeriodHertz(50);
  sv1.attach(SERVO1, 500, 2500);
  sv2.attach(SERVO2, 500, 2500);

  for(std::size_t i=0; i<sv2_waypoints::NUM_SAMPLES; i++){
    sv2.write(sv2_waypoints::LUT1[i]);
    delay(SV2_PERIOD/sv2_waypoints::NUM_SAMPLES);
  }
  for(std::size_t i=0; i<sv1_waypoints::NUM_SAMPLES; i++){
    sv1.write(sv1_waypoints::LUT1[i]);
    delay(SV2_PERIOD/sv1_waypoints::NUM_SAMPLES);
  }

  for(std::size_t i=0; i<sv2_waypoints::NUM_SAMPLES; i++){
    sv2.write(sv2_waypoints::LUT2[i]);
    delay(SV2_PERIOD/sv2_waypoints::NUM_SAMPLES);
  }
  
  delay(3000);

  for(std::size_t i=0; i<sv2_waypoints::NUM_SAMPLES; i++){
    sv2.write(sv2_waypoints::LUT3[i]);
    delay(SV2_PERIOD/sv2_waypoints::NUM_SAMPLES);
  }

  for(std::size_t i=0; i<sv1_waypoints::NUM_SAMPLES; i++){
    sv1.write(sv1_waypoints::LUT2[i]);
    delay(SV2_PERIOD/sv1_waypoints::NUM_SAMPLES);
  }

  for(std::size_t i=0; i<sv2_waypoints::NUM_SAMPLES; i++){
    sv2.write(sv2_waypoints::LUT4[i]);
    delay(SV2_PERIOD/sv2_waypoints::NUM_SAMPLES);
  }


  // sv1.write(120);
  // delay(1000);
  // sv2.write(60);

  // sv2.write(90);
  // delay(1000);



  
}





void loop() {
  cellVoltage = ina.getShuntVoltage_mV()/1000 + ina.getBusVoltage_V();
  cellCurrent = ina.getCurrent_mA();
  Serial.print("Cell Voltage (V): ");
  Serial.println(ina.getShuntVoltage_mV());
  Serial.println(ina.getBusVoltage_V());
  Serial.println(cellVoltage);

  Serial.print("Cell Current (mA): ");
  Serial.println(cellCurrent);
  delay(1000);
}
