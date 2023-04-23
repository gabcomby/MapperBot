// * Nom: Sensor
// * Nom des auteurs: Gabriel Comby, Maxime Savy, Nicolas Mayr, Charles-Olivier Caron
// * Section: 01
// * Équipe: 1618
// * Description: Permet de lire les données du senseur infrarouge monté à l'avant du robot

#ifndef SENSOR_H
#define SENSOR_H

#include <avr/io.h>
#include "can.h"

class Sensor
{
public:
    Sensor(){
        DDRA |= (1 << PORTA0);
        DDRA &= ~(1 << PORTA0);
    };
    //~Sensor();
    uint8_t distance();
private:
    //can cann;
    //uint8_t dist = cann.lecture(PORTA0) >> 2;
};
#endif