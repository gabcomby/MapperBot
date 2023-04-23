// * Nom: TransmissionUART
// * Nom des auteurs: Gabriel Comby, Maxime Savy, Nicolas Mayr, Charles-Olivier Caron
// * Section: 01
// * Équipe: 1618
// * Description: Permet d'envoyer des données (octet par octet) à travers le RS232

#ifndef TRANSMISSIONUART_H
#define TRANSMISSIONUART_H

#include <avr/io.h> 

class TransmissionUART {
public:
    TransmissionUART();
    void transmissionUART ( uint8_t donnee );
    uint8_t receptionUART();
};

#endif
