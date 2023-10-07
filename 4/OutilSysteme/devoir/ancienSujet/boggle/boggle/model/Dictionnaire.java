package boggle.model;


import java.io.InputStream;
import java.util.ArrayList;
import java.util.Scanner;

public class Dictionnaire {
    private static Dictionnaire instance = new Dictionnaire("/boggle/model/dico.txt") ;
    private ArrayList<String> dico ;

    /**
     * Créer un dictionnaire sur la base d'un fichier texte
     * @param s nom de fichier
     */
    private  Dictionnaire(String s) {
        this.dico = new ArrayList<String>(4000) ;
        InputStream file = getClass().getResourceAsStream(s);
        Scanner sc = new Scanner(file);
        while (sc.hasNext())
                    this.dico.add(sc.next());
    }

    /**
     * @return dictionnaire de la langue française
     */
    public static Dictionnaire getInstance() {
        return instance ;
    }

    /**
     * @param s
     * @return vrai si le mot s est dans le dictionnaire
     */
    public boolean contient(String s) {
        return dico.contains(s.toLowerCase()) ;
    }

}

