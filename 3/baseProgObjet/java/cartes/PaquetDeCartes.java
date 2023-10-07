package cartes;

import java.util.ArrayList;
import java.util.Random;


public class PaquetDeCartes {

    private ArrayList<Carte> paquet;

    public PaquetDeCartes(){
        this.paquet = new ArrayList<>();
    }

    public void ajouter(Carte ... cartes){
        for(Carte c : cartes){
            assert(c!=null):"les cartes doivent être initialisées";
            paquet.add(c);
        }
    }

    public void ajouter(PaquetDeCartes pdc){
        assert(pdc!=null):"le paquet de carte doit être initialisé";
        paquet.addAll(pdc.paquet);
    }

    public int getNombreDeCartes(){
        return paquet.size();
    }

    public boolean estVide(){
        return paquet.isEmpty();
    }

    public int getValeur(){
        int somme = 0;
        for(Carte c : paquet){
            somme += c.getValeur();
        }
        return somme;
    }

    public String toString(){
        StringBuilder builder = new StringBuilder();
        for(Carte carte : paquet){
            builder.append(carte);
        }
        return builder.toString();
    }

    public void melanger(){
        Random rand = new Random();
        int ind = 0;
        ArrayList<Carte> newPaquet = new ArrayList<>();
        while(!paquet.isEmpty()){
            ind = rand.nextInt(paquet.size());
            newPaquet.add(paquet.get(ind));
            paquet.remove(paquet.get(ind));
        }
        paquet = newPaquet;
    }

    public void retourner(){
        ArrayList<Carte> newPaquet = new ArrayList<>();
        for(int i = paquet.size()-1; i>=0; i--){
            newPaquet.add(paquet.get(i));
            paquet.remove(i);
        }
        paquet = newPaquet;
    }

    public Carte getSommet(){
        return paquet.get(paquet.size()-1);
    }
}
