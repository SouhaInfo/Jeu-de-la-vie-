// Main de moodle pour verifier les cases
// le main ici est pour la Q6 

#include "grille.hh"
#include <string>
#include <utility> // pour le swap
using namespace std;

int main()
{
    grille courant(40,20);
    grille suivant(40,20); 
    courant.ajouterstructure(structure::oscillateurcroix, 6,7);
    
    string s; 
    while(true)
    {
        courant.afficher();
        cout << "Entree pour continuer, q pour quitter" << endl;
        getline(cin,s); // cin est le clavier et s : string tape

        if (s == "q")
        {
            break;   // sort de la boucle -> return 0
        }
        /*
        getline lit toute une ligne, et une ligne se termine quand on appuie sur Entrée. 
        Tant que tu n’appuies pas sur Entrée, le programme attend.
        */
       courant.evolution(suivant); 
       swap(courant, suivant); // switch comme ca suivant et le nouveau courant
        /*
            - ici le swap marche sans soucis comme un constructeur par copie
            - on utilise la regle de 0 (pas de destrcteur ou constructeur par recopie qui fait la meme chose comme swap) prsk on utilise des vecteurs -> donc la copie est profonde par defaut -> donc pas besoin de re-definir le constructeur par copie manuallement 
        
        */
    }

    return 0; 
}