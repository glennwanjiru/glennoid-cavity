#include <Arduino.h>
#include <Servo.h>

Servo myServo;
int trigPin = 10;   // Trig pin for ultrasonic sensor
int echoPin = 11;   // Echo pin for ultrasonic sensor
int servoPin = 9;   // PWM pin for servo motor
int obstacleDistance = 20;  // Distance in centimeters to consider as an obstacle
int servoPosition = 0;  // Initial position of the servo
boolean obstacleDetected = false;  // Flag to track if an obstacle is detected
int servoSpeed = 5;  // Speed of the servo motor movement (adjust as needed)

void setup() {
  myServo.attach(servoPin);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  Serial.begin(9600);  // Initialize Serial for debugging
}

void loop() {
  long duration, distance;
  
  // Move the servo back and forth only if no obstacle is detected
  if (!obstacleDetected) {
    for (servoPosition = 0; servoPosition <= 180; servoPosition += servoSpeed) {
      myServo.write(servoPosition);
      delay(15);  // Adjust the delay for smoother movement
    }

    for (servoPosition = 180; servoPosition >= 0; servoPosition -= servoSpeed) {
      myServo.write(servoPosition);
      delay(15);  // Adjust the delay for smoother movement
    }
  }

  // Measure distance using the ultrasonic sensor
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance = (duration / 2) * 0.0343;

  // Check for obstacle
  if (distance <= obstacleDistance) {
    if (!obstacleDetected) {
      myServo.write(90);  // Stop the servo motor only once when obstacle detected
      Serial.println("Obstacle detected!");
    }
    obstacleDetected = true;  // Set obstacle detected flag
  } else {
    obstacleDetected = false;  // Reset obstacle detected flag
  }

  delay(200);  // Adjust the delay as needed
}
