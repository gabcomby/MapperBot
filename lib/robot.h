// * Nom: Robot
// * Nom des auteurs: Gabriel Comby, Maxime Savy, Nicolas Mayr, Charles-Olivier Caron
// * Section: 01
// * Équipe: 1618
// * Description: Classe encapsulant toutes les fonctions matérielles du robot (patron singleton)

#ifndef ROBOT_H
#define ROBOT_H
#include <avr/io.h>
#include <avr/interrupt.h>
#include "memoire_24.h"
#include "sensor.h"
#include "transmissionUART.h"

//extern bool directionRouge;

enum class Direction{
    AVANT,
    ARRIERE,
    DROITE,
    GAUCHE,
    ARRET
};

enum class EtatLumiere {
    ROUGE,
    VERT,
    ETEINT,
    AMBRE,
};

enum class Directions
{
    NORD,
    NORD_EST,
    EST,
    SUD_EST,
    SUD,
    SUD_OUEST,
    OUEST,
    NORD_OUEST,
    FINI
};

enum class Mode{
    DETECTION,
    TRANSMISSION
};

class Robot{
    public:
        Robot() {};
        ~Robot() {};
        bool directionRouge;
        void initialisation(void);
        void moteur(int puissance1, int puissance2, Direction direction );
        void tournerDroite(int vitesse);
        void tournerGauche(int vitesse);
        void allumerLumiere(EtatLumiere couleur);
        void jouerNote(uint8_t indexNote);
        void arreterSon(void);
        bool boutonCarte (void);
        void calculerDeltaCoordonnees(uint8_t distance, Directions dir);
        void ecrireDeltaDansMemoire();
        void ajouterNbrPoteau();
        void ecrireDeltaDansTest(uint8_t x, uint8_t y);
        void trouverPoteau(void);
        void del2HzAmbre(void);
        void del2HzRouge(void);
        void sonDeFin(void);
        void afficherMemoirePoint(uint8_t nbrPoint);
        void partirMinuterie(uint16_t duree);
        uint8_t nbrPoteau = 0;
        uint8_t deltaX = 0;
        uint8_t deltaY = 0;
        uint16_t adresseEcriture = 1;
        uint8_t distInitiale;
        bool directionFinale = false;
        int delai = 100;
        bool deplacementFini = false;
        bool chercherPoteauFini = false;
        uint8_t trouver;
        int capte;
        int compteur;
        bool placeBien = false;
        bool selection4 = false;

    private:
        const double tableauTempsActif_[37]={4.545, 4.290, 4.050, 3.822, 3.608, 3.405, 3.214, 3.034, 2.863, 2.703, 2.551, 2.408, 
            2.273, 2.154, 2.025, 1.911, 1.804, 1.703, 1.607, 1.517, 1.432, 1.351, 1.276, 1.204, 1.136, 1.073, 1.012, 0.956, 0.902, 
            0.851, 0.804, 0.758, 0.716, 0.676, 0.638, 0.602, 0.568};
        Memoire24CXXX memoire;
};
#endif