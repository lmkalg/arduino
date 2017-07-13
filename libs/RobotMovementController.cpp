#include <Arduino.h>
#include "RobotMovementController.h"

//Public
void RobotMovementController::go_forwards(){
    go_forwards_left_engine();
    go_forwards_right_engine();
}   

void RobotMovementController::go_backwards(){
    go_backwards_left_engine();
    go_backwards_right_engine();
    delay(1000);

}

void RobotMovementController::turn_left(){
    go_forwards_right_engine();
    stop_left_engine();
    delay(500);
}

void RobotMovementController::turn_right(){
    go_forwards_left_engine();
    stop_right_engine();
    delay(500);
}

void RobotMovementController::stop(){
    stop_right_engine();
    stop_left_engine();
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








