#include<iostream>
#include<thread>
#include<mutex>
#include<vector>
#include<string>
#include<condition_variable>

using namespace std;

mutex candado;
condition_variable vc;

class ArregloCompartido{
    public:
        vector<int> numeros;
        int cont, tam;
        long int sumaNums, sumaTotal;

    public:
        ArregloCompartido(int tam){
            this->tam = tam;
            sumaNums = 0;
            sumaTotal = 0;
            cont = 0;
            for (int i = 0; i < tam; i++)
            {
                numeros.push_back(i+1);
                sumaNums = sumaNums + numeros[i];
            }
            cout<<"La suma de los primeros" << tam <<" numeros naturales debe ser: "<<sumaNums<<endl;       
        }

        int getNum(){
            return numeros[cont];
        }

        void addCont(){
            cont++;
        }

        int getCont(){
            return cont;
        }

        int getTam(){
            return tam;
        }

        void addSumaTotal(long int valor){
            sumaTotal = sumaTotal + valor;
        }

        long int getSumaTotal(){
            return sumaTotal;
        }
};

class matematico{
    public:
        ArregloCompartido *numeros;
        long int sumaParcial;
        string nombre;
        bool band;
    public:
        matematico(string nombre, ArregloCompartido *numeros){
            this->nombre = nombre;
            this->numeros = numeros;
            sumaParcial = 0;
            band = false;
        }

        long int getSumaParcial(){
            return sumaParcial;
        }

        void operator()(){
            while (!band)
            {
                {
                    unique_lock<mutex> lock(candado);

                    if (numeros->getCont()<numeros->getTam())
                    {
                        sumaParcial = sumaParcial + numeros->getNum();
                        numeros->addCont();
                        vc.notify_all();
                    }
                    else{
                        cout<<nombre<<" suma parcial = "<<sumaParcial <<endl;
                        numeros->addSumaTotal(sumaParcial);
                        band = true;
                        vc.notify_all();
                    }
                    if(numeros->getCont()<numeros->getTam()){
                        vc.wait(lock);
                    }                    
                }
                this_thread::sleep_for(chrono::miliseconds(100));
            }
        }
};


int main(){
    int Nmat = 0;
    int totalNums = 0;

    cout<<"Introduce el numero de matematicos: ";
    cin >> Nmat;
    cout<<"Introduce el numero maximo: ";
    cin >> totalNums;

    vector<std::thread> hilos;

    ArregloCompartido *arrayNums = new ArregloCompartido(totalNums);

    for (int i = 0; i < Nmat; i++){
        hilos.push_back(thread(matematico("Matematico " + to_string(i + 1), arrayNums)));
    }

    for (int i = 0; i < Nmat; i++)
    {
        hilos[i].join();
    }

    cout<<"Suma Total = " << arrayNums -> getSumaTotal()<< endl;
    return 0;
}