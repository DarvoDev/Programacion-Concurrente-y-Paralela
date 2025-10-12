//Version con monitores
#include<iostream>
#include<thread>
#include<mutex>
#include<condition_variable>
#include<cstdlib>
#include<ctime>
#include<chrono>

using namespace std;

class MonitorMesa{
    private:
        mutex candado;
        condition_variable cv;
        int papel_arroz = 0, tabaco = 0, cerillos = 0;

    public:
        void colocar_recurso(int tipo){
            unique_lock<mutex> lk(candado);
            switch (tipo)
            {
            case 1:
                papel_arroz++;
                cout <<"Agente coloca un papel de arroz"<<endl;
                break;
            
            case 2:
                tabaco++;
                cout << "Agente coloca tabaco"<<endl;
                break;
            
            case 3:
                cerillos++;
                cout<<"Agente coloca unos cerillos"<<endl;
                break;
            }
            lk.unlock();
            cv.notify_all();
        }

        void fumar(int id){
            unique_lock<mutex> lk(candado);
            while (papel_arroz == 0 || tabaco == 0 || cerillos == 0){
                cv.wait(lk);
            }

            papel_arroz--;
            tabaco--;
            cerillos--;
            
            cout<<"Fumador "<< id + 1 << " esta fumando"<<endl;
            lk.unlock();

            cv.notify_all();
        }
};

MonitorMesa mesa;

void agente(){
    srand(time(0));

    while (true){
        this_thread::sleep_for(chrono::seconds(2));
        mesa.colocar_recurso(rand()%3 + 1);
    }
}

void fumador(int id){
    while (true){
        mesa.fumar(id);
    }
}

int main(){
    thread fumadores[3];
    for (int i = 0; i < 3; i++){
        fumadores[i] = thread(fumador, i);
    }

    thread agente_thread(agente);

    for(auto &fumador : fumadores){
        fumador.join();
    }

    agente_thread.join();
    return 0;
}
