// Ejercicio 3
#include <iostream>
#include <thread>

using namespace std;

int j = 0, k = 0;

int main(){
    for(int i = 1; i <= 3; i++){ 
        
        //Uso de funciones lambda
        thread hilo1([](){ // S1
            j = j + 10;
        });

        thread hilo2([](){ // S2
            k = k + 100;
        });

        hilo1.join();
        hilo2.join();
    }

    return 0;
}