/*
  Analog Input

  Demonstrates analog input by reading an analog sensor on analog pin 0 and
  turning on and off a light emitting diode(LED) connected to digital pin 13.
  The amount of time the LED will be on and off depends on the value obtained
  by analogRead().

  The circuit:
  - potentiometer
    center pin of the potentiometer to the analog input 0
    one side pin (either one) to ground
    the other side pin to +5V
  - LED
    anode (long leg) attached to digital output 13 through 220 ohm resistor
    cathode (short leg) attached to ground

  - Note: because most Arduinos have a built-in LED attached to pin 13 on the
    board, the LED is optional.

  created by David Cuartielles
  modified 30 Aug 2011
  By Tom Igoe

  This example code is in the public domain.

  https://www.arduino.cc/en/Tutorial/BuiltInExamples/AnalogInput
*/

int sensorPin = A0;   // select the input pin for the potentiometer
int sensorPin2 = A1;   // select the input pin for the potentiometer
int ledPin = 13;      // select the pin for the LED
int sensorValue = 0;  // variable to store the value coming from the sensor

const float top = 80; // * 1000s
const float bottom = 13; // * 1000s



void setup() {
  Serial.begin(115200); //number of bits per second 
}

void loop() {

  float reading = analogRead(sensorPin);
  reading = reading*slope-yIntercept;
  float reading2 = analogRead(sensorPin2);
  reading2 = reading2*slope-yIntercept;

  reading = constrain(reading, -1, 1);
  reading2 = constrain(reading2,-1, 1);

  Serial.print(convertResistance(0));
  Serial.print(",");
  Serial.println(convertResistance(1));
  delay(100);
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

  // Consider adding code to normalize each port here
  // (Convert resistance to a value between -1 and +1)
  
  return resistance;
}
