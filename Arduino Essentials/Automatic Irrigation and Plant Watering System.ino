#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <DHT.h>

#define DHT11PIN 3
#define DHTTYPE DHT11

DHT dht(DHT11PIN, DHTTYPE);
LiquidCrystal_I2C lcd(0x20, 16, 2); // Set the LCD address to 0x27 for a 16x2 display

int percentage= 0;
int soilMoistureValue = 0; 
int chk = 0; // Digital pin for DHT11 sensor

void setup() {
  lcd.init();         // Initialize the LCD
  lcd.backlight();    // Turn on the backlight
  dht.begin();
  pinMode(12,OUTPUT);
  Serial.begin(9600);
}

void loop() {
  delay(2000);
  soilMoistureValue = analogRead(A1);
  chk = dht.read(3);
  float humidity = dht.readHumidity(true);
  float temp = dht.readTemperature(true);
  percentage = map(soilMoistureValue, 490, 1023, 100, 0);

  lcd.setCursor(0, 0);
  lcd.print("Soil Moisture:");
  lcd.setCursor(0, 1);
  lcd.print(soilMoistureValue);

  delay(500);
  lcd.clear();

  lcd.setCursor(0, 0);
  lcd.print("Temperature: ");
  lcd.setCursor(0, 1);
  lcd.print(temp);

  delay(500);
  lcd.clear();

  lcd.setCursor(0, 0);
  lcd.print("Humidity: ");
  lcd.setCursor(0, 1);
  lcd.print(humidity);

  delay(500);
  lcd.clear();
  
  if(percentage < 10){
    Serial.println(" pump is off");
    digitalWrite(12,LOW);
    lcd.setCursor(0, 0);
    lcd.print("Pump is off");
    delay(500);
    lcd.clear();
    }
  if(percentage >80){
    Serial.println("pump is on");
    digitalWrite(12,HIGH);
    lcd.setCursor(0, 0);
    lcd.print("Pump is on");
    delay(500);
    lcd.clear();
    }

  Serial.print("Soil Moisture: ");
  Serial.print(soilMoistureValue);
  Serial.print(", Temperature: ");
  Serial.print(temp);
  Serial.print(", Humidity: ");
  Serial.print(humidity);
  Serial.println("%");

  delay(500); // Read and update every 1 second
}
