/*
 * movement.h
 *
 *  Created on: Sep 7, 2023
 *      Author: esivets
 */
#include "open_interface.h"

#ifndef MOVEMENT_H_
#define MOVEMENT_H_


void move_forward(oi_t *sensor, int centimeters);
void move_backwards(oi_t *sensor, int millimeters);
void turn_clockwise(oi_t *sensor, int degrees);
void turn_cclockwise(oi_t *sensor, int degrees);
#endif /* MOVEMENT_H_ */
