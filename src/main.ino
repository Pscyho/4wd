#include <Arduino.h>
#include <L298N.h>

// IR Sensor pins
const int L_IR = 0;  // left IR sensor pin
const int R_IR = 0;  // right IR sensor pin
const int M_IR = 0;  // mid IR sensor pin

// Buzzer pins
const int BUZER = 0;

// LED pins
const int R_LED = 0;  // red led pin
const int B_LED = 0;  // blue led pin
const int G_LED = 0;  // green led pin

// UV pins
const int ECHO = 0;
const int TRIG = 0;

// MOTOR DRIVE
const int EA = 0;
const int EB = 0;
const int IN1 = 0;
const int IN2 = 0;
const int IN3 = 0;
const int IN4 = 0;

L298N L_Motor(EA, IN1, IN2);
L298N R_Motor(EB, IN3, IN4);

const int MOTOR_SPEED = 50;

// UV pins related variables
long duration;
int distance;

void get_distance() {
    digitalWrite(TRIG, LOW);
    delayMicroseconds(2);
    digitalWrite(TRIG, HIGH);
    delayMicroseconds(10);
    digitalWrite(TRIG, LOW);
    duration = pulseIn(ECHO, HIGH);

    distance = (duration / 2) / 29.1;
    // distance= duration * 0.0344 / 2;
    Serial.print("Distance: ");
    Serial.print(distance);
    Serial.println(" cm");
}

void setup() {
    // Used to display information
    Serial.begin(9600);

    // IR related pinmodes
    pinMode(L_IR, INPUT);
    pinMode(R_IR, INPUT);
    pinMode(M_IR, INPUT);

    // buzzer pin modes
    pinMode(BUZER, OUTPUT);

    // uv pin modes
    pinMode(TRIG, OUTPUT);
    pinMode(ECHO, INPUT);

    // LED pin modes
    pinMode(R_LED, OUTPUT);
    pinMode(B_LED, OUTPUT);
    pinMode(G_LED, OUTPUT);

    L_Motor.setSpeed(MOTOR_SPEED);
    R_Motor.setSpeed(MOTOR_SPEED);
}
void loop() {
}