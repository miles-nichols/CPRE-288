#include "Timer.h"
#include "lcd.h"
#include "servo.h"
#include "button.h"

#define _PART1 0
#define _PART2 1
#define _PART3 0



int main(void) {

    timer_init();
    lcd_init();
    servo_init();
    button_init();
    init_button_interrupts();

    lcd_printf("init");

    extern volatile int button_event;
    extern volatile int button_num;
    extern volatile int clockwise;


#if _PART1 //make drawing
    servo_move(0);
#endif

#if _PART2
    servo_move(90);
    while(1){
           timer_waitMillis(100);
           if(clockwise){
               lcd_printf("%d \nClockwise", abs(180 - button_Handler(button_num)));

           }
           else{
               lcd_printf("%d \nCounter Clockwise", abs(180 - button_Handler(button_num)));
           }

       }
#endif

#if PART3

#endif
}
