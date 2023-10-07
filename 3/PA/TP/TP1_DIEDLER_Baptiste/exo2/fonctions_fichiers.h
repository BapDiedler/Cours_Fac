#ifndef FONCTIONS_FICHIERS_H
#define FONCTIONS_FICHIERS_H

/**
 * allouer un tableau de caractères de
 * taille n × m, où n et m sont les nombres de lignes et de colonnes, et initialiser
 * ce tableau avec le caractère espace (’ ’)
 * @param int n
 * @param int m
 * @return char**
*/
char** allouer_tab_2D(int n, int m);

/**
 * libérer un tableau à deux
 * dimensions, de n lignes.
 * @param char** tab
 * @param int n
*/
void desallouer_tab_2D(char** tab, int n);

/**
 * afficher le contenu d’un
 * tableau de caractères de taille n × m.
 * @param  char** tab
 * @param int n
 * @param int m
*/
void afficher_tab_2D(char** tab, int n, int m);

/**
 * compter le nombre max de lignes (nbLig) et de colonnes (nbCol) dans le fichier
 * dont le nom est nomFichier.
 * @param const char* nomFichier
 * @param int* nbLig
 * @param int* nbCol
*/
void taille_fichier(const char* nomFichier, int* nbLig, int* nbCol);

/**
 * lire un fichier dont le nom
 * est nomFichier, et retourner le tableau qui contient les caractères du fichier
 * tel qu’une ligne du tableau correspond à une ligne du fichier.
 * @param const char* nomFichier
 * @return char** 
*/
char** lire_fichier(const char* nomFichier);

/**
 * Retourner un nouveau tableau, dans lequel toutes les occurrences du
 * caractère ancien sont remplacées par le caractère nouveau
 * @param char** tab
 * @param int n
 * @param int m
 * @param char ancien
 * @param char nouveau
 * @return char**
*/
char** modifier_caractere(char** tab, int n, int m, char ancien, char nouveau);

/**
 * Écrire le tableau tab de taille n × m dans un fichier dont le nom est nomFichier
 * @param const char* nomFichier
 * @param char** tab
 * @param int n
 * @param int m
 * @return void
*/
void ecrire_fichier(const char* nomFichier, char** tab, int n, int m);

#endif