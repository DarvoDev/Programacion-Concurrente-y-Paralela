package pcyp_dept3_jpmi;

import Jpmi.*;

public class Escribe implements Proceso {
    CanalSimple canalOut;
    Object dato;

    public Escribe(Object dato, CanalSimple canalOut){
        this.dato=dato;
        this.canalOut=canalOut;
    }

    @Override
    public void run(){
        canalOut.send(dato);
    }
}