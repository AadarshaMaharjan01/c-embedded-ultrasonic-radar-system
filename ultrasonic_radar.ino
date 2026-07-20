#define TRIG_PIN 9
#define ECHO_PIN 10
#define RED_LED_PIN 12
#define YELLOW_LED_PIN 13
#define GREEN_LED_PIN 7
#define BUZZER_PIN 8

#include <LiquidCrystal.h>
LiquidCrystal lcd(A0, A1, A2, A3, A4, A5);
#include <Servo.h>
Servo Servomotor;

void setup() {
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  Serial.begin(9600);
  pinMode(BUZZER_PIN, OUTPUT);
  pinMode(RED_LED_PIN, OUTPUT);
  pinMode(YELLOW_LED_PIN, OUTPUT);
  pinMode(GREEN_LED_PIN, OUTPUT);
  lcd.begin(16, 2);
  Servomotor.attach(6);
  Servomotor.write(0);
}

int angle = 10;
int direction = 1;

void loop() {
  long duration;
  float distance;

  if (angle >= 175) {
    direction = -3;
  }
  else if (angle <= 5) {
    direction = 3;
  }
  angle += direction;
  Servomotor.write(angle);

  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);
  duration = pulseIn(ECHO_PIN, HIGH);

  distance = duration * 0.034 / 2;
  Serial.print(angle);
  Serial.print(",");
  Serial.println(distance);
  delay(60);

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Distance: ");
  lcd.print(distance);
  lcd.setCursor(0, 1);

  if (distance < 15) { // RED LED
    digitalWrite(RED_LED_PIN, HIGH);
    digitalWrite(YELLOW_LED_PIN, LOW);
    digitalWrite(GREEN_LED_PIN, LOW);
    digitalWrite(BUZZER_PIN, HIGH);
    lcd.print("Close range");
  }
  else if (distance >= 15 && distance < 30) { // YELLOW LED
    digitalWrite(YELLOW_LED_PIN, HIGH);
    digitalWrite(RED_LED_PIN, LOW);
    digitalWrite(GREEN_LED_PIN, LOW);
    digitalWrite(BUZZER_PIN, LOW);
    lcd.print("Medium range");
  }
  else { // GREEN LED
    digitalWrite(GREEN_LED_PIN, HIGH);
    digitalWrite(YELLOW_LED_PIN, LOW);
    digitalWrite(RED_LED_PIN, LOW);
    digitalWrite(BUZZER_PIN, LOW);
    lcd.print("Far range");
  }
}
