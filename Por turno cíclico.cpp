#include<iostream>
#include<thread>
#include<mutex>
#include<vector>
#include <windows.h>

using namespace std;

int verif=1;
mutex mtx;

void action_f(int opc,int i){

    mtx.lock();                         //Para evitar que otro hilo entre en el mismo proceso
    if(opc==0){
        cout<<"El filosofo"<<i<<" esta comiendo\n";
    }
    else if(opc==1){
        cout<<"El filosofo"<<i<<" no comio y paso turno\n";
    }
    verif=i+1;
    mtx.unlock();
}

void verificacion(int opc,int i){       //Esta funcion nos ayudara los hilos de forma consecuente
    if(verif!=i){
        Sleep(100*i);                   // Con el dato i haremos que los primeros salgan para que sea consecuente
    }
    action_f(opc,i);
}

int main(){
    srand(time(0));
    vector<std::thread> procesos;

    for(int i=1;i<=5;i++){
        procesos.push_back(thread(verificacion,rand() % 2,i)); //El rand es para decidir la accion del filosofo y el i es para saber
    }                                                           //que filosofo es

    for(int i=0;i<procesos.size();i++){
        procesos[i].join();
    }

    return 0;
}
