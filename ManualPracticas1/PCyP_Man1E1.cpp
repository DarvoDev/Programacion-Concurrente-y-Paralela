// Ejercicio 1
#include <iostream>
#include <thread>

using namespace std;

int A, B, C, D, E, F, W, Y, Z;

void hilo1(){
   A = B * B;
   C = E * A;
}

void hilo2(){
   D = F * B;
}

int main(){
   B = 2, E = 3, F = 4, W = 5; //Valores iniciales

   thread h1(hilo1);
   thread h2(hilo2);

   h1.join();
   h2.join();

   Z = C + D;
   Y = Z + W;

   cout << "Valores finales: " << endl;
   cout << "A = " << A << endl;
   cout << "C = " << C << endl;
   cout << "D = " << D << endl;
   cout << "Z = " << Z << endl;
   cout << "Y = " << Y << endl;

   return 0;
}