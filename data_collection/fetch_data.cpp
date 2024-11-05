#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>

Adafruit_BME280 bme;
#define OXYGEN_SENSOR_PIN 34

const float OXYGEN_SENSOR_VOLTAGE_21 = 2.0;
const float OXYGEN_SENSOR_VOLTAGE_0 = 0.0;

void setup() {
    Serial.begin(115200);
    if (!bme.begin(0x76)) {
        Serial.println("Could not find a valid BME280 sensor, check wiring!");
        while (1);
    }
}

float readOxygenPercentage() {
    int sensorValue = analogRead(OXYGEN_SENSOR_PIN);
    float sensorVoltage = sensorValue * (3.3 / 4095.0);
    float oxygen_percentage = (sensorVoltage - OXYGEN_SENSOR_VOLTAGE_0) * (21.0 / (OXYGEN_SENSOR_VOLTAGE_21 - OXYGEN_SENSOR_VOLTAGE_0));
    return oxygen_percentage;
}

void loop() {
    float temperature = bme.readTemperature();
    float humidity = bme.readHumidity();
    float pressure = bme.readPressure() / 100.0F;
    float oxygen_percentage = readOxygenPercentage();

    Serial.print("Temperature: ");
    Serial.print(temperature);
    Serial.print(" °C, Humidity: ");
    Serial.print(humidity);
    Serial.print(" %, Pressure: ");
    Serial.print(pressure);
    Serial.print(" hPa, Oxygen: ");
    Serial.print(oxygen_percentage);
    Serial.println(" %");

    delay(3600000);
}
