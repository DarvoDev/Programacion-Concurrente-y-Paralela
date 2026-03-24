package pcyp_dept3_jpmi;

import Jpmi.*;

public class Impares implements Proceso {
    private CanalSimple in;
    private CanalSimple out;

    public Impares(CanalSimple in, CanalSimple out) {
        this.in = in;
        this.out = out;
    }

    @Override
    public void run() {
        while (true) {
            Integer dato = (Integer) in.receive();
            if (dato % 2 != 0) {
                out.send(dato);
            } else {
                out.send(dato + 1);
            }
        }
    }
}