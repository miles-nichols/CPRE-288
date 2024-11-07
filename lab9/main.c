#include "Timer.h"
#include "lcd.h"
#include "ping.h"


int main(void) {
    timer_init();
    lcd_init();
    ping_init();


    char str[100];

    while(1)
    {

        float pingDist = ping_getDistance();
        //sprintf(str, "%.2f", pingDist);
        //lcd_puts(str);
        timer_waitMillis(500);


    }

}
