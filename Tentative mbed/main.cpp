#include "mbed.h"
 
AnalogIn analog_value(A0);
 
Serial pc(SERIAL_TX, SERIAL_RX);

DigitalOut myled(LED1);
 
// Calculate the corresponding acquisition measure for a given value in mV
#define MV(x) ((0xFFF*x)/3300)
#define SIZE_BUF 5000
 
int main() {
    uint16_t buffer[SIZE_BUF];
    uint16_t i=0;
    while(i<SIZE_BUF) {      
        uint16_t meas = analog_value.read_u16(); // Converts and read the analog input value
        buffer[i]=meas;
        i++;
        }
        
        for(int j=0; j<5000; j++)
            pc.printf("%d\n", buffer[j]);
            
        wait(0.2); // 200 ms
        pc.printf("Fin\n");
    }

