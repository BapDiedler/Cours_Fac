package cartes.tests;

import cartes.PaquetDeCartes;
import cartes.Carte;
import cartes.Couleur;
import cartes.FabriqueCartes;

public class TestPaquetDeCartes {

    public static void testGetNombreDeCartes(){
        FabriqueCartes fabrique = FabriqueCartes.getInstance();
        PaquetDeCartes paquet = fabrique.getPaquetVide();
        assert(paquet.getNombreDeCartes()==0):"le nombre de cartes n'est pas le bon";
        paquet = fabrique.getPaquet1Vert();
        assert(paquet.getNombreDeCartes()==1):"le nombre de cartes n'est pas le bon";
        paquet = fabrique.getPaquet5Vert();
        assert(paquet.getNombreDeCartes()==5):"le nombre de cartes n'est pas le bon";
    }

    public static void testAjouterCartes(){
        FabriqueCartes fabrique = FabriqueCartes.getInstance();
        PaquetDeCartes paquet = fabrique.getPaquetVide(); 
        Carte carte = new Carte(2, Couleur.BLEU);
        paquet.ajouter(carte);
        assert(paquet.getNombreDeCartes()==1):"le nombre de cartes n'est pas le bon";
    }

    public static void testAjouterPaquet(){
        FabriqueCartes fabrique = FabriqueCartes.getInstance();
        PaquetDeCartes paquet = fabrique.getPaquetVide(); 
        PaquetDeCartes tmp = fabrique.getPaquet5Vert();
        paquet.ajouter(tmp);
        assert(paquet.getNombreDeCartes()==5):"le nombre de cartes n'est pas le bon";
    }

    public static void testEstVideVrai(){
        FabriqueCartes fabrique = FabriqueCartes.getInstance();
        PaquetDeCartes paquet = fabrique.getPaquetVide();
        assert(paquet.estVide()):"la methode est vide ne marche pas";
    }

    public static void testEstVideFaux(){
        FabriqueCartes fabrique = FabriqueCartes.getInstance();
        PaquetDeCartes paquet = fabrique.getPaquet1Vert();
        assert(!paquet.estVide()):"la methode est vide ne marche pas";
    }

    public static void testGetValeur(){
        FabriqueCartes fabrique = FabriqueCartes.getInstance();
        PaquetDeCartes paquet = fabrique.getPaquetVide();
        boolean val = paquet.getValeur()==0;
        assert(val):"le paquet vide n'a pas de valeur";
        paquet = fabrique.getPaquet1Vert();
        val = paquet.getValeur()==1;
        assert(val):"le paquet remplit n'a pas la bonne valeur";
        paquet = fabrique.getPaquet5Vert();
        val = paquet.getValeur()==6;
        assert(val):"le paquet remplit n'a pas la bonne valeur";
    }

    public static void testToString(){
        FabriqueCartes fabrique = FabriqueCartes.getInstance();
        PaquetDeCartes paquet = fabrique.getPaquetVide();
        boolean val = paquet.toString().equals("");
        assert(val):"le toString du paquet vide ne marche pas";
        paquet = fabrique.getPaquet1Vert();
        val = paquet.toString().equals("Carte{valeur=1, couleur=Vert}");
        assert(val):"le toString du paquet rempli ne marche pas";
    }

    public static void testMelanger(){
        FabriqueCartes fabrique = FabriqueCartes.getInstance();
        PaquetDeCartes paquet = fabrique.getPaquetVide();
        int valeurPaquet = paquet.getValeur();
        paquet.melanger();
        int valeurNewPaquet = paquet.getValeur();
        boolean val = valeurNewPaquet==valeurPaquet;
        assert(val):"Erreur avec la fonction mélanger un paquet vide";
        paquet = fabrique.getPaquet1Vert();
        valeurPaquet = paquet.getValeur();
        paquet.melanger();
        valeurNewPaquet = paquet.getValeur();
        val = valeurNewPaquet==valeurPaquet;
        assert(val):"Erreur avec la fonction mélanger un paquet a une carte";
        paquet = fabrique.getPaquet5Vert();
        valeurPaquet = paquet.getValeur();
        paquet.melanger();
        valeurNewPaquet = paquet.getValeur();
        val = valeurNewPaquet==valeurPaquet;
        assert(val):"Erreur avec la fonction mélanger un paquet a 5 cartes";
    }

    public static void testRetourner(){
        FabriqueCartes fabrique = FabriqueCartes.getInstance();
        PaquetDeCartes paquet = fabrique.getPaquetVide();
        paquet.retourner();
        boolean val = paquet.toString().equals("");
        assert(val):"Erreur avec la fonction retourner un paquet vide";
        paquet = fabrique.getPaquet1Vert();
        paquet.retourner();
        val = paquet.toString().equals("Carte{valeur=1, couleur=Vert}");
        assert(val):"Erreur avac la fonction retourner avec une carte";
        paquet = fabrique.getPaquet5Vert();
        paquet.retourner();
        val = paquet.toString().equals("Carte{valeur=1, couleur=Vert}Carte{valeur=1, couleur=Vert}Carte{valeur=1, couleur=Vert}Carte{valeur=1, couleur=Vert}Carte{valeur=2, couleur=Vert}");
        assert(val):"Erreur avac la fonction retourner avec 5 cartes";
    }

    public static void testGetSommet(){
        FabriqueCartes fabrique = FabriqueCartes.getInstance();
        PaquetDeCartes paquet = fabrique.getPaquet1Vert(); 
        Carte c1 = paquet.getSommet();
        paquet.retourner();
        Carte c2 = paquet.getSommet();
        boolean val = c1.equals(c2);
        assert(val):"il y a une erreur pour le sommet d'un paquet de 1 carte";
        paquet = fabrique.getPaquet5Vert(); 
        c1 = paquet.getSommet();
        paquet.retourner();
        c2 = paquet.getSommet();
        val = c1.equals(c2);
        assert(!val):"il y a une erreur pour le sommet d'un paquet de 5 cartes";
    }

    public static void main(String[] args){
        testGetNombreDeCartes();
        testAjouterCartes();
        testAjouterPaquet();
        testEstVideVrai();
        testEstVideFaux();
        testGetValeur();
        testToString();
        testMelanger();
        testRetourner();
        testGetSommet();
    }
}
