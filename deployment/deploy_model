#include "TensorFlowLite.h"
#include "model_data.h"
#include "alerts.h"
#include <Adafruit_BME280.h>

Adafruit_BME280 bme;
#define OXYGEN_SENSOR_PIN 34

float input[4];
float output[1];

void setup() {
    Serial.begin(9600);
    bme.begin(0x76);
}

void loop() {
    input[0] = bme.readTemperature();
    input[1] = bme.readHumidity();
    input[2] = bme.readPressure() / 100.0F;
    input[3] = readOxygenPercentage();

    checkForAnomalies(input[0], input[1], input[2], input[3]);
    interpreter.Invoke();

    if (output[0] > THRESHOLD) {
        Serial.println("Anomaly detected in prediction!");
    }

    delay(3600000);
}
