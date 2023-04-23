#include "generateurSVG.h"
#include <string.h>
#include <stdio.h>

int32_t calculerAireArrondie(PointPoteau pointsBordure[], uint8_t& nPointsBordure) {
    int32_t area = 0;
    uint8_t j = nPointsBordure - 1;
    for (uint8_t i = 0; i < nPointsBordure; i++) {
        area += (pointsBordure[j].posX + pointsBordure[i].posX) * (pointsBordure[j].posY - pointsBordure[i].posY);
        j = i;
    }
    if(area < 0) {area *= -1;}
    area/=2;
    const int32_t ppi = 11;
    area/=(ppi*ppi);
    int32_t arrondi = int32_t(area);
    return arrondi;
}

void GenerateurSVG::afficherBackground() {
    sprintf(ligne.stringAsTab, "<svg width=\"100%%\" height=\"100%%\" xmlns=\"http://www.w3.org/2000/svg\" viewBox=\"0 0 1152 576\">\n");
    ligne.tailleLigne = 92;
    calculerCRC();
    envoyerAuPC();

    sprintf(ligne.stringAsTab, "<rect x=\"96\" y=\"48\" width=\"960\" height=\"480\" stroke=\"black\" stroke-width=\"1\" fill=\"white\"/>\n");
    ligne.tailleLigne = 93;
    calculerCRC();
    envoyerAuPC();

    sprintf(ligne.stringAsTab, "<text x=\"96\" y=\"36\" font-family=\"arial\" font-size=\"20\" fill=\"blue\">Section 01 - Equipe 1618 - Robot Alain Goffi</text>\n");
    ligne.tailleLigne = 120;
    calculerCRC();
    envoyerAuPC();
}

void GenerateurSVG::afficherPoints() {
    int yDeBase = 120;
    int posX = 150;
    int posY = yDeBase;
    ligne.tailleLigne = 73;
    for(int i = 1; i < 33; i++) {
        sprintf(ligne.stringAsTab, "<rect x=\"%d\" y=\"%d\" width=\"15\" height=\"15\" style=\"fill:rgb(0,0,0)\" />\n", posX, posY);
        calculerCRC();
        envoyerAuPC();

        if(i%4 == 0) {
            posY = yDeBase;
            posX+=121;
        } else {
            posY+=121;
        }
    }

    sprintf(ligne.stringAsTab, "<rect x=\"150\" y=\"485\" width=\"15\" height=\"15\" style=\"fill:rgb(255,0,0)\" />\n");
    ligne.tailleLigne = 75;
    calculerCRC();
    envoyerAuPC();
}

void GenerateurSVG::afficherPolygone() {
    //Dessine le polygone représentant l'aire selon le nombre de points de côté qu'il y a
    switch(nPointsBordure) {
    case 3:
        sprintf(ligne.stringAsTab, "<polygon points=\"%ld,%ld %ld,%ld %ld,%ld\" style=\"fill:green;stroke:black;stroke-width:1\" />\n", pointsBordure[0].posX,pointsBordure[0].posY,pointsBordure[1].posX,
        pointsBordure[1].posY,pointsBordure[2].posX,pointsBordure[2].posY);
        ligne.tailleLigne = 93;
        break;
    case 4:
        sprintf(ligne.stringAsTab, "<polygon points=\"%ld,%ld %ld,%ld %ld,%ld %ld,%ld\" style=\"fill:green;stroke:black;stroke-width:1\" />\n", pointsBordure[0].posX,pointsBordure[0].posY,pointsBordure[1].posX,
        pointsBordure[1].posY,pointsBordure[2].posX,pointsBordure[2].posY,pointsBordure[3].posX,pointsBordure[3].posY);
        ligne.tailleLigne = 101;
        break;
    case 5:
        sprintf(ligne.stringAsTab, "<polygon points=\"%ld,%ld %ld,%ld %ld,%ld %ld,%ld %ld,%ld\" style=\"fill:green;stroke:black;stroke-width:1\" />\n", pointsBordure[0].posX,pointsBordure[0].posY,pointsBordure[1].posX,
        pointsBordure[1].posY,pointsBordure[2].posX,pointsBordure[2].posY,pointsBordure[3].posX,pointsBordure[3].posY,pointsBordure[4].posX,pointsBordure[4].posY);
        ligne.tailleLigne = 109;
        break;
    case 6:
        sprintf(ligne.stringAsTab, "<polygon points=\"%ld,%ld %ld,%ld %ld,%ld %ld,%ld %ld,%ld %ld,%ld\" style=\"fill:green;stroke:black;stroke-width:1\" />\n", pointsBordure[0].posX,pointsBordure[0].posY,pointsBordure[1].posX,
        pointsBordure[1].posY,pointsBordure[2].posX,pointsBordure[2].posY,pointsBordure[3].posX,pointsBordure[3].posY,pointsBordure[4].posX,pointsBordure[4].posY, pointsBordure[5].posX,pointsBordure[5].posY);
        ligne.tailleLigne = 117;
        break;
    case 7:
        sprintf(ligne.stringAsTab, "<polygon points=\"%ld,%ld %ld,%ld %ld,%ld %ld,%ld %ld,%ld %ld,%ld %ld,%ld\" style=\"fill:green;stroke:black;stroke-width:1\" />\n", pointsBordure[0].posX,pointsBordure[0].posY,pointsBordure[1].posX,
        pointsBordure[1].posY,pointsBordure[2].posX,pointsBordure[2].posY,pointsBordure[3].posX,pointsBordure[3].posY,pointsBordure[4].posX,pointsBordure[4].posY, pointsBordure[5].posX,pointsBordure[5].posY,
        pointsBordure[6].posX,pointsBordure[6].posY);
        ligne.tailleLigne = 125;
        break;
    case 8:
        sprintf(ligne.stringAsTab, "<polygon points=\"%ld,%ld %ld,%ld %ld,%ld %ld,%ld %ld,%ld %ld,%ld %ld,%ld %ld,%ld\" style=\"fill:green;stroke:black;stroke-width:1\" />\n", pointsBordure[0].posX,pointsBordure[0].posY,pointsBordure[1].posX,
        pointsBordure[1].posY,pointsBordure[2].posX,pointsBordure[2].posY,pointsBordure[3].posX,pointsBordure[3].posY,pointsBordure[4].posX,pointsBordure[4].posY, pointsBordure[5].posX,pointsBordure[5].posY,
        pointsBordure[6].posX,pointsBordure[6].posY, pointsBordure[7].posX,pointsBordure[7].posY);
        ligne.tailleLigne = 133;
        break;
    }
    calculerCRC();
    envoyerAuPC();

    int32_t aire = calculerAireArrondie(pointsBordure, nPointsBordure);
    if(aire >= 100) {
        sprintf(ligne.stringAsTab, "<text x=\"96\" y=\"570\" font-family=\"arial\" font-size=\"30\" fill=\"red\">Aire: %ld pouces carres</text>\n",
            aire);
        ligne.tailleLigne = 100;
    } else if (aire >= 10) {
        sprintf(ligne.stringAsTab, "<text x=\"96\" y=\"570\" font-family=\"arial\" font-size=\"30\" fill=\"red\">Aire: %ld pouces carres</text>\n",
            aire);
        ligne.tailleLigne = 99;
    } else {
        sprintf(ligne.stringAsTab, "<text x=\"96\" y=\"570\" font-family=\"arial\" font-size=\"30\" fill=\"red\">Aire: %ld pouces carres</text>\n",
            aire);
        ligne.tailleLigne = 98;
    }
    calculerCRC();
    envoyerAuPC();
}

void GenerateurSVG::afficherPoteaux() {
    for(uint8_t i = 0; i < nPoteau; i++) {
        sprintf(ligne.stringAsTab, "<circle cx=\"%ld\" cy=\"%ld\" r=\"15\" stroke=\"black\" stroke-width=\"2\" fill=\"rgb(128,128,128)\" />\n", tabDePoteau[i].posX, tabDePoteau[i].posY);
        ligne.tailleLigne = 93;
        calculerCRC();
        envoyerAuPC();
    }
}

void GenerateurSVG::envoyerAuPC() {
    for ( int j=0; j < ligne.tailleLigne; j++ ) {
        if(ligne.stringAsTab[j] != 0) {
            transmetteur.transmissionUART ( ligne.stringAsTab[j] );
        }
    }
}

//Fonction utilisée dans l'algorithme Jarvis March pour calculer le hull
int orientation(PointPoteau& p, PointPoteau& q, PointPoteau& r, int32_t& val)
{
    val = (q.posY - p.posY) * (r.posX - q.posX) -
          (q.posX - p.posX) * (r.posY - q.posY);
    if (val == 0) return 0;  // collinear
    return (val > 0)? 1: 2; // clock or counterclock wise
}

//Fonction qui implémente l'algorithme Jarvis March pour calculer le hull (source: https://www.geeksforgeeks.org/convex-hull-using-jarvis-algorithm-or-wrapping/)
void GenerateurSVG::convexHull()
{
    //S'il y a moins de 3 poteaux, on ne peut pas générer un convex hull, donc on sort
    if (nPoteau < 3) return;
  
    int32_t val;
    uint16_t l = 0;
    for (uint8_t i = 1; i < nPoteau; i++)
        if (tabDePoteau[i].posX < tabDePoteau[l].posX) {
            l = i;
        }
  
    uint16_t p = l, q;
    nPointsBordure = 0;
    do
    {
        pointsBordure[nPointsBordure] = tabDePoteau[p];
        nPointsBordure++;
        q = (p+1)%nPoteau;
        for (uint8_t i = 0; i < nPoteau; i++)
        {
           if (orientation(tabDePoteau[p], tabDePoteau[i], tabDePoteau[q], val) == 2) {
               q = i;
           }
        }
        p = q;
    } while (p != l);
}

void GenerateurSVG::envoyerOctet(uint8_t octet) {
    transmetteur.transmissionUART ( octet );
}

void GenerateurSVG::envoyerCRC() {
    crc = crc ^ 0xFFFFFFFF;
    sprintf(ligne.stringAsTab, "%08lx", (uint32_t)crc);
    ligne.tailleLigne = 8;
    envoyerAuPC();
}

void GenerateurSVG::generer() {
    //Envoie l'octet signalant le début du code SVG  
    envoyerOctet(signalDebut);

    //Envoie le code SVG
    afficherBackground();
    convexHull();
    afficherPolygone();
    afficherPoints();
    afficherPoteaux();

    //Envoie l'argument final du fichier SVG
    sprintf(ligne.stringAsTab, "</svg>\n");
    ligne.tailleLigne = 8;
    calculerCRC();
    envoyerAuPC();

    //Envoie l'octet indiquant la fin du code SVG
    envoyerOctet(signalMilieu);

    //Envoie le CRC32
    //uint32_t crc32 = (uint32_t) crc;
    envoyerCRC();

    //Envoie l'octet indiquant la fin de la transmission
    envoyerOctet(signalFin);
}

//Ajoute un point (poteau) au dessin et à la liste des poteaux détectés
void GenerateurSVG::ajouterPoint() {
    PointPoteau point (coordX, coordY);
    tabDePoteau[nPoteau] = point;
    nPoteau++;
}

void GenerateurSVG::calculerCRC() {
    for(int i = 0; i < ligne.tailleLigne; i++) {
        if(ligne.stringAsTab[i] != 0) {
            crc ^= ligne.stringAsTab[i];
            for (int j = 0; j < 8; j++)
            {
                if (crc & 1)
                    crc = (crc >> 1) ^ 0xEDB88320;
                else
                    crc = (crc >> 1);
            }
        }
    }
}

void GenerateurSVG::calculerPositionPoteau() {
    memoire.lecture(adresseLecture, &deltaX);
    _delay_ms(10);
    switch(deltaX) {
        case 0:
            break;
        case 1:
            coordX += 121;
            break;
        case 2:
            coordX += (2*121);
            break;
        case 3:
            coordX -= (121);
            break;
        case 4:
            coordX -= (2*121);
            break;
    }
    adresseLecture++;
    memoire.lecture(adresseLecture, &deltaY);
    _delay_ms(10);
    switch(deltaY) {
        case 0:
            break;
        case 1:
            coordY += 121;
            break;
        case 2:
            coordY += (2*121);
            break;
        case 3:
            coordY -= (121);
            break;
        case 4:
            coordY -= (2*121);
            break;
    }
    adresseLecture++;
}

void GenerateurSVG::lireNPoteau() {
    memoire.lecture(0, &nPoteauMem);
}