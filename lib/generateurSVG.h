// * Nom: GenerateurSVG
// * Nom des auteurs: Gabriel Comby, Maxime Savy, Nicolas Mayr, Charles-Olivier Caron
// * Section: 01
// * Équipe: 1618
// * Description: Permet de lire les points en mémoire, de générer un polygone convexe selon ces derniers et d'envoyer une image SVG par le RS232

#define F_CPU 8000000UL
#ifndef GENSVG_H
#define GENSVG_H
#include <stdint.h>
#include "memoire_24.h"
#include "transmissionUART.h"
#include <util/delay.h>
#include "memoire_24.h"

//Structure représentant un poteau
struct PointPoteau {
    int32_t posX;
    int32_t posY;
    PointPoteau(){};
    PointPoteau(int32_t x, int32_t y) {
        posX = x;
        posY = y;
    }
};

//Structure représentant une ligne de code SVG
struct LigneSVG {
    uint8_t tailleLigne;
    char stringAsTab [160];
    LigneSVG(){};
};

//Objet permettant de générer un code SVG
class GenerateurSVG {
public:
    GenerateurSVG(){};
    ~GenerateurSVG(){};
    void generer();
    void ajouterPoint();
    void calculerPositionPoteau();
    void lireNPoteau();
    uint16_t coordX = 157;
    uint16_t coordY = 492;
    uint8_t nPoteauMem = 0;

private:
    LigneSVG ligne;
    PointPoteau tabDePoteau [8];
    PointPoteau pointsBordure [8];
    TransmissionUART transmetteur = TransmissionUART();
    Memoire24CXXX memoire = Memoire24CXXX();
    uint8_t nPointsBordure = 0;
    uint8_t nPoteau = 0;
    uint64_t crc = 0xFFFFFFFF;
    uint8_t signalDebut = 0x02;
    uint8_t signalMilieu = 0x03;
    uint8_t signalFin = 0x04;
    uint8_t deltaX;
    uint8_t deltaY;
    uint16_t adresseLecture = 1;
    void envoyerAuPC();
    void afficherBackground();
    void afficherPolygone();
    void afficherPoints();
    void afficherPoteaux();
    void convexHull();
    void envoyerOctet(uint8_t octet);
    void calculerCRC();
    void envoyerCRC();
};
#endif