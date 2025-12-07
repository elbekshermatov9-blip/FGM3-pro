// -------------------------------
// FGM-3 PRO Mobile Phone Detector
// Arduino Mega 2560
// Elbek Project – Final Version
// -------------------------------

#define FMG_3_PRO A1     // Sensor analog pin
#define LED_pin 3        // LED indicator

int prevValue = 0;       
bool phoneDetected = false;

const int DETECT_THRESHOLD = 1017;  // Signal threshold
const int STABLE_COUNT = 5;         // How many samples to confirm detection

int highCount = 0;
int lowCount = 0;

void setup() {
  Serial.begin(9600);
  pinMode(LED_pin, OUTPUT);
  pinMode(FMG_3_PRO, INPUT);

  Serial.println("FGM-3 PRO Phone Detector Started...");
  Serial.println("Monitoring electromagnetic activity...");
}

void loop() {
  int value = analogRead(FMG_3_PRO);

  // Show raw sensor value
  Serial.print("Sensor: ");
  Serial.println(value);

  // --- Detection Logic ---
  
  if (value >= DETECT_THRESHOLD) {
    highCount++;
    lowCount = 0;
  } else {
    lowCount++;
    highCount = 0;
  }

  // If sensor is HIGH for several cycles → phone detected
  if (highCount >= STABLE_COUNT && !phoneDetected) {
    phoneDetected = true;
    digitalWrite(LED_pin, HIGH);
    Serial.println("📱 PHONE DETECTED!");
  }

  // If sensor is LOW for several cycles → phone left
  if (lowCount >= STABLE_COUNT && phoneDetected) {
    phoneDetected = false;
    digitalWrite(LED_pin, LOW);
    Serial.println("✔ Area Clear (No phone)");
  }

  delay(50);  // Stabilization delay
}
