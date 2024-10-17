#include "open_interface.h"

#ifndef MOVEMENT_H_
#define MOVEMENT_H_

//drive cybot forward and avoid objects using only sensors
double move_forward_obj(oi_t* sensor_data, double distance_mm);

//drive cybot forward
double move_forward(oi_t *sensor_data, double distance_mm);

//drive cybot backward
double move_backward(oi_t *sensor_data, double distance_mm);

//turn cybot 90 degrees to the right
double turn_right(oi_t *sensor, double degrees);

//turn cybot 90 degrees to the left
double turn_left(oi_t *sensor, double degrees);

#endif /* MOVEMENT_H_ */
