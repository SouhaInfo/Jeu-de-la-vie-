# Jeu de la vie (C++)

Implémentation du jeu de la vie de Conway en C++, réalisée dans le cadre du TP 2 de POO2 (L3 Informatique).

## Principe

La grille contient des cellules vivantes ou mortes. À chaque génération :

- une cellule morte avec exactement 3 voisines vivantes naît ;
- une cellule vivante avec 2 ou 3 voisines vivantes survit ;
- une cellule vivante avec 0 ou 1 voisine meurt d'isolement ;
- une cellule vivante avec 4 voisines ou plus meurt d'étouffement.

Les cases hors de la grille sont considérées comme mortes.

## Fichiers

| Fichier | Rôle |
|---|---|
| `grille.hh` | déclaration de la classe `grille` et des types `etatcellule`, `structure`, `coordonnee` |
| `grille.cc` | implémentation des méthodes |
| `main.cc` | tests unitaires Catch2 (fournis) |
| `main_texte.cc` | programme principal en mode texte (question 6) |
| `CMakeLists.txt` | configuration de la compilation |

## Classe `grille`

- `grille(largeur, hauteur)` : crée une grille vide
- `vider()` : tue toutes les cellules
- `vivante(x, y)` : indique si une cellule est vivante
- `generer(x, y)` / `tuer(x, y)` : rend une cellule vivante / morte
- `afficher()` : affiche la grille (`*` = vivante, espace = morte)
- `ajouterstructure(s, x, y)` : ajoute une structure à partir du point (x, y)
- `vivantes(x, y)` : compte les voisines vivantes d'une cellule
- `evolution(resultat)` : calcule la génération suivante dans `resultat`

Structures disponibles : `oscillateurligne`, `floraison`, `planeur`, `oscillateurcroix`.

Les données sont stockées dans un `std::vector<std::vector<etatcellule>>`. La classe n'a ni constructeur par recopie ni destructeur écrits à la main (règle des 0).

## Compilation

Le projet utilise CMake. Catch2 est téléchargé automatiquement à la configuration (connexion internet nécessaire la première fois).

```bash
cmake -S . -B build
cmake --build build
```

Ou ouvrir `CMakeLists.txt` dans Qt Creator.

## Exécution

Tests unitaires :

```bash
./build/jeu_de_la_vie_test
```

Mode texte : une structure est placée au milieu de la grille. Chaque appui sur Entrée affiche la génération suivante.

```bash
./build/jeu_de_la_vie_texte
```

## À venir

Interface graphique avec la bibliothèque SFML : affichage en continu, ajout de structures et de cellules à la souris, mise en pause.
