#include "movement.h"


//move the robot in a straight line for a certain distance
//param distance : the number of millimeters we want the robot to move
//param speed: the speed at which the bot moves
//param linearErrorMultiple : the adjustment we need to make for each robot
//param sensor_data : data from the sensors on the bot
void moveForward(double distance, double speed, double linearErrorMultiple, oi_t *sensor_data){
    double traveled = 0;

    oi_setWheels(speed, speed);
    while(traveled < (distance * linearErrorMultiple)){
        oi_update(sensor_data);
        traveled += sensor_data->distance;
     }
     oi_setWheels(0, 0);
}

//move the robot backwards in a straight line for a certain distance
//param distance : the number of millimeters we want the robot to move
//param speed: the speed at which the bot moves
//param linearErrorMultiple : the adjustment we need to make for each robot
//param sensor_data : data from the sensors on the bot
void moveBackward(double distance, double speed, double linearErrorMultiple, oi_t *sensor_data){
    double traveled = 0;

    oi_setWheels(-speed, -speed);
    while(-traveled < (distance * linearErrorMultiple)){
        oi_update(sensor_data);
        traveled += sensor_data->distance;
     }
     oi_setWheels(0, 0);
}

//move the robot backwards in a straight line for a certain distance
//param distance : the number of millimeters we want the robot to move
//param speed: the speed at which the bot moves
//param turnErrorMultiple: the adjustment we need based on the robot
//param linearErrorMultiple : the adjustment we need to make for each robot
//param sensor_data : data from the sensors on the bot
void moveForwardWithObstacles(double distance, double speed, double turnErrorMultiple,  double linearErrorMultiple, oi_t *sensor_data){
    double traveled = 0;

    oi_setWheels(speed, speed);
    while(traveled < (distance * linearErrorMultiple)){
        oi_update(sensor_data);
        traveled += sensor_data->distance;
        if(sensor_data->bumpLeft){
            bumpHandler('L', turnErrorMultiple, linearErrorMultiple, sensor_data);
            oi_setWheels(speed, speed);
        }else if(sensor_data->bumpRight){
            bumpHandler('R', turnErrorMultiple, linearErrorMultiple, sensor_data);
            oi_setWheels(speed, speed);
        }
     }
     oi_setWheels(0, 0);
}


//turns the bot in place and counter clockwise a certain number of degrees
//param degrees : how many degrees to turn
//param speed: the speed at which the bot turns
//param turnErrorMultiple : the adjustment we to make for each robot
//param sensor_data : data from the sensors on the bot
void turnCC(double degreeTurn, double speed, double turnErrorMultiple, oi_t *sensor_data){
    double turnSum = 0;
    oi_setWheels(speed,-speed);
    while(turnSum < (degreeTurn * turnErrorMultiple)){
        oi_update(sensor_data);
        turnSum += sensor_data->angle;
    }
    oi_setWheels(0,0);
}

//turns the bot in place and clockwise a certain number of degrees
//param degrees : how many degrees to turn
//param speed: the speed at which the bot turns
//param turnErrorMultiple : the adjustment we to make for each robot
//param sensor_data : data from the sensors on the bot
void turnC(double degreeTurn, double speed, double turnErrorMultiple, oi_t *sensor_data){
    double turnSum = 0;
    oi_setWheels(-speed, speed);
    while(turnSum > (-degreeTurn * turnErrorMultiple)){
        oi_update(sensor_data);
        turnSum += sensor_data->angle;
    }
    oi_setWheels(0,0);
}

//naviagtes the bot around any opstacles that it bumps into
void bumpHandler(char direction, double turnErrorMultiple, double linearErrorMultiple, oi_t *sensor_data){
    if(direction == 'R'){
        moveBackward(150, 75, linearErrorMultiple, sensor_data);
        turnCC(90.0 , 100.0, turnErrorMultiple, sensor_data);
        moveForward(250, 75, linearErrorMultiple, sensor_data);
        turnC(90.0 , 100.0, turnErrorMultiple, sensor_data);
        moveForward(150, 75, linearErrorMultiple, sensor_data);
    }else if(direction =='L'){
        moveBackward(150, 75, linearErrorMultiple, sensor_data);
        turnC(90.0 , 100.0, turnErrorMultiple, sensor_data);
        moveForward(250, 75, linearErrorMultiple, sensor_data);
        turnCC(90.0 , 100.0, turnErrorMultiple, sensor_data);
        moveForward(150, 75, linearErrorMultiple, sensor_data);
    }
}
