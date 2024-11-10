#include "Timer.h"
#include "lcd.h"
#include "servo.h"
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>

unsigned int RIGHT_VAL = 0;
unsigned int LEFT_VAL = 0;

void servo_init(void){

    //Config PB5 as T1CCP1
    GPIO_PORTB_AFSEL_R |= 0x20;
    GPIO_PORTB_PCTL_R &= ~0x00F00000;
    GPIO_PORTB_PCTL_R |= 0x00700000;
    GPIO_PORTB_DIR_R |= 0x20;
    GPIO_PORTB_DEN_R |= 0x20;

    SYSCTL_RCGCGPIO_R |= 0x02; //send clock to gpio B
      while((SYSCTL_PRGPIO_R & 0x02) == 0){}

    //Timer 1, Timer B, T1CCP1, PB5
    TIMER1_CTL_R &= ~0x00000100; // Disabling the timer
    TIMER1_CFG_R = 0x00000004; //GPTM config

    TIMER1_TBMR_R &= ~(0x4); // clear TnCMR (bit 2) for edge count mode
    TIMER1_TBMR_R |= 0x2; //sets TnMR, bits 0 and 1 to 0x2 for periodic mode
    TIMER1_TBMR_R |= 0x8; //set TnAMS, bit 3 to 1 for PWM mode enable

    //set the peropds fpr 20 ms PWM signal (320,000) ticks
    TIMER1_TBPR_R = 0x04; //add upper hex val of 04 to prescale
    TIMER1_TBILR_R = 0xE200; //upper value of e200 which is smushed together with prescaler to make 04e200
    TIMER1_TBPMR_R = 0x04;
    //match to clock cycle count of 0 degrees
    TIMER1_TBMATCHR_R = 0xC4B4;


    TIMER1_CTL_R |= 0x00000100; // enable timer

}



void servo_move(float degrees){
    int clockCyclesFromMax = (((LEFT_VAL - RIGHT_VAL) / 180) * degrees) + RIGHT_VAL;
       int matchValues = 320000 - clockCyclesFromMax;
       //set clock cycles
       TIMER1_TBPMR_R = (matchValues >> 16);
       //match to clock cycle count of 0 degrees
       TIMER1_TBMATCHR_R = (matchValues &= ~0x110000);
}
