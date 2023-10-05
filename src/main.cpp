#include <Arduino.h>
#include <Servo.h>

// Pinout
#define PIN_PWMA            9
#define PIN_AIN2            8
#define PIN_AIN1            7
#define PIN_STBY            6
#define PIN_BIN1            5
#define PIN_BIN2            4
#define PIN_PWMB            3
#define PIN_SERVO           16

// Movement parameters
#define STRAIGHT_SPEED      255
#define ROTATION_SPEED      200
#define TRIM_SPEED          0
#define SERVO_START         20
#define SERVO_FIRE          90

// Invert sense of motors
#define INVERT_MA           0
#define INVERT_MB           0


Servo servo;
char serial_input;

void setup() {
    pinMode(PIN_PWMA, OUTPUT);
    pinMode(PIN_AIN2, OUTPUT);
    pinMode(PIN_AIN1, OUTPUT);
    pinMode(PIN_STBY, OUTPUT);
    pinMode(PIN_BIN1, OUTPUT);
    pinMode(PIN_BIN2, OUTPUT);
    pinMode(PIN_PWMB, OUTPUT);

    Serial.begin(9600);
    Serial1.begin(9600);
    //servo.attach(PIN_SERVO);

    digitalWrite(PIN_STBY, HIGH);
    digitalWrite(PIN_AIN1, LOW);
    digitalWrite(PIN_AIN2, LOW);
    digitalWrite(PIN_BIN1, LOW);
    digitalWrite(PIN_BIN2, LOW);
    analogWrite(PIN_PWMA, 0);
    analogWrite(PIN_PWMB, 0);
    servo.write(SERVO_START);
}

void loop() {
    if(Serial1.available()){
        serial_input = Serial1.read();
        Serial.println(serial_input);
        switch (serial_input){
        case 'F':
            // Forward
            digitalWrite(PIN_AIN1, INVERT_MA!=HIGH);
            digitalWrite(PIN_AIN2, INVERT_MA!=LOW);
            digitalWrite(PIN_BIN1, INVERT_MB!=HIGH);
            digitalWrite(PIN_BIN2, INVERT_MB!=LOW);
            analogWrite(PIN_PWMA, STRAIGHT_SPEED+TRIM_SPEED);
            analogWrite(PIN_PWMB, STRAIGHT_SPEED-TRIM_SPEED);
            break;

        case 'B':
            // Backward
            digitalWrite(PIN_AIN1, INVERT_MA!=LOW);
            digitalWrite(PIN_AIN2, INVERT_MA!=HIGH);
            digitalWrite(PIN_BIN1, INVERT_MB!=LOW);
            digitalWrite(PIN_BIN2, INVERT_MB!=HIGH);
            analogWrite(PIN_PWMA, STRAIGHT_SPEED+TRIM_SPEED);
            analogWrite(PIN_PWMB, STRAIGHT_SPEED-TRIM_SPEED);
            break;

        case 'L':
            // Left
            digitalWrite(PIN_AIN1, INVERT_MA!=HIGH);
            digitalWrite(PIN_AIN2, INVERT_MA!=LOW);
            digitalWrite(PIN_BIN1, INVERT_MB!=LOW);
            digitalWrite(PIN_BIN2, INVERT_MB!=HIGH);
            analogWrite(PIN_PWMA, ROTATION_SPEED+TRIM_SPEED);
            analogWrite(PIN_PWMB, ROTATION_SPEED-TRIM_SPEED);
            break;

        case 'R':
            // Right
            digitalWrite(PIN_AIN1, INVERT_MA!=LOW);
            digitalWrite(PIN_AIN2, INVERT_MA!=HIGH);
            digitalWrite(PIN_BIN1, INVERT_MB!=HIGH);
            digitalWrite(PIN_BIN2, INVERT_MB!=LOW);
            analogWrite(PIN_PWMA, ROTATION_SPEED+TRIM_SPEED);
            analogWrite(PIN_PWMB, ROTATION_SPEED-TRIM_SPEED);
            break;

        case 'S':
            // Stop
            digitalWrite(PIN_AIN1, HIGH);
            digitalWrite(PIN_AIN2, HIGH);
            digitalWrite(PIN_BIN1, HIGH);
            digitalWrite(PIN_BIN2, HIGH);
            analogWrite(PIN_PWMA, ROTATION_SPEED+TRIM_SPEED);
            analogWrite(PIN_PWMB, ROTATION_SPEED-TRIM_SPEED);
            break;

        case '0':
            // Release
            digitalWrite(PIN_AIN1, LOW);
            digitalWrite(PIN_AIN2, LOW);
            digitalWrite(PIN_BIN1, LOW);
            digitalWrite(PIN_BIN2, LOW);
            analogWrite(PIN_PWMA, 0);
            analogWrite(PIN_PWMB, 0);
            break;

        case 'X':
            // Fire
            servo.write(SERVO_FIRE);
            break;

        default:
            break;
        }
    }
    else{
        delay(1);
    }
}
