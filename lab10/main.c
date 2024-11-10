#include "servo.h"
#include "lcd.h"
#include "Timer.h"
#include "cyBot_Scan.h"

extern unsigned int RIGHT_VAL;
extern unsigned int LEFT_VAL;

int main(void)
{

    servo_init();
    lcd_init();
    timer_init();

    RIGHT_VAL = 7500;
    LEFT_VAL = 35000;

    timer_waitMillis(1500);
   servo_move(45);
    timer_waitMillis(1000);
    servo_move(90);
    timer_waitMillis(1000);
    servo_move(135);
    timer_waitMillis(1000);
    servo_move(180);
}
