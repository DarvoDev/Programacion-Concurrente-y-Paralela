#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <vector>

using namespace std;

class Barrera {
private:
    mutex mtx;
    condition_variable cv;
    int contador;
    const int totalHilos;
    int generacion;

public:
    Barrera(int n) : contador(0), totalHilos(n), generacion(0) {}

    void esperar(int id) {
        unique_lock<mutex> lock(mtx);
        int mi_generacion = generacion;
        
        contador++;
        cout << "Hilo " << id << " ha llegado a la barrera (" 
             << contador << "/" << totalHilos << ")" << endl;

        if (contador == totalHilos) {
            generacion++;
            contador = 0;
            cout << "Hilo " << id << " (ultimo) libera la barrera" << endl;
            cv.notify_all();
        } else {
            cv.wait(lock, [this, mi_generacion] { 
                return mi_generacion != generacion; 
            });
            cout << "Hilo " << id << " continua despues de la barrera" << endl;
        }
    }
};
  
void trabajoHilo(int id, Barrera& barrera) {
    int pasos = id + 1;
    
    for (int i = 1; i <= pasos; ++i) {
        cout << "Hilo " << id << " progreso: " << i << "/" << pasos << endl;
        this_thread::sleep_for(chrono::seconds(1));
    }
    
    barrera.esperar(id);
    cout << "Hilo " << id << " ha terminado completamente" << endl;
}

int main() {
    const int numHilos = 4;
    Barrera barrera(numHilos);
    vector<thread> hilos;

    for(int i = 0; i < numHilos; i++){
    hilos.push_back(thread(trabajoHilo, i, ref(barrera)));
    }
    for (auto& h : hilos) {
        h.join();
    }

    return 0;
}
