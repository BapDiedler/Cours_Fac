package reseau;

import reseau.Machine;
import reseau.Message;
import java.util.ArrayList;
import reseau.adresses.*;
/**
 * @author martine
 */
public  class ReseauLocal {

	private ArrayList<Machine> machines;
	
    public ReseauLocal(){
    	machines = new ArrayList<Machine>();
    }
    
    public  String getNom() {
        return getClass().getName() ;
    }
    public void ajouter(Machine m){
    	m.getCoucheLiaison().setReseau(this);
    	machines.add(m);
    }
    
    public void sendTrame(Message trame){
    	AdresseMac adrm = trame.extraireAdresseMac();
    	for(Machine m : machines){
    		if(m.getAdresseMac().equals(adrm)){
    			 System.out.println("Je suis "+getNom()+" et j'ai reçu "+trame.size()+" octets : " +trame);
    			m.getCoucheLiaison().receiveMessage(trame);
    		}
    	}
    }
    
}
         
          
