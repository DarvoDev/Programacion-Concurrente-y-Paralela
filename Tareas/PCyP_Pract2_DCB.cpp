#include <iostream>
#include <thread>
#include <vector>

using namespace std;

void hil1(vector<int>& a) {
    a[3] = a[1] + 4;  // S1
    a[5] = a[3] + 4;  // S3
    a[7] = a[5] + 4;  // S5
}

void hil2(vector<int>& a) {
    a[4] = a[2] + 4;  // S2
    a[6] = a[4] + 4;  // S4
    a[8] = a[6] + 4;  // S6
}

int main() {
    vector<int> a(9);
    //valores iniciales
    a[1] = 10;  
    a[2] = 20;  
    
    thread hilo1(hil1, ref(a));
    thread hilo2(hil2, ref(a));
    

    hilo1.join();
    hilo2.join();
    
    for (int i = 3; i <= 8; i++) {
        cout << "a[" << i << "] = " << a[i] << endl;
    }
    
    return 0;
}

//DCB