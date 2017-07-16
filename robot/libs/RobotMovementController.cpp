#include <Arduino.h>
#include "RobotMovementController.h"

int TIME_TO_TURN = 800;
int TIME_TO_GO_BACKWARDS = 1000;
int RANDOM_BASE_TIME = 1000;
int RANDOM_MAX_RANGE_TIME = 3000;


//Public
void RobotMovementController::go_forwards(){
    go_forwards_left_engine();
    go_forwards_right_engine();
}   

void RobotMovementController::go_backwards(){
    go_backwards_left_engine();
    go_backwards_right_engine();
    delay(TIME_TO_GO_BACKWARDS);

}

void RobotMovementController::turn_left(){
    go_forwards_right_engine();
    stop_left_engine();
    delay(TIME_TO_TURN);
}

void RobotMovementController::turn_right(){
    go_forwards_left_engine();
    stop_right_engine();
    delay(TIME_TO_TURN);
}

void RobotMovementController::stop(){
    stop_right_engine();
    stop_left_engine();
}

void RobotMovementController::do_random_slalom(){
    if (random(2) % 2 == 0){
        go_forwards_right_engine();
        go_backwards_left_engine();
    }
    else{
        go_backwards_right_engine();
        go_forwards_left_engine();
    }

    delay(random(RANDOM_MAX_RANGE_TIME) + RANDOM_BASE_TIME);
}


//Private
void RobotMovementController::go_forwards_right_engine(){
    digitalWrite(pin_right_engine_1, HIGH );
    digitalWrite(pin_right_engine_2, LOW );
}
void RobotMovementController::go_forwards_left_engine(){
    digitalWrite(pin_left_engine_2, HIGH );
    digitalWrite(pin_left_engine_1, LOW );
}
void RobotMovementController::go_backwards_left_engine(){
    digitalWrite(pin_left_engine_2, LOW );
    digitalWrite(pin_left_engine_1, HIGH );
}

void RobotMovementController::go_backwards_right_engine(){
    digitalWrite(pin_right_engine_1, LOW);
    digitalWrite(pin_right_engine_2, HIGH);
}

void RobotMovementController::stop_left_engine(){
    digitalWrite(pin_left_engine_1,LOW);
    digitalWrite(pin_left_engine_2,LOW);
    
}
void RobotMovementController::stop_right_engine(){
    digitalWrite(pin_right_engine_1,LOW);
    digitalWrite(pin_right_engine_2,LOW);
}








