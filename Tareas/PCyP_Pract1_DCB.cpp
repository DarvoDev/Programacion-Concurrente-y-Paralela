#include <thread>
#include <iostream>
#include <string>
#include <vector>

#define MAX_HILOS thread::hardware_concurrency()

using namespace std;

void funcPalabra(int i, string palabra){  
    cout << palabra[i] << endl;
   }

void secuencial(vector<thread> &hilos,string palabra, int cant_hilos){
    for(int i = 0; i<cant_hilos; i++){
        hilos[i] = thread(funcPalabra, i, palabra);
        hilos[i].join();
    }
}

void paralelo(vector<thread> &hilos, string palabra, int cant_hilos){
    for(int i = 0; i<cant_hilos; i++){
        hilos[i] = thread(funcPalabra, i, palabra);
    }
    for(thread &h : hilos){
        if(h.joinable()){
            h.join();
        }
    }
} 

int main(){
    string palabra;
    char opcion;
    int cant_hilos;

    cout<<"Ingresa una palabra (se utilizaran maximo "<<MAX_HILOS<<" caracteres): ";
    cin>>palabra;

    if(palabra.length()<MAX_HILOS){
        cant_hilos = palabra.length();
    }else{
        cant_hilos = MAX_HILOS;
    }
  
    cout<<"Deseas la ejecucion paralela o secuencial? (p / s): ";
    cin>>opcion;
    
    vector<thread> hilos(cant_hilos);
    
    switch(opcion){
        case 'p':
            paralelo(hilos, palabra, cant_hilos);
            break;
        case 's':
            secuencial(hilos, palabra, cant_hilos);
            break;
        default:
            cout <<"Opcion incorrecta."<<endl;
            return 1;
    }

   return 0;
  }
