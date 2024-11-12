#include "movement.h"

/*
 * @Author Winson Vetsavong Miles Nichols
 * @Date 9/12/2024
 */

void move_forward(oi_t *sensor, int centimeters)
{
    double sum = 0;
    double milimeters = centimeters * 10;

    oi_setWheels(100, 100);

    while (sum < milimeters)
    {
        oi_update(sensor);
        sum += sensor->distance;

    }

    oi_setWheels(0, 0); // stop
    return;
}

void move_backward(oi_t *sensor, int centimeters)
{
    int millimeters = centimeters * 10;
    oi_setWheels(-100, -100);
    int sum = millimeters;

    while (sum > 0)
    {
        oi_update(sensor);
        sum += sensor->distance;
    }
    oi_setWheels(0, 0); // stop
    return;

}

void turn_clockwise(oi_t *sensor, double desiredDegrees)
{
    double degrees = desiredDegrees * -1;
    double sum = 0.0;

    oi_setWheels(-100, 100);

    while (sum > degrees)
    {
        oi_update(sensor);
        sum += sensor->angle;
    }

    oi_setWheels(0, 0); // stop
    return;

}

void turn_counterclockwise(oi_t *sensor, double desiredDegrees)
{
    double degrees = desiredDegrees;
    double sum = 0.0;

        oi_setWheels(100, -100);

        while (sum < degrees)
        {
            oi_update(sensor);
            sum += sensor->angle;
        }

        oi_setWheels(0, 0); // stop
        return;

}
