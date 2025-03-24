// Fichier principal
// j'explique juste un peu le code pour qu'on s'y repere mieux

// Inclure les libs requises
#include <LiquidCrystal.h>
#include <DFRobot_BME680_I2C.h>
#include <Wire.h>
#include <string.h>
#include <stdlib.h>

// Initialiser un ecran à cristaux liquides (LCD) à partir de la classe LiquidCrystal definie dans l'en-tete LiquidCrystal.h
// (LiquidCrystal::LiquidCrystal())
LiquidCrystal lcd(8, 9, 4, 5, 6, 7);
// Meme chose mais pour le petit capteur BME680
DFRobot_BME680_I2C bme(0x76);


// void signifie que cette fonction ne retourne rien
void reset_ecran ()
{
  lcd.setCursor(0, 0); // On commence à écrire à la position (0; 0) sachant que l'origine est en haut a gauche
  lcd.print("                "); // ecrire un string vide sur l'ecran (donc ca efface)
  lcd.setCursor(0, 1); // Meme chose mais pour la ligne du bas
  lcd.print("                ");
}

void affiche_ecran (String ligne1, String ligne2, int duree)
{
  lcd.setCursor(0, 0); lcd.print(ligne1);
  lcd.setCursor(0, 1); lcd.print(ligne2);
  delay(duree); // attendre <duree> millisecondes
  reset_ecran();
}

void affiche_ecran_blink (String ligne1, String ligne2, int duree)
{

  /*
  
  une boucle for s'ecrit de telle maniere:

  for(int x = 0; x < i; ++x) {
    ...
  }
  ++x veut dire: x = x + 1
  on peut aussi ecrire x++ mais alors la variable x va etre incrementee apres avoir ete evaluee

  ce qui est dans le scope du for va etre execute pour x allant de 0 a i - 1

  mais je peux aussi ecrire
  for(int x = 0; x < i; x += 2) {

  }

  x sera a chaque fois incremente de 2 et non de 1

  */

  for (int i=0 ; i<(duree/1000+1) ; i++)
    {
      lcd.setCursor(0, 0); lcd.print(ligne1);
      lcd.setCursor(0, 1); lcd.print(ligne2);
      delay(600);
      reset_ecran();   
      delay(400); // attendre 400 ms
    }
}


// bool car bouton_select retourne un boolean (cad soit vrai soit faux)
bool bouton_select()
{
  // analogRead() lit un signal analogique sur le port analogique 0
  // pour lire un signal digital il y a digitalRead()
  // pour ecrire on peut faire analogWrite() (et digitalWrite() pour un signal digital)
  // "&&" veut dire : si les deux conditions sont vraies alors faire ca
  // pour le OU ca sera "||"

  if ((analogRead(A0) >= 600) && (analogRead(A0)< 850))
    { return true; }
  else
    { return false; }
}

// idem
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



// setup sera appelee automatiquement a chaque demarrage de l'arduino
void setup()
{
  // initialiser le capteur
  // le ! est l'operateur de negation
  if(!bme.begin()) {
    // ca crash
    exit(0); // Terminer le programme + Code de retour
  }
  // Initialiser le capteur
  bme.startConvert();
  bme.update();

  // Initialiser l'ecran
  lcd.begin(16, 2); 
  reset_ecran(); // effacer l'ecran

  affiche_ecran("Bonjour", "Bonjour", 20);
}

// POUR TOUT CE QUI EST DE LA JUSQU'A LA FONCTION LOOP NE VOUS EN OCCUPEZ PAS C'EST PAS IMPORTANT
#define C_ARRAY_SIZE(arr) sizeof(arr) / sizeof(*arr)
#define FLOAT_CONVERT_STRING_SIZE 5

char* convertFloatToStringPrec(float x) {

  char buffer[FLOAT_STRING_SIZE];
  // malloc(sizeof(char) * (uint8_t)FLOATSTRINGSIZE) = pas une bonne idee

  snprintf(buffer, 5, "%f");
  return buffer;

}

// loop est appelee a l'infini jusqu'a ce qu'on eteigne l'arduino
void loop()
{
  float temperature = bme.readTemperature()/100; // Lire la temperature et la convertir en deg Celsius (/100)
  float pressure = bme.readPressure()/100; // Meme chose mais pour la P
  String s = String(temperature, 4); // creer un string et mettre la temperature dedans (4 chiffres apres la virgule)
  String s2 = String(pressure, 4); // idem
  
  // ca vous connaissez
  lcd.setCursor(0, 0);
  lcd.print(s + " deg C");
  lcd.setCursor(0, 1);
  lcd.print(s2 + " hPa");
  delay(50);
  reset_ecran();
  
}
