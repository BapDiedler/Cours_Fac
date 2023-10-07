package boggle.view;

import boggle.Observateur;
import boggle.model.Boggle;
import javafx.scene.control.Button;
import javafx.scene.layout.GridPane;

public class VueLettres extends GridPane implements Observateur {

    private Boggle bog;
    private Button tabBouton[][];
    private int nbLettres;
    private int idPartie;
}
