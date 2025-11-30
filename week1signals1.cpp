#include "mbed.h"

DigitalIn input(BUTTON1);
DigitalOut output(LED1);
int x = input.read(); 
int y = output.read();

int main() {
    while (1) {
        printf("Week 1 Exercise 1");
        printf("Button = %d, LED = %d\n", input.read(), output.read());
        if (input == 1) {
            output = 1;
        }
        else if (input == 0 && output == 1) {
            output = 0;
        }
        else {
            output = 0;
        }
        // MAKE SURE THERE IS ALWAYS A WAIT ON THE SIM OR IT WILL CRASH
        wait_ms(500); 
    }
}
