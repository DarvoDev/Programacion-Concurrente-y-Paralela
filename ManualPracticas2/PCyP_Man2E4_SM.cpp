//Version sin monitores
#include<iostream>
#include<thread>
#include<mutex>
#include<condition_variable>
#include<cstdlib>
#include<ctime>
#include<chrono>

using namespace std;

mutex candado;
condition_variable cv;
int papel_Arroz = 0, tabaco = 0; cerillos = 0;

void fumador(int id){
    while (true){
        unique_lock<mutex> lk(candado);
        while (papel_Arroz == 0 || tabaco == 0 || cerillos == 0){
            cv.wait(lk);
        }

        papel_Arroz--;
        tabaco--;
        cerillos--;

        cout<<"Fumador "<<id+1<<" esta fumando"<<endl;
        lk.unlock();
        this_thread::sleep_for(chrono::seconds(1));

        cv.notify_all();
    }
}

void agente(){
    srand(time(0));

    while (true)
    {
        this_thread::sleep_for(chrono::seconds(2));
        unique_lock<mutex> lk(candado);
        int recurso = rand() % 3 + 1;
        switch (recurso)
        {
        case 1:
            papel_Arroz++;
            cout<<"Agente coloca un papel de arroz"<<endl;
            break;
        
        case 2:
            tabaco++;
            cout<<"Agente coloca tabaco"<<endl;
            break;
        
        case 3:
            cerillos++;
            cout<<"Agente coloca cerillos"<<endl;
            break;
        }
        lk.unlock();
        cv.notify_all();
    }
}

int main(){

    thread fumadores[3];
    for (int i = 0; i < 3; i++){
        fumadores[i] = thread(fumador, i);
    }

    thread agente_tread(agente);

    for(auto &fumador : fumadores){
        fumador.join();
    }

    agente_tread.join();
    return 0;
}

