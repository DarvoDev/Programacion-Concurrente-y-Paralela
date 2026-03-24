package pcyp_dept3_jpmi;
import Jpmi.*;

public class PCyP_Dept3_JPMI {
    public static void main(String[] args) {
        CanalSimple a = new CanalSimple();
        CanalSimple b = new CanalSimple();
        CanalSimple c = new CanalSimple();
        CanalSimple d = new CanalSimple();
        CanalSimple e = new CanalSimple();
        CanalSimple f = new CanalSimple();
        CanalSimple g = new CanalSimple();
        CanalSimple h = new CanalSimple();
        CanalSimple i = new CanalSimple();

        Proceso naturales = new Naturales(a);
        Proceso delta1 = new Delta(a, b, c);
        Proceso pares = new Pares(b, d);
        Proceso impares = new Impares(c, e);
        Proceso delta2 = new Delta(e, g, h);
        Proceso prod = new Prod(d, g, f);
        Proceso plus = new Plus(f, h, i);
        Proceso display = new Display(i);

        Paralelo sistema = new Paralelo(new Proceso[]{
                naturales, delta1, pares, impares, delta2, prod, plus, display
        });

        sistema.run();
    }
}