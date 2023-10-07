package reseau.tables;

import java.util.HashMap;
import reseau.adresses.Adresse;
import reseau.adresses.AdresseMac;

/**
 * @author martine
 */

public class DNS {

    private HashMap<String, Adresse> nomIP;

    public DNS() {
        nomIP = new HashMap<>();
    }

    public void ajouter(String nomMachine, Adresse adresseIP) {
        nomIP.put(nomMachine, adresseIP);
        
    }
    
    public boolean nomConnue(String nom) {
        return nomIP.containsKey(nom);
    }
    
    /*public boolean adresseConnue(Adresse adr) {
        return nomIP.containsKey(adr);
    }*/
    
    /**
     * @param nom de la machine reçu
     * @return l'adresse IP correspondant à ce nom
     */
    public Adresse getAdresse(String nom) {
        return nomIP.get(nom) ;
    }
    

}
