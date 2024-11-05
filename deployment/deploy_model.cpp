#include "TensorFlowLite.h"
#include "XEdgeLab_tflite_model.h"  // Contains the model as a byte array
#include "alerts.h"
#include <Adafruit_BME280.h>        // BME280 library

// TensorFlow Lite setup
const tflite::Model* model;
tflite::MicroInterpreter* interpreter;
tflite::MicroErrorReporter micro_error_reporter;
tflite::ErrorReporter* error_reporter;
tflite::MicroAllocator* allocator;

constexpr int tensor_arena_size = 2 * 1024;  // Adjust based on model size
uint8_t tensor_arena[tensor_arena_size];

Adafruit_BME280 bme;                  // BME280 instance for temperature, humidity, and pressure
#define OXYGEN_SENSOR_PIN 34          // Analog pin for Grove Oxygen Sensor

float* input;    
float* output;    

void setup() {
    Serial.begin(9600);
    if (!bme.begin(0x76)) {
        Serial.println("BME280 sensor not found");
        while (1);
    }

    // Initialize TensorFlow Lite model and interpreter
    model = tflite::GetModel(XEdgeLab_tflite_model);  // Load the model from header file
    if (model->version() != TFLITE_SCHEMA_VERSION) {
        Serial.println("Model schema version mismatch");
        while (1);
    }

    interpreter = new tflite::MicroInterpreter(
        model, tflite::ops::micro::AllOpsResolver(), tensor_arena, tensor_arena_size, &micro_error_reporter);

    // Allocate memory for the model's input and output tensors
    interpreter->AllocateTensors();
    input = interpreter->input(0)->data.f;
    output = interpreter->output(0)->data.f;
}

// Function to read oxygen percentage from the Grove Oxygen Sensor
float readOxygenPercentage() {
    int sensorValue = analogRead(OXYGEN_SENSOR_PIN);          // Read analog value
    float sensorVoltage = sensorValue * (3.3 / 4095.0);       // Convert ADC value to voltage
    float oxygen_percentage = (sensorVoltage - 0.0) * (21.0 / (2.0 - 0.0));  // Adjust based on calibration
    return oxygen_percentage;
}

void loop() {
    // Collect sensor data for model input
    input[0] = bme.readTemperature();
    input[1] = bme.readHumidity();
    input[2] = bme.readPressure() / 100.0F;  // Pressure in hPa
    input[3] = readOxygenPercentage();

    checkForAnomalies(input[0], input[1], input[2], input[3]);

    // Run inference with TensorFlow Lite
    if (interpreter->Invoke() != kTfLiteOk) {
        Serial.println("Model inference failed");
        return;
    }

    if (output[0] > THRESHOLD) {
        Serial.println("Anomaly detected in prediction!");
    }

    delay(3600000);  // Run every hour
}
