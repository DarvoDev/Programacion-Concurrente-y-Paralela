#include <iostream>
#include <thread>
#include <chrono>

#define MAX_HILOS std::thread::hardware_concurrency()

using namespace std;

int* cajas;
int total_hojas = 0;

int leerPersonas() {
    int n;
    while (true) {
        cout << "Ingrese el numero de personas (Min: 2, Max: " << MAX_HILOS << "): ";
        cin >> n;
        if (n >= 2 && n <= MAX_HILOS) break;
        cout << "Error: debe escoger un numero entre 2 y " << MAX_HILOS << endl;
    }
    return n;
}

void Persona(int id, int hojas) {
    for (int i = 0; i < hojas; i++) {
        cajas[id]++;
        cout << "Persona " << id + 1 << ": Agrega hoja" << endl;
        this_thread::sleep_for(chrono::milliseconds(10));
    }
}

void Engrapador(int n) {
    for (int i = 0; i < n; i++) {
        total_hojas += cajas[i];
    }
    cout << "El engrapador ha contado un total de: " << total_hojas << " hojas." << endl;
}

int main() {
    int n = leerPersonas();

    cajas = new int[n]();
    int* hojasPersona = new int[n];
    
    for (int i = 0; i < n; i++) {
        cout << "Ingrese el numero de hojas para la persona " << i + 1 << ": ";
        cin >> hojasPersona[i];
    }

    thread* personas = new thread[n];
    for (int i = 0; i < n; i++) {
        personas[i] = thread(Persona, i, hojasPersona[i]);
    }

    for (int i = 0; i < n; i++) {
        personas[i].join();
    }

    Engrapador(n);

    delete[] cajas;
    delete[] hojasPersona;
    delete[] personas;

    return 0;
}

/* COMPILACION:



BORRAR
*/