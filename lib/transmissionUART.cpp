#include <avr/io.h>
#include "transmissionUART.h"
#include "memoire_24.h"

TransmissionUART::TransmissionUART() {
    UBRR0H = 0;
    UBRR0L = 0xCF;
//Permettre la réception et la transmission par le UART0
    UCSR0A = 0;
    UCSR0B |= (1 << RXEN0) | (1 << TXEN0);
//Format des trames: 8 bits, 1 stop bits, sans parité
    UCSR0C = (UCSZ11 << 1) | (UCSZ10 << 1) | (0 << UCSZ12);
}

void TransmissionUART::transmissionUART ( uint8_t donnee ) {
    while (!(UCSR0A & (1 << UDRE0))){}
    UDR0 = donnee;
}

uint8_t TransmissionUART::receptionUART() {
    while(!(UCSR0A&(1 << RXC0))){}
    return UDR0; //UDR0 reçoit le BUFFER
}

