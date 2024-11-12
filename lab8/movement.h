#ifndef MOVEMENT_H_
#define MOVEMENT_H_

#include "open_interface.h"

void move_forward(oi_t *sensor, int centimeters);

void move_backward(oi_t *sensor, int centimeters);

void turn_clockwise(oi_t *sensor, double degrees);

void turn_counterclockwise(oi_t *sensor, double degrees);



#endif /* MOVEMENT_H_ */
