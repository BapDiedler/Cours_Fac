typedef struct arbre_s * arbre_t;

struct arbre_s{
    int racine;
    int hauteur;
    arbre_t feuille_gauche;
    arbre_t feuille_droite;
};

/*CONSTRUCTEUR*/

//constructeur vide
arbre_t ConsVide();
//constructeur classic
arbre_t Cons(int val, arbre_t arb_gauche, arbre_t arb_droit);

/*AUTRE*/
arbre_t FG(arbre_t arb);

arbre_t FD(arbre_t arb);

int Racine(arbre_t arb);

int Hauteur(arbre_t arb);

void liberer(arbre_t arb);

int est_vide(arbre_t arb);

void ModifFG(arbre_t arb, arbre_t new_FG);

void ModifFD(arbre_t arb, arbre_t new_FD);

void ModifRacine(arbre_t arb, int val);

void ModifHauteur(arbre_t arb, int h);

int factEquilibre(arbre_t arb);

void rotationGauche(arbre_t arb);

void rotationDroite(arbre_t arb);

void miseAJourHauteur(arbre_t arb);

/*FONCTION*/
int estEquilibre(arbre_t arb);

void Equilibrage(arbre_t arb);

void insert(arbre_t* arb, int val);

int supprimerMax(arbre_t *arb);

void supprimer(arbre_t *arb, int val);

int max(arbre_t arb);

int min(arbre_t arb);

arbre_t copie(arbre_t arb);

int taille(arbre_t arb);

int exists(arbre_t arb, int val);

/*FONCTION D'AFFICHAGE*/
void graphical_print_link(arbre_t a, int depth, int trace[]);

void graphical_print(arbre_t a, int depth);