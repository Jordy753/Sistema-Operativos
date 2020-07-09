#ifndef CONSUMIDORES_H
#define CONSUMIDORES_H
#include<librerias.h>

class consumidores: public QThread
{
    Q_OBJECT

signals:
    void insert_text(QString);
    void act_con(QString);
    void tim_con(double);
    void des_con(double);
    void abarra(int);

public:
    int idcon;
    int consumidos;
    QProgressBar* b;
    vector<int>* buffer;
    unsigned t0, t1;
    int ba;

    consumidores(int ext_id=0, vector<int>* asd=nullptr, QObject *parent=nullptr):QThread(parent){
        idcon=ext_id;
        buffer=asd;
        consumidos=0;
    }
    ~consumidores(){}

    void bi(QProgressBar* ext_b=0){
        b=ext_b;
    }

    bool vacio(vector<int> &buffer){
        for(int i=0;i<buffer.size();i++){
            if(buffer[i]==1) return false;
        }
        return true;
    }

    void run(){
        mutex mtx;
        double tot_desperdicio=0;
        ba=b->value();
        //mtx.lock();

        QString msm;
        qDebug() << "HilosC";

        t0=clock();
        for(int i=0;i<30;i++){  //hacerlo infinito
            if(vacio(*buffer)==true){
                qDebug()<<"El consumidor "+QString::number(idcon)+" dormir y vacio\n";
                msm="El consumidor "+QString::number(idcon)+" dormir y vacio";
                emit insert_text(msm);
                //un random de cuanto tiempo va a dormir
                srand(time(NULL));      //random
                double tiempo_desp=1+rand()%(501-1);;
                tot_desperdicio=tot_desperdicio+tiempo_desp;
                msleep(tiempo_desp);
                //msleep(500);
                emit des_con(tot_desperdicio);
            }

            for(int i=0;i<buffer[0].size();i++){
                if(buffer[0][i]==1){
                   buffer[0][i]=0;
                   qDebug() <<"El consumidor "+QString::number(idcon)+" se consumio un producto\n";
                   msm="El consumidor "+QString::number(idcon)+" se consumio un producto";
                   emit insert_text(msm);
                   consumidos++;
                   QString s = QString::number(consumidos);
                   emit act_con(s);
                   //
                   ba--;
                   emit abarra(ba);
                   //
                   break; //Ya consumio un producto al buffer
                }
            }
        }
        t1 = clock();
        double time = (double(t1-t0)/CLOCKS_PER_SEC);
        emit tim_con(time);
        //mtx.unlock();
    }
};
#endif // CONSUMIDORES_H
