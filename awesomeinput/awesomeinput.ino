#include <Servo.h>

Servo myservo;  // create servo object to control a servo
int sensorPin = A0;   // select the input pin for the potentiometer
int sensorPin2 = A1;   // select the input pin for the potentiometer
int ledPin = 13;      // select the pin for the LED
int sensorValue = 0;  // variable to store the value coming from the sensor
const float slope = (0.00571429);
const float yIntercept = 3.1429;
float convertedReading;

const float top = 80; // * 1000s
const float bottom = 13; // * 1000s


void setup() {
  Serial.begin(115200); //number of bits per second
  myservo.attach(A4);  // attaches the servo on pin 9 to the servo object
}

void loop() {

  float reading = analogRead(sensorPin);
  reading = reading*slope-yIntercept;
  reading = constrain(reading, -1, 1);
  float servoReading1 = convertToServo(reading);

  float reading2 = analogRead(sensorPin2);
  reading2 = reading2*slope-yIntercept;
  reading2 = constrain(reading2,-1, 1);


  Serial.print(convertResistance(0));
  Serial.print(",");
  Serial.println(convertResistance(1));

  Serial.println(convertedReading);

  myservo.write(servoReading1); // sets the servo position according to the scaled value

  delay(15);                // waits for the servo to get there
}

float convertToServo(float reading) {
  return ( reading* 90  + 90);
}

float convertResistance(int port) {
  float slope = 0;
  float resistorValue = getResistance(port);
  slope = (2 / (top - bottom)) ;
  return slope * (resistorValue / 1000) + 1 - (slope * top);
}

float getResistance(int port) {

  float resistance = 0;
  // Constants trelated to the circuit, set resistor and analog read pin
  const float setResistor[] = {47001.0, 46750.0};
  const int portPin[] = {A0, A1};
  // Start collecting   
  float reading = analogRead(portPin[port]);
  resistance = (1024.0/reading) - 1.0; // Find the relative value of the potentiometer
  resistance = resistance * setResistor[port]; // Find the actual value
  // (Convert resistance to a value between -1 and +1)
  return resistance;
}
