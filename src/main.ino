#include <Arduino.h>
#include <L298N.h>

#define DEBUG false

// IR Sensor pins
const int L_IR = A3;  // left IR sensor pin
const int R_IR = A5;  // right IR sensor pin
const int M_IR = A4;  // mid IR sensor pin

// Buzzer pins
const int BUZER = 6;

// LED pins
const int R_LED = 11;  // red led pin
const int B_LED = 10;  // blue led pin
const int G_LED = 9;   // green led pin

// UV pins
const int ECHO = 12;
const int TRIG = 13;

// MOTOR DRIVE
const int EA = 5;
const int EB = 3;
const int IN1 = 8;
const int IN2 = 7;
const int IN3 = 4;
const int IN4 = 2;

L298N R_Motor(EA, IN1, IN2);
L298N L_Motor(EB, IN4, IN3);

const int MOTOR_SPEED = 50;

// UV pins related variables
long duration;
int distance;

int r_count = 0;
int b_count = 0;
int g_count = 0;

int box_count = 0;

enum LED {
    R,
    G,
    B,
    OFF
};

void set_led(LED l);
void set_led(LED l) {
    switch (l) {
        case R:
            digitalWrite(R_LED, LOW);
            digitalWrite(G_LED, HIGH);
            digitalWrite(B_LED, HIGH);
            break;
        case G:
            digitalWrite(R_LED, HIGH);
            digitalWrite(G_LED, LOW);
            digitalWrite(B_LED, HIGH);
            break;
        case B:
            digitalWrite(R_LED, HIGH);
            digitalWrite(G_LED, HIGH);
            digitalWrite(B_LED, LOW);
            break;
        case OFF:
            digitalWrite(R_LED, HIGH);
            digitalWrite(G_LED, HIGH);
            digitalWrite(B_LED, HIGH);
            break;
        default:
            break;
    }
}
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
void get_block() {
    if (distance <= 10) {  // for blue c
        set_led(B);
        Serial.println("blue");
        b_count += 1;
    } else if (distance <= 13) {  // for green b
        set_led(G);
        Serial.println("green");
        g_count += 1;
    } else if (distance <= 16) {  // for red a
        set_led(R);
        Serial.println("red");
        r_count += 1;
    } else {  // vacant
        set_led(OFF);
        analogWrite(BUZER, 0);
        delay(500);
        analogWrite(BUZER, 255);
    }
}

void move_bot() {
    int LeftVal = digitalRead(L_IR);
    int MidVal = digitalRead(M_IR);
    int RightVal = digitalRead(R_IR);

    Serial.print(LeftVal);
    Serial.print(MidVal);
    Serial.println(RightVal);

    Serial.print("Left val:");
    Serial.print(LeftVal ? "W" : "B");

    Serial.print(",Mid val:");
    Serial.print(MidVal ? "W" : "B");

    Serial.print(",Right val:");
    Serial.println(RightVal ? "W" : "B");

    if (LeftVal == 1 && MidVal == 0 && RightVal == 1) {
        bot_forward();
        Serial.println("forward");
    } else if (LeftVal == 0 && MidVal == 1 && RightVal == 0) {
        bot_forward();
        Serial.println("forward");
    } else if (LeftVal == 0 && MidVal == 0 && RightVal == 0) {
        bot_stop();
        Serial.println("stop");
    } else if (LeftVal == 1 && MidVal == 1 && RightVal == 1) {
        bot_stop();
        Serial.println("stop");
        get_distance();
        get_block();
    } else if (LeftVal == 0 && MidVal == 0 && RightVal == 1) {
        bot_right();
        L_Motor.stop();
        Serial.println("slight left");
    } else if (LeftVal == 1 && MidVal == 0 && RightVal == 0) {
        bot_left();
        R_Motor.stop();
        Serial.println("slight right");

    } else if (LeftVal == 0 && MidVal == 1 && RightVal == 1) {
        bot_right();
        Serial.println("left");
    } else if (LeftVal == 1 && MidVal == 1 && RightVal == 0) {
        bot_left();

        Serial.println("right");
    }
}

enum CZone {
    C1,
    C2,
    C3
};

enum Tables {
    T1,
    T2,
    T3,
    T4,
    T5,
    T6,
    T7,
    T8,
    T9
};

void setup() {
// Used to display information only in debug
#ifdef DEBUG
    Serial.begin(9600);
#endif
    // IR related   pinmodes
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

    digitalWrite(R_LED, HIGH);
    digitalWrite(G_LED, HIGH);
    digitalWrite(B_LED, HIGH);

    L_Motor.setSpeed(MOTOR_SPEED);
    R_Motor.setSpeed(MOTOR_SPEED);
}

void bot_forward() {
    L_Motor.forward();
    R_Motor.forward();
}
void bot_backward() {
    L_Motor.backward();
    R_Motor.backward();
}
void bot_stop() {
    L_Motor.stop();
    R_Motor.stop();
}
void bot_right() {
    L_Motor.forward();
    R_Motor.backward();
}
void bot_left() {
    L_Motor.backward();
    R_Motor.forward();
}
void loop() {
    delay(500);

    // Reset buzzer and led
    analogWrite(BUZER, 0);

    int LeftVal = digitalRead(L_IR);
    int MidVal = digitalRead(M_IR);
    int RightVal = digitalRead(R_IR);

    Serial.print(LeftVal);
    Serial.print(MidVal);
    Serial.println(RightVal);

    Serial.print("Left val:");
    Serial.print(LeftVal ? "W" : "B");

    Serial.print(",Mid val:");
    Serial.print(MidVal ? "W" : "B");

    Serial.print(",Right val:");
    Serial.println(RightVal ? "W" : "B");

    Serial.println();
    move_bot();
}
