// Children's Supervillian Science Workshop by Field Lab 7

#include <U8g2lib.h>
#include <Adafruit_BMP280.h>
#include <Wire.h>

#define LM393Power 7
#define LM393Pin 5

Adafruit_BMP280 bmp280;
U8G2_SH1106_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0, U8X8_PIN_NONE);

void setup() {
  pinMode(LM393Power, OUTPUT);
  digitalWrite(LM393Power, LOW);

  Serial.begin(9600);

  Wire.begin();
  bmp280.begin(0x76);
  u8g2.begin();
}

void loop() {
  uint32_t pressure = bmp280.readPressure();
  float tempC = bmp280.readTemperature();
  float tempF = (tempC * 9) / 5 + 32;
  float altitude = bmp280.readAltitude(1013.25) * 3.281;

  u8g2.clearBuffer();
  u8g2.setFont(u8g2_font_ncenB10_tr);
  
  if(readLM393()) {
    u8g2.drawStr(5,11,"Please Water");
  } 
  else {
    u8g2.drawStr(25,11,"Happy Soil");
  }

  char buffer[10];
  dtostrf(tempC, 6, 1, buffer);
  u8g2.drawStr(7, 30, buffer);
  u8g2.drawStr(47, 30, "C");

  dtostrf(tempF, 6, 1, buffer);
  u8g2.drawStr(61, 30, buffer);
  u8g2.drawStr(101, 30, "F");

  sprintf(buffer, "%d", pressure);
  u8g2.drawStr(20, 46, buffer);
  u8g2.drawStr(70, 46, "hPa");

  dtostrf(altitude, 6, 0, buffer);
  u8g2.drawStr(20, 62, buffer);
  u8g2.drawStr(70, 62, "FASL");

  u8g2.sendBuffer();

  delay(5000);
  Serial.println();
}

int readLM393() {
  digitalWrite(LM393Power, HIGH);   // Turn the sensor ON
  delay(10);                        // Allow power to settle
  int val = digitalRead(LM393Pin);  // Read the analog value form sensor
  digitalWrite(LM393Power, LOW);    // Turn the sensor OFF
  return val;                       // Return analog moisture value
}
