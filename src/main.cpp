#include <Arduino.h>
#include <GyverMAX6675.h>

#define T4_SCK 4
#define T4_CS 3
#define T4_SO 2

#define T3_SCK 7
#define T3_CS 6
#define T3_SO 5

#define T2_SCK 10
#define T2_CS 9
#define T2_SO 8

#define T1_SCK A0
#define T1_CS 13
#define T1_SO 11

#define BTN 12

GyverMAX6675<T1_SCK, T1_SO, T1_CS> T1;
GyverMAX6675<T2_SCK, T2_SO, T2_CS> T2;
GyverMAX6675<T3_SCK, T3_SO, T3_CS> T3;
GyverMAX6675<T4_SCK, T4_SO, T4_CS> T4;

// EncButton btn(A1, A2, BTN);

int b = 0;

void setup()
{
  Serial.begin(115200);
  pinMode(BTN, INPUT_PULLUP);
  // digitalWrite(BTN, HIGH);
  // btn.setHoldTimeout(400);
  // btn.setButtonLevel(LOW);
}

uint32_t tmr = millis();
uint16_t tmr_interval = 500;

bool welding = false;

void loop()
{
  // btn.tick();
  // if(btn.click())
  // Serial.println("rrrrrrrr");
  // if(btn.click()) welding = !welding;

  welding = digitalRead(BTN);
  if (millis() - tmr > tmr_interval)
  {
    tmr = millis();
    float t1, t2, t3, t4 = -1.00;

    if (T1.readTemp())
      t1 = T1.getTemp();
    if (T2.readTemp())
      t2 = T2.getTemp();
    if (T3.readTemp())
      t3 = T3.getTemp();
    if (T4.readTemp())
      t4 = T4.getTemp();

    // char buf[64];
    // snprintf(buf, 64, "%d\t%f\t%f\t%f\t%f", welding, t1, t2, t3, t4);
    // Serial.println(buf);

    Serial.print(welding);
    Serial.print('\t');
    Serial.print(t1);
    Serial.print('\t');
    Serial.print(t2);
    Serial.print('\t');
    Serial.print(t3);
    Serial.print('\t');
    Serial.println(t4);
  }
}