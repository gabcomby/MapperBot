// * Nom: Minuterie
// * Nom des auteurs: Gabriel Comby, Maxime Savy, Nicolas Mayr, Charles-Olivier Caron
// * Section: 01
// * Équipe: 1618
// * Description: Cette classe permet d'initialiser et d'utiliser une minuterie
 
#ifndef MINUTERIE_H
#define MINUTERIE_H
#include <avr/io.h> 

//Permet de creer une minuterie avec un temps d'expiration specifique
class Minuterie{
    public:
        volatile uint8_t gMinuterieExpiree;
        Minuterie(){};
        ~Minuterie(){};
        void initialisation( void );
        void partirMinuterie( uint16_t duree);
};

#endif
