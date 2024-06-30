const int in1 = 4;
const int in2 = 6;
const int in3 = 5;
const int in4 = 7;
const int enA = 10;
const int enB = 11;
const int L_S = 13;
const int R_S = 12;
int M1_Speed = 110;           // speed of motor 1
int M2_Speed = 110;           // speed of motor 2
int Lspeed = 100;
int Rspeed = 100;
float kLeft = 0.1;
float kRight = 0.1;
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
    analogWrite(enB, M2_Speed);}
void loop() {
    int LEFT_SENSOR = digitalRead(L_S);
    int RIGHT_SENSOR = digitalRead(R_S);
    int state;

    if (LEFT_SENSOR && RIGHT_SENSOR) {
        state = 0;  // stop state
        Stop();
    } else if (LEFT_SENSOR && !RIGHT_SENSOR) {
        state = 1;  // turn left state
        right();
    } else if (!LEFT_SENSOR && RIGHT_SENSOR) {
        state = 2;  // turn right state
        left();
    } else if (!LEFT_SENSOR && !RIGHT_SENSOR) {
        state = 3;  // go state
        forward();  }
    int startTime = millis();
    switch (state) {
        case 0:
            analogWrite(enA, 0);
            analogWrite(enB, 0);
            break;
        case 1:
            while (digitalRead(L_S)) {
                int RnewSpeed = Rspeed + kRight * (millis() - startTime);
                analogWrite(enA, RnewSpeed);
                int LnewSpeed = Lspeed - kLeft * (millis() - startTime);
                analogWrite(enB, LnewSpeed);}
            break;
        case 2:
            while (digitalRead(R_S)) {
                int RnewSpeed = Rspeed + kRight * (millis() - startTime);
                analogWrite(enA, RnewSpeed);
                int LnewSpeed = Lspeed - kLeft * (millis() - startTime);
                analogWrite(enB, LnewSpeed);}
            break;
        case 3:  // go
            analogWrite(enA, Rspeed);
            analogWrite(enB, Lspeed);
            break;
        default: 
            break;}}
void forward() {
    digitalWrite(in1, HIGH);
    digitalWrite(in2, LOW);
    digitalWrite(in3, HIGH);
    digitalWrite(in4, LOW);}
void backward() {
    digitalWrite(in1, LOW);
    digitalWrite(in2, HIGH);
    digitalWrite(in3, LOW);
    digitalWrite(in4, HIGH);}
void right() {
    digitalWrite(in1, LOW);
    digitalWrite(in2, HIGH);
    digitalWrite(in3, HIGH);
    digitalWrite(in4, LOW);}
void left() {
    digitalWrite(in1, HIGH);
    digitalWrite(in2, LOW);
    digitalWrite(in3, LOW);
    digitalWrite(in4, HIGH);}
void Stop() {
    digitalWrite(in1, LOW);
    digitalWrite(in2, LOW);
    digitalWrite(in3, LOW);
    digitalWrite(in4, LOW);}
