#include <iostream>
using namespace std;

/* on importe la classe olcConsoleGameEngine*/
#include "../olcConsoleGameEngine.h"

/*on crée une classe Example qui hérite publiquement de olcConsoleGameEngine*/
class Example : public olcConsoleGameEngine 
{
/*on ajoute un constructeur*/
public:
    Example() 
    {}
    /*on remplace par notre propre fonction de creation d'utilisateur
      fonction virtual(redefinition de la fonction) qui retourne un boolean
      si return false : quitte l'application*/
    virtual bool OnUserCreate()
    {
        return true;
    }
    /*fonction qui va update l'utilisateur avec le temps ecoulé F*/
    virtual bool OnUserUpdate(float fElapsedTime)
    {
        return true;
    }
};

int main() {
    /*on initialise la classe Example par l'instance demo*/
    Example demo;
    /*on applique la methode ConstructConsole(largeur-array, longueur-array, largeur-objet, longueur-objet)*/
    demo.ConstructConsole(160, 100, 8, 8);
    /*on demarre le thread qui executera le moteur du jeu*/
    demo.Start();
    return 0;
}