package cartes;

import java.util.ArrayList;
import java.util.Random;

public class FabriqueCartes {
    
    private static final FabriqueCartes instance = new FabriqueCartes();
    private PaquetDeCartes paquet;

    public static final FabriqueCartes getInstance(){
        return instance;
    }

    private FabriqueCartes(){
        this.paquet = new PaquetDeCartes();
    }

    public PaquetDeCartes getPaquetVide(){
        paquet = new PaquetDeCartes();
        return paquet;
    }

    public PaquetDeCartes getPaquet1Vert(){
        paquet = new PaquetDeCartes();
        Carte carte = new Carte(1, Couleur.VERT);
        paquet.ajouter(carte);
        return paquet;
    }

    public PaquetDeCartes getPaquet5Vert(){
        paquet = new PaquetDeCartes();
        Carte carte1 = new Carte(2, Couleur.VERT);
        Carte carte2 = new Carte(1, Couleur.VERT);
        Carte carte3 = new Carte(1, Couleur.VERT);
        Carte carte4 = new Carte(1, Couleur.VERT);
        Carte carte5 = new Carte(1, Couleur.VERT);
        paquet.ajouter(carte1,carte2,carte3,carte4,carte5);
        return paquet;
    }

    public PaquetDeCartes getPaquet32(){
        paquet = new PaquetDeCartes();
        Random rand = new Random();
        Couleur[] colors = new Couleur[]{Couleur.BLEU,Couleur.VERT,Couleur.JAUNE,Couleur.ROUGE};
        int val = 0;
        int valColor = 0;
        Couleur col;
        for(int i=0; i<32; i++){
            val = rand.nextInt(8);
            valColor = rand.nextInt(4);
            col = colors[valColor];
            Carte carte = new Carte(val+1, col);
            paquet.ajouter(carte);
        }
        return paquet;
    }
}
