#include <avr/io.h>
#include "antirebond.h"
#include <util/delay.h>

//Retourne "true" si le bouton a reellement ete active
bool AntiRebond::verificationRebond(void){
    if (PIND & 0x04){
        _delay_ms(10);
        if (PIND & 0x04){
            return true;
        }
    }
    return false;
}