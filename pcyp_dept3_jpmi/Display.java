package pcyp_dept3_jpmi;
import Jpmi.*;

public class Display implements Proceso {
    private CanalSimple in;

    public Display(CanalSimple in) {
        this.in = in;
    }

    @Override
    public void run() {
        System.out.println("--- Iniciando Secuencia ---");
        while (true) {
            Object dato = in.receive();
            System.out.println("Salida: " + dato);

            try { Thread.sleep(500); } catch (InterruptedException e) {}
        }
    }
}