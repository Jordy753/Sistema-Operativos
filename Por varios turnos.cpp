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

int turno=1;                        //El turno es del primer filosofo
vector<int> eat;                    //La comida en los platos de fideos


bool morir(int in){                 //Funcion que determinara mediante un tiempo si el filosofo logra morir o no
    sleep(10);
    if(estomagos[in-1]<=0){
        cout<<"El Filosofo "<<in<<" ha muerto a pesar del plazo de 4seg\n";
        return true;
    }
    return false;
}

void filoso(int in,int mn, int nn){ //Filosofo come o piensa

    mtx.lock();

    int tmax;

        cout<<in<<" "<<mn<<" "<<nn<<"\n";   //Los flosofos que tienen ficha(turno)

        srand(time(NULL));
        int tiem1=1+rand() % (5);           //El tiempo random que pueden demorar en comer
        cout<<"Filosofo "<<in<<" esta comiendo y demora en comer "<<tiem1<<"\n";
        int tiem2=1+rand() % (5);
        cout<<"Filosofo "<<mn<<" esta comiendo y demora en comer "<<tiem2<<"\n";
        int tiem3=1+rand() % (5);
        cout<<"Filosofo "<<nn<<" esta comiendo y demora en comer "<<tiem3<<"\n";

        sleep(2);

        //Buscamos al maximo
        if(tiem1>tiem2){
            if(tiem1>tiem3){
               tmax=tiem1;
            }
            else{
               tmax=tiem3;
            }
        }
        else{
            if(tiem2>tiem3){
               tmax=tiem2;
            }
            else{
               tmax=tiem3;
            }
        }
        cout<<tmax<<" el tiempo maximo de los turnos\n";


        //tiem1
        for(int i=0;i<tiem1;i++){
            if(estomagos[in-1]<200){
                estomagos[in-1]=estomagos[in-1]+25;         //e) incremento del valor de su estomago
                //eat
                eat[in-1]=eat[in-1]-25;
            }
            else{
                cout<<"Filosofo "<<in<<" esta lleno tiene "<<estomagos[in-1]<<" de energia\n"; //f) cuando un filosofo se llena
                break;
            }
        }

        //tiem2
        for(int i=0;i<tiem2;i++){
            if(estomagos[mn-1]<200){
                estomagos[mn-1]=estomagos[mn-1]+25;         //e) incremento del valor de su estomago
                //eat
                eat[mn-1]=eat[mn-1]-25;
            }
            else{
                cout<<"Filosofo "<<mn<<" esta lleno tiene "<<estomagos[mn-1]<<" de energia\n"; //f) cuando un filosofo se llena
                break;
            }
        }

        //tiem3
        for(int i=0;i<tiem3;i++){
            if(estomagos[nn-1]<200){
                estomagos[nn-1]=estomagos[nn-1]+25;         //e) incremento del valor de su estomago
                //eat
                eat[nn-1]=eat[nn-1]-25;
            }
            else{
                cout<<"Filosofo "<<nn<<" esta lleno tiene "<<estomagos[nn-1]<<" de energia\n";  //f) cuando un filosofo se llena
                break;
            }
        }

        //aqui presentamos los filosofos que piensan luego de comer
        int counter=0;
        for(int j=tiem1;j<tmax;j++){
            if(estomagos[in-1]> -100){
                estomagos[in-1]=estomagos[in-1]-25;         //d) decremento del valor de su estomago
                counter=counter+25;
            }
            else{
                cout<<"El Filosofo "<<in<<" se puede morir de hambre\n";        //g) un filosofo se puede morir de hambre
                //morirt.push_back(thread(morir,in));
                break;
            }
        }
        if(counter != 0) cout<<"Filosofo "<<in<<" ha gastado "<<counter<<" de energia en pensar\n";


        counter=0;
        for(int j=tiem2;j<tmax;j++){
            if(estomagos[mn-1]> -100){
                estomagos[mn-1]=estomagos[mn-1]-25;         //d) decremento del valor de su estomago
                counter=counter+25;
            }
            else{
                cout<<"El Filosofo "<<mn<<" se puede morir de hambre\n";        //g) un filosofo se puede morir de hambre
                //morirt.push_back(thread(morir,mn));
                break;
            }
        }
        if(counter != 0) cout<<"Filosofo "<<mn<<" ha gastado "<<counter<<" de energia en pensar\n";


        counter=0;
        for(int j=tiem3;j<tmax;j++){
            if(estomagos[nn-1]> -100){
                estomagos[nn-1]=estomagos[nn-1]-25;         //d) decremento del valor de su estomago
                counter=counter+25;
            }
            else{
                cout<<"El Filosofo "<<nn<<" se puede morir de hambre\n";        //g) un filosofo se puede morir de hambre
                //morirt.push_back(thread(morir,nn));
                break;
            }
        }
        if(counter != 0) cout<<"Filosofo "<<nn<<" ha gastado "<<counter<<" de energia en pensar\n";

    // Los demas filosofos pensado

    for(int i=0;i<estomagos.size();i++){
        if(mn!=i+1 && nn!=i+1 && in!=i+1){
            int counter2=0;

            for(int j=0;j<tmax;j++){            //El tiempo que pensaron
                if(estomagos[i]> -100){
                    estomagos[i]=estomagos[i]-25;           //d) decremento del valor de su estomago
                    counter2=counter2+25;
                }
                else{
                    cout<<"El Filosofo "<<i+1<<" se puede morir de hambre\n";   //g) un filosofo se puede morir de hambre
                    //morirt.push_back(thread(morir,i+1));
                    break;
                }
            }
        if(counter2 != 0)cout<<"Filosofo "<<i+1<<" ha gastado "<<counter2<<" de energia en pensar\n";
        }
    }

    cout<<"\n";
    mtx.unlock();
    return;
}


int main(){
    vector<std::thread> hilos;

    int cantidad;
    cout<<"Numero de filosofos: ";
    cin>>cantidad;                                      //b) cantidad cualquiera de filosofos

//Inicializacion de estomagos de los filosofos
    for(int i=0;i<cantidad;i++){
        estomagos.push_back(100);                       //c) estomago de filosofos
    }
//Eat
    for(int i=0;i<cantidad;i++){
        eat.push_back(1000);
    }

//R
    for(int i=1,n=cantidad-1,m=cantidad/2; i<=cantidad ;i++){
        if(n>cantidad) n=1;
        if(m>cantidad) m=1;

        hilos.push_back(thread(filoso,i,m,n));          //a) thread pensando o comiendo

        n++;
        m++;
    }



//Hilos
    for(int i=0;i<hilos.size();i++){
        hilos[i].join();
    }

    for(int i=0;i<morirt.size();i++){
        morirt[i].join();
    }

//Resultado de estomagos
    cout<<"Los estomagos de los filosofos\n"<<endl;
    for(int i=0;i<estomagos.size();i++){
            cout<<estomagos[i]<<" ";
    }
    cout<<"\n";
    cout<<"\n";

//Resultado de los platos de fideos
    cout<<"La comida que esta en los platos\n"<<endl;
    for(int i=0;i<eat.size();i++){
            cout<<eat[i]<<" ";
    }

    return 0;
}


/*
    Seccion Critica:
    La seccion critica en mi programa es la cantidad de filosofos que se vaya abordar(numero grande) ya que no cuento
    con las fichas suficientes para poder llegar a mas filosofos a la vez porque solo poseo tres fichas.
    Al principio con pocos filosofos funciona bien ya que con tres fichas es suficiente y tambien que el tiempo de su turno
    es equivalente al tiempo que demora de comer y el proceso de varios turnos esta en su forma optima
    La seccion critica tambien puede darse tambien por la igualdad de comer(obtener energia) y pensar(gasto de energia) ya que
    el correcto funcionamiento le puede durar en grupos pequeños pero mediante se engrandezca la distancia entre filosofos no
    podra seguir
*/

