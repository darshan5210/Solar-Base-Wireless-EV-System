/ Constants
const int analogPin = A0; // Pin for battery voltage
const int chargePin = 2; // Pin connected to CHG pin of TP4056
const int irSensorPin = 3; // Pin connected to IR sensor OUT
const int relayPin = 4; // Pin connected to relay
const float maxBatteryVoltage = 4.2; // Fully charged battery voltage
const float minBatteryVoltage = 3.0; // Fully discharged battery voltage
const float lowBatteryThreshold = 3.3; // Voltage threshold to stop relay
void setup() {
pinMode(chargePin, INPUT_PULLUP); // Use internal pull-up resistor for CHG
pin
pinMode(irSensorPin, INPUT); // IR sensor input
pinMode(relayPin, OUTPUT); // Relay control pin
digitalWrite(relayPin, LOW); // Initially, turn off the relay
Serial.begin(9600);
}
void loop() {
// Read battery voltage
int analogValue = analogRead(analogPin);
float batteryVoltage = (analogValue / 1023.0) * 5.0;
// Calculate battery percentage
float batteryPercentage = ((batteryVoltage - minBatteryVoltage) /
(maxBatteryVoltage - minBatteryVoltage)) * 100.0;
batteryPercentage = constrain(batteryPercentage, 0, 100);
// Read charging status
int chargingStatus = digitalRead(chargePin);
// Read IR sensor status
int irStatus = digitalRead(irSensorPin);
// Display battery and charging information
Serial.print("Battery Voltage: ");
Serial.print(batteryVoltage);
Serial.print(" V, Battery Percentage: ");
Serial.print(batteryPercentage);
Serial.print(" %, Charging Status: ");
Serial.println(chargingStatus == LOW ? "Charging" : "Not Charging");
// Control relay based on IR sensor and battery voltage
if (batteryVoltage < lowBatteryThreshold) {
Serial.println("Low battery! Relay OFF to protect battery.");
digitalWrite(relayPin, LOW); // Turn off relay
} else if (irStatus == HIGH) { // IR sensor detects object
Serial.println("NO Object detected! Relay OFF.");
digitalWrite(relayPin, HIGH); // Turn off relay
}
else
{
Serial.println("Relay ON. Wireless transmitter active.");
digitalWrite(relayPin, LOW); // Turn on relay
}
delay(1000); // Wait for 1 second before the next reading
}
