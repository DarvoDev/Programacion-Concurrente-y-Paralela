package pcyp_dept3_jpmi;

import Jpmi.*;

public class Prefijo implements Proceso{
    CanalSimple canalIn, canalOut;
    Integer numero;

    public Prefijo(Integer n, CanalSimple canalIn, CanalSimple canalOut){
        numero=n;
        this.canalIn=canalIn;
        this.canalOut=canalOut;
    }

    public void run(){
        canalOut.send(numero);
        Id id=new Id(canalIn, canalOut);
        id.run();
    }
}