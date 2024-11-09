#include "Timer.h"
#include "lcd.h"
#include "servo.h"
#include <stdint.h>

void servo_init(){
    SYSCTL_RCGC0_R = 0x00100000; //Enable PWM clock by set RCGC0 to bit 20
    SYSCTL_RCGC2_R |= 0x01; //Enable the run mode clock by setting bit 1 (port b)
    GPIO_PORTB_AFSEL_R |= 0x08; //Enable bit 4 for PB4 pin 58 M0PWM2
    GPIO_PORTB_PCTL_R |= 0x000F0000; //bit 4 of port B for PMC4 I'm not really sure if this is correct
    SYSCTL_RCC_R |= 0x00100000; //set bit 20 to enable USEPWMDIV
    SYSCTL_RCC_R &= ~0x000E0000; //set bits 17-19 to 0

    //Config PWN gen for countdown mode
    PWM_PWM0CTL_R = 0x00000000;
    PWM_PWM0HENA_R = 0x0000_008C
    PWM_PWM0GENB_R = 0x0000_008C
    PWM_PWM0LOAD_R = 399; //setting the period to amount of clock ticks per period - 1 (0x0000.018F)
    PWM_PWM0CMPA_R = 0x0000012B; // pulse width of MnPWM0 to 25%
    PWM_PWM0CMPB_R = 0x00000063; // pulse width of MnPWM1 to 75%
    PWM_PWM0CTL_R = 0x00000001; //start the timers in PWN gen 0
    PWM_PWMENABLE_R = 0x00000003; // enable PWN outputs
}

int servo_move(degrees){
    return 0;
}
