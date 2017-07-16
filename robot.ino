#include "libs/RobotMovementController.h"
#include "libs/NewPing.h"
#include "libs/constants.h"
//#include "libs/auxiliaries.h"
#include <Servo.h>

// Seting pin
int pin_right_engine_2 = 6; // ROJO
int pin_right_engine_1 = 5; // AMRILLO
int pin_servo = 8; // Amarillo
int pin_left_engine_1 = 9; // NARJANA 
int pin_left_engine_2 = 10; // MARRON
int pin_sensor_echo = 11; // Violeta
int pin_sensor_trigger = 12; // Gris
int pin_buzzer = 13; 
int amount_of_measures;
int distance;
int next_distance_read_delay; 


// Instances of components
RobotMovementController rmv_controller = RobotMovementController(pin_left_engine_1, pin_left_engine_2, pin_right_engine_1, pin_right_engine_2);
Servo servo;
NewPing sensor = NewPing(pin_sensor_trigger, pin_sensor_echo, MAX_DISTANCE);

void starting_delay(){
    delay(10000);
}


void move_servo_to_right(Servo servo){
    int current_pos  = servo.read();
    if (current_pos >= SERVO_RIGHT_ANGLE){
        for (;current_pos > SERVO_RIGHT_ANGLE; current_pos--){
            servo.write(current_pos);
            delay(20);
        }
    } 
    else{
        // Not possible but just to be sure
        for (;current_pos < SERVO_RIGHT_ANGLE; current_pos++){
            servo.write(current_pos);
            delay(20);
        }
    }
    delay(50);
}

void move_servo_to_center(Servo servo){
    int current_pos = servo.read();
    if (current_pos <= SERVO_CENTER_ANGLE){
        for (;current_pos < SERVO_CENTER_ANGLE; current_pos++){
            servo.write(current_pos);
            delay(20);
        }
    }
    else{
        for (;current_pos > SERVO_CENTER_ANGLE; current_pos--){
            servo.write(current_pos);
            delay(20);
        }
    }
    delay(50);
}

void move_servo_to_left(Servo servo){
    int current_pos  = servo.read();
    if (current_pos <= SERVO_LEFT_ANGLE){
        for (;current_pos < SERVO_LEFT_ANGLE; current_pos++){
            servo.write(current_pos);
            delay(20);
        }
    } 
    else{
        // Not possible but just to be sure
        for (;current_pos > SERVO_LEFT_ANGLE; current_pos--){
            servo.write(current_pos);
            delay(20);
        }
    }
    delay(50);
}


bool is_able_to_turn(int distance){
    return distance == 0 or distance > SHORT_DISTANCE_THRESHOLD;
}

bool is_object_too_close(int distance){
    return distance <= VERY_SHORT_DISTANCE_THRESHOLD;
}
bool is_object_close(int distance){
    return distance <= SHORT_DISTANCE_THRESHOLD;
}

bool is_false_read(int distance){
    return distance <= FALSE_READ_THRESHOLD or distance > MAX_DISTANCE;
}

void turn_and_stop(Servo servo, NewPing sensor, RobotMovementController rmv_controller){
    move_servo_to_left(servo);
    distance = sensor.ping_cm();
    if (is_able_to_turn(distance)) { // Try to turn left
        rmv_controller.turn_left();
    }
    else{
        move_servo_to_right(servo);
        distance = sensor.ping_cm();
        if (is_able_to_turn(distance)){ // Try to turn rigth
            rmv_controller.turn_right();
        }
        else{// It can't turn neither to left nor right
            rmv_controller.go_backwards();
            rmv_controller.stop();
            rmv_controller.turn_right();
        }
    }
    rmv_controller.stop();
    move_servo_to_center(servo);
}


void setup() {
    // Engines
    pinMode(pin_left_engine_1, OUTPUT);
    pinMode(pin_left_engine_2, OUTPUT);
    pinMode(pin_right_engine_1, OUTPUT);
    pinMode(pin_right_engine_2, OUTPUT);

    // Servo
    servo.attach(pin_servo);
    servo.write(90);

    //Debug
    Serial.begin(SERIAL_FREQ);
    pinMode(13, OUTPUT); // ? Debug? 
    starting_delay();
    amount_of_measures = 0;
    rmv_controller.do_random_slalom();
    rmv_controller.stop();
}

void loop(){
    distance = sensor.ping_cm();
    amount_of_measures++;
    if (is_false_read(distance))
        next_distance_read_delay = FAST_DELAY;
    else{
        next_distance_read_delay = NORMAL_DELAY;
        if (is_object_close(distance)) {
            rmv_controller.stop();
            if (is_object_too_close(distance)){
                rmv_controller.go_backwards();
                rmv_controller.stop();
            }
            turn_and_stop(servo, sensor, rmv_controller);
        }
        //else{
        //    if (amount_of_measures > MEASURES_BORING){
        //        rmv_controller.do_random_slalom()
        //        amount_of_measures = 0;
        //    }
        //}
    }
    rmv_controller.go_forwards();
    delay(next_distance_read_delay);
}   
