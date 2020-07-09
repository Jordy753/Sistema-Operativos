#ifndef PRODUCTORES_H
#define PRODUCTORES_H
#include<librerias.h>

class productores: public QThread
{
    Q_OBJECT

signals:
    void insert_text(QString);
    void act_pro(QString);
    void tim_pro(double);
    void des_pro(double);
    void abarra(int);

public:
    unsigned t0, t1;
    int idpro;
    int producidos;
    QProgressBar* b;
    vector<int>* buffer;
    int ba;


    productores(int ext_id=0, vector<int>* asd=nullptr,QObject *parent=nullptr):QThread(parent){
        idpro=ext_id;
        buffer=asd;
        producidos=0;
    }
    ~productores(){}

    void bi(QProgressBar* ext_b=0){
        b=ext_b;
    }

    bool lleno(vector<int> &buffer){
        for(int i=0;i<buffer.size();i++){
            if(buffer[i]==0) return false;
        }
        return true;
    }

    void run(){
        mutex mtx;
        double tot_desperdicio=0;
        ba=b->value();

        QString msm;
        qDebug() << "HilosP";

        //
        if(buffer[0].size()==0){
            qDebug() <<"Infinito";
            while(1!=0){
                buffer[0].push_back(1);
                qDebug() <<"El productor "+QString::number(idpro)+" agrego un productoI\n";
                msm ="El productor "+QString::number(idpro)+" agrego un productoI";   //emit string
                emit insert_text(msm);
                producidos++;    //emit int
                QString s = QString::number(producidos);
                emit act_pro(s);
                msleep(200);
            }
        }
        //

        t0=clock();
        for(int i=0;i<37;i++){  //hacerlo infinito
            if(lleno(*buffer)==true){
                qDebug()<<"El productor "+QString::number(idpro)+" dormir y lleno\n";
                msm="El productor "+QString::number(idpro)+" dormir y lleno";
                emit insert_text(msm);
                //un random de cuanto tiempo va a dormir
                srand(time(NULL));      //random
                double tiempo_desp=1+rand()%(251-1);;
                tot_desperdicio=tot_desperdicio+tiempo_desp;
                msleep(tiempo_desp);
                //msleep(250);
                emit des_pro(tot_desperdicio);
            }
            //funcion
            for(int i=0;i<buffer[0].size();i++){
                if(buffer[0][i]==0){
                   buffer[0][i]=1;
                   qDebug() <<"El productor "+QString::number(idpro)+" agrego un producto\n";
                   msm ="El productor "+QString::number(idpro)+" agrego un producto";   //emit string
                   emit insert_text(msm);
                   producidos++;    //emit int
                   QString s = QString::number(producidos);
                   emit act_pro(s);
                   //
                   ba++;
                   //qDebug() <<QString::number(ba)+" valor de la barra";
                   emit abarra(ba);
                   //
                   break; //Ya agrego un producto al buffer
                }
            }
        }
        t1 = clock();
        double time = (double(t1-t0)/CLOCKS_PER_SEC);
        emit tim_pro(time);


        //Impresion de elementos que se encuentran en el buffer
        for(int i=0;i<buffer[0].size();i++){
            QString tmp = QString::number(buffer[0][i]);
            qDebug()<< tmp;
        }
    }

};

#endif // PRODUCTORES_H
