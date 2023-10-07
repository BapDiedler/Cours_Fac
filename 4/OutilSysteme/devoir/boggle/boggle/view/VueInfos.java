package boggle.view;

import boggle.Observateur;
import boggle.model.Boggle;
import javafx.geometry.Insets;
import javafx.geometry.Pos;
import javafx.scene.control.Label;
import javafx.scene.layout.TilePane;
import javafx.scene.text.Font;

public class VueInfos extends TilePane implements Observateur {
    private Label score, motChoisi;
    private Boggle bog;

    public VueInfos(Boggle bog){
        super();
    }

    @Override
    public void reagir() {}
}
