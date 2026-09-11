# ESP32: Temperature & Humidity Monitoring with LED Control


A lightweight IoT project built using the ESP32 micro-controller to stream real-time temperature, humidity, and motion detection data via an asynchronous local web server.

---

## Hardware Requirements

* **Microcontroller:** ESP32 Development Board
* **Sensors:**
* DHT11 Temperature & Humidity Sensor
* PIR (Passive Infrared) Motion Sensor


* **Prototyping:**
* Breadboard
* Jumper Wires (Male-to-Male, Male-to-Female, Female-to-Female)
* LED


* **Connectivity:** Mobile Hotspot, Pocket Wi-Fi, or local local Wi-Fi network

---

## 💻 Software & Driver Setup

### 1. USB Driver

If your computer does not recognize the ESP32 board when connected via USB, install the CP210x USB to UART Bridge VCP Driver:

* 📥 **Download Driver:** [Silicon Labs CP210x Drivers](https://www.silabs.com/software-and-tools/usb-to-uart-bridge-vcp-drivers?tab=downloads)

### 2. Development Environment

1. Download and install [Arduino IDE](https://www.arduino.cc/en/software).
2. Add ESP32 board support:
* Go to **Tools** > **Board** > **Boards Manager...**
* Search for **`esp32`** by **Espressif Systems** and click **Install**.



---

## 📦 Required Arduino Libraries

Open the Library Manager in Arduino IDE (**Tools** > **Manage Libraries...** or `Ctrl+Shift+I` / `Cmd+Shift+I`) and install the following:

| Library | Author | Purpose |
| --- | --- | --- |
| **DHT sensor library** | Adafruit | Interface with the DHT11 sensor |
| **Adafruit Unified Sensor** | Adafruit | Dependency for Adafruit sensor libraries |
| **ESPAsyncWebServer** | dvarrel | Asynchronous HTTP web server management |
| **AsyncTCP** | dvarrel | Asynchronous TCP library for ESP32 |

---

## 🚀 Quick Start Guide

1. **Wire the Circuit:** Connect the DHT11, PIR sensor, and LED to the designated GPIO pins on your ESP32 board using the appropriate jumper wires.
2. **Configure Network:** Open the project sketch in Arduino IDE and update the Wi-Fi credentials (`SSID` and `Password`) to match your local network or mobile hotspot.
3. **Upload Sketch:** Select your ESP32 board model and COM port under **Tools**, then click **Upload**.
4. **View Output:** Open the Serial Monitor (`115200` baud rate) to find the IP address assigned to your ESP32. Navigate to that IP address in any web browser to view the live dashboard.
