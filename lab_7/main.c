

/**
 * main.c
 */

#include <cyBot_uart.h>
#include "cyBot_Scan.h"
#include "cyBot_uart.h"
#include "Timer.h"
#include "lcd.h"
#include <math.h>
#include "open_interface.h"
#include "movement.h"

int main(void)
{

    timer_init();
    lcd_init();
    lcd_putc('a');

    oi_t *sensor_data = oi_alloc();
    oi_init(sensor_data);
    uart_init();
    lcd_putc('b');


    cyBOT_init_Scan(0b0111);

    //cyBOT_SERVO_cal();

   //volatile  char uart_data;
   //volatile  char flag;



    right_calibration_value = 280000; //bot 10
       left_calibration_value = 1267000; //bot 10
    lcd_putc('c');

    int previousScan = 1;
    int objectStartDegree;
    int objectEndDegree;
    char angle[4];
    char distance[4];
    char width[4];
    char linearWidth[4];
    typedef struct{
        int degree;
        int distance;
        int width;
        int linearWidth;
    }Object;
    Object objectList[4];
       int objectCount = 0;
       // YOUR CODE HERE
       char scanval[5];
       int i = 0;
       char pingScan[5];
       char degre[3];
       int previousPingScan = 0;
       char calculatedDistance[5];
       int deg;
       cyBOT_Scan_t scan;
       cyBOT_Scan_t tempscan;

       uart_receive();
       for(deg = 0; deg <= 180; deg += 2){
           cyBOT_Scan(deg, &scan);
           lcd_clear();


           sprintf(scanval, "%d", (scan.IR_raw_val+previousScan)/2);


           sprintf(pingScan, "%f", (scan.sound_dist+previousPingScan)/2);

           sprintf(degre, "%d", deg);
           for(i = 0; i< 3; i++){
               uart_sendChar(degre[i]);
           }
           uart_sendChar(',');
           uart_sendChar(' ');
           for(i = 0; i< 5; i++){
               uart_sendChar(scanval[i]);
           }
           uart_sendChar(',');
           uart_sendChar(' ');
           for(i = 0; i< 5; i++){
               uart_sendChar(pingScan[i]);
           }

           float Stock = pow( ((scan.IR_raw_val+previousScan)/2.0), -1.626);
           float Ham = 4000000 * Stock;

           float calculatedIRVAL = 10000000 * pow(scan.IR_raw_val, -1.867);
           float calculatedPREVIOUSVAL = 10000000 * pow(previousScan, -1.867);

           sprintf(calculatedDistance, "%f", calculatedIRVAL);
           uart_sendChar(',');
           uart_sendChar(' ');
           for(i = 0; i< 5; i++){
               uart_sendChar(calculatedDistance[i]);

           }



           if(calculatedIRVAL - calculatedPREVIOUSVAL < -5){
                       //Start object
                       objectStartDegree = deg;
                       uart_sendChar('\n');
                       uart_sendChar('\r');
                       uart_sendChar('s');
                       lcd_putc('s');
                   }
           if(calculatedPREVIOUSVAL - calculatedIRVAL < -5){
               //end object
               objectEndDegree = deg;

               if(objectEndDegree-objectStartDegree > 3 ){
              //     if(((objectEndDegree+objectStartDegree)/2) > (objectList[objectCount--].degree + 3)){
                       //object is valid
                       uart_sendChar('\n');
                       uart_sendChar('\r');
                       uart_sendChar('o');
                       uart_sendChar('b');
                       uart_sendChar('j');
                       uart_sendChar('\n');
                       uart_sendChar('\r');
                       lcd_clear();
                       //save object
                       objectList[objectCount].degree = (objectEndDegree + objectStartDegree )/ 2;
    //                   cyBOT_Scan(objectList[objectCount].degree, &tempscan);
    //                   objectList[objectCount].distance = tempscan.sound_dist;
                       objectList[objectCount].distance = scan.sound_dist;
                       objectList[objectCount].linearWidth = abs(2*((sin((objectEndDegree - objectStartDegree)/2))*objectList[objectCount].distance));
                       objectList[objectCount].width = objectEndDegree-objectStartDegree;

                       objectCount++;
             //      }
               }

           }

           previousScan = scan.IR_raw_val;
           previousPingScan = scan.sound_dist;


           uart_sendChar('\n');
           uart_sendChar('\r');
       }

       uart_sendChar('O');
       uart_sendChar('b');
       uart_sendChar('j');
       uart_sendChar(' ');
       uart_sendChar(' ');
       uart_sendChar(' ');
       uart_sendChar(' ');
       uart_sendChar('A');
       uart_sendChar('n');
       uart_sendChar('g');
       uart_sendChar(' ');
       uart_sendChar(' ');
       uart_sendChar(' ');
       uart_sendChar(' ');
       uart_sendChar('D');
       uart_sendChar('i');
       uart_sendChar('s');
       uart_sendChar('t');
       uart_sendChar(' ');
       uart_sendChar(' ');
       uart_sendChar(' ');
       uart_sendChar(' ');
       uart_sendChar('W');
       uart_sendChar('i');
       uart_sendChar('d');
       uart_sendChar('t');
       uart_sendChar('h');
       uart_sendChar(' ');
       uart_sendChar(' ');
       uart_sendChar(' ');
       uart_sendChar(' ');
       uart_sendChar('L');
       uart_sendChar('W');
       uart_sendChar('i');
       uart_sendChar('d');
       uart_sendChar('t');
       uart_sendChar('h');
       uart_sendChar('\n');
       uart_sendChar('\r');
       for(i = 0; i < objectCount; i ++){
           uart_sendChar(i + 48);
           uart_sendChar(' ');
           uart_sendChar(' ');
           uart_sendChar(' ');
           uart_sendChar(' ');
           sprintf(angle, " %d", objectList[i].degree);
           sprintf(distance, " %d", objectList[i].distance);
           sprintf(width, " %d", objectList[i].width);
           sprintf(linearWidth, " %d", objectList[i].linearWidth);
           uart_sendChar(angle[0]);
           uart_sendChar(angle[1]);
           uart_sendChar(angle[2]);
           uart_sendChar(angle[3]);
           uart_sendChar(' ');
           uart_sendChar(' ');
           uart_sendChar(' ');
           uart_sendChar(' ');
           uart_sendChar(distance[0]);
           uart_sendChar(distance[1]);
           uart_sendChar(distance[2]);
           uart_sendChar(distance[3]);
           uart_sendChar(' ');
           uart_sendChar(' ');
           uart_sendChar(' ');
           uart_sendChar(' ');
           uart_sendChar(width[0]);
           uart_sendChar(width[1]);
           uart_sendChar(width[2]);
           uart_sendChar(width[3]);
           uart_sendChar(' ');
           uart_sendChar(' ');
           uart_sendChar(' ');
           uart_sendChar(' ');
           uart_sendChar(linearWidth[0]);
           uart_sendChar(linearWidth[1]);
           uart_sendChar(linearWidth[2]);
           uart_sendChar(linearWidth[3]);
           uart_sendChar('\n');
           uart_sendChar('\r');

       }


       int shortestWidth = objectList[0].width;
       int shortestObjectIndex = 0;
       for(i = 0; i < objectCount; i ++){


           if(objectList[i].width < shortestWidth){
               shortestWidth = objectList[i].width;
               shortestObjectIndex = i;
           }
       }

       timer_waitMillis(500);
       cyBOT_Scan(objectList[shortestObjectIndex].degree, &tempscan);
       objectList[shortestObjectIndex].distance = tempscan.sound_dist;
       timer_waitMillis(200);

       uart_sendChar('\n');
       uart_sendChar('\r');
       sprintf(angle, " %d", objectList[shortestObjectIndex].degree);
       uart_sendChar(angle[0]);
       uart_sendChar(angle[1]);
       uart_sendChar(angle[2]);
       uart_sendChar(angle[3]);


       if(objectList[shortestObjectIndex].degree > 90){
           //turn counter clockwise
                turn_cclockwise(sensor_data, (objectList[shortestObjectIndex].degree - 90)*2.77777778);
                move_forward(sensor_data, objectList[shortestObjectIndex].distance*4);


       }
       else{
           //turn clockwise
           turn_clockwise(sensor_data, (90-objectList[shortestObjectIndex].degree)*2.77777778);
           move_forward(sensor_data, objectList[shortestObjectIndex].distance*4);

       }
       oi_free(sensor_data);
}

    //part 4
//
//        right_calibration_value = 180250;
//        left_calibration_value = 1309000;
//        lcd_putc('c');
//
//        int previousScan = 1;
//        int objectStartDegree;
//        int objectEndDegree;
//        char angle[4];
//        char distance[4];
//        char width[4];
//        int shortestObjectIndex = 0;
//        char linearWidth[4];
//        typedef struct{
//            int degree;
//            int distance;
//            int width;
//            int linearWidth;
//        }Object;
//        Object objectList[4];
//           int objectCount = 0;
//
//           char scanval[5];
//           int i = 0;
//           char pingScan[5];
//           char degre[3];
//           int previousPingScan = 0;
//           char calculatedDistance[5];
//           int deg;
//           char readVal;
//           int toggle = 0;
//           cyBOT_Scan_t scan;
//           cyBOT_Scan_t tempscan;
//
//           uart_receive();
//           while(1){
//               readVal = uart_receive();
//               uart_sendChar(readVal);
//               if(readVal == 'h' && toggle == 0){
//
//                   for(deg = 0; deg <= 180; deg += 2){
//                       if((char)(UART1_DR_R & 0xFF) == 't'){
//                           for( i = 0; i < 20; i ++){
//                               uart_sendChar('-');
//                           }
//                           uart_sendChar('\n');
//                           uart_sendChar('\r');
//                           toggle = 1;
//                           break;
//                       }
//                       cyBOT_Scan(deg, &scan);
//                       lcd_clear();
//
//
//                       sprintf(scanval, "%d", (scan.IR_raw_val+previousScan)/2);
//
//
//                       sprintf(pingScan, "%f", (scan.sound_dist+previousPingScan)/2);
//
//                       sprintf(degre, "%d", deg);
//                       for(i = 0; i< 3; i++){
//                           uart_sendChar(degre[i]);
//                       }
//                       uart_sendChar(',');
//                       uart_sendChar(' ');
//                       for(i = 0; i< 5; i++){
//                           uart_sendChar(scanval[i]);
//                       }
//                       uart_sendChar(',');
//                       uart_sendChar(' ');
//                       for(i = 0; i< 5; i++){
//                           uart_sendChar(pingScan[i]);
//                       }
//
//                       float Stock = pow( ((scan.IR_raw_val+previousScan)/2.0), -1.626);
//                       float Ham = 4000000 * Stock;
//
//                       float calculatedIRVAL = 10000000 * pow(scan.IR_raw_val, -1.867);
//                       float calculatedPREVIOUSVAL = 10000000 * pow(previousScan, -1.867);
//
//                       sprintf(calculatedDistance, "%f", calculatedIRVAL);
//                       uart_sendChar(',');
//                       uart_sendChar(' ');
//                       for(i = 0; i< 5; i++){
//                           uart_sendChar(calculatedDistance[i]);
//
//                       }
//
//
//
//                       if(calculatedIRVAL - calculatedPREVIOUSVAL < -5){
//                                   //Start object
//                                   objectStartDegree = deg;
//                                   uart_sendChar('\n');
//                                   uart_sendChar('\r');
//                                   uart_sendChar('s');
//                                   lcd_putc('s');
//                               }
//                       if(calculatedPREVIOUSVAL - calculatedIRVAL < -5){
//                           //end object
//                           objectEndDegree = deg;
//
//                           if(objectEndDegree-objectStartDegree > 3 ){
//                          //     if(((objectEndDegree+objectStartDegree)/2) > (objectList[objectCount--].degree + 3)){
//                                   //object is valid
//                                   uart_sendChar('\n');
//                                   uart_sendChar('\r');
//                                   uart_sendChar('o');
//                                   uart_sendChar('b');
//                                   uart_sendChar('j');
//                                   uart_sendChar('\n');
//                                   uart_sendChar('\r');
//                                   lcd_clear();
//                                   //save object
//                                   objectList[objectCount].degree = (objectEndDegree + objectStartDegree )/ 2;
//                //                   cyBOT_Scan(objectList[objectCount].degree, &tempscan);
//                //                   objectList[objectCount].distance = tempscan.sound_dist;
//                                   objectList[objectCount].distance = scan.sound_dist;
//                                   objectList[objectCount].linearWidth = abs(2*((sin((objectEndDegree - objectStartDegree)/2))*objectList[objectCount].distance));
//                                   objectList[objectCount].width = objectEndDegree-objectStartDegree;
//
//                                   objectCount++;
//                         //      }
//                           }
//
//                       }
//
//                       previousScan = scan.IR_raw_val;
//                       previousPingScan = scan.sound_dist;
//
//
//                       uart_sendChar('\n');
//                       uart_sendChar('\r');
//                   }
//
//                   uart_sendChar('O');
//                   uart_sendChar('b');
//                   uart_sendChar('j');
//                   uart_sendChar(' ');
//                   uart_sendChar(' ');
//                   uart_sendChar(' ');
//                   uart_sendChar(' ');
//                   uart_sendChar('A');
//                   uart_sendChar('n');
//                   uart_sendChar('g');
//                   uart_sendChar(' ');
//                   uart_sendChar(' ');
//                   uart_sendChar(' ');
//                   uart_sendChar(' ');
//                   uart_sendChar('D');
//                   uart_sendChar('i');
//                   uart_sendChar('s');
//                   uart_sendChar('t');
//                   uart_sendChar(' ');
//                   uart_sendChar(' ');
//                   uart_sendChar(' ');
//                   uart_sendChar(' ');
//                   uart_sendChar('W');
//                   uart_sendChar('i');
//                   uart_sendChar('d');
//                   uart_sendChar('t');
//                   uart_sendChar('h');
//                   uart_sendChar(' ');
//                   uart_sendChar(' ');
//                   uart_sendChar(' ');
//                   uart_sendChar(' ');
//                   uart_sendChar('L');
//                   uart_sendChar('W');
//                   uart_sendChar('i');
//                   uart_sendChar('d');
//                   uart_sendChar('t');
//                   uart_sendChar('h');
//                   uart_sendChar('\n');
//                   uart_sendChar('\r');
//                   for(i = 0; i < objectCount; i ++){
//                       uart_sendChar(i + 48);
//                       uart_sendChar(' ');
//                       uart_sendChar(' ');
//                       uart_sendChar(' ');
//                       uart_sendChar(' ');
//                       sprintf(angle, " %d", objectList[i].degree);
//                       sprintf(distance, " %d", objectList[i].distance);
//                       sprintf(width, " %d", objectList[i].width);
//                       sprintf(linearWidth, " %d", objectList[i].linearWidth);
//                       uart_sendChar(angle[0]);
//                       uart_sendChar(angle[1]);
//                       uart_sendChar(angle[2]);
//                       uart_sendChar(angle[3]);
//                       uart_sendChar(' ');
//                       uart_sendChar(' ');
//                       uart_sendChar(' ');
//                       uart_sendChar(' ');
//                       uart_sendChar(distance[0]);
//                       uart_sendChar(distance[1]);
//                       uart_sendChar(distance[2]);
//                       uart_sendChar(distance[3]);
//                       uart_sendChar(' ');
//                       uart_sendChar(' ');
//                       uart_sendChar(' ');
//                       uart_sendChar(' ');
//                       uart_sendChar(width[0]);
//                       uart_sendChar(width[1]);
//                       uart_sendChar(width[2]);
//                       uart_sendChar(width[3]);
//                       uart_sendChar(' ');
//                       uart_sendChar(' ');
//                       uart_sendChar(' ');
//                       uart_sendChar(' ');
//                       uart_sendChar(linearWidth[0]);
//                       uart_sendChar(linearWidth[1]);
//                       uart_sendChar(linearWidth[2]);
//                       uart_sendChar(linearWidth[3]);
//                       uart_sendChar('\n');
//                       uart_sendChar('\r');
//
//                   }
//
//
//                   int shortestWidth = objectList[0].width;
//                   int shortestObjectIndex = 0;
//                   for(i = 0; i < objectCount; i ++){
//
//
//                       if(objectList[i].width < shortestWidth){
//                           shortestWidth = objectList[i].width;
//                           shortestObjectIndex = i;
//                       }
//                   }
//
//                   timer_waitMillis(500);
//                   cyBOT_Scan(objectList[shortestObjectIndex].degree, &tempscan);
//                   objectList[shortestObjectIndex].distance = tempscan.sound_dist;
//                   timer_waitMillis(200);
//
//                   uart_sendChar('\n');
//                   uart_sendChar('\r');
//                   sprintf(angle, " %d", objectList[shortestObjectIndex].degree);
//                   uart_sendChar(angle[0]);
//                   uart_sendChar(angle[1]);
//                   uart_sendChar(angle[2]);
//                   uart_sendChar(angle[3]);
//
//                   readVal = '0';
//                  readVal = uart_receive();
//                  if(readVal == 'h'){
//
//                      if(objectList[shortestObjectIndex].degree > 90){
//                          //turn counter clockwise
//                               turn_cclockwise(sensor_data, (objectList[shortestObjectIndex].degree - 90)*2.66666667); // debug: index out of bounds. ran, got index 20
//                               move_forward(sensor_data, objectList[shortestObjectIndex].distance*4.5);
//
//
//                      }
//                      else{
//                          //turn clockwise
//                          turn_clockwise(sensor_data, (90-objectList[shortestObjectIndex].degree)*2.66666667);
//                          move_forward(sensor_data, objectList[shortestObjectIndex].distance*4.5);
//
//                      }
//                  }
//               }
//
//               if(toggle == 1){
//                   readVal = uart_receive();
//                   uart_sendChar(readVal);
//                   if(readVal == 'w'){
//                       move_forward(sensor_data, 100);
//                   }
//                   else if(readVal == 's'){
//                       move_backwards(sensor_data, 100);
//                   }
//                   else if(readVal == 'a'){
//                       turn_cclockwise(sensor_data, 25);
//                   }
//                   else if(readVal == 'd'){
//                       turn_clockwise(sensor_data, 25);
//                   }
//                   else if(readVal == 'm'){
//                       for(deg = 0; deg <= 180; deg += 2){
//                           if((char)(UART1_DR_R & 0xFF) == 't'){
//                               for( i = 0; i < 20; i ++){
//                                   uart_sendChar('-');
//                               }
//                               uart_sendChar('\n');
//                               uart_sendChar('\r');
//                               toggle = 1;
//                               break;
//                           }
//                           cyBOT_Scan(deg, &scan);
//                           lcd_clear();
//
//
//                           sprintf(scanval, "%d", (scan.IR_raw_val+previousScan)/2);
//
//
//                           sprintf(pingScan, "%f", (scan.sound_dist+previousPingScan)/2);
//
//                           sprintf(degre, "%d", deg);
//                           for(i = 0; i< 3; i++){
//                               uart_sendChar(degre[i]);
//                           }
//                           uart_sendChar(',');
//                           uart_sendChar(' ');
//                           for(i = 0; i< 5; i++){
//                               uart_sendChar(scanval[i]);
//                           }
//                           uart_sendChar(',');
//                           uart_sendChar(' ');
//                           for(i = 0; i< 5; i++){
//                               uart_sendChar(pingScan[i]);
//                           }
//
//                           float Stock = pow( ((scan.IR_raw_val+previousScan)/2.0), -1.626);
//                           float Ham = 4000000 * Stock;
//
//                           float calculatedIRVAL = 10000000 * pow(scan.IR_raw_val, -1.867);
//                           float calculatedPREVIOUSVAL = 10000000 * pow(previousScan, -1.867);
//
//                           sprintf(calculatedDistance, "%f", calculatedIRVAL);
//                           uart_sendChar(',');
//                           uart_sendChar(' ');
//                           for(i = 0; i< 5; i++){
//                               uart_sendChar(calculatedDistance[i]);
//
//                           }
//
//
//
//                           if(calculatedIRVAL - calculatedPREVIOUSVAL < -5){
//                                       //Start object
//                                       objectStartDegree = deg;
//                                       uart_sendChar('\n');
//                                       uart_sendChar('\r');
//                                       uart_sendChar('s');
//                                       lcd_putc('s');
//                                   }
//                           if(calculatedPREVIOUSVAL - calculatedIRVAL < -5){
//                               //end object
//                               objectEndDegree = deg;
//
//                               if(objectEndDegree-objectStartDegree > 3 ){
//                              //     if(((objectEndDegree+objectStartDegree)/2) > (objectList[objectCount--].degree + 3)){
//                                       //object is valid
//                                       uart_sendChar('\n');
//                                       uart_sendChar('\r');
//                                       uart_sendChar('o');
//                                       uart_sendChar('b');
//                                       uart_sendChar('j');
//                                       uart_sendChar('\n');
//                                       uart_sendChar('\r');
//                                       lcd_clear();
//                                       //save object
//                                       objectList[objectCount].degree = (objectEndDegree + objectStartDegree )/ 2;
//                    //                   cyBOT_Scan(objectList[objectCount].degree, &tempscan);
//                    //                   objectList[objectCount].distance = tempscan.sound_dist;
//                                       objectList[objectCount].distance = scan.sound_dist;
//                                       objectList[objectCount].linearWidth = abs(2*((sin((objectEndDegree - objectStartDegree)/2))*objectList[objectCount].distance));
//                                       objectList[objectCount].width = objectEndDegree-objectStartDegree;
//
//                                       objectCount++;
//                             //      }
//                               }
//
//                           }
//
//                           previousScan = scan.IR_raw_val;
//                           previousPingScan = scan.sound_dist;
//
//
//                           uart_sendChar('\n');
//                           uart_sendChar('\r');
//                       }
//
//                       uart_sendChar('O');
//                       uart_sendChar('b');
//                       uart_sendChar('j');
//                       uart_sendChar(' ');
//                       uart_sendChar(' ');
//                       uart_sendChar(' ');
//                       uart_sendChar(' ');
//                       uart_sendChar('A');
//                       uart_sendChar('n');
//                       uart_sendChar('g');
//                       uart_sendChar(' ');
//                       uart_sendChar(' ');
//                       uart_sendChar(' ');
//                       uart_sendChar(' ');
//                       uart_sendChar('D');
//                       uart_sendChar('i');
//                       uart_sendChar('s');
//                       uart_sendChar('t');
//                       uart_sendChar(' ');
//                       uart_sendChar(' ');
//                       uart_sendChar(' ');
//                       uart_sendChar(' ');
//                       uart_sendChar('W');
//                       uart_sendChar('i');
//                       uart_sendChar('d');
//                       uart_sendChar('t');
//                       uart_sendChar('h');
//                       uart_sendChar(' ');
//                       uart_sendChar(' ');
//                       uart_sendChar(' ');
//                       uart_sendChar(' ');
//                       uart_sendChar('L');
//                       uart_sendChar('W');
//                       uart_sendChar('i');
//                       uart_sendChar('d');
//                       uart_sendChar('t');
//                       uart_sendChar('h');
//                       uart_sendChar('\n');
//                       uart_sendChar('\r');
//                       for(i = 0; i < objectCount; i ++){
//                           uart_sendChar(i);
//                           uart_sendChar(' ');
//                           uart_sendChar(' ');
//                           uart_sendChar(' ');
//                           uart_sendChar(' ');
//                           sprintf(angle, " %d", objectList[i].degree);
//                           sprintf(distance, " %d", objectList[i].distance);
//                           sprintf(width, " %d", objectList[i].width);
//                           sprintf(linearWidth, " %d", objectList[i].linearWidth);
//                           uart_sendChar(angle[0]);
//                           uart_sendChar(angle[1]);
//                           uart_sendChar(angle[2]);
//                           uart_sendChar(angle[3]);
//                           uart_sendChar(' ');
//                           uart_sendChar(' ');
//                           uart_sendChar(' ');
//                           uart_sendChar(' ');
//                           uart_sendChar(distance[0]);
//                           uart_sendChar(distance[1]);
//                           uart_sendChar(distance[2]);
//                           uart_sendChar(distance[3]);
//                           uart_sendChar(' ');
//                           uart_sendChar(' ');
//                           uart_sendChar(' ');
//                           uart_sendChar(' ');
//                           uart_sendChar(width[0]);
//                           uart_sendChar(width[1]);
//                           uart_sendChar(width[2]);
//                           uart_sendChar(width[3]);
//                           uart_sendChar(' ');
//                           uart_sendChar(' ');
//                           uart_sendChar(' ');
//                           uart_sendChar(' ');
//                           uart_sendChar(linearWidth[0]);
//                           uart_sendChar(linearWidth[1]);
//                           uart_sendChar(linearWidth[2]);
//                           uart_sendChar(linearWidth[3]);
//                           uart_sendChar('\n');
//                           uart_sendChar('\r');
//
//                       }
//                   }
//
//               }
//            }
//
//           oi_free(sensor_data);
//
//}
