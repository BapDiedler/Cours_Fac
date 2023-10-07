package glaces.tests;

import glaces.Iceberg2D;
import geometrie.Point;
import glaces.Ocean;
import glaces.ArcticImage;

public class TestOcean {

    private static void testConstructeur(){
        Ocean ocean = new Ocean();
        boolean val = ocean.getHeight()==300;
        assert(val);
        val = ocean.getWidth()==300;
        assert(val);
        val = ocean.getCount()==2;
        assert(val);
    }

    private static void testGet(){
        Ocean ocean = new Ocean();
        boolean val = ocean.getWidth()==300;
        assert(val);
        val = ocean.getHeight()==300;
        assert(val);
        val = ocean.getCount()==2;
        assert(val);
    }

    private static void testFondre(){
        Ocean ocean = new Ocean(3,300,300);
        ArcticImage image = new ArcticImage(ocean.getWidth(),ocean.getHeight());
        image.setColors(ocean.getColors());
        ocean.Fondre(0.25);
        image.setColors(ocean.getColors());
    }

    public static void main(String[] args){
        testConstructeur();
        testGet();
        testFondre();
    }
}
