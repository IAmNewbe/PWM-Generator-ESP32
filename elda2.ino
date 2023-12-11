// #include <Arduino.h>
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27,16,2);  // set the LCD address to 0x27 for a 16 chars and 2 line display
const int potPin = 34;
const int potPin2 = 35;
// variable for storing the potentiometer value
int potValue = 0;
int potValue2 = 0;
const int pwmChannel = 0; // choose a PWM channel (0-15)
const int pwmResolution = 8; // choose a PWM resolution (1-16 bits)
const int frequency = 1000; // initial frequency in Hertz
const int ledPin = 13; // choose the output pin for PWM
int dutyCycle;
int setDuty;
int Frequency;

void setup() {
  Serial.begin(115200);
  lcd.init();                      // initialize the lcd 
  lcd.init();
  // configure PWM
  ledcSetup(pwmChannel, frequency, pwmResolution);
  ledcAttachPin(ledPin, pwmChannel);
  
  // Print a message to the LCD.
  lcd.backlight();
  lcd.setCursor(0,0);
  lcd.print("PWM Generator");
  lcd.setCursor(0,1);
  lcd.print("ESP 32");
  delay(2000);
  lcd.clear();
}

void loop() {
  // Adjust frequency and duty cycle based on user input
  potValue = analogRead(potPin);
  potValue2 = analogRead(potPin2);

  Frequency = map(potValue, 0, 4095, 0, 10000);
  
  setDuty = map(potValue2, 0, 4095, 0, 100);
  dutyCycle = map(setDuty, 0, 100, 0, 1024);

  Serial.print("Pot 1 : ");
  Serial.println(potValue);
  Serial.print("Duty Cycle : ");
  Serial.println(dutyCycle);
  LCD();


  // update PWM frequency and duty cycle
  ledcWriteTone(pwmChannel, Frequency);
  ledcWrite(pwmChannel, dutyCycle);
}

void LCD() {
  lcd.setCursor(0,0);
  lcd.print("Freq : ");
  lcd.setCursor(7,0);
  lcd.print(Frequency);
  lcd.setCursor(14,0);
  lcd.print("Hz");
  lcd.setCursor(0,1);
  lcd.print("Duty C : ");
  lcd.setCursor(9,1);
  lcd.print(setDuty);
  lcd.setCursor(15,1);
  lcd.print("%");
  lcd.clear();
  lcd.setCursor(0,1);
  lcd.print("Duty C : ");
  lcd.setCursor(9,1);
  lcd.print(setDuty);
  lcd.setCursor(15,1);
  lcd.print("%");
}


