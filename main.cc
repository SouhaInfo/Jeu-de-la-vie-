#include "grille.hh"

#include <catch2/catch_test_macros.hpp>

#include <initializer_list>
#include <iostream>
#include <utility>
#include <sstream>
#include <string>

namespace {

void verifier_cellules(const grille& g,
	const std::initializer_list<std::pair<coordonnee, coordonnee>>& vivantes,
	coordonnee largeur, coordonnee hauteur) {
	for (coordonnee y = 0; y < hauteur; ++y)
		for (coordonnee x = 0; x < largeur; ++x) {
			bool attendue = false;
			for (const auto& cellule : vivantes)
				if (cellule.first == x && cellule.second == y)
					attendue = true;
			CHECK(g.vivante(x, y) == attendue);
		}
}

void generer_cellules(grille& g,
	const std::initializer_list<std::pair<coordonnee, coordonnee>>& cellules) {
	for (const auto& cellule : cellules)
		g.generer(cellule.first, cellule.second);
}

} // namespace

TEST_CASE("Q1 - une grille est construite vide", "[q1]") {
	grille g(4, 3);

	verifier_cellules(g, { }, 4, 3);
}

TEST_CASE("Q2 - vider supprime toutes les cellules vivantes", "[q2]") {
	grille g(5, 4);
	generer_cellules(g, { { 0, 0 }, { 2, 1 }, { 4, 3 } });

	CHECK(g.vivante(0, 0));
	CHECK(g.vivante(2, 1));
	CHECK(g.vivante(4, 3));

	g.vider();
	verifier_cellules(g, { }, 5, 4);

	// La méthode doit aussi être sans effet lorsqu'elle est appelée plusieurs fois.
	g.vider();
	verifier_cellules(g, { }, 5, 4);
}

TEST_CASE("Q2 - generer et tuer modifient une cellule", "[q2]") {
	grille g(3, 2);

	CHECK_FALSE(g.vivante(1, 0));
	g.generer(1, 0);
	CHECK(g.vivante(1, 0));

	// Generer une cellule déjà vivante ne change pas son état.
	g.generer(1, 0);
	CHECK(g.vivante(1, 0));

	g.tuer(1, 0);
	CHECK_FALSE(g.vivante(1, 0));

	// Tuer une cellule déjà morte ne change pas son état.
	g.tuer(1, 0);
	CHECK_FALSE(g.vivante(1, 0));
}

TEST_CASE("Q3 - ajouter une ligne oscillante", "[q3]") {
	grille g(7, 5);
	g.ajouterstructure(structure::oscillateurligne, 2, 3);

	verifier_cellules(g, { { 2, 3 }, { 3, 3 }, { 4, 3 } }, 7, 5);
}

TEST_CASE("Q3 - ajouter une floraison", "[q3]") {
	grille g(7, 5);
	g.ajouterstructure(structure::floraison, 1, 1);

	verifier_cellules(g,
		{ { 2, 1 }, { 3, 1 }, { 4, 1 },
			{ 1, 2 }, { 3, 2 }, { 5, 2 },
			{ 2, 3 }, { 3, 3 }, { 4, 3 } },
		7, 5);
	CHECK_FALSE(g.vivante(1, 1));
}

TEST_CASE("Q3 - ajouter un planeur", "[q3]") {
	grille g(7, 5);
	g.ajouterstructure(structure::planeur, 2, 1);

	verifier_cellules(g, { { 2, 1 }, { 3, 1 }, { 4, 1 }, { 4, 2 }, { 3, 3 } }, 7, 5);
}

TEST_CASE("Q3 - ajouter un oscillateur en croix", "[q3]") {
	grille g(7, 5);
	g.ajouterstructure(structure::oscillateurcroix, 2, 1);

	verifier_cellules(g, { { 3, 1 }, { 2, 2 }, { 3, 2 }, { 4, 2 }, { 3, 3 } }, 7, 5);
}

TEST_CASE("Q3 - ajouter une structure conserve les cellules déjà vivantes", "[q3]") {
	grille g(6, 4);
	g.generer(0, 0);
	g.generer(3, 1); // cellule qui ne fait pas partie de la ligne ajoutée
	g.ajouterstructure(structure::oscillateurligne, 1, 1);

	CHECK(g.vivante(0, 0));
	CHECK(g.vivante(3, 1));
	verifier_cellules(g, { { 0, 0 }, { 1, 1 }, { 2, 1 }, { 3, 1 } }, 6, 4);
}

TEST_CASE("Q4 - vivantes compte les huit voisines", "[q4]") {
	grille g(5, 5);
	generer_cellules(g, { { 1, 1 }, { 2, 1 }, { 3, 1 }, { 1, 2 }, { 3, 2 }, { 1, 3 }, { 2, 3 }, { 3, 3 } });

	CHECK(g.vivantes(2, 2) == 8);
	CHECK(g.vivantes(2, 1) == 4);
	CHECK(g.vivantes(0, 0) == 1);
}

TEST_CASE("Q4 - vivantes traite correctement les bords et les coins", "[q4]") {
	grille g(3, 3);
	generer_cellules(g, { { 0, 0 }, { 1, 0 }, { 0, 1 }, { 2, 2 } });

	CHECK(g.vivantes(0, 0) == 2); // seules (1,0) et (0,1) sont voisines
	CHECK(g.vivantes(2, 0) == 1); // (1,0) est la seule voisine dans la grille
	CHECK(g.vivantes(0, 2) == 1); // (0,1) est la seule voisine dans la grille
	CHECK(g.vivantes(1, 1) == 4);
	CHECK(g.vivantes(2, 2) == 0);
}

TEST_CASE("Q5 - evolution applique les règles de naissance et de survie", "[q5]") {
	SECTION("une cellule morte entourée de trois cellules nait") {
		grille depart(3, 3);
		grille resultat(3, 3);
		generer_cellules(depart, { { 0, 1 }, { 1, 0 }, { 2, 1 } });

		depart.evolution(resultat);

		verifier_cellules(resultat, { { 1, 0 }, { 1, 1 } }, 3, 3);
	}

	SECTION("une cellule vivante entourée de deux cellules survit") {
		grille depart(3, 3);
		grille resultat(3, 3);
		generer_cellules(depart, { { 0, 1 }, { 1, 1 }, { 2, 1 } });

		depart.evolution(resultat);

		CHECK(resultat.vivante(1, 1));
	}
}

TEST_CASE("Q5 - evolution tue par isolement et etouffement", "[q5]") {
	grille depart(5, 3);
	grille resultat(5, 3);

	// La cellule (0, 1) est isolée ; (2, 1) a six voisines.
	generer_cellules(depart, { { 0, 1 }, { 2, 1 }, { 2, 0 }, { 2, 2 }, { 3, 0 }, { 3, 1 }, { 3, 2 } });
	depart.evolution(resultat);

	CHECK_FALSE(resultat.vivante(0, 1));
	CHECK_FALSE(resultat.vivante(2, 1));
}

TEST_CASE("Q5 - evolution traite les bords et remplace entièrement le resultat", "[q5]") {
	grille depart(3, 3);
	grille resultat(3, 3);
	generer_cellules(depart, { { 0, 0 }, { 1, 0 }, { 2, 0 } });
	generer_cellules(resultat, { { 0, 2 }, { 1, 2 }, { 2, 2 } }); // on génère des cellules dans result, et ils devaient être écrasés par evolution

	depart.evolution(resultat);

	verifier_cellules(resultat, { { 1, 0 }, { 1, 1 } }, 3, 3);
}

TEST_CASE("Q5 - evolution : enchainement", "[q5]") {
	grille courant(5, 5);
	grille suivant(5, 5);
	courant.ajouterstructure(structure::oscillateurligne, 1, 2);

	courant.evolution(suivant);
	verifier_cellules(suivant, { { 2, 1 }, { 2, 2 }, { 2, 3 } }, 5, 5);

	suivant.evolution(courant);
	verifier_cellules(courant, { { 1, 2 }, { 2, 2 }, { 3, 2 } }, 5, 5);
}
