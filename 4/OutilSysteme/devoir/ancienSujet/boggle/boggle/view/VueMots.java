package boggle.view;

import boggle.Observateur;
import boggle.model.Boggle;

public class VueMots extends VBox implements Observateur {

    private Boggle bog;
    private ScrollPane listeDeroulante;

    public VueMots(Boggle bog){
        super();
    }
}
