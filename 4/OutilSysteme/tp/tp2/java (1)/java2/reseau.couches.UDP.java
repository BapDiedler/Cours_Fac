package reseau.couches;

import reseau.Message;
import reseau.adresses.Adresse;

/**
 * @author martine
 */
public class UDP extends Transport {

    public UDP() { 
        super();
    }
    
    @Override
    protected Message getEntete(int portSource, Adresse adrDest, int portDest, Message message) {
        // Port source (16 bits), port destination (16 bits), longueur entête + données (16 bits), somme de contrôle (16 bits)
        Message enTete = new Message();
        enTete.ajouter(portSource);
        enTete.ajouter(portDest);
        enTete.ajouter(2*4+message.size());
        enTete.ajouter(0); 
        return enTete ;
    }

}
