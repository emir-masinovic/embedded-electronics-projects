# ESP 8266

#### **1. Driver and Software Installation**

- **Install the USB Driver**: Download and install the **CH340 driver** to ensure your computer can communicate with the ESP8266 board.
- **Install the Arduino IDE**: Download and install the latest version of the **Arduino IDE**. This is the software you'll use to write and upload your code.

#### **2. Board Setup in the Arduino IDE**

- **Add the ESP8266 Board URL**: Open the Arduino IDE, then go to `File > Preferences > Additional Boards Manager URLs` and paste the following link:
  ```
  http://arduino.esp8266.com/stable/package_esp8266com_index.json
  ```
- **Install the ESP8266 Board**: Go to `Tools > Board > Boards Manager > esp8266`. Install your board (If you're not sure, use **Generic ESP8266 Module**).

#### **3. Connect and Test Your Board**

- **Connect the ESP8266**: Plug your ESP8266 board into your computer with a micro USB cable.
- **Select the Port**: In the Arduino IDE, go to `Tools > Port` and select the active COM port (e.g., COM3, COM4) that corresponds to your connected board.
- **Upload a Test Sketch**: To ensure everything is working, go to `File > Examples > 01.Basics > Blink`. Click the **Upload** button to compile and upload the sketch to your board. If the built-in LED starts blinking, your setup is complete!
