#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);

const int PIEZO_PIN = A0;
const int THRESHOLD = 2;

int stepCount = 0;
float voltage = 0;

void setup() {
  lcd.init();
  lcd.backlight();
  Serial.begin(9600);
  lcd.setCursor(0,0);
  lcd.print("Footstep Energy");
  delay(2000);
  lcd.clear();
}

void loop() {
  int rawValue = analogRead(PIEZO_PIN);

  // Print for debugging
  Serial.println(rawValue);

  voltage = (rawValue / 1023.0) * 5.0;

  // Simple step detection
  if (rawValue > THRESHOLD) {
    stepCount++;
    delay(300); // debounce
  }

  // Display
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Steps:");
  lcd.print(stepCount);

  lcd.setCursor(0, 1);
  lcd.print("V:");
  lcd.print(voltage, 2);

  delay(150);
}
