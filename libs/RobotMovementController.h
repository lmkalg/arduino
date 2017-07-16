#ifndef ROBOT_MOVEMENT_CONTROLLER_H
#define ROBOT_MOVEMENT_CONTROLLER_H

class RobotMovementController{

    public:
        RobotMovementController(int ple1, int ple2, int pre1, int pre2 ): pin_left_engine_1(ple1),pin_left_engine_2(ple2),pin_right_engine_1(pre1),pin_right_engine_2(pre2){};
        void go_forwards();
        void go_backwards();
        void turn_right();
        void turn_left();
        void stop();
        void do_random_slalom();

    private:
        //Variables
        int pin_left_engine_1;
        int pin_left_engine_2;
        int pin_right_engine_1;
        int pin_right_engine_2;

        // Functions
        void go_backwards_right_engine();
        void go_backwards_left_engine();
        void go_forwards_right_engine();
        void go_forwards_left_engine();
        void stop_right_engine();
        void stop_left_engine();

};
#endif


