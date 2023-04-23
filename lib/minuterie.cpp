#include <avr/io.h>
#include <avr/interrupt.h>
#include "minuterie.h"

//Initialise le timer
void Minuterie::initialisation(void)
{
    cli();
    DDRA = 0xff; //Sortie
    DDRD = 0x00; //Entrée
    EIMSK |= (1 << INT0);
    EICRA |= (1 << INT0);
    sei();
}

//Demarre la minuterie
void Minuterie::partirMinuterie ( uint16_t duree ) {
    gMinuterieExpiree = 0;
    TCNT1 = 0;
    OCR1A = duree;
    TCCR1A |= (1 << COM1A0);
    TCCR1B |= (1 << WGM12) | (1 << CS12) | (1 << CS10);
    TCCR1C = 0;
    TIMSK1 = (1 << OCIE1A);
}
