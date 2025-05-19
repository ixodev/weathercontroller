#include <LiquidCrystal.h>


// void signifie que cette fonction ne retourne rien
void reset_ecran (LiquidCrystal* lcd)
{
  lcd->setCursor(0, 0); // On commence à écrire à la position (0; 0) sachant que l'origine est en haut a gauche
  lcd->print("                "); // ecrire un string vide sur l'ecran (donc ca efface)
  lcd->setCursor(0, 1); // Meme chose mais pour la ligne du bas
  lcd->print("                ");
}

void affiche_ecran (LiquidCrystal* lcd, String ligne1, String ligne2, int duree)
{
  lcd->setCursor(0, 0); lcd->print(ligne1);
  lcd->setCursor(0, 1); lcd->print(ligne2);
  delay(duree); // attendre <duree> millisecondes
  //reset_ecran(lcd);
}

void affiche_ecran_blink (LiquidCrystal* lcd, String ligne1, String ligne2, int duree)
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
      lcd->setCursor(0, 0); lcd->print(ligne1);
      lcd->setCursor(0, 1); lcd->print(ligne2);
      delay(600);
      reset_ecran(lcd);   
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
