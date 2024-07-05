#include <Arduino.h>
#include <L298N.h>

// IR Sensor pins
const int L_IR = 11;  // left IR sensor pin
const int R_IR = 9;   // right IR sensor pin
const int M_IR = 10;  // mid IR sensor pin

// Buzzer pins
const int BUZER = 0;

// LED pins
const int R_LED = 0;  // red led pin
const int B_LED = 0;  // blue led pin
const int G_LED = 0;  // green led pin

// UV pins
const int ECHO = 12;
const int TRIG = 13;

// MOTOR DRIVE
const int EA = 3;
const int EB = 5;
const int IN1 = 8;
const int IN2 = 7;
const int IN3 = 4;
const int IN4 = 2;

L298N L_Motor(EA, IN1, IN2);
L298N R_Motor(EB, IN4, IN3);

const int MOTOR_SPEED = 70;

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
void get_block() {
}

void move_bot() {
    int LeftSensor = digitalRead(L_IR);
    int MidVal = digitalRead(M_IR);
    int RightVal = digitalRead(R_IR);

    Serial.print("Left val:");
    Serial.print(LeftSensor?"W":"B");

    Serial.print(",Mid val:");
    Serial.print(MidVal?"W":"B");

    Serial.print(",Right val:");
    Serial.println(RightVal?"W":"B");

    //  if (LeftSensor == 0 && MidVal == 1 && RightVal == 0) {
    //     L_Motor.forward();
    //     R_Motor.forward();
    //     Serial.println("forward");
    // }
    // else if (LeftSensor == 0 && MidVal == 1 && RightVal == 1) {
    //     L_Motor.backward();
    //     R_Motor.forward();
    //     Serial.println("left");
    // }
    //     else if (LeftSensor == 0 && MidVal == 0 && RightVal == 1) {
    //     L_Motor.backward();
    //     R_Motor.forward();
    //     Serial.println("left");
    // }else if (LeftSensor == 1 && MidVal == 1 && RightVal == 0) {
    //     R_Motor.backward();
    //     L_Motor.forward();
    //     Serial.println("right");
    // }else if (LeftSensor == 0 && MidVal == 0 && RightVal == 0) {
    //     L_Motor.stop();
    //     R_Motor.stop();
    //     Serial.println("stop");
    // }else if (LeftSensor == 1 && MidVal == 1 && RightVal == 1) {
    //     L_Motor.stop();
    //     R_Motor.stop();
    //     Serial.println("stop");
    // }

    if (LeftSensor == 1 && MidVal == 0 && RightVal == 1) {
        L_Motor.forward();
        R_Motor.forward();
        Serial.println("forward");
    } else if (LeftSensor == 0 && MidVal == 1 && RightVal == 0) {
        L_Motor.forward();
        R_Motor.forward();
        Serial.println("forward");
    }
    
    else if (LeftSensor == 0 && MidVal == 0 && RightVal == 0) {
        L_Motor.stop();
        R_Motor.stop();
        Serial.println("stop");
    } else if (LeftSensor == 1 && MidVal == 1 && RightVal == 1) {
        L_Motor.stop();
        R_Motor.stop();
        Serial.println("stop");
    } else if (LeftSensor == 0 && MidVal == 0 && RightVal == 1) {
        L_Motor.backward();
        R_Motor.forward();
        //todo speed
        Serial.println("slight left");
    } else if (LeftSensor == 1 && MidVal == 0 && RightVal == 0) {
        R_Motor.backward();
        L_Motor.forward();
                // todo speed
        Serial.println("slight right");
    } else if (LeftSensor == 0 && MidVal == 1 && RightVal == 1) {
        L_Motor.backward();
        R_Motor.forward();
        Serial.println("left");
    } else if (LeftSensor == 1 && MidVal == 1 && RightVal == 0) {
        R_Motor.backward();
        L_Motor.forward();

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

enum LED {
    R,
    G,
    B,
};

// void set_led(bool val,LED l) {}
//     switch (l) {
//         case R:
//             digitalWrite(R_LED, val);
//             break;
//         case B:
//             digitalWrite(B_LED, val);
//             break;
//         case G:
//             digitalWrite(G_LED, val);
//             break;
//         default:
//             break;
//     }
// }
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
    delay(1000);
    move_bot();
    // get_distance();
    // if (distance>20){

    // }
}