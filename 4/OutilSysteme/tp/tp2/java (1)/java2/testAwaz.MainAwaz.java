package testAwaz;

import awaz.Awaz;
import awaz.AwazImage;
/**
 * Cette classe est le point de d�part du Tp Awaz
 * @author martine
 * @version Janvier 2018
 */
public class MainAwaz {
    public static void main(String[] args) {
        // Cr�ation d'une m�lodie vide
        Awaz melodie = new Awaz() ;
        melodie.add("Ré");
        melodie.add("Mi");
        System.out.println(melodie.toString());
        //melodie.transposer(2);
        //System.out.println(melodie.toString());

        int i = 0;
        while(i < melodie.nbNotes())
        {
            System.out.print(melodie.ieme(i) + " ");
            i++;
        }
        if(args.length < 1)
            System.out.println("Usage : <nomFichier>");
        else
            melodie.enregistrer(args[0]+".txt");


        AwazImage melodieImg = new AwazImage();
        melodieImg.setMelodie(melodie.toString());
        melodieImg.setTitre("truc");
    }
}
