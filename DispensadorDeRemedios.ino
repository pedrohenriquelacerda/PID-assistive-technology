#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <Stepper.h>
#include <math.h>

LiquidCrystal_I2C lcd(0x27, 16, 2); //Portas utilizadas
int seconds = 0, minutes = 0, hours = 0;
int numberOfDoses = 0;
int medicationTime = 1;
const int buttonIncreasePin = 7;
const int buttonDecreasePin = 6;
const int buttonConfirmPin = 5;

int buttonConfirmState = 0, buttonIncreaseState = 0, buttonDecreaseState = 0;

const int stepsPerRevolution = 1000;
Stepper myStepper(stepsPerRevolution, 8, 10, 9, 11);

void setup() {
  myStepper.setSpeed(10);
  Serial.begin(9600);
  lcd.init();
  lcd.backlight();
  lcd.clear();

  pinMode(buttonIncreasePin, INPUT);
  pinMode(buttonDecreasePin, INPUT);
  pinMode(buttonConfirmPin, INPUT);

  while(digitalRead(buttonConfirmPin) == LOW){
  buttonIncreaseState = digitalRead(buttonIncreasePin);
  buttonDecreaseState = digitalRead(buttonDecreasePin);

  lcd.setCursor(0, 0);
  lcd.print("Intervalo: ");
  lcd.setCursor(11, 0);
  lcd.print("    ");
  lcd.setCursor(11, 0);
  lcd.print(medicationTime);
  Serial.println(medicationTime);

  if(buttonIncreaseState == HIGH && medicationTime < 24){
    medicationTime++;
    Serial.println(medicationTime);
    delay(350);
  }else if(buttonDecreaseState == HIGH && medicationTime > 1){
    medicationTime--;
    Serial.println(medicationTime);
    delay(350);
  }
  }
  lcd.clear();
  hours = medicationTime;
  numberOfDoses = (int)floor(24 / medicationTime);
  numberOfDoses = min(numberOfDoses, 4);
  Serial.println(numberOfDoses);
}

void loop() {
for (int i=0; i < numberOfDoses; i++){
  hours = medicationTime;
  minutes = 0;
  seconds = 0;

 while (hours > 0 || minutes > 0 || seconds > 0) {
  lcd.setCursor(0,0); // Primeira linha do display
  lcd.print(hours);
  lcd.print(":");
  lcd.print(minutes);
  lcd.print(":");
  lcd.print(seconds);
 if (seconds > 0) {
      seconds--;
    } else if (minutes > 0) {
      minutes--;
      seconds = 59;  // Reseta os segundos
    } else if (hours > 0) {
      hours--;
      minutes = 59;  // Reseta os minutos
      seconds = 59;  // Reseta os segundos
    }
  delay(1000);
  }
  //Ajustar a quantidade de passos
  lcd.clear();
  lcd.setCursor(0,0); // Primeira linha do display
  lcd.print("Hora de tomar");
  lcd.setCursor(0,1); // Segunda linha do display
  lcd.print("seu medicamento!");
  myStepper.step(500);
  delay(10000);
  lcd.clear();
  }
  setup();
}
