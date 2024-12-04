/***********************************************************************************************
    projet robocup 2024
    module afficheur
    mjc fablab atelier codage 2023 2024
    https://tutorial45.com/mcp2515-arduino-project-can-arduino/
    https://github.com/sandeepmistry/arduino-CAN/tree/master
    https://github.com/Jorgen-VikingGod/LEDMatrix
    https://electroniqueamateur.blogspot.com/2021/03/ecrire-des-nombres-sur-une-matrice-de.html
    https://electroniqueamateur.blogspot.com/2020/05/matrice-de-leds-rgb-16-x-16-ws2812b-et.html
    https://electroniqueamateur.blogspot.com/2021/02/esp8266-et-esp32-controle-dune-matrice.html
    https://www.instructables.com/16x16-RGB-LED-Panel-Arduino-Projects/

*************************************************************************************************/

//=============================
// inclusion des bibliothèques
//=============================
#include <CAN.h>           // pour la bibliothèque CAN
#include <SPI.h>           // bus spi
#include "variables.h"     // fichier variables
#include <avr/pgmspace.h>  // pour utiliser la memoire flash et augmenter la memoire de travail
#include <FastLED.h>       // https://github.com/FastLED/FastLED
//#include <LEDMatrix.h>  // https://github.com/Jorgen-VikingGod/LEDMatrix


CRGB leds[NUM_LEDS];  // creation d'un objet leds avec la bibliotheque fastled

CRGB laCouleur = CRGB::Black;
//cLEDMatrix<MATRIX_WIDTH, MATRIX_HEIGHT, MATRIX_TYPE> leds;

// tableau representant la matrice de leds multicolores Noir Red Green Blue Yellow Fuchsia
const char tableau[NUM_LIGNE][NUM_COLONNE] PROGMEM = {
  //  0    1    2    3    4    5    6    7    8    9    10   11   12   13   14   15
  { 'N', 'N', 'N', 'N', 'N', 'N', 'N', 'N', 'N', 'N', 'N', 'N', 'N', 'N', 'N', 'N' },  // 15
  { 'N', 'V', 'V', 'N', 'N', 'N', 'N', 'N', 'N', 'N', 'N', 'N', 'N', 'N', 'N', 'N' },  // 14
  { 'V', 'N', 'N', 'N', 'N', 'N', 'N', 'N', 'N', 'N', 'N', 'N', 'N', 'N', 'N', 'N' },  // 13
  { 'V', 'N', 'N', 'N', 'N', 'N', 'N', 'N', 'N', 'N', 'N', 'N', 'N', 'N', 'N', 'N' },  // 12
  { 'V', 'N', 'N', 'N', 'V', 'N', 'V', 'N', 'N', 'N', 'N', 'N', 'N', 'N', 'N', 'N' },  // 11
  { 'V', 'N', 'N', 'N', 'V', 'N', 'V', 'N', 'V', 'V', 'V', 'N', 'N', 'N', 'N', 'N' },  // 10
  { 'V', 'N', 'N', 'N', 'V', 'N', 'V', 'N', 'V', 'N', 'V', 'N', 'N', 'N', 'N', 'N' },  // 9
  { 'N', 'V', 'V', 'N', 'V', 'N', 'V', 'N', 'V', 'N', 'V', 'N', 'N', 'N', 'N', 'N' },  // 7
  { 'N', 'N', 'N', 'N', 'N', 'V', 'N', 'N', 'V', 'V', 'N', 'N', 'N', 'V', 'V', 'N' },  // 8
  { 'N', 'N', 'N', 'N', 'N', 'N', 'N', 'N', 'V', 'N', 'V', 'N', 'V', 'N', 'N', 'V' },  // 6
  { 'N', 'N', 'N', 'N', 'N', 'N', 'N', 'N', 'V', 'N', 'V', 'N', 'V', 'N', 'N', 'V' },  // 5
  { 'N', 'N', 'N', 'N', 'N', 'N', 'N', 'N', 'V', 'V', 'V', 'N', 'V', 'N', 'N', 'V' },  // 4
  { 'N', 'N', 'N', 'N', 'N', 'N', 'N', 'N', 'N', 'N', 'N', 'N', 'V', 'N', 'N', 'V' },  // 3
  { 'N', 'N', 'N', 'N', 'N', 'N', 'N', 'N', 'N', 'N', 'N', 'N', 'N', 'V', 'V', 'N' },  // 2
  { 'N', 'N', 'N', 'N', 'N', 'N', 'N', 'N', 'N', 'N', 'N', 'N', 'N', 'N', 'N', 'N' },  // 1
  { 'N', 'N', 'N', 'N', 'N', 'N', 'N', 'N', 'N', 'N', 'N', 'N', 'N', 'N', 'N', 'N' }   // 0
};

// tableau representant la matrice de leds multicolores Noir Red Green Blue Yellow Fuchsia
const char tableau1[NUM_LIGNE][NUM_COLONNE] PROGMEM = {
  //  0    1    2    3    4    5    6    7    8    9    10   11   12   13   14   15
  { 'N', 'N', 'N', 'N', 'N', 'N', 'N', 'N', 'N', 'N', 'N', 'N', 'N', 'N', 'N', 'N' },  // 15
  { 'N', 'N', 'N', 'N', 'N', 'N', 'N', 'N', 'N', 'N', 'N', 'N', 'N', 'N', 'N', 'N' },  // 14
  { 'N', 'N', 'N', 'N', 'N', 'N', 'N', 'N', 'N', 'N', 'N', 'V', 'V', 'V', 'N', 'N' },  // 13
  { 'N', 'N', 'N', 'N', 'N', 'N', 'N', 'N', 'N', 'N', 'N', 'N', 'V', 'N', 'N', 'N' },  // 12
  { 'N', 'V', 'V', 'V', 'V', 'N', 'N', 'V', 'V', 'N', 'N', 'N', 'V', 'N', 'N', 'N' },  // 11
  { 'N', 'V', 'N', 'N', 'V', 'N', 'V', 'N', 'N', 'V', 'N', 'N', 'V', 'N', 'N', 'N' },  // 10
  { 'N', 'V', 'N', 'N', 'V', 'N', 'V', 'N', 'N', 'V', 'N', 'N', 'V', 'N', 'N', 'N' },  // 9
  { 'N', 'V', 'V', 'V', 'V', 'N', 'V', 'N', 'N', 'V', 'N', 'N', 'V', 'N', 'N', 'N' },  // 8
  { 'N', 'V', 'V', 'V', 'N', 'N', 'N', 'V', 'V', 'N', 'N', 'N', 'N', 'N', 'N', 'N' },  // 7
  { 'N', 'V', 'N', 'N', 'V', 'N', 'N', 'N', 'N', 'N', 'N', 'N', 'N', 'N', 'N', 'N' },  // 6
  { 'N', 'V', 'N', 'N', 'V', 'N', 'N', 'N', 'N', 'N', 'N', 'N', 'N', 'N', 'N', 'N' },  // 5
  { 'N', 'V', 'V', 'V', 'V', 'N', 'N', 'N', 'N', 'N', 'N', 'N', 'N', 'N', 'N', 'N' },  // 4
  { 'N', 'N', 'N', 'N', 'N', 'N', 'N', 'N', 'N', 'N', 'N', 'N', 'N', 'N', 'N', 'N' },  // 3
  { 'N', 'N', 'N', 'N', 'N', 'N', 'N', 'N', 'N', 'N', 'N', 'N', 'N', 'N', 'N', 'N' },  // 2
  { 'N', 'N', 'N', 'N', 'N', 'N', 'N', 'N', 'N', 'N', 'N', 'N', 'N', 'N', 'N', 'N' },  // 1
  { 'N', 'N', 'N', 'N', 'N', 'N', 'N', 'N', 'N', 'N', 'N', 'N', 'N', 'N', 'N', 'N' }   // 0
};

//==================================
//  CAN reception suite interruption
//==================================
void onReceive(int packetSize) {
  while (CAN.available()) {
    caractere = (char)CAN.read();  // lecture du bus can dans la variable caractere
    id = CAN.packetId();           // id du message can  dans la variable id
  }
}

//====================
// allumage d'une led
//====================
void allumageLed(int i, int y, CRGB laCouleur) {

  int num;
  if ((i % 2) == 1) {
    num = 255 - (i * 16) - 15 + y;  // ligne pair
  } else {
    num = 255 - (i * 16) - y;  // ligne impair
  }

  leds[num] = laCouleur;
  delay(1);
  FastLED.show();
}

//======
// setup
//======
void setup() {

  if (debug) {
    Serial.begin(9600);
    while (!Serial)
      ;
    Serial.println("Demarrage de l'afficheur");
  }

  FastLED.addLeds<CHIPSET, DATA_PIN_ARDUINO, COLOR_ORDER >(leds, NUM_LEDS);  // GRB ordering is typical
  FastLED.setBrightness(10);                                                 // Number 0-255
  FastLED.clear(true);

  // effacement du tableau de leds
  for (int i = 0; i < NUM_LEDS; i++) {
    leds[i] = CRGB::Black;
    delay(1);
    FastLED.show();
  }


  /*
  // start the CAN bus at 125 kbps
  if (!CAN.begin(125E3)) {
    if (debug) {
      Serial.println("Starting CAN failed!");
    }
    while (1)
      ;
  } else {
    if (debug) {
      Serial.println("Starting CAN");
    }
  }

  // register the receive callback - interruption des l'arrivee d'un message sur le bus can
  CAN.onReceive(onReceive);
  */
}

//======
// loop
//======
void loop() {

  delay(500);
  // affichage tableau
  for (int i = 0; i < NUM_LIGNE; i++) {
    for (int y = 0; y < NUM_COLONNE; y++) {
      char valCouleur = pgm_read_byte_near(&tableau[i][y]);
      //Serial.print("valeur de la couleur = : ");
      //Serial.println (valCouleur);
      if (valCouleur == 'N') {
        laCouleur = CRGB::Black;
        allumageLed(i, y, laCouleur);
      } else if (valCouleur == 'R') {
        laCouleur = CRGB::Red;
        allumageLed(i, y, laCouleur);
      } else if (valCouleur == 'G') {
        laCouleur = CRGB::Green;
        allumageLed(i, y, laCouleur);
      } else if (valCouleur == 'B') {
        laCouleur = CRGB::Blue;
        allumageLed(i, y, laCouleur);
      } else if (valCouleur == 'Y') {
        laCouleur = CRGB::Yellow;
        allumageLed(i, y, laCouleur);
      } else if (valCouleur == 'V') {
        laCouleur = CRGB::Red;
        allumageLed(i, y, laCouleur);
      } else if (valCouleur == 'W') {
        laCouleur = CRGB::White;
        allumageLed(i, y, laCouleur);

      } else {
        laCouleur = CRGB::Black;
        allumageLed(i, y, laCouleur);
      }
    }
  }

  delay(500);

  // affichage tableau1
  for (int i = 0; i < NUM_LIGNE; i++) {
    for (int y = 0; y < NUM_COLONNE; y++) {
      char valCouleur = pgm_read_byte_near(&tableau1[i][y]);
      //Serial.print("valeur de la couleur = : ");
      //Serial.println (valCouleur);
      if (valCouleur == 'N') {
        laCouleur = CRGB::Black;
        allumageLed(i, y, laCouleur);
      } else if (valCouleur == 'R') {
        laCouleur = CRGB::Red;
        allumageLed(i, y, laCouleur);
      } else if (valCouleur == 'G') {
        laCouleur = CRGB::Green;
        allumageLed(i, y, laCouleur);
      } else if (valCouleur == 'B') {
        laCouleur = CRGB::Blue;
        allumageLed(i, y, laCouleur);
      } else if (valCouleur == 'Y') {
        laCouleur = CRGB::Yellow;
        allumageLed(i, y, laCouleur);
      } else if (valCouleur == 'V') {
        laCouleur = CRGB::Violet;
        allumageLed(i, y, laCouleur);
      } else if (valCouleur == 'W') {
        laCouleur = CRGB::White;
        allumageLed(i, y, laCouleur);

      } else {
        laCouleur = CRGB::Black;
        allumageLed(i, y, laCouleur);
      }
    }
  }
}
