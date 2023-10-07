package boggle;

import boggle.model.Boggle;
import boggle.view.VueInfos;
import boggle.view.VueLettres;
import boggle.view.VueMots;

public class Main extends Application {
    @Override
    public void start(Stage primaryStage){
        Boggle bog = new Boggle(4);

        primaryStage.setTitle("Boggle");

        //Disposition des différentes parties du jeu
        BorderPane root = new BorderPane();
        root.setBottom(new VueInfos(bog));
        root.setCenter(new VueLettres(bog));
        root.setLeft(new VueMots(bog));
        primaryStage.setScene(new Scene(root, 1000, 700));
        primaryStage.show();
    }

    public static void main(String[] args) {
        launch(args);
    }
}
