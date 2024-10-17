/**
 * lab6_template_extra_help.c
 *
 * Description: This is file is meant for those that would like a little
 *              extra help with formatting their code.
 *
 */

#define _RESET 0
#define _PART1 0
#define _PART2 0
#define _PART3 0
#define _PART4 1

#include <stdint.h>
#include <stdbool.h>
#include "timer.h"
#include "lcd.h"
#include <inc/tm4c123gh6pm.h>
#include "driverlib/interrupt.h"
#include "uart.h"
#include "cyBot_Scan.h"
#include "String.h"
#include "open_interface.h"
#include "movement.h"

#if _RESET
#include "Simulation_User Files_resetSimulation.h"
#endif

// Adding global volatile varibles for communcating between 
// your Interupt Service Routine, and your non-interupt code.

volatile  char uart_data;  // Your UART interupt code can place read data here
volatile  char flag;       // Your UART interupt can update this flag
                           // to indicate that it has placed new data
                           // in uart_data                     
typedef struct {
    int angle;
    float soundD;
    int IRD;
    float smoothDistance;
} scan;

typedef struct{
    int startAngle;
    int endAngle;
    int angularWidth;
    float startDistance;
    int objectNum;
    float linearWidth;
} object;

void sendString(char *str){
    int i;
    for(i = 0; i < strlen(str); i++){
        uart_sendChar(str[i]);
    }
}

float calcDisFromIR(int IRDistance){
    float exponent = (-0.0013 * (float)IRDistance) + (-30.937);
    float e = 2.718;
    return (5.6499 * pow(10, 15) * pow((e), (exponent)));
}

void main()
{
#if _RESET
    resetSimulationBoard();
#else

    timer_init();
    lcd_init();
    uart_init(115200);
    uart_interrupt_init();

    //turningn and driving the bot
    oi_t *sensor_data = oi_alloc();
    oi_init(sensor_data);


#if _PART1      // Receive and display text
    int numChars = 0;
    char receivedChar = 0;
    char buffer[30] = {0};

    while(1){
        receivedChar = uart_receive();
        if((numChars < 20) && (receivedChar != '\r')){
            buffer[numChars] = receivedChar;
            numChars++;
            lcd_printf("%d", numChars);
        }else{
            lcd_clear();
            lcd_puts(buffer);
            numChars = 0;
            int i;
            for( i = 0; i < 30; i++){
                buffer[i] = 0;
            }
        }
    }

#endif

#if _PART2      // Echo Received Character
    char receivedChar = 0;

    while(1){
        receivedChar = uart_receive();
        if(receivedChar == '\r'){
            uart_sendChar('\r');
            uart_sendChar('\n');
        }
        else {
            uart_sendChar(receivedChar);
        }
    }

#endif

#if _PART3 // Receive and send characters using interrupts.
    char receivedChar = 0;
    flag = 0;

        while(1){
            if(flag == 1){
                receivedChar = uart_data;
                if(receivedChar == '\r'){
                    uart_sendChar('\r');
                    uart_sendChar('\n');
                }
                else {
                    uart_sendChar(receivedChar);
                }
                flag = 0;
            }
        }
#endif

#if _PART4
    cyBOT_init_Scan(0b0111);
    //right_calibration_value = 343000; //bot 08
    //left_calibration_value = 1351000; //bot 08
    right_calibration_value = 280000; //bot 10
    left_calibration_value = 1267000; //bot 10
    //cyBOT_SERVO_cal();

    flag = 0;
    scan scans[100];
    cyBOT_Scan_t singleScan;

    while(1){
//        receivedChar = uart_receive();
        if(uart_receive() == 'q'){
           break;
        }

        if(flag == 1){
            char str[] = "";
            int angle;
            for(angle = 0; angle <= 180; angle += 2){
                cyBOT_Scan(angle, &singleScan);

                scans[angle / 2].angle = angle;
                scans[angle / 2].smoothDistance = singleScan.sound_dist;
                scans[angle / 2].IRD = calcDisFromIR(singleScan.IR_raw_val);

                sprintf(str, "%d    %d    %f\r\n", scans[angle / 2].angle , scans[angle / 2].IRD, scans[angle / 2].smoothDistance);
                sendString(str);
                str[0] = '\0';
           }

            object objects[10] = {{0, 0, 0, 0, 0,0}};
            int degreeWidth = 3;
            int scanCount = 0;
            int objectCount = 0;
            int i;
            for(i = 0; i < 90; i++){
                sprintf(str, "%d  %d\r\n", scans[i].IRD, scans[i + 1].IRD);
                sendString(str);
                str[0] = '\0';
                if(scans[i].IRD <= scans[i + 1].IRD + 2 && scans[i].IRD >= scans[i + 1].IRD - 2 && scans[i].IRD < 50){
                    scanCount++;
                }else{
                    scanCount = 0;
                }

                if(scanCount > degreeWidth){
                    objects[objectCount - 1].angularWidth += 2;
                }else if(scanCount == degreeWidth){
                    objects[objectCount].startAngle = i * 2;
                    objects[objectCount].angularWidth = degreeWidth * 2;
                    if(i - degreeWidth - 1 < 0){
                        objects[objectCount].startDistance = scans[0].IRD;
                    }
                    objects[objectCount].startDistance = scans[i - degreeWidth - 1].IRD;
                    objects[objectCount].objectNum = objectCount;
                    objectCount++;
                }
            }


            for(i = 0; i < objectCount; i++){
                objects[i].endAngle = scans[(objects[i].startAngle + objects[i].angularWidth) / 2].angle;
                if(objects[i].endAngle > 180){
                    objects[i].endAngle = 180;
                }
                if(objects[i].endAngle == 180){
                    objects[i].angularWidth = objects[i].endAngle - objects[i].startAngle;
                }
            }

            for(i = 0; i < objectCount; i++){
                objects[i].linearWidth = sqrt(2 * objects[i].startDistance * objects[i].startDistance *(1-cos(  objects[i].angularWidth * (3.14/180) )));
            }

            object narrowest = {0, 0, 0, 0, 0, 1000};
            for(i = 0; i < objectCount; i++){
                if(objects[i].linearWidth < narrowest.linearWidth){
                    narrowest = objects[i];
                }
            }

            //points scanner at the narrowest object
            int narrowestAngle = (narrowest.endAngle + narrowest.startAngle) / 2;
            cyBOT_Scan(narrowestAngle, &singleScan);

            //printing to putty
            sprintf(str, "Object      Start Angle   End Angle  Start Distance    Angular Width      Linear Width\r\n");
            sendString(str);
            str[0] = '\0';
            for(i = 0; i < objectCount; i++){
                sprintf(str, "%d           %d                %d          %f         %d            %f\r\n", objects[i].objectNum, objects[i].startAngle, objects[i].endAngle, objects[i].startDistance, objects[i].angularWidth, objects[i].linearWidth);
                sendString(str);
                str[0] = '\0';
            }

            sprintf(str, "Thinnest Object is %d: Angle to point to is %d\r\n", narrowest.objectNum, (narrowest.endAngle + narrowest.startAngle) / 2);
             sendString(str);
             str[0] = '\0';

             double forwardErrorMultiple = 0.98;
             double turnErrorMultiple = 0.9125;

             if(90 - narrowestAngle > 0){
                 turnC(90 - narrowestAngle, 100, turnErrorMultiple, sensor_data);
             }else {
                 turnCC((narrowestAngle - 90) /2, 100, turnErrorMultiple, sensor_data);
             }
             moveForward(narrowest.startDistance * 5, 100, forwardErrorMultiple, sensor_data);
        }
        flag = 0;
    }
    oi_free(sensor_data);
#endif

#endif
}

