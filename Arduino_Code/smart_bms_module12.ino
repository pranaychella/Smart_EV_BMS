#include <LiquidCrystal.h>

LiquidCrystal lcd(12,11,5,4,3,2);

//-------------------- INPUT PINS --------------------
const int voltagePin = A0;
const int currentPin = A1;
const int tempPin    = A2;

//-------------------- OUTPUT PINS -------------------
const int fanPin     = 6;
const int relayPin   = 7;

const int redLED     = 8;
const int buzzerPin  = 9;
const int greenLED   = 10;
const int yellowLED  = 13;

//-------------------- LIMITS ------------------------
const int LOW_BATTERY = 20;       // %
const float HIGH_TEMP = 45.0;     // Fan ON
const float CRITICAL_TEMP = 60.0; // Shutdown
const float HIGH_CURRENT = 2.0;   // Amps

//----------------------------------------------------


//---------------- BATTERY ICON ----------------
void batteryIcon(int battery)
{
  lcd.setCursor(0,1);

  if(battery>=80)
      lcd.print("[|||||]");
  else if(battery>=60)
      lcd.print("[|||| ]");
  else if(battery>=40)
      lcd.print("[|||  ]");
  else if(battery>=20)
      lcd.print("[||   ]");
  else if(battery>0)
      lcd.print("[|    ]");
  else
      lcd.print("[     ]");
}

void setup()
{
  lcd.begin(16,2);

  pinMode(fanPin,OUTPUT);
  pinMode(relayPin,OUTPUT);

  pinMode(redLED,OUTPUT);
  pinMode(greenLED,OUTPUT);
  pinMode(yellowLED,OUTPUT);

  pinMode(buzzerPin,OUTPUT);

  digitalWrite(relayPin,HIGH);
  digitalWrite(fanPin,LOW);

  digitalWrite(redLED,LOW);
  digitalWrite(greenLED,HIGH);
  digitalWrite(yellowLED,LOW);

  digitalWrite(buzzerPin,LOW);

  lcd.clear();
  lcd.print("SMART EV BMS");
  lcd.setCursor(0,1);
  lcd.print("System Ready");

  delay(2000);
}

//----------------------------------------------------
void loop()
{
  //---------------- BATTERY ----------------

  int adcVoltage = analogRead(voltagePin);

  float voltage = adcVoltage * 5.0 / 1023.0;

  int battery = map(adcVoltage,0,1023,0,100);

  //---------------- CURRENT ----------------

  int adcCurrent = analogRead(currentPin);

  float sensorVoltage = adcCurrent * 5.0 / 1023.0;

  float current = (sensorVoltage - 2.5) / 0.185;

  //---------------- TEMPERATURE ----------------

  int adcTemp = analogRead(tempPin);

  float tempVoltage = adcTemp * 5.0 / 1023.0;

  float temperature = tempVoltage * 100.0;

  //------------------------------------------------
  // NORMAL STATE
  //------------------------------------------------

  digitalWrite(greenLED,HIGH);
  digitalWrite(yellowLED,LOW);
  digitalWrite(redLED,LOW);

  digitalWrite(fanPin,LOW);
  digitalWrite(relayPin,HIGH);
  digitalWrite(buzzerPin,LOW);

  //------------------------------------------------
  // LOW BATTERY
  //------------------------------------------------

  if(battery <= LOW_BATTERY)
  {
      digitalWrite(redLED,HIGH);
      digitalWrite(greenLED,LOW);

      digitalWrite(buzzerPin,HIGH);

      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("LOW BATTERY");

      lcd.setCursor(0,1);
      lcd.print("CHARGE NOW");

      delay(2000);

      digitalWrite(buzzerPin,LOW);
  }

  //------------------------------------------------
  // HIGH CURRENT
  //------------------------------------------------

  if(current > HIGH_CURRENT)
  {
      digitalWrite(relayPin,LOW);

      digitalWrite(redLED,HIGH);

      digitalWrite(greenLED,LOW);

      digitalWrite(buzzerPin,HIGH);

      lcd.clear();

      lcd.setCursor(0,0);
      lcd.print("OVER CURRENT");

      lcd.setCursor(0,1);
      lcd.print("SYSTEM OFF");

      delay(2000);

      return;
  }

  //------------------------------------------------
  // TEMPERATURE
  //------------------------------------------------

  if(temperature >= HIGH_TEMP && temperature < CRITICAL_TEMP)
  {
      digitalWrite(fanPin,HIGH);

      digitalWrite(greenLED,LOW);

      digitalWrite(yellowLED,HIGH);

      lcd.clear();

      lcd.setCursor(0,0);

      lcd.print("HIGH TEMP");

      lcd.setCursor(0,1);

      lcd.print("FAN ON");

      delay(2000);
  }

  //------------------------------------------------
  // CRITICAL TEMPERATURE
  //------------------------------------------------

  if(temperature >= CRITICAL_TEMP)
  {
      digitalWrite(fanPin,HIGH);

      digitalWrite(relayPin,LOW);

      digitalWrite(redLED,HIGH);

      digitalWrite(greenLED,LOW);

      digitalWrite(yellowLED,LOW);

      digitalWrite(buzzerPin,HIGH);

      lcd.clear();

      lcd.setCursor(0,0);

      lcd.print("OVER TEMP");

      lcd.setCursor(0,1);

      lcd.print("SYSTEM OFF");

      delay(2000);

      return;
  }

  //------------------------------------------------
  // LCD SCREEN 1
  //------------------------------------------------

  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("BATTERY:");
  lcd.print(battery);
  lcd.print("%");
  batteryIcon(battery);
  delay(2000);

  //------------------------------------------------
  // LCD SCREEN 2
  //------------------------------------------------

  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Volt:");
  lcd.print(voltage,2);
  lcd.print("V");

  lcd.setCursor(0,1);
  lcd.print("Cur:");
  lcd.print(current,2);
  lcd.print("A");
  delay(2000);

  //------------------------------------------------
  // LCD SCREEN 3
  //------------------------------------------------

  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Temp:");
  lcd.print(temperature,1);
  lcd.print((char)223);
  lcd.print("C");

  lcd.setCursor(0,1);
  if(digitalRead(fanPin))
    lcd.print("Fan: ON ");
  else
    lcd.print("Fan: OFF");
  delay(2000);

  //------------------------------------------------
  // LCD SCREEN 4
  //------------------------------------------------

  lcd.clear();
  lcd.setCursor(0,0);

  if(digitalRead(relayPin))
    lcd.print("Relay:ON ");
  else
    lcd.print("Relay:OFF");

  lcd.setCursor(0,1);

  if(temperature>=CRITICAL_TEMP)
    lcd.print("CRITICAL");
  else if(temperature>=HIGH_TEMP)
    lcd.print("WARNING");
  else if(battery<=LOW_BATTERY)
    lcd.print("LOW BAT");
  else
    lcd.print("NORMAL");

  delay(2000);
}