package reseau.clientsServeurs;

import reseau.couches.Application;
import reseau.Message;
import reseau.adresses.Adresse;

/**
 * @author martine
 */
public class ClientNumerique extends Application {

    public ClientNumerique(int port) {
        super(port) ;
    }
   
    /**
     * Je reçois un message de la couche inférieure 
     * @param source adresse de la source
     * @param portSource port de la source
     * @param message message reçu
     */
    @Override
    public void receiveMessage(Adresse source, int portSource, Message message) {
        System.out.println("Je suis "+getNom()+" et je reçois "+message);
        resultat = message ;
    } 

}