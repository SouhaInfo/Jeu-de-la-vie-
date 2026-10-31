#include "grille.hh"
#include <iostream>
#include <stdexcept>
using namespace std; 
grille::grille(coordonnee largeur, coordonnee hauteur)
{
    if (hauteur > 0 && largeur > 0)
    {
        this->largeur = largeur; 
        this->hauteur = hauteur; 
        vector<etatcellule> ligne(largeur,etatcellule::mort); // une ligne init = mort (larguer = nombre d'element)
        vector <vector<etatcellule>> G (hauteur,ligne); // hauteur = nombre de vecteurs<etatcellule>
        this->G = G; 
    }

    else 
    {
        cout<<"Erreur"<<endl;
        return;
    }

}

void grille:: vider() // supprime toutes les cellules vivantes de la grille.
{
    vector<vector<etatcellule>>::iterator ite_ligne = this->G.begin(); // premiere ligne
    for(ite_ligne = this->G.begin(); ite_ligne != this->G.end(); ite_ligne++) // ligne par ligne
    {
        for(etatcellule& etat: *ite_ligne) // pour chaque ligne, supprime les cellules vivantes + la & pour modifier la source
        {
            if (etat == etatcellule::vivant) // mort skip
            {
                etat = etatcellule::mort;
            }

        }
    }

}

bool grille:: vivante(coordonnee col, coordonnee ligne) const//  prenant comme paramètre un couple de coordonnées et retournant true si la cellule correspondante est vivante, false sinon.
{
    if(ligne >= 0 && ligne < this->hauteur && col >= 0 && col < this->largeur)
    {
     return this->G.at(ligne).at(col) == etatcellule::vivant;

    }
    else 
    {
        return false; 
    }

}

void grille:: generer(coordonnee col, coordonnee ligne) //  prenant comme paramètre un couple de coordonnées et générant une cellule vivante dans la grille aux coordonnées passées.
{
    if (ligne >= 0 && ligne < this->hauteur && col >= 0 && col < this->largeur)
    {
        this->G.at(ligne).at(col) = etatcellule::vivant;
    }
    else 
    {
        throw out_of_range("indice incorrect");

    }


}

void grille:: tuer(coordonnee col, coordonnee ligne) // tuant la cellule vivante située aux coordonnées passées
{
    if (ligne >= 0 && ligne < this->hauteur && col >= 0 && col < this->largeur)
    {
        this->G.at(ligne).at(col) = etatcellule::mort;
    }
    else 
    {
        throw out_of_range("indice incorrect");

    }

}

void grille::afficher()const //  affichant à l’écran, ligne par ligne, le contenu de la grille : le caractère * sera utilisé pour les cellules vivantes et l’espace pour les cellules mortes.
{
    vector<vector<etatcellule>>::const_iterator ite_ligne = this->G.begin(); // premiere ligne
    for(ite_ligne = this->G.begin(); ite_ligne != this->G.end(); ite_ligne++) // ligne par ligne
    {
        for(const etatcellule etat: *ite_ligne) // pour chaque ligne
        {
            if (etat == etatcellule::vivant) 
            {
                cout<<"*";
            }
            else
            {
                cout<<" ";
            }

        }
        cout<<endl;
    }

}


void grille::ajouterstructure(structure s, coordonnee x, coordonnee y)
{
    if (s == structure::oscillateurligne)
    {
        generer(x, y);
        generer(x + 1, y);
        generer(x + 2, y);
    }
    else if (s == structure::floraison)
    {
        ajouterstructure(structure::oscillateurligne, x + 1, y);     // ligne du haut
        generer(x, y + 1);
        generer(x + 2, y + 1);
        generer(x + 4, y + 1);
        ajouterstructure(structure::oscillateurligne, x + 1, y + 2); // ligne du bas
    }
    else if (s == structure::planeur)
    {
        ajouterstructure(structure::oscillateurligne, x, y);
        generer(x + 2, y + 1);
        generer(x + 1, y + 2);
    }
    else if (s == structure::oscillateurcroix)
    {
        generer(x + 1, y);                                           // haut
        ajouterstructure(structure::oscillateurligne, x, y + 1);     // milieu
        generer(x + 1, y + 2);                                       // bas
    }
}

coordonnee grille::vivantes(coordonnee col, coordonnee ligne) const
{
    int nb = 0;
    // up 
    for(coordonnee i = col - 1; i<=col+1; i++)
    {
        if (vivante(i,ligne-1))
        {
            nb++;
        }

    }

    // down 

    for(coordonnee i = col - 1; i<=col+1; i++)
    {
        if (vivante(i,ligne+1))
        {
            nb++;
        }

    }


    //sides
    if(vivante(col-1, ligne)) nb++; // gauche

    if(vivante(col+1, ligne)) nb++ ; // droite
    return nb;
}

void grille::evolution(grille& g) const // la grille g : c'est l'etat suivant de la grille this
{
    for(coordonnee ligne = 0; ligne < this->hauteur; ligne++)
    {
        for(coordonnee col = 0; col<this->largeur; col++)
        {
            int nb = vivantes(col,ligne) ;
            if (this->G.at(ligne).at(col) == etatcellule::mort && nb == 3)
            {
                g.generer(col,ligne); 
            }
            else if (this->G.at(ligne).at(col) == etatcellule::vivant && (nb == 0 || nb == 1 || nb >=4))
            {
                g.tuer(col,ligne); 
            }
            else if (this->G.at(ligne).at(col) == etatcellule::vivant && (nb == 3 || nb == 2))
            {
                g.generer(col,ligne);
            }
            else 
            {
                g.tuer(col,ligne);
            }

        }

    }

}