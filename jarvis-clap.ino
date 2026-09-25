#include <DHT.h>

#define DHTPIN A2
#define DHTTYPE DHT11

#define SOUND_DO 4
#define SOUND_VCC 5
#define SOUND_GND 6

#define BUZZER 9
#define BUZZER_GND 11

DHT dht(DHTPIN, DHTTYPE);
int count = 0;

void startupSound() {
  tone(BUZZER, 784, 200); delay(250);
  tone(BUZZER, 1047, 400); delay(450);
  noTone(BUZZER);
}

void setup() {
  Serial.begin(9600);
  pinMode(SOUND_VCC, OUTPUT); digitalWrite(SOUND_VCC, HIGH);
  pinMode(SOUND_GND, OUTPUT); digitalWrite(SOUND_GND, LOW);
  pinMode(BUZZER, OUTPUT);
  pinMode(BUZZER_GND, OUTPUT); digitalWrite(BUZZER_GND, LOW);
  pinMode(SOUND_DO, INPUT);
  dht.begin();
  delay(2000);
}

void loop() {
  int sound = digitalRead(SOUND_DO);
  if (sound == LOW) {
    count++;
    if (count > 3) {
      float temp = dht.readTemperature();
      float humidity = dht.readHumidity();
      startupSound();
      Serial.print("CLAP|");
      Serial.print(temp);
      Serial.print("|");
      Serial.println(humidity);
      count = 0;
      delay(2000);
    }
  } else {
    count = 0;
  }
  delay(10);
}
