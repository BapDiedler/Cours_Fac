package boggle.model;

import boggle.Observateur;

public class Boggle  {

    private ArrayList<Observateur> listeObservateur;

    public Boggle(int taille) {
        this.listeObservateur = new ArrayList<Observateur>();
    }

    public void notifierObservateurs(){
        for(Observateur o : this.listeObservateur){
            o.reagir();
        }
    }

}
