#include<iostream>
#include<thread>
#include<mutex>
#include<condition_variable>

using namespace std;

mutex candado;
condition_variable vc;

class Sumatoria{
    private:
        int suma = 0;
        int turno = 1;
        int n;
    public:
        Sumatoria(int n){
            this->n = n;
        }

        void sumar(int id){
            unique_lock<mutex> lk(candado);
            while (id != turno){
                vc.wait(lk);
            }
            suma +=id;
            cout<<"Hilo "<<id<<"suma: "<<id<<endl;
            turno++;
            vc.notify_all();
            lk.unlock();
        }

        int getSuma(){
            return suma;
        }
};

class Hilosum{
    private:
        Sumatoria &sumatoria;
        int id;

    public:
        Hilosum(Sumatoria &s, int id) : sumatoria(s), id(id){}

        void operator()(){ sumatoria.sumar(id);}
};

int main(){
    int n;
    cout<<"Ingrese el valor de la sumatoria: ";
    cin>>n;

    Sumatoria sumatoria(n);

    thread *hilos = new thread[n];

    for (int i = 1; i <= n; i++){
        hilos[i-1] = thread(Hilosum(sumatoria, i));
    }

    for (int i = 0; i < n; i++){
        hilos[i].join();
    }

    cout << "Suma total: " << sumatoria.getSuma()<<endl;
    return 0;
    
}