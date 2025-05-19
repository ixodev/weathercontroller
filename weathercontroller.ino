// Fichier principal
// j'explique juste un peu le code pour qu'on s'y repere mieux

// Inclure les libs requises
#include <LiquidCrystal.h>
#include <DFRobot_BME680_I2C.h>
#include <Wire.h>
#include "weatherdisplay.h"
#include "weatherlib.h"

// Initialiser un ecran à cristaux liquides (LCD) à partir de la classe LiquidCrystal definie dans l'en-tete LiquidCrystal.h
// (LiquidCrystal::LiquidCrystal())
LiquidCrystal lcd(8, 9, 4, 5, 6, 7);
// Meme chose mais pour le petit capteur BME680
DFRobot_BME680_I2C bme(0x76);



static int current_data = _MIN_;


void check_buttons() {
 
  if(bouton_down()){
    current_data--;
    if(current_data < _MIN_) {
      current_data = _MAX_;
    }
  }
 
  else if(bouton_up()){
    current_data++;
    if(current_data > _MAX_){
      current_data = _MIN_;
    }
  }
}

// setup sera appelee automatiquement a chaque demarrage de l'arduino
void setup()
{
  // initialiser le capteur
  // le ! est l'operateur de negation
  if(!bme.begin()) {
  }
  // Initialiser le capteur
  bme.startConvert();
  bme.update();

  // Initialiser l'ecran
  lcd.begin(16, 2);
  reset_ecran(&lcd); // effacer l'ecran
 
  Serial.begin(9600);

}

// loop est appelee a l'infini jusqu'a ce qu'on eteigne l'arduino
void loop()
{
  check_buttons();
 
  String value = String((weatherlib[current_data])(&bme), 3);

  if(weather(&bme) >= 0 && current_data == _WEATHER_) {
    value = "good";
  }
  else if(weather(&bme) < 0 && current_data == _WEATHER_) {
    value = "bad";
  }
  
  affiche_ecran(&lcd, keys[current_data] + "         ", value + " " + units[current_data] + "            ", 5);
  Serial.println(value);
  bme.update();
}
