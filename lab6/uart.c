/*
*
*   uart_extra_help.c
* Description: This is file is meant for those that would like a little
*              extra help with formatting their code, and followig the Datasheet.
*/

#include "uart.h"
#include "timer.h"
#define REPLACE_ME 0x00

static char data = 0;

void uart_init(int baud)
{
    SYSCTL_RCGCGPIO_R |= 0x2;      // enable clock GPIOB (page 340)
    SYSCTL_RCGCUART_R |= 0x02;      // enable clock UART1 (page 344)
    GPIO_PORTB_AFSEL_R = 0x03;      // sets PB0 and PB1 as peripherals (page 671)
    GPIO_PORTB_PCTL_R  = 0x00000011;       // pmc0 and pmc1       (page 688)  also refer to page 650
    GPIO_PORTB_DEN_R   = 0x03;        // enables pb0 and pb1
    GPIO_PORTB_DIR_R   = 0x01;   // sets pb0 as output, pb1 as input

    //compute baud values [UART clock= 16 MHz] 
    double fbrd;
    int    ibrd;

    fbrd = 0.68055555; // page 903
    ibrd = 8;
    fbrd = 44;

    UART1_CTL_R &= 0b0;      // disable UART1 (page 918)
    UART1_IBRD_R = 8;        // write integer portion of BRD to IBRD
    UART1_FBRD_R = 44;   // write fractional portion of BRD to FBRD
    UART1_LCRH_R = 0b01100000;        // write serial communication parameters (page 916) * 8bit and no parity
    UART1_CC_R   = 0x0;          // use system clock as clock source (page 939)
    UART1_CTL_R |= 0b1100000001;        // enable UART1

}

void uart_sendChar(char data)
{
   while(UART1_FR_R & 0b100000){
   }
   UART1_DR_R = data;
   
}

char uart_receive(void)
{
    while(UART1_FR_R & 0b10000){
    }
    data = (char)(UART1_DR_R & 0xFF);
    return data;

 
}

void uart_sendStr(const char *data)
{
    int i = 0;
    while(data[i] != '\0'){
        uart_sendChar(data[i]);
        i++;
    }
}

// _PART3


void uart_interrupt_init()
{
    // Enable interrupts for receiving bytes through UART1
    UART1_IM_R |= 0b10000; //enable interrupt on receive - page 924

    // Find the NVIC enable register and bit responsible for UART1 in table 2-9
    // Note: NVIC register descriptions are found in chapter 3.4
    NVIC_EN0_R |= 0b01000000; //enable uart1 interrupts - page 104

    // Find the vector number of UART1 in table 2-9 ! UART1 is 22 from vector number page 104
    IntRegister(INT_UART1, uart_interrupt_handler); //give the microcontroller the address of our interrupt handler - page 104 22 is the vector number

}

void uart_interrupt_handler()
{
    uart_data = (UART1_DR_R & 0xFF);
    UART1_ICR_R = 0x10;
    flag = 1;
}
