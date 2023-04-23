// * Nom: Projet
// * Nom des auteurs: Gabriel Comby, Maxime Savy, Nicolas Mayr, Charles-Olivier Caron
// * Section: 01
// * Équipe: 1618
// * Description:

#define F_CPU 8000000UL
#define DELAI_DEBOUNCE 30 

#include "can.h"
#include "transmissionUART.h"
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include "sensor.h"
#include "robot.h"
#include "generateurSVG.h"

volatile bool boutonAppuye = false;
bool selection1Faite = false;
bool selection2Faite = false;
bool selection3Faite = false;
bool orientationHaut;
bool placeBien = false;
bool deplacementFini = false;
int compteurTour = 0;
Directions direc = Directions::NORD;

Robot robot;
GenerateurSVG generateur = GenerateurSVG();
Mode mode;
TransmissionUART transmetteur = TransmissionUART();

 ISR(INT1_vect)
{
    _delay_ms(DELAI_DEBOUNCE);
    boutonAppuye = !boutonAppuye;
    EIFR |= (1 << INTF1);
}

int main() {
    robot.initialisation();
    while (!selection1Faite){
        if (boutonAppuye){
            mode = Mode::TRANSMISSION;
            selection1Faite = true;
            
        }
        if (robot.boutonCarte()){
            mode = Mode::DETECTION;
            selection1Faite = true;
        }
    }
    _delay_ms(500);
    switch(mode){
        case Mode::DETECTION:
        while (!selection2Faite){
            robot.allumerLumiere(EtatLumiere::AMBRE);
            if (robot.boutonCarte()){
                orientationHaut = true;
                selection2Faite = true;
            }
            if(boutonAppuye){
                orientationHaut = false;
                selection2Faite = true;
            }
        }
        robot.allumerLumiere(EtatLumiere::ETEINT);
            switch (orientationHaut){
                case false:
                    robot.directionRouge = true;
                    robot.allumerLumiere(EtatLumiere::ROUGE);
                    _delay_ms(2000);
                    robot.allumerLumiere(EtatLumiere::ETEINT);
                    _delay_ms(500);
                    robot.trouverPoteau();
                    break;
                case true:
                    robot.directionRouge = false;
                    robot.allumerLumiere(EtatLumiere::VERT);
                    _delay_ms(2000);
                    robot.allumerLumiere(EtatLumiere::ETEINT);
                    _delay_ms(500);
                    robot.trouverPoteau();
                    robot.allumerLumiere(EtatLumiere::ETEINT);
                    robot.jouerNote(45);
                    _delay_ms(2000);
                    robot.arreterSon();
                    while(true){
                        robot.del2HzRouge();
                    }
                    break;
            
        }
            break;
        case Mode::TRANSMISSION:
            robot.allumerLumiere(EtatLumiere::VERT);
            generateur.lireNPoteau();
            for(uint8_t i = 0; i < generateur.nPoteauMem; i++) {
                generateur.calculerPositionPoteau();
                generateur.ajouterPoint();
            }
            generateur.generer();
            break;
    }

}  