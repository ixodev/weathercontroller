////////////////////
// BIBLIOTHEQUES  //
////////////////////

#include <LiquidCrystal.h>
#include <DFRobot_BME680_I2C.h>
#include <Wire.h>
#include <string.h>
#include <stdlib.h>

LiquidCrystal lcd(8, 9, 4, 5, 6, 7);        // select the pins used on the LCD panel
DFRobot_BME680_I2C bme(0x76);


/////////////////////////
// VARIABLES GENERALES //
/////////////////////////



///////////////////////////////////////
// FONCTIONS POUR GESTION DE L'ECRAN //
///////////////////////////////////////

void reset_ecran ()
{
  lcd.setCursor(0, 0); lcd.print("                ");
  lcd.setCursor(0, 1); lcd.print("                ");
}

void affiche_ecran (String ligne1, String ligne2, int duree)
{
  lcd.setCursor(0, 0); lcd.print(ligne1);
  lcd.setCursor(0, 1); lcd.print(ligne2);
  delay(duree);
  reset_ecran();
}

void affiche_ecran_blink (String ligne1, String ligne2, int duree)
{
  for (int i=0 ; i<(duree/1000+1) ; i++) 
    {
      lcd.setCursor(0, 0); lcd.print(ligne1);
      lcd.setCursor(0, 1); lcd.print(ligne2);
      delay(600);
      reset_ecran();   
      delay(400);
    }
}


////////////////////////////////////////
// FONCTIONS POUR GESTION DES BOUTONS //
////////////////////////////////////////
// Fonctions booléennes

bool bouton_select()
{
  if ((analogRead(A0) >= 600) && (analogRead(A0)< 850))
    { return true; }
  else
    { return false; }
}

bool bouton_left()
{
  if ((analogRead(A0) >= 400) && (analogRead(A0)< 600))
    { return true; }
  else
    { return false; }
}

bool bouton_right()
{
  if ((analogRead(A0) >= 0) && (analogRead(A0)< 50))
    { return true; }
  else
    { return false; }
}

bool bouton_up()
{
  if ((analogRead(A0) >= 50) && (analogRead(A0)< 250))
    { return true; }
  else
    { return false; }
}

bool bouton_down()
{
  if ((analogRead(A0) >= 250) && (analogRead(A0)< 400))
    { return true; }
  else
    { return false; }
}



////////////////////
// FONCTION SETUP //
////////////////////

void setup()
{
  if(!bme.begin()) {}
  bme.startConvert();
  bme.update();
  lcd.begin(16, 2); 
  reset_ecran();
  affiche_ecran("Bonjour", "Bonjour", 20);
}


///////////////////
// FONCTION LOOP //
///////////////////

#define C_ARRAY_SIZE(arr) sizeof(arr) / sizeof(*arr)
#define FLOAT_STRING_SIZE 5

char* convertFloatToString(float x) {

  char buffer[FLOAT_STRING_SIZE];
  // malloc(sizeof(char) * (uint8_t)FLOATSTRINGSIZE) = pas une bonne idée n'essaie pas

  snprintf(buffer, 5, "%f");
  return buffer;

}

void loop()
{
  float temperature = bme.readTemperature()/100;
  float pressure = bme.readPressure()/100;
  String s = String(temperature, 4);
  String s2 = String(pressure, 4);
  lcd.setCursor(0, 0);
  lcd.print(s + " deg C");
  lcd.setCursor(0, 1);
  lcd.print(s2 + " hPa");
  delay(50);
  reset_ecran();
  
}
