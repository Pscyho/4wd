const int in1 = 4;
const int in2 = 6;

const int in3 = 5;
const int in4 = 7;
const int enA = 10;
const int enB = 11;

const int L_S = 13;
const int R_S = 12;
int M1_Speed = 70;             // speed of motor 1
int M2_Speed = 70;             // speed of motor 2
int LeftRotationSpeed = 100;   // Left Rotation Speed
int RightRotationSpeed = 100;  // Right Rotation Speed

#include <Arduino.h>
void setup() {
    Serial.begin(9600);
    pinMode(in1, OUTPUT);
    pinMode(in2, OUTPUT);
    pinMode(in3, OUTPUT);
    pinMode(in4, OUTPUT);

    pinMode(enA, OUTPUT);
    pinMode(enB, OUTPUT);

    analogWrite(enA, M1_Speed);
    analogWrite(enB, M2_Speed);
}

void loop() {
    int LEFT_SENSOR = digitalRead(L_S);
    int RIGHT_SENSOR = digitalRead(R_S);

    if (RIGHT_SENSOR == 0 && LEFT_SENSOR == 0) {
        Serial.println("forward");
        forward();  // FORWARD
    }

    else if (RIGHT_SENSOR == 0 && LEFT_SENSOR == 1) {
        Serial.println("right");
        right();  // Move Right
    }

    else if (RIGHT_SENSOR == 1 && LEFT_SENSOR == 0) {
        Serial.println("left");
        left();  // Move Left
    }

    else if (RIGHT_SENSOR == 1 && LEFT_SENSOR == 1) {
        Serial.println("Stop");
        Stop();  // STOP
    }
}

void forward() {
    digitalWrite(in1, HIGH);
    digitalWrite(in2, LOW);
    digitalWrite(in3, HIGH);
    digitalWrite(in4, LOW);

    analogWrite(enA, M1_Speed);
    analogWrite(enB, M2_Speed);
}
void backward() {
    digitalWrite(in1, LOW);
    digitalWrite(in2, HIGH);
    digitalWrite(in3, LOW);
    digitalWrite(in4, HIGH);

    analogWrite(enA, M1_Speed);
    analogWrite(enB, M2_Speed);
}

void right() {
    digitalWrite(in1, LOW);
    digitalWrite(in2, HIGH);
    digitalWrite(in3, HIGH);
    digitalWrite(in4, LOW);

    analogWrite(enA, LeftRotationSpeed);
    analogWrite(enB, RightRotationSpeed);
}

void left() {
    digitalWrite(in1, HIGH);
    digitalWrite(in2, LOW);
    digitalWrite(in3, LOW);
    digitalWrite(in4, HIGH);

    analogWrite(enA, LeftRotationSpeed);
    analogWrite(enB, RightRotationSpeed);
}

void Stop() {
    digitalWrite(in1, LOW);
    digitalWrite(in2, LOW);
    digitalWrite(in3, LOW);
    digitalWrite(in4, LOW);
}
