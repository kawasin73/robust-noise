#include <stdio.h>
#include <MsTimer2.h>

#define LED_PIN 13
#define OUT_PIN 2
#define RECORDS 7
#define DURATION 60000

long i = 0;
long j = 0;
boolean finish = false;

// cycle, min-ON, max-ON, min-OFF, max-OFF
long table[RECORDS][5] = {
  // member1
  {5, 100, 200, 50, 50},
  // member2
  {2,500,600, 40,50},
  // member3
  {4, 250, 251, 250, 251},
  // member4
  {2, 300, 450, 50, 80},
  // member5
  {1, 200, 400, 300, 700},
  {1, 200, 300, 250, 600},
  // member6
  {1, 500, 1500, 500, 1500},
};

void timerFire() {
  finish = true;
  MsTimer2::stop();
}

void setup() {
  // put your setup code here, to run once:
  randomSeed(0);
  pinMode(OUT_PIN, OUTPUT);
  Serial.begin(9600);
  Serial.println("setup");
  i = 0;
  j = 0;
  Serial.println("start");
  MsTimer2::set(DURATION, timerFire);
  MsTimer2::start();
}

void loop() {
  if (finish) {
    Serial.println("finished");
    digitalWrite(OUT_PIN, HIGH);
    delay(1000);
    return;
  }
  long *record = table[i];
  long on = random(record[1], record[2]+1);
  long off = random(record[3], record[4]+1);

  // log
  char buf[100];
  sprintf(buf, "i: %ld, j: %ld, on: %ld, off:%ld", i, j, on, off);
  Serial.println(buf);

  digitalWrite(OUT_PIN, HIGH);
  Serial.println("high");
  delay(on);
  digitalWrite(OUT_PIN, LOW);
  Serial.println("low");
  delay(off);

  // finish 1 cycle
  j++;
  if (j >= record[0]) {
    j = 0;
    // next record
    i++;
    if (i >= RECORDS) {
      // rotate
      i = 0;
    }
  }
}
