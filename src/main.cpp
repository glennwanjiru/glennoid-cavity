#include <DHT.h>
#include <LiquidCrystal.h>

#define DHTPIN 10    // Connect the DHT sensor to digital pin 2
#define DHTTYPE DHT11   // Change to DHT11 if you're using that sensor

DHT dht(DHTPIN, DHTTYPE);

const int rs = 7, en = 6, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);  // Connect the LCD to pins 8, 9, 4, 5, 6, 7

void setup() 
  lcd.begin(16, 2);  // Initialize the LCD with 16 columns and 2 rows
  dht.begin();
}

void loop() {
  delay(50);  // Delay between readings

  float humidity = dht.readHumidity();
  float temperature =dht.readTemperature();

  lcd.clear();  // Clear the LCD display

  lcd.setCursor(0, 0);  // Set the cursor to the first column, first row
  lcd.print("Temp: ");
  lcd.print(temperature);
  lcd.print(" C");


  lcd.setCursor(0, 1);  // Set the cursor to the first column, second row
  lcd.print("Humidity: ");
  lcd.print(humidity);
  lcd.print(" %");
}