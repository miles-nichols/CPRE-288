#include "open_interface.h"

//drive forward
double move_forward(oi_t *sensor_data, double distance_mm)
{
    double sum = 0; // distance member in oi_t struct is type double
    oi_setWheels(300, 300); //drive forward
    while (sum < distance_mm) // while cybot still has distance to travel
    {
        oi_update(sensor_data); // update sensor data
        sum += sensor_data->distance; // calculate distance traveled (use -> b/c pointer)
        lcd_printf("Distance moved: %.2fmm", sum);
    }
    oi_setWheels(0, 0); //stop
    return sum;
}

//drive backward
double move_backward(oi_t *sensor_data, double distance_mm)
{
    double sum = 0; // keep track of distance
    oi_setWheels(-300, -300); // move backward
    while (sum > distance_mm * -1) // while cybot still has negative (backwards) distance to travel
    {
        // update, calculate, and display the distance traveled
        oi_update(sensor_data);
        sum += sensor_data->distance;
        lcd_printf("Distance moved: %.2fmm", sum);
    }
    oi_setWheels(0, 0); //stop
    return sum;
}

//turn right 90 degrees
double turn_right(oi_t *sensor, double degrees)
{
    oi_setWheels(-100, 100); //wheels parameter: (right,left)
    double sum = 0;
    while (sum > degrees * -1) //while cybot still has negative (
    {
        // update, calculate, and display the angle turned
        oi_update(sensor);
        sum += sensor->angle;
        lcd_printf("Angles(right): %.2f\n", sum);
    }
    return sum;
}

//turn left 90 degrees
double turn_left(oi_t *sensor, double degrees)
{
    oi_setWheels(100, -100);
    double sum = 0;
    while (sum < degrees)
    {
        oi_update(sensor);
        sum += sensor->angle;
        lcd_printf("Angles(left): %.2f\n", sum);
    }
    return sum;
}

//drive forward and avoid objects using only bumper sensors
double move_forward_obj(oi_t *sensor_data, double distance_mm)
{
    double sum = 0; // distance member in oi_t struct is type double
    oi_setWheels(300, 300); //move forward
    while (sum < distance_mm)
    {
        oi_update(sensor_data);

        //Check bumpers
        if (sensor_data->bumpLeft)
        {
            oi_setWheels(0, 0); //reset wheels
            move_backward(&sensor_data, 150); //back 15cm
            turn_right(&sensor_data, 90); //90 degrees right
            move_forward(&sensor_data, 250); //drive 25 cm
            turn_left(&sensor_data, 90); //turn left 90, keep going*
        }

        if (sensor_data->bumpRight)
        {
            oi_setWheels(0, 0); //reset wheels
            move_backward(&sensor_data, 150); //back 15cm
            turn_left(&sensor_data, 90); //90 degrees left
            move_forward(&sensor_data, 250); //drive 25 cm
            turn_right(&sensor_data, 90); //turn right 90, keep going*
        }
        oi_setWheels(300, 300); //*keep going
        sum += sensor_data->distance; // update distance moved
        lcd_printf("Distance moved: %.2fmm", sum);
    }
    //print total distance traveled instead of updating after every loop(?)
    //lcd_printf("Total distance moved: %.2fmm", sum);
    oi_setWheels(0, 0); //stop
    return sum;
}
