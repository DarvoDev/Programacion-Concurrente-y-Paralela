package pcyp_dept3_jpmi;
import Jpmi.*;

public class Prod implements Proceso {
    private CanalSimple in1;
    private CanalSimple in2;
    private CanalSimple out;

    public Prod(CanalSimple in1, CanalSimple in2, CanalSimple out) {
        this.in1 = in1;
        this.in2 = in2;
        this.out = out;
    }

    @Override
    public void run() {
        while (true) {
            Integer val1 = (Integer) in1.receive();
            Integer val2 = (Integer) in2.receive();

            Integer resultado = val1 * val2;
            out.send(resultado);
        }
    }
}