//Ejercicio 2
#include <iostream>
#include <thread>

using namespace std;

int a, b, c, d, Y, W, Z;
float x;

void hilo1(){
   W = Y + c;
}

void hilo2(){
   Z = Y - d;
}

int main(){
   a = 2, b = 3, c = 4, d = 5; // Valores iniciales

   Y = a * b;

   thread h1(hilo1);
   thread h2(hilo2);

   h1.join();
   h2.join();

   if(Z == 0){
        cout << "Error: Division entre 0" << endl; 
        return 1;
   }

   x = W / Z;

   cout << "Valores finales: " << endl;
   cout << "Y = " << Y << endl;
   cout << "W = " << W << endl;
   cout << "Z = " << Z << endl;
   cout << "x = " << x << endl;

   return 0;
}