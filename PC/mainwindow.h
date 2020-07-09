#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include<productores.h>
#include<consumidores.h>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_startpr_clicked();

    void on_startcon_clicked();

    void on_pushButton_clicked();

    void on_stoppr_clicked();

    void on_stopcon_clicked();

    void on_pushButton_2_clicked();

    void on_radioButton_4_clicked();

    void on_infinito_clicked();

private:
    Ui::MainWindow *ui;
    vector<int> stock;
    bool e=true;

    //caballo=new mythread(this,"Pegaso",ui->progressBar_1,ui->name_1,ui->R1,ui->D1,ui->listWidget);
    productores *prod1 =new productores(1,&stock,this);
    consumidores *con1 =new consumidores(2,&stock,this);
    consumidores *con2 =new consumidores(3,&stock,this);

};

#endif // MAINWINDOW_H
