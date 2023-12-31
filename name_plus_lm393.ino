// Children's Supervillian Science Workshop by Field Lab 7

#include <U8g2lib.h>
#include <Wire.h>

#define LM393Power 7
#define LM393Pin 5

U8G2_SH1106_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0, U8X8_PIN_NONE);

void setup() {
  pinMode(LM393Power, OUTPUT);
  digitalWrite(LM393Power, LOW);
  
  Serial.begin(9600);
  Wire.begin(); //Join I2C bus

  u8g2.begin();
  u8g2.clearBuffer();
  u8g2.setFont(u8g2_font_ncenB08_tr);
  u8g2.drawStr(50, 10, "2023");
  u8g2.setFont(u8g2_font_ncenB14_tr);
  u8g2.drawStr(20, 30, "built by");
  u8g2.drawStr(20, 46, "Orin");
  u8g2.drawStr(20, 62, "Duncan");
  u8g2.sendBuffer();

  delay(5000);
}

void loop() {
  int val =  readLM393();
  Serial.print("Digital Output: ");
  Serial.println(val);
  
  u8g2.clearBuffer();
  u8g2.setFont(u8g2_font_ncenB10_tr);
  
  if(val) {
    u8g2.drawStr(45,11,"ADD");
    u8g2.drawStr(60,45,"2");
    u8g2.setFont(u8g2_font_ncenB14_tr);
    u8g2.drawStr(44,40,"H  0");
    Serial.println("Please Water");
  } 
  else {
    u8g2.drawStr(60,11,":)");
    u8g2.drawStr(40,45,"2");
    u8g2.setFont(u8g2_font_ncenB14_tr);
    u8g2.drawStr(24,40,"H  O OK");
    Serial.println("Happy Soil");
  }

  u8g2.sendBuffer();

  delay(5000);
  Serial.println();
}

int readLM393() {
  digitalWrite(LM393Power, HIGH);   // Turn the sensor ON
  delay(10);                        // Allow power to settle
  int val = digitalRead(LM393Pin);  // Read the digital value form sensor
  digitalWrite(LM393Power, LOW);    // Turn the sensor OFF
  return val;                       // Return analog moisture value
}
