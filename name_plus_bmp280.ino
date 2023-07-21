// Children's Supervillian Science Workshop by Field Lab 7

#include <U8g2lib.h>
#include <Adafruit_BMP280.h>
#include <Wire.h>

Adafruit_BMP280 bmp280;
U8G2_SH1106_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0, U8X8_PIN_NONE);

void setup() {
  //Serial.begin(9600);

  Wire.begin(); //Join I2C bus
  bmp280.begin(0x76);

  u8g2.begin();
  u8g2.clearBuffer();
  u8g2.setFont(u8g2_font_ncenB08_tr);
  u8g2.drawStr(50, 10, "2023");
  u8g2.setFont(u8g2_font_ncenB14_tr);
  u8g2.drawStr(20, 30, "built by");
  u8g2.drawStr(20, 46, "Lucien");
  u8g2.drawStr(20, 62, "Duncan");
  u8g2.sendBuffer();

  delay(3000);
}

void loop() {
  uint32_t pressure = bmp280.readPressure();
  float tempC = bmp280.readTemperature();
  float tempF = (tempC * 9) / 5 + 32;
  float altitude = bmp280.readAltitude(1013.25) * 3.281;

  u8g2.clearBuffer();
  u8g2.setFont(u8g2_font_ncenB10_tr);
  u8g2.drawStr(46, 11, "ENV");

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
  //Serial.println("-");
}
