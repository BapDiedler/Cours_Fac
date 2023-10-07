/**
 * \file jouer.h
 * \brief jouer un pion sur un plateau.
 */
 
 #ifndef JOUER_H
#define JOUER_H

int creation_jeu();
/**
* \fn  int creation_jeu()
* \brief crée un pion et le met au centre
 * \return succés de la création
*/
int dpl(int sens);
/**
* \fn  int dpl(int sens);
* \brief déplace le pion le long de la sphère
* \param sens \b int : 1 droite, 2 gauche, 3 haut, 4 bas
 * \return succés de la création
*/
void dpl_micro(int sens, int *val, int max);
/**
* \fn  int dpl_micro(int sens, int *val, int max);
* \brief Fonction auxilière à dpl(). Change val.
* \param sens \b int : 1 droite, 2 gauche, 3 haut, 4 bas
*/
#endif

