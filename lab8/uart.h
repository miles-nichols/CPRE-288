/*
*
*   uart.h
*
*   Used to set up the UART
*   uses UART1 at 115200
*
*/

#ifndef UART_H_
#define UART_H_

#include "Timer.h"
#include <inc/tm4c123gh6pm.h>

void uart_init(void);

void uart_sendChar(char data);

char uart_receive(void);

void uart_sendStr(const char *data);

void uart_interrupt_init();

void uart_interrupt_handler();


#endif /* UART_H_ */
