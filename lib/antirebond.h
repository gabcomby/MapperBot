// * Nom: Antirebond
// * Nom des auteurs: Gabriel Comby, Maxime Savy, Nicolas Mayr, Charles-Olivier Caron
// * Section: 01
// * Équipe: 1618
// * Description: Cette classe permet de pouvoir appuyer sur le bouton de manière à détecter une seule pression

#ifndef ANTIREBOND_H
#define ANTIREBOND_H
#include <avr/io.h> 

class AntiRebond{
    public:
        AntiRebond(){};
        ~AntiRebond(){};
        bool verificationRebond(void);
};
#endif