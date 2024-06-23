const int Ln1= 8;   // Right Motor MA1
const int Ln2= 7;   // Right Motor MA2
const int Ln3= 6;   // Left Motor MB1
const int Ln4= 11;  // Left Motor MB2
const int EA= 10;  // Right Motor Enable Pin EA
const int EB= 9;   // Left Motor Enable Pin EB

//**********5 Channel IR Sensor Connection**********//
const int S1= 2;
const int S2= 3;
const int S3= 4;
const int S4= 5;
const int S5= 12;
//*************************************************//
const int MSpeed=120;

#include <Arduino.h>
void setup() {
    Serial.begin(9600);
    pinMode(Ln1, OUTPUT);
    pinMode(Ln2, OUTPUT);
    pinMode(Ln3, OUTPUT);
    pinMode(Ln4, OUTPUT);
    pinMode(EA, OUTPUT);
    pinMode(EB, OUTPUT);
    pinMode(S1, INPUT);
    pinMode(S2, INPUT);
    pinMode(S3, INPUT);
    pinMode(S4, INPUT);
    pinMode(S5, INPUT);
}

void loop() {
    // Reading Sensor Values
    int s1 = digitalRead(S1);  // Left Most Sensor
    int s2 = digitalRead(S2);  // Left Sensor
    int s3 = digitalRead(S3);  // Middle Sensor
    int s4 = digitalRead(S4);  // Right Sensor
    int s5 = digitalRead(S5);  // Right Most Sensor
    Serial.print(s1);
    Serial.print(" ");
    Serial.print(s2);
    Serial.print(" ");
    Serial.print(s3);
    Serial.print(" ");
    Serial.print(s4);
    Serial.print(" ");
    Serial.print(s5);
    Serial.println(" ");
    // if only middle sensor detects black line
    if ((s1 == 1) && (s2 == 1) && (s3 == 0) && (s4 == 1) && (s5 == 1)) {
        // going forward with full speed
        analogWrite(EA, MSpeed);  // you can adjust the speed of the motors from 0-100
        analogWrite(EB, MSpeed);  // you can adjust the speed of the motors from 0-100
        digitalWrite(Ln1, HIGH);
        digitalWrite(Ln2, LOW);
        digitalWrite(Ln3, HIGH);
        digitalWrite(Ln4, LOW);
    }

    // if only left sensor detects black line
    if ((s1 == 1) && (s2 == 0) && (s3 == 1) && (s4 == 1) && (s5 == 1)) {
        // going right with full speed
        analogWrite(EA, MSpeed);  // you can adjust the speed of the motors from 0-100
        analogWrite(EB, MSpeed);  // you can adjust the speed of the motors from 0-100
        digitalWrite(Ln1, HIGH);
        digitalWrite(Ln2, LOW);
        digitalWrite(Ln3, LOW);
        digitalWrite(Ln4, LOW);
    }

    // if only left most sensor detects black line
    if ((s1 == 0) && (s2 == 1) && (s3 == 1) && (s4 == 1) && (s5 == 1)) {
        // going right with full speed
        analogWrite(EA, MSpeed);  // you can adjust the speed of the motors from 0-100
        analogWrite(EB, MSpeed);  // you can adjust the speed of the motors from 0-100
        digitalWrite(Ln1, HIGH);
        digitalWrite(Ln2, LOW);
        digitalWrite(Ln3, LOW);
        digitalWrite(Ln4, HIGH);
    }

    // if only right sensor detects black line
    if ((s1 == 1) && (s2 == 1) && (s3 == 1) && (s4 == 0) && (s5 == 1)) {
        // going left with full speed
        analogWrite(EA, MSpeed);  // you can adjust the speed of the motors from 0-100
        analogWrite(EB, MSpeed);  // you can adjust the speed of the motors from 0-100
        digitalWrite(Ln1, LOW);
        digitalWrite(Ln2, LOW);
        digitalWrite(Ln3, HIGH);
        digitalWrite(Ln4, LOW);
    }

    // if only right most sensor detects black line
    if ((s1 == 1) && (s2 == 1) && (s3 == 1) && (s4 == 1) && (s5 == 0)) {
        // going left with full speed
        analogWrite(EA, MSpeed);  // you can adjust the speed of the motors from 0-100
        analogWrite(EB, MSpeed);  // you can adjust the speed of the motors from 0-100
        digitalWrite(Ln1, LOW);
        digitalWrite(Ln2, HIGH);
        digitalWrite(Ln3, HIGH);
        digitalWrite(Ln4, LOW);
    }

    // if middle and right sensor detects black line
    if ((s1 == 1) && (s2 == 1) && (s3 == 0) && (s4 == 0) && (s5 == 1)) {
        // going left with full speed
        analogWrite(EA, MSpeed);  // you can adjust the speed of the motors from 0-100
        analogWrite(EB, MSpeed);  // you can adjust the speed of the motors from 0-100
        digitalWrite(Ln1, LOW);
        digitalWrite(Ln2, LOW);
        digitalWrite(Ln3, HIGH);
        digitalWrite(Ln4, LOW);
    }

    // if middle and left sensor detects black line
    if ((s1 == 1) && (s2 == 0) && (s3 == 0) && (s4 == 1) && (s5 == 1)) {
        // going right with full speed
        analogWrite(EA, MSpeed);  // you can adjust the speed of the motors from 0-100
        analogWrite(EB, MSpeed);  // you can adjust the speed of the motors from 0-100
        digitalWrite(Ln1, HIGH);
        digitalWrite(Ln2, LOW);
        digitalWrite(Ln3, LOW);
        digitalWrite(Ln4, LOW);
    }

    // if middle, left and left most sensor detects black line
    if ((s1 == 0) && (s2 == 0) && (s3 == 0) && (s4 == 1) && (s5 == 1)) {
        // going right with full speed
        analogWrite(EA, MSpeed);  // you can adjust the speed of the motors from 0-100
        analogWrite(EB, MSpeed);  // you can adjust the speed of the motors from 0-100
        digitalWrite(Ln1, HIGH);
        digitalWrite(Ln2, LOW);
        digitalWrite(Ln3, LOW);
        digitalWrite(Ln4, LOW);
    }

    // if middle, right and right most sensor detects black line
    if ((s1 == 1) && (s2 == 1) && (s3 == 0) && (s4 == 0) && (s5 == 0)) {
        // going left with full speed
        analogWrite(EA, MSpeed);  // you can adjust the speed of the motors from 0-100
        analogWrite(EB, MSpeed);  // you can adjust the speed of the motors from 0-100
        digitalWrite(Ln1, LOW);
        digitalWrite(Ln2, LOW);
        digitalWrite(Ln3, HIGH);
        digitalWrite(Ln4, LOW);
    }

    // if all sensors are on a black line
    if ((s1 == 0) && (s2 == 0) && (s3 == 0) && (s4 == 0) && (s5 == 0)) {
        // stop
        digitalWrite(Ln1, LOW);
        digitalWrite(Ln2, LOW);
        digitalWrite(Ln3, LOW);
        digitalWrite(Ln4, LOW);
    }
}
