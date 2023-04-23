#include <avr/io.h> 
#include "transmissionUART.h"

#ifdef	DEBUG
    #define DEBUG_CONFIGURE TransmissionUART transmetteur; \
    transmetteur.initialisationUART()
    #define DEBUG_PRINT(str) \
	    for (uint8_t i = 0; i < sizeof(str); i++) { \
		    transmetteur.transmissionUART(str[i]); \
	    }
#else
#define DEBUG_CONFIGURE 0
#define DEBUG_PRINT(str) do {} while (0) 
#endif