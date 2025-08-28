/ Constants for pin configuration
const int chargingPin = 8; // Pin connected to charging indicator (LED/Relay)
const int batteryPin = A0; // Pin for reading battery voltage
const int detectPin = 7; // Pin for charging status detection
float batteryVoltage = 0; // Battery voltage
int chargingStatus = 0; // Charging status (0 = Not charging, 1 = Charging)
// Battery voltage range for a 3.7V Li-ion battery
const float batteryMinVoltage = 3.0; // Minimum battery voltage (fully
discharged)
const float batteryMaxVoltage = 4.2; // Maximum battery voltage (fully charged)
void setup() {
Serial.begin(9600); // Start Serial Monitor
// Pin configurations
pinMode(chargingPin, OUTPUT); // Set chargingPin to output
pinMode(detectPin, INPUT_PULLUP); // Use internal pull-up to stabilize the
input signal
digitalWrite(chargingPin, LOW); // Initially, no charging
}
void loop() {
// Read battery voltage
batteryVoltage = analogRead(batteryPin) * (5.0 / 1023.0); // 5V reference, 10-bit
ADC
// Map battery voltage to percentage (0 to 100%)
int batteryPercentage = map(batteryVoltage * 1000, batteryMinVoltage * 1000,
batteryMaxVoltage * 1000, 0, 100);

// Ensure battery percentage is within 0 to 100%
batteryPercentage = constrain(batteryPercentage, 0, 100);
// Print battery percentage
Serial.print("Battery Percentage: ");
Serial.print(batteryPercentage);
Serial.println("%");
// Detect charging status and update
detectChargingStatus();
if (chargingStatus == 1) {
Serial.println("Charging...");
digitalWrite(chargingPin, HIGH); // Enable charging indicator (e.g., relay or
LED)
} else {
Serial.println("Not Charging");
digitalWrite(chargingPin, LOW); // Disable charging indicator
}
delay(1000); // Delay before repeating
}
// Function to detect the charging status
void detectChargingStatus() {
int sensorValue = digitalRead(detectPin); // Read the sensor value from detectPin
// Debugging: Print raw sensor value
Serial.print("CHRG Pin State: ");
Serial.println(sensorValue);
// Update chargingStatus based on the sensor state
if (sensorValue == HIGH) { // LOW indicates the receiver is in contact with the
transmitter
chargingStatus = 1; // Charging is active
} else {
chargingStatus = 0; // Not charging
}
}
