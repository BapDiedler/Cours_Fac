package testAwaz;

import awaz.Awaz;
import awaz.AwazImage;

/**
 * Cette classe est le point de d part du Tp Awaz
 * @author martine
 * @version Janvier 2018
 */
public class MainAwaz {
    public static void main(String[] args) {
        // Cr ation d'une m lodie vide
        Awaz melodie = new Awaz();
        AwazImage melodieImage = new AwazImage();

        //ajout d'une note
        melodie.add("Do");
        melodie.add("Ré");
        melodie.add("Mi");
        melodie.add("Fa");
        melodie.add("Sol");
        //affichage des notes
        System.out.println(melodie.toString());
        //affichage du nombre de notes
        System.out.println(melodie.nbNotes());
        //transposition des notes
        melodie.transposer(0);

        //suppricion de melodie et création d'une nouvelle melodi
        melodie.nouveau();

        melodie.add("Do");
        melodie.add("Fa");
        melodie.add("Mi");
        System.out.println(melodie.nbNotes());
        for(int i=0;i<melodie.nbNotes();i++){
            System.out.print(melodie.ieme(i)+" ");
        }
        melodie.enregistrer(melodie.getTitre());
        melodie.add("Ré#");
        melodie.add("Do");
        String melodieABC = melodie.toABC();
        melodieImage.setTitre("melodie");
        melodieImage.setMelodie(melodieABC);

    }
}