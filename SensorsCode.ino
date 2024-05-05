#include <Arduino.h>
#include <stdio.h>
#include <dht.h>
#define DHT22_PIN 6
#define WATER_POWER_PIN  7
#define WATER_SIGNAL_PIN A5
#define RAIN_sensorPower 9
#define RAIN_sensorPin 8


dht DHT;
int water_value = 0; // variable to store the water sensor value
int vibration_Sensor = A2; // analog pin for vibration sensor
int tiltsensor = 12; // tilt sensor digital pin

const int hygrometer = A0;	//Hygrometer sensor analog pin output at pin A0 of Arduino
int value;

int present_condition = 0;
int previous_condition = 0;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(WATER_POWER_PIN, OUTPUT);   // configure D7 pin as an OUTPUT
  digitalWrite(WATER_POWER_PIN, LOW); // turn the sensor OFF
  pinMode(vibration_Sensor, INPUT);
  pinMode(tiltsensor, INPUT);
	pinMode(RAIN_sensorPower, OUTPUT);
	digitalWrite(RAIN_sensorPower, LOW);


}

void WaterSensorLoop() {
  digitalWrite(WATER_POWER_PIN, HIGH);  // turn the sensor ON
  delay(10);                      // wait 10 milliseconds
  water_value = analogRead(WATER_SIGNAL_PIN); // read the analog value from sensor
  digitalWrite(WATER_POWER_PIN, LOW);   // turn the sensor OFF
  Serial.print("Water Sensor value: ");
  Serial.println(water_value);
  delay(1000);
}

void VibrationSensorLoop(){
  previous_condition = present_condition;
  present_condition = digitalRead(A2);
  if (previous_condition != present_condition) {
    Serial.print("Vibration Detected");
  } else {
    Serial.print("No Vibration")
  }
}

void TiltSensorLoop(){
  Serial.println(digitalRead(tiltsensor));
  delay(100);
}

void SoilMoistureSensorLoop(){
  value = analogRead(hygrometer);		//Read analog value 
	value = constrain(value,400,1023);	//Keep the ranges!
	value = map(value,400,1023,100,0);	//Map value : 400 will be 100 and 1023 will be 0
	Serial.print("Soil humidity: ");
	Serial.print(value);
	Serial.println("%");
	delay(1000); //Read every 1 sec.
}

int readWaterSensor() {
	digitalWrite(sensorPower, HIGH);	// Turn the sensor ON
	delay(10);							// Allow power to settle
	int val = digitalRead(sensorPin);	// Read the sensor output
	digitalWrite(sensorPower, LOW);		// Turn the sensor OFF
	return val;							// Return the value
}

void RainSensorLoop(){
  int val = readWaterSensor();
	Serial.print("Digital Output: ");
	Serial.println(val);
	// Determine status of rain
	if (val) {
		Serial.println("Status: Clear");
	} else {
		Serial.println("Status: It's raining");
	}

	delay(1000);	// Take a reading every second
	Serial.println();
}

void DHTSensorLoop(){
  int chk = DHT.read22(DHT22_PIN);
  //Read data and store it to variables hum and temp
  hum = DHT.humidity;
  temp= DHT.temperature;
  //Print temp and humidity values to serial monitor
  Serial.print("Humidity: ");
  Serial.print(hum);
  Serial.print(" %, Temp: ");
  Serial.print(temp);
  Serial.println(" Celsius");
  delay(1000); //Delay 1 sec.
}

void loop() {
  // put your main code here, to run repeatedly:
  WaterSensorLoop();
  VibrationSensorLoop();
  TiltSensorLoop();
  SoilMoistureSensorLoop();
  RainSensorLoop();
  DHTSensorLoop();
}

