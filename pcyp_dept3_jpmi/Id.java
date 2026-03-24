package pcyp_dept3_jpmi;

import Jpmi.*;
public class Id implements Proceso{
    CanalSimple canalIn, canalOut;
    Object dato;

    public Id(CanalSimple canalIn, CanalSimple canalOut){
        this.canalIn=canalIn;
        this.canalOut=canalOut;
        dato=null;
    }

    @Override
    public void run(){
        while(true){
            dato=canalIn.receive();
            canalOut.send(dato);
        }
    }
}