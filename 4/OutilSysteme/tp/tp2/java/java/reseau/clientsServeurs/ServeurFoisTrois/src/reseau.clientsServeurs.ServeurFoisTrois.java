package reseau.clientsServeurs;

import reseau.couches.Application;
import reseau.Message;

/**
 * @author martine
 */
public class ServeurFoisTrois extends Application {
    
    /**
     * @param port le port dans la couche transport
     */
    public ServeurFoisTrois(int port) {
        super(port);
    }

    /**
     * @param message entier à convertir en * 2
     * @return entier * 2
     */
    @Override
    protected Message traiter(Message message) {
        System.out.println("Je calcule * 2 ...");
        int entier = message.extraireEntier(0) ;
        int res = entier * 3 ;
        return new Message(res);
    }

}
