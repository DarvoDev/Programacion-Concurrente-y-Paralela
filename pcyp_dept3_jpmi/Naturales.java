package pcyp_dept3_jpmi;

import Jpmi.*;

public class Naturales implements Proceso {
    private CanalSimple canalSalida;

    public Naturales(CanalSimple canalSalida) {
        this.canalSalida = canalSalida;
    }

    @Override
    public void run() {
        CanalSimple c_suc_a_pref = new CanalSimple();
        CanalSimple c_pref_a_delta = new CanalSimple();
        CanalSimple c_delta_a_suc = new CanalSimple();

        Paralelo generador = new Paralelo(new Proceso[]{
                new Prefijo(0, c_suc_a_pref, c_pref_a_delta),
                new Delta(c_pref_a_delta, canalSalida, c_delta_a_suc),
                new Suc(c_delta_a_suc, c_suc_a_pref)
        });

        generador.run();
    }
}