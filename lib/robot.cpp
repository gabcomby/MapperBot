#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include "robot.h"

#define DELAI_MEMOIRE 5
uint8_t trouver = 0;
uint8_t distInitiale;
int capte = 0;
int compteur = 0;
bool directionFinale = false;
int delai = 100;
Sensor capteur;
bool gMinuterieExpiree = false;

void Robot::initialisation(void){
        DDRA |= (1 << PORTA0); //Pour sensor
        DDRA &= ~(1 << PORTA0); // Pour sensor 

        DDRA |= (1 << PORTA4)|(1 << PORTA5); //Pour la DEL

        DDRD |= (1 << PD5) | (1 << PD7); //Pour le son

        cli(); //Registres pour la PWM
        DDRB = 0xff; //DDRB en mode sortie
        TCCR0A |= (1 << COM0A1) | (1 << COM0B1)| (1 << WGM00);
        TCCR0B |= (1 << CS01);
        sei();

        cli(); //Registres pour le bouton poussoir
         //DDRD en entree 
        EIMSK |= (1 << INT1); //Bouton poussoir -- Signal interrupt sur INT1 (PD3)
        EICRA |= (1 << ISC10); //Bouton poussoir
        sei();
}

void Robot::moteur(int puissance1, int puissance2, Direction direction)
{
    switch (direction)
    {
    case Direction::AVANT:
        PORTB &= ~(1 << PB1);
        PORTB &= ~(1 << PB2);
        OCR0A = puissance1;
        OCR0B = puissance2;
        break;
    case Direction::ARRIERE:
        PORTB |= (1 << PB1);
        PORTB |= (1 << PB2);
        OCR0A = puissance1;
        OCR0B = puissance2;
        break;
    case Direction::GAUCHE:
        PORTB &= ~(1 << PB2);
        PORTB |= (1 << PB1);
        OCR0A = puissance1;
        OCR0B = puissance2;
        break;
    case Direction::DROITE:
        PORTB |= (1 << PB2);
        PORTB &= ~(1 << PB1);
        OCR0A = puissance1;
        OCR0B = puissance2;
        break;
    case Direction::ARRET:
        PORTB &= ~(1 << PB1);
        PORTB &= ~(1 << PB2);
        OCR0A = 0;
        OCR0B = 0;
        break;
    }
}
void Robot::tournerDroite(int vitesse)
{
    Robot::moteur(vitesse, vitesse,  Direction::DROITE);
    _delay_ms(100);
    Robot::moteur(vitesse, vitesse, Direction::ARRET);
    _delay_ms(100);
}
void Robot::tournerGauche(int vitesse)
{
    Robot::moteur(vitesse, vitesse, Direction::GAUCHE);
    _delay_ms(100);
    Robot::moteur(vitesse, vitesse, Direction::ARRET);
    _delay_ms(100);
}

void Robot::allumerLumiere(EtatLumiere couleur)
{
    switch (couleur)
    {
    case EtatLumiere::ROUGE:
        PORTA |= 1 << PORTA4;
        PORTA &= ~(1 << PORTA5);
        break;
    case EtatLumiere::VERT:
        PORTA |= 1 << PORTA5;
        PORTA &= ~(1 << PORTA4);
        break;
    case EtatLumiere::ETEINT:
        PORTA &= ~(1 << PORTA5);
        PORTA &= ~(1 << PORTA4);
        break;
    case EtatLumiere::AMBRE:
        PORTA |= 1 << PORTA4;
        PORTA &= ~(1 << PORTA5);
        _delay_ms(2.46);
        PORTA |= 1 << PORTA5;
        PORTA &= ~(1 << PORTA4);
        _delay_ms(2);
        break;
    }
}

void Robot::jouerNote(uint8_t indexNote)
{
    double temps_actif = tableauTempsActif_[indexNote - 45];

    double temps = 7812.5 * temps_actif * 0.001;
    OCR2A = temps;
    TCCR2A |= (1 << WGM21) | (1 << COM2A0);
    TCCR2B |= (1 << CS22) ;
}

void Robot::arreterSon(void)
{

    PORTD &= ~(0 << PD5);
    PORTD |= (0 << PD7);

    OCR2A = 0x00;
}
void Robot::partirMinuterie(uint16_t duree)
{
    gMinuterieExpiree = false;
    TCNT1 = 0;
    OCR1A = duree;
    TCCR1A |= (1 << COM1A0);
    TCCR1B |= (1 << WGM12) | (1 << CS12) | (1 << CS10);
    TIMSK1 |= (1 << OCIE1A);
}
bool Robot::boutonCarte(void)
{
    if (PIND & 0x04)
    {
        _delay_ms(15);
        if (PIND & 0x04)
        {
            return true;
        }
    }
    return false;
}

void Robot::del2HzAmbre(void){
    for (int i = 0 ; i < 83; i++){
        Robot::allumerLumiere(EtatLumiere::ROUGE);
        _delay_us(1000);
        Robot::allumerLumiere(EtatLumiere::VERT);
        _delay_us(2000);
    }
    Robot::allumerLumiere(EtatLumiere::ETEINT);
    _delay_ms(250);
}

void Robot::del2HzRouge(void){
    Robot::allumerLumiere(EtatLumiere::ROUGE);
    _delay_ms(250);
    Robot::allumerLumiere(EtatLumiere::ETEINT);
    _delay_ms(250);
    Robot::allumerLumiere(EtatLumiere::ROUGE);
    _delay_ms(250);
    Robot::allumerLumiere(EtatLumiere::ETEINT);
    _delay_ms(250);
}

void Robot::sonDeFin(void){
    Robot::jouerNote(50);
    _delay_ms(300);
    Robot::arreterSon();
    _delay_ms(300);
    Robot::jouerNote(55);
    _delay_ms(300);
    Robot::arreterSon();
    _delay_ms(300);
    Robot::jouerNote(70);
    _delay_ms(300);
    Robot::arreterSon();
}


void Robot::calculerDeltaCoordonnees(uint8_t dist, Directions dir) {
    switch (dir)
    {
    case Directions::NORD:
        if (dist <= 0x02)
        {
            deltaX = 0;
            deltaY = 3;
        } else if(dist > 0x02){
            deltaX = 0;
            deltaY = 4;
        }
        break;

    case Directions::NORD_EST:
        if (dist <= 0x03)
        {
            deltaY = 3;
            deltaX = 1;
        } else if(dist > 0x03){
            deltaY = 4;
            deltaX = 2;
        }
        break;

    case Directions::EST:
        if (dist <= 0x02)
        {
            deltaY = 0;
            deltaX = 1;
        } else if(dist > 0x02){
            deltaY = 0;
            deltaX = 2;
        }
        break;

    case Directions::SUD_EST:
        if (dist <= 0x03)
        {
            deltaY = 1;
            deltaX = 1;
        } else if(dist > 0x03){
            deltaY = 2;
            deltaX = 2;
        }
        break;

    case Directions::SUD:
        if (dist <= 0x02)
        {
            deltaY = 1;
            deltaX = 0;
        } else if(dist > 0x02){
            deltaY = 2;
            deltaX = 0;
        }
        break;

    case Directions::SUD_OUEST:
        if (dist <= 0x03)
        {
            deltaY = 1;
            deltaX = 3;
        } else if(dist > 0x03){
            deltaY = 2;
            deltaX = 4;
        }
        break;

    case Directions::OUEST:
        if (dist <= 0x02)
        {
            deltaY = 0;
            deltaX = 3;
        } else if(dist > 0x02){
            deltaY = 0;
            deltaX = 4;
        }
        break;

    case Directions::NORD_OUEST:
        if (dist <= 0x03)
        {
            deltaY = 3;
            deltaX = 3;
        } else if(dist > 0x03){
            deltaY = 4;
            deltaX = 4;
        }
        break;

    case Directions::FINI:
        deltaY = 0;
        deltaX = 0;
        break;
    }
}

void Robot::ecrireDeltaDansMemoire() {
    memoire.ecriture(adresseEcriture, deltaX);
    _delay_ms(10);
    adresseEcriture++;

    memoire.ecriture(adresseEcriture, deltaY);
    _delay_ms(10);
    adresseEcriture++;
}

void Robot::ecrireDeltaDansTest(uint8_t x, uint8_t y) {
    deltaX = x;
    memoire.ecriture(adresseEcriture, deltaX);
    _delay_ms(10);
    adresseEcriture++;

    deltaY = y;
    memoire.ecriture(adresseEcriture, deltaY);
    _delay_ms(10);
    adresseEcriture++;
}

void Robot::ajouterNbrPoteau() {
    nbrPoteau ++;
    memoire.ecriture(0, nbrPoteau);
    _delay_ms(10);
}

void Robot::afficherMemoirePoint(uint8_t nbrPoint) {
    TransmissionUART transmetteur;
    uint16_t adresse = 1;
    uint8_t donnee;
    while(true) {
        for(uint8_t i = 0; i < nbrPoint; i++) {
            memoire.lecture(adresse, &donnee);
            transmetteur.transmissionUART(donnee);
            _delay_ms(150);
        }
    }
}

void Robot::trouverPoteau(void){
    while (chercherPoteauFini == false)
    {
        trouver = 0;
        capte = 0;
        compteur = 0;
        placeBien = false;
        selection4 = false;

        trouver = capteur.distance();
        while (trouver == 0 && compteur <= 80)
        {
            _delay_ms(300);
            Robot::tournerDroite(180);
            trouver = capteur.distance();
            _delay_ms(5);
            compteur++;
        }

        distInitiale = trouver;

        if ((compteur >= 80) == true) {
            placeBien = true;
            selection4 = true;
        }

        while (placeBien == false){
            capte = capteur.distance();
            if (capte == 0x05 || capte == 0x01){
                placeBien = true;
                Robot::moteur(255, 255, Direction::ARRET);
            }
            else {
                _delay_ms(200);
                Robot::moteur(230, 255,  Direction::AVANT);
                _delay_ms(600);
                Robot::moteur(255, 255, Direction::ARRET);
                _delay_ms(1000);
                trouver = capteur.distance();
                while(trouver == 0) {
                    _delay_ms(30);
                    Robot::tournerDroite(175);
                    trouver = capteur.distance();
                }
            }
        }
        if ((compteur >= 80) == true){
            break;
        }
        Robot::sonDeFin();

        if (directionRouge == true && compteur >= 0 && compteur <= 3){
            Robot::calculerDeltaCoordonnees(distInitiale, Directions::EST);
            Robot::ecrireDeltaDansMemoire();
            Robot::ajouterNbrPoteau();
            _delay_ms(10);
        }
        else if (directionRouge == true && compteur >= 45 && compteur <= 51){
            Robot::calculerDeltaCoordonnees(distInitiale, Directions::NORD);
            Robot::ecrireDeltaDansMemoire();
            Robot::ajouterNbrPoteau();
            _delay_ms(10);
        }
        else if (directionRouge == true && compteur >= 53 && compteur <= 59){
            Robot::calculerDeltaCoordonnees(distInitiale, Directions::NORD_EST);
            Robot::ecrireDeltaDansMemoire();
            Robot::ajouterNbrPoteau();
            _delay_ms(10);
        }
        else if(compteur >= 0 && compteur <= 3) {
            Robot::calculerDeltaCoordonnees(distInitiale, Directions::NORD);
            Robot::ecrireDeltaDansMemoire();
            Robot::ajouterNbrPoteau();
            _delay_ms(10);
        } else if (compteur >= 5 && compteur <= 11) {
            Robot::calculerDeltaCoordonnees(distInitiale, Directions::NORD_EST);
            Robot::ecrireDeltaDansMemoire();
            Robot::ajouterNbrPoteau();
            _delay_ms(10);
        } else if (compteur >= 13 && compteur <= 19) {
            Robot::calculerDeltaCoordonnees(distInitiale, Directions::EST);
            Robot::ecrireDeltaDansMemoire();
            Robot::ajouterNbrPoteau();
            _delay_ms(10);
        } else if (compteur >= 21 && compteur <= 27) {
            Robot::calculerDeltaCoordonnees(distInitiale, Directions::SUD_EST);
            Robot::ecrireDeltaDansMemoire();
            Robot::ajouterNbrPoteau();
            _delay_ms(10);
        } else if (compteur >= 29 && compteur <= 35) {
            Robot::calculerDeltaCoordonnees(distInitiale, Directions::SUD);
            Robot::ecrireDeltaDansMemoire();
            Robot::ajouterNbrPoteau();
            _delay_ms(10);
        } else if (compteur >= 37 && compteur <= 43) {
            Robot::calculerDeltaCoordonnees(distInitiale, Directions::SUD_OUEST);
            Robot::ecrireDeltaDansMemoire();
            Robot::ajouterNbrPoteau();
            _delay_ms(10);
        } else if (compteur >= 45 && compteur <= 51) {
            Robot::calculerDeltaCoordonnees(distInitiale, Directions::OUEST);
            Robot::ecrireDeltaDansMemoire();
            Robot::ajouterNbrPoteau();
            _delay_ms(10);
        } else if (compteur >= 53 && compteur <= 59) {
            Robot::calculerDeltaCoordonnees(distInitiale, Directions::NORD_OUEST);
            Robot::ecrireDeltaDansMemoire();
            Robot::ajouterNbrPoteau();
            _delay_ms(10);
        }
        else if (compteur >= 62 && compteur <= 70) {
            Robot::calculerDeltaCoordonnees(distInitiale, Directions::NORD_OUEST);
            Robot::ecrireDeltaDansMemoire();
            Robot::ajouterNbrPoteau();
            _delay_ms(10);
        
        } else if (compteur >=80) {
            chercherPoteauFini = true;
        }

        while (selection4 == false){
            Robot::del2HzAmbre();
            if ((compteur >= 80) == true){
                selection4 = true;
                break;
            }
            
            if ((boutonCarte()) == true){
                selection4 = true;
            }
        }
    }
}