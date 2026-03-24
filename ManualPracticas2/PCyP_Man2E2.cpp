#include<iostream>
#include<thread>
#include<mutex>
#include<condition_variable>
#include<chrono>
#include<cstdlib>

using namespace std;

class Caja{
    private:
        int max = 100;
        int hojas = 0;
        mutex candado;
        condition_variable cv;
    public:
        void ColocaHoja(int id){
            while (true){
                unique_lock<mutex> lock(candado);
                while (hojas>=max){
                    cv.wait(lock);
                }
                hojas++;
                cout<<"Persona "<<id<<" ha colocado una hoja, total de hojas: "<<hojas<<endl;
                cv.notify_all();
                lock.unlock();
                this_thread::sleep_for(chrono::milliseconds(100+rand()%200));

            }    
        }

        void VaciaCaja(){
        while (true){
            unique_lock<mutex> lock(candado);
            while (hojas < max){
                cv.wait(lock);
            }
            cout<<"La caja esta llena, observador vaciando "<<hojas<<" hojas."<<endl;
            hojas = 0;
            cv.notify_all();
        }
}
};

void observador(Caja& caja){
    caja.VaciaCaja();
}

void persona(int id, Caja& caja){
    caja.ColocaHoja(id);
}

int main(){
    srand(time(0));
    int num_personas=3;
    Caja caja;
    thread personas[num_personas];  

    for (int i = 0; i < num_personas; i++){
        personas[i] = thread(persona, i+1, ref(caja));
    }

    thread obs(observador, ref(caja));
    for (int i = 0; i < num_personas; i++)
    {
        personas[i].join();
    }

    obs.join();

    return 0;
    
}