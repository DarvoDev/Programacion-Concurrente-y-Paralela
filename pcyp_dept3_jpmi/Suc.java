package pcyp_dept3_jpmi;
import Jpmi.*;

public class Suc implements Proceso {
    CanalSimple canalIn, canalOut;
    Integer numero;

    public Suc(CanalSimple canalIn, CanalSimple canalOut){
        this.canalIn=canalIn;
        this.canalOut=canalOut;
        numero=null;
    }

    public void run(){
        while(true){
            numero=(Integer)canalIn.receive();
            numero=numero+1;
            canalOut.send(numero);
        }
    }
}
