#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include "DHT.h"
#include <BH1750.h>

// Chân kết nối cảm biến
#define SOIL_SENSOR_PIN PA1
#define DHTPIN PA0
#define DHTTYPE DHT11

// Khởi tạo đối tượng
LiquidCrystal_I2C lcd(0x27, 16, 2);
DHT dht(DHTPIN, DHTTYPE);
BH1750 lightMeter;
const Rx = PA10;
void setup() {
  Serial.begin(9600, Rx , Tx); // USART1 - Giao tiếp qua PA9 (TX) và PA10 (RX)
  dht.begin();
  pinMode(SOIL_SENSOR_PIN, INPUT);
  Wire.begin();
  lightMeter.begin();
  lcd.init();
  lcd.backlight();
  lcd.clear();
}

void loop() {
  // Đọc dữ liệu từ các cảm biến
  float TempV1 = dht.readTemperature();
  float HumiV1 = dht.readHumidity();
  int sensorValue = analogRead(SOIL_SENSOR_PIN);
  float soilMoisturePercent = map(sensorValue, 1023, 0, 0, 100);
  int lux = lightMeter.readLightLevel();

  // Gửi dữ liệu qua UART
  Serial.print("Temp:");
  Serial.print(TempV1);
  Serial.print(",Humi:");
  Serial.print(HumiV1);
  Serial.print(",Soil:");
  Serial.print(soilMoisturePercent);
  Serial.print(",Lux:");
  Serial.println(lux);
  delay(1000);
}
