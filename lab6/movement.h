#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include "Timer.h"
#include <inc/tm4c123gh6pm.h>
#include "lcd.h"
#include "open_interface.h"

//move the robot in a straight line for a certain distance
void moveForward(double distance, double speed, double linearErrorMultiple, oi_t *sensor_data);

//move the robot backward in a straight line for a certain distance
void moveBackward(double distance, double speed, double linearErrorMultiple, oi_t *sensor_data);

//move the robot in a straight line for a certain distance with the ability to avoid objects in the way
void moveForwardWithObstacles(double distance, double speed, double turnErrorMultiple, double linearErrorMultiple, oi_t *sensor_data);

//turns the bot in place and counter clockwise a certain number of degrees
void turnCC(double turnDegree, double speed, double turnErrorMultiple, oi_t *sensor_data);

//turns the bot in place and clockwise a certain number of degrees
void turnC(double turnDegree, double speed, double turnErrorMultiple, oi_t *sensor_data);

//handles the navigation around obstacles
void bumpHandler(char direction, double turnErrorMultiple, double linearErrorMultiple, oi_t *sensor_data);
