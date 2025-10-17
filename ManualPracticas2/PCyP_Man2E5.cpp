#include<iostream>
#include<thread>
#include<mutex>
#include<condition_variable>
#include<cstdlib>
#include<ctime>
#include<chrono>
#include<vector>
#include<string>


using namespace std;

mutex candado;
condition_variable vc;

class CalderoCompartido{
    public:
        int pot;
        int capacidad;
        bool cocineroDespierto;

    public:
        CalderoCompartido(int M){
            this->capacidad = M;
            this->pot = M;
            this->cocineroDespierto = false;
        }

        void servirRacion(int id){
            unique_lock<mutex> lock(candado);

            while (pot == 0)
            {
                if(!cocineroDespierto){
                    cocineroDespierto = true;
                    cout<<"[Amigo " << id <<"] La cacerola está vacia, despertando al cocinero"<<endl;
                    vc.notify_one();
                }

                vc.wait(lock, [this]{
                    return pot > 0;
                });
            }      
            pot--;
            cout << "[Amigo "<<id<<"] Toma su racion. Raciones restantes: "<<pot<<endl;      
        }

        void rellenar(){
            unique_lock<mutex> lock(candado);

            vc.wait(lock, [this]{
                return pot == 0;
            });

            pot = capacidad;

            cout << "[Cocinero] Ha rellenado la carerola con " << pot << " raciones"<<endl;

            cocineroDespierto = false;

            vc.notify_all();
        }
};

class Amigo{
    public:
        CalderoCompartido *caldero;
        int id;


    public:
        Amigo(int id, CalderoCompartido *caldero){
            this->id = id;
            this->caldero = caldero;
        }

        void operator()(){
            while (true){
                this_thread::sleep_for(chrono::milliseconds(500 + rand() % 1000));
                caldero->servirRacion(id);
                this_thread::sleep_for(chrono::milliseconds(300 + rand() % 700));
            }
        }
};

class Cocinero{
    public:
        CalderoCompartido *caldero;
    
    public:
        Cocinero(CalderoCompartido *caldero){  
            this->caldero = caldero;
        }

        void operator()(){
            while (true)
            {
                caldero->rellenar();
                this_thread::sleep_for(chrono::milliseconds(1000));
            }
        }
};


int main(){
    srand(static_cast<unsigned int>(time(nullptr)));

    int N=0;
    int M=0;

    cout<<"Introduce el numero de amigos: ";
    cin>>N;
    cout<<"Introduce la capacidad del caldero: "<<endl;
    cin>>M;

    CalderoCompartido *caldero = new CalderoCompartido(M);

    vector<thread> hilos;

    for (int i = 0; i < N; i++){
        hilos.push_back(thread(Amigo(i+1, caldero)));
    }

    thread hiloCocinero{Cocinero(caldero)};


    for(auto &t : hilos){
        t.join();
    }

    hiloCocinero.join();

    delete caldero;
    return 0;
}