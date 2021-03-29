package Model;

import java.io.Serializable;

import static java.lang.System.nanoTime;

public class Crono implements Serializable {

    private static long inicio = 0L;
    private static long fim = 0L;

    public void start() {
        fim = 0L; inicio = nanoTime();
    }

    public double stop() {
        fim = nanoTime();
        long elapsedTime = fim - inicio;
        // segundos
        return elapsedTime / 1.0E09;
    }

    public String getTime() {
        return "" + stop();
    }


    public String getTImeString() {
        return "Elapsed Time: " +getTime() + " s";
    }
}