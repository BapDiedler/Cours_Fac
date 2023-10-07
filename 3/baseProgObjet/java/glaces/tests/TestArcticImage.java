/**
 * @author Baptiste Diedler
 * 
 * @version 2022 
 */

package glaces.tests;

import glaces.ArcticImage;
import geometrie.Point ;


public class TestArcticImage {
    public static void main(String[] args){
        int[][] tab = new int[300][300];
        for(int i=1; i<300; i+=2){
            for(int j=0; j<300; ++j){
                tab[j][i]=1;
            }
        }
        ArcticImage image = new ArcticImage(300,300);
        image.setColors(tab);
        
    }
}
