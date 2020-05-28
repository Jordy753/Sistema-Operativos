#include<iostream>
#include<thread>
#include<mutex>
#include<vector>
#include<stdlib.h>
#include<time.h>
#include <windows.h>
#include <unistd.h>

using namespace std;

mutex mtx;

vector<int> estomagos;              //Los estomagos de los filosofos
vector<std::thread> morirt;         //Este hilo ejecutara la funcion que tiene el plazo para que muera o no
vector<int> fil_muertos;            //Filosofos que murieron

int turno=1;                        //El turno del primer filosofo (dato que nos ayuda a confirmar)
int eat=10000;                      //La comida que hay en el plato de fideo

bool estadovm(int in){                      //Aqui nos presenta si el filosofo esta vivo o muerto
    for(int i=0;i<fil_muertos.size();i++){
        if(in==fil_muertos[i]) return true;
    }
    return false;
}

void morir(int in){                 //Funcion que determinara mediante un tiempo si el filosofo logra morir o no
    sleep(8);
    if(estomagos[in-1]<=0){
        cout<<"El Filosofo "<<in<<" ha muerto a pesar del plazo de 4seg\n";
        fil_muertos.push_back(in);
    }
}

void filoso(int in){                //Funcion filosofo come o piensa

    mtx.lock();
    int ntiem;

    if(turno==in && false==estadovm(in)){   //Aqui tenemos el proceso de comer del filosofo que es su turno
        srand(time(NULL));
        int tiem=1+rand() % (10);           //Tiempo random que pueden demorar en comer
        cout<<"Filosofo "<<in<<" esta comiendo y demora en comer "<<tiem<<"\n";
        for(int i=0;i<tiem;i++){
            if(estomagos[in-1]<200){
                estomagos[in-1]=estomagos[in-1]+25;     //e) incrementa el valor de su estomago
                eat=eat-25;
                ntiem=ntiem+1;
            }
            else{                                       //f) cuando un filosofo se llena
                cout<<"Filosofo "<<in<<" esta lleno con "<<estomagos[in-1]<<" de energia\n";
                break;
            }
        }

        turno=turno+1;
        sleep(2);

        //Aqui tenemos a los demas filosofos pensando
        for(int i=0;i<estomagos.size();i++){
            if(in!=i+1 && false==estadovm(i+1)){
                int counter=0;
                for(int j=0;j<ntiem;j++){
                    if(estomagos[i]> -100){
                        estomagos[i]=estomagos[i]-25;   //d) decrementa el valor de su estomago
                        counter=counter+25;
                    }
                    else{
                        cout<<"El Filosofo "<<i+1<<" se puede morir de hambre\n"; //g) Se puede morir de hambre
                        usleep(7);
                        morirt.push_back(thread(morir,i+1));
                        break;
                    }
                }
                if(counter!=0)cout<<"Filosofo "<<i+1<<" ha gastado "<<counter<<" de energia en pensar\n";
            }
        }
    }
    mtx.unlock();
    return;
}


int main(){
    vector<std::thread> hilos;

    int cantidad;
    cout<<"Numero de filosofos: ";
    cin>>cantidad;                              // b) cantidad cualquiera de filosofos

    //La inicialización de los estomagos de mis filosofos
    for(int i=0;i<cantidad;i++){
        estomagos.push_back(100);               // c) estomago de filosofos
    }

    for(int i=1;i<=cantidad;i++){
            hilos.push_back(thread(filoso,i));  // a) thread pensando o comiendo
    }


    //Aqui esperamos la finalizacion de los hilos para que no terminen antes que el main
    for(int i=0;i<hilos.size();i++){
        hilos[i].join();
    }

    for(int i=0;i<morirt.size();i++){
        morirt[i].join();
    }

    cout<<endl;
    cout<<eat<<"\n";

    //Aqui presento los estomagos finales que tiene mis filosofos
    for(int i=0;i<estomagos.size();i++){
            cout<<estomagos[i]<<" ";
    }

    return 0;
}


/*
    Seccion Critica
    La seccion critica que puede presentar mi programa es cuando existe una enorme cantidad de filosofos
    en espera existe la probalidad de que algun filosofo muera especialmente a los ultimos ya que no
    podra satifacerlos por lo que estan muy lejos otra seccion critica en mi programa es que el costo de
    comer(obtener energia) es igual al costo de pensar(gastar energia) ya que lo que un filosofo come probablemente
    solo le dure un turno despues que comio y exista la probalidad qe muera porque tiene habre nuevamente

*/
