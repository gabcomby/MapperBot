#include <avr/io.h>
#include "sensor.h"

uint8_t Sensor::distance (){
    //uint16_t compteur = 0;

    while(true){
        can cann;
        uint8_t dist = cann.lecture(PORTA0) >> 2;
        if (dist >= 0x80)
            return 0x05;
        else if ((0x78>= dist) && (dist > 0x50))
            return 0x01;
        else if ((0x4f>= dist) && (dist > 0x25))
            return 0x02;
        else if ((0x24 >= dist) && (dist > 0x1b))
            return 0x03;
        else if ((0x1a>= dist) && (dist > 0x0e))
            return 0x04;
        else
            return 0x00;
    } 
}

// max =0xbf
// 1 = 10-28 cm
       // 0x50 - 0x7a
// 2 = 29-40 cm
       //0x30 - 0x4f
// 3 = 41-52 cm
       //0x20 - 0x2f
// 4 = 52-80 cm
       //0x17 - 0x1f
// Rien = 0x00 - 0x06
