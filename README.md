
# XEdgeLab: Real-Time Lab Environment Monitoring with On-Device ML on Microcontrollers

**XEdgeLab** is a project designed to monitor environmental parameters (oxygen, temperature, humidity, and pressure) in a lab setting using an ESP32 microcontroller with the BME280 and Grove Oxygen Sensor. The system uses an XGBoost model with engineered lagged features to predict future values and detect anomalies. This model is converted by/to ONNX/TensorFlow Lite for efficient on-device inference.

## Project Structure

- **data_collection**: Scripts for real-time data collection using BME280 and oxygen sensor with the ESP32.
- **feature_engineering**: Python script to generate lagged and cyclic features for the model.
- **model_training**: Contains scripts for model training, conversion to TensorFlow Lite, and comparison.
- **deployment**: Code for deploying the TensorFlow Lite model on the ESP32, including real-time anomaly detection and alerts.

## Hardware Requirements

- **ESP32 Microcontroller or similar and platform**
- **BME280 Sensor**: Measures temperature, humidity, and pressure.
- **Grove Oxygen Sensor (ME2-O2)**: Measures oxygen concentration in the air.
- **Jumper Wires** and **Breadboard** for connections.

## Software Requirements

- Python 3.6+
- Arduino IDE or PlatformIO for ESP32 microcontroller code
- TensorFlow Lite for Microcontrollers

Install Python dependencies using:

```bash
pip install -r requirements.txt
