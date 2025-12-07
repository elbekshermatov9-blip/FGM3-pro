# 📡 FGM-3 PRO Mobile Phone Detector

This project uses the **FGM-3 PRO electromagnetic sensor** with an **Arduino Mega 2560** to detect nearby mobile phones, whether they are on, off, or transmitting signals.

The detector works by identifying electromagnetic spikes created by mobile phones while connecting to the network, sending data, or searching for signal.

---

## 🔧 Features

* Detects mobile phones within range (ON or OFF)
* LED indicator shows when a phone is detected
* Serial Monitor shows real-time sensor values
* Noise filtering built-in for stable detection
* Works with Arduino Mega, Uno, Nano

---

## 🧪 Hardware Requirements

| Component         | Quantity |
| ----------------- | -------- |
| Arduino Mega 2560 | 1        |
| FGM-3 PRO Sensor  | 1        |
| LED (any color)   | 1        |
| 220Ω resistor     | 1        |
| Jumper wires      | Several  |
| Breadboard        | 1        |

---

## 📌 Wiring Diagram

| FGM-3 PRO Pin | Arduino Mega Pin |
| ------------- | ---------------- |
| OUT           | A1               |
| VCC           | 5V               |
| GND           | GND              |

| LED Pin          | Arduino Mega Pin |
| ---------------- | ---------------- |
| + (through 220Ω) | D3               |
| -                | GND              |

---

## 🧠 How It Works

The FGM-3 PRO detects fluctuations in the electromagnetic field. Mobile phones create high-frequency pulses that the Arduino reads as spikes.

If the sensor value passes a threshold several times in a row, the code confirms phone presence.

---

## 💻 Arduino Code

Copy this into your Arduino IDE and save it as `fgm3_phone_detector.ino`.

```cpp
#define FMG_3_PRO A1
#define LED_pin 3

int prevValue = 0;  
bool phoneDetected = false;

const int DETECT_THRESHOLD = 1017;
const int STABLE_COUNT = 5;

int highCount = 0;
int lowCount = 0;

void setup() {
  Serial.begin(9600);
  pinMode(LED_pin, OUTPUT);
  pinMode(FMG_3_PRO, INPUT);

  Serial.println("FGM-3 PRO Phone Detector Started...");
}

void loop() {
  int value = analogRead(FMG_3_PRO);

  Serial.print("Sensor: ");
  Serial.println(value);

  if (value >= DETECT_THRESHOLD) {
    highCount++;
    lowCount = 0;
  } else {
    lowCount++;
    highCount = 0;
  }

  if (highCount >= STABLE_COUNT && !phoneDetected) {
    phoneDetected = true;
    digitalWrite(LED_pin, HIGH);
    Serial.println("📱 PHONE DETECTED!");
  }

  if (lowCount >= STABLE_COUNT && phoneDetected) {
    phoneDetected = false;
    digitalWrite(LED_pin, LOW);
    Serial.println("✔ Area Clear (No phone)");
  }

  delay(50);
}
```

---

## 🧪 Testing Instructions

1. Upload the code to Arduino
2. Open **Serial Monitor** → set 9600 baud
3. Bring a phone near the sensor
4. Watch the sensor values spike
5. LED turns ON when detection is confirmed

---

## 📈 Sensitivity Adjustment

Change this value in the code:

```
const int DETECT_THRESHOLD = 1017;
```

Lower value → more sensitive
Higher value → less sensitive

---

## 📄 License

You are free to modify and use this project for personal and educational purposes.

---

## ✨ Author

**Elbek** — Cybersecurity & Arduino enthusiast.

If you need an advanced version with:

* LCD I2C display
* OLED screen
* Buzzer alarm
* Relay output
* Sensitivity calibration menu

Just tell me!
