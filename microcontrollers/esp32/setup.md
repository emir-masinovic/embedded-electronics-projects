# ESP32

#### **1. Driver and Software Installation**

- **Install the USB Driver**: Download and install the **CH340 driver** to ensure your computer can communicate with the ESP32 board.
- **Install the Arduino IDE**: Download and install the latest version of the **Arduino IDE**.
Note: https://www.silabs.com/software-and-tools/usb-to-uart-bridge-vcp-drivers?tab=downloads

#### **2. Board Setup in the Arduino IDE**

- **Add the ESP32 Board URL**: Open the Arduino IDE, then go to `File > Preferences > Additional Boards Manager URLs` and paste in the following link:
  ```
  https://espressif.github.io/arduino-esp32/package_esp32_index.json
  ```
- **Install the ESP32 Board**: Go to `Tools > Board > Boards Manager > esp8266`. Install your board (If you're not sure which model is your board, use **ESP32 Dev Module**).

#### **3. Connect and Test Your Board**

- **Connect the ESP32**: Plug ESP32 into your computer with a USB cable.
- **Select the Port**: In the Arduino IDE, go to `Tools > Port` and select the active COM port (e.g., COM3, COM4).
- **Upload a Test Sketch**: To ensure everything is working, go to `File > Examples > 01.Basics > Blink` and click the **Upload** button. This will compile and upload the sketch to your board. If the built-in LED starts blinking, your setup is complete!
