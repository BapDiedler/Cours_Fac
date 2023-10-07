package reseau.couches;

import reseau.Message;
import reseau.adresses.Adresse;

/**
 * @author martine
 */
public abstract class Reseau extends Couche {

    public abstract void receiveMessage(Message message) ;

    public abstract void sendMessage(Adresse dest, Message message);

}
