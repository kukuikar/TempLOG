#include <Arduino.h>
#include <GyverMAX6675.h>
#include <EncButton.h>

#define T1_SCK 2
#define T1_CS  3
#define T1_SO  4

#define T2_SCK 5
#define T2_CS  6
#define T2_SO  7

#define T3_SCK 8
#define T3_CS  9
#define T3_SO  10

#define T4_SCK 11
#define T4_CS  12
#define T4_SO  13

#define BTN A0

GyverMAX6675<T1_SCK, T1_SO, T1_CS> T1;
GyverMAX6675<T2_SCK, T2_SO, T2_CS> T2;
GyverMAX6675<T3_SCK, T3_SO, T3_CS> T3;
GyverMAX6675<T4_SCK, T4_SO, T4_CS> T4;

Button btn(BTN, INPUT, LOW);

int b = 0;

void setup() 
{
  Serial.begin(115200);
  pinMode(BTN, INPUT_PULLUP);
  btn.setHoldTimeout(400);
}

uint32_t tmr = millis();
int tmr_interval = 1000;

bool welding = false;

void loop() 
{
  btn.tick();
  if(btn.click()) welding = !welding;

  if(millis() - tmr > tmr_interval)
  {
    tmr = millis();
    float t1, t2, t3, t4 = -1;

    if(T1.readTemp()) t1 = T1.getTemp();
    if(T2.readTemp()) t2 = T2.getTemp();
    if(T3.readTemp()) t3 = T3.getTemp();
    if(T4.readTemp()) t4 = T4.getTemp();

    Serial.print(welding);
    Serial.print(';');
    Serial.print(t1);
    Serial.print(';');
    Serial.print(t2);
    Serial.print(';');
    Serial.print(t3);
    Serial.print(';');
    Serial.println(t4);
  }
}