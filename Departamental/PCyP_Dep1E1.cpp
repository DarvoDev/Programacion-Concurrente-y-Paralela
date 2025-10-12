#include <iostream> 
#include <thread> 
#include <chrono> 
using namespace std; 
int j=0,k=0,i=0,a[2]={0}; 
void s1(int s,int &j){ 
this_thread::sleep_for(chrono::milliseconds(1000)); 
j+=10; 
cout<<"S"<<s<<": j = "<<j<<endl; 
} 
void s2(int s,int &k){ 
this_thread::sleep_for(chrono::milliseconds(1000)); 
k+=100; 
cout<<"S"<<s<<": k = "<<k<<endl; 
} 
void s8(int s,int i,int a){ 
this_thread::sleep_for(chrono::milliseconds(1000)); 
cout<<"S"<<s<<": a["<<i<<"] = "<<a<<endl; 
} 
void s7(int &j,int &k){ 
this_thread::sleep_for(chrono::milliseconds(1000)); 
cout<<"S7: j = "<<j<<" | k = "<<k<<endl; 
} 
int main(){ 
// Cobegin: S1 S2 paralelo 
thread h1(s1,1,ref(j)); 
thread h2(s2,2,ref(k)); 
h1.join(); 
h2.join(); 
//S3 
a[0]=j*k; 
cout<<"S3: a[0] = "<<a[0]<<endl; 
// Cobegin: S8 paralelo 
thread h8(s8,8,i,a[0]);
// Cobegin: S4 S5 paralelo 
thread h4(s1,4,ref(j)); 
thread h5(s2,5,ref(k)); 
h4.join(); 
h5.join(); 
// Cobegin: S6/S9 paralelo S7 
thread h7(s7,ref(j),ref(k)); 
// 
a[i]=j*k; 
cout<<"S6: a["<<i<<"] = "<<a[i]<<endl; // s6 
s8(9,i+1,a[1]); // s9 
h7.join(); // Join S7 
h8.join(); // Join S8 
return 0; 
}
