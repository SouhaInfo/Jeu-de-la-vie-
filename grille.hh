#ifndef GRILLE_HH
#define GRILLE_HH
#include<iostream>
#include<vector>


enum class etatcellule
{
 vivant, mort
};

enum class structure{
oscillateurligne , floraison , planeur , oscillateurcroix 

};

using coordonnee = int; 
class grille
{
    private:
    coordonnee largeur; 
    coordonnee hauteur; 
    std::vector< std::vector<etatcellule>>  G; 

    public:
    grille(coordonnee largeur, coordonnee hauteur); 
    void vider(); // supprime toutes les cellules vivantes de la grille.
    bool vivante(coordonnee col, coordonnee ligne)const; //  prenant comme paramètre un couple de coordonnées et retournant true si la cellule correspondante est vivante, false sinon.
    void generer(coordonnee x, coordonnee y); //  prenant comme paramètre un couple de coordonnées et générant une cellule vivante dans la grille aux coordonnées passées.
    void tuer(coordonnee x, coordonnee y); // tuant la cellule vivante située aux coordonnées passées
    void afficher()const; //  affichant à l’écran, ligne par ligne, le contenu de la grille : le caractère * sera utilisé pour les cellules vivantes et l’espace pour les cellules mortes.
    void ajouterstructure(structure s, coordonnee x, coordonnee y);
    coordonnee vivantes(coordonnee x, coordonnee y) const; 
    void evolution(grille& g) const; 
};

#endif