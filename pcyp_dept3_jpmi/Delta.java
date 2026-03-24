package pcyp_dept3_jpmi;

import Jpmi.*;

public class Delta implements Proceso {
    CanalSimple canalIn, canalOut1, canalOut2;
    Object dato;

    public Delta(CanalSimple canalIn, CanalSimple canalOut1, CanalSimple canalOut2) {
        this.canalIn = canalIn;
        this.canalOut1 = canalOut1;
        this.canalOut2 = canalOut2;
        dato = null;
    }

    @Override
    public void run() {
        while (true) {
            dato = canalIn.receive();
            Paralelo par = new Paralelo(new Proceso[]{
                    new Escribe(dato, canalOut1),
                    new Escribe(dato, canalOut2)
            });
            par.run();
        }
    }
}