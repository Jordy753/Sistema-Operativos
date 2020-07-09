#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QtCore>
#include <QtGui>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //int numelem=int(ui->box->value());
    //for(int i=0;i<10;i++) stock.push_back(0);
    ui->progressBar->setValue(0);
    prod1->bi(ui->progressBar);
    con1->bi(ui->progressBar);
    con2->bi(ui->progressBar);
    //ui->progressBar->value();

    connect(prod1,&productores::insert_text,[&](QString n){ui->listevent->addItem(n);});
    connect(prod1,&productores::act_pro,ui->producidos,&QLabel::setText);
    connect(prod1,&productores::tim_pro,[&](double n){ui->ejecucion_p->setNum(n);});
    connect(prod1,&productores::des_pro,[&](double n){ui->desperdicio_p->setNum(n);});
    //connect(prod1,&productores::abarra, ui->progressBar, &QProgressBar::setValue);
    //connect(prod1,&productores::label,ui->label,&QLabel::setText);

    connect(con1,&consumidores::insert_text,[&](QString n){ui->listevent->addItem(n);});
    connect(con1,&consumidores::act_con,ui->consumidos,&QLabel::setText);
    connect(con1,&consumidores::tim_con,[&](double n){ui->ejecucion_c1->setNum(n);});
    connect(con1,&consumidores::des_con,[&](double n){ui->desperdicio_c1->setNum(n);});
    //connect(con1,&consumidores::abarra, ui->progressBar, &QProgressBar::setValue);
    //connect(cont1,&consumidores::)

    connect(con2,&consumidores::insert_text,[&](QString n){ui->listevent->addItem(n);});
    connect(con2,&consumidores::tim_con,[&](double n){ui->ejecucion_c2->setNum(n);});
    connect(con2,&consumidores::des_con,[&](double n){ui->desperdicio_c2->setNum(n);});
    //connect(con2,&consumidores::abarra, ui->progressBar, &QProgressBar::setValue);

}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_startpr_clicked()
{
    prod1->start();
}

void MainWindow::on_startcon_clicked()
{
    int n_con=ui->cant_con->value();
    if(n_con==1) con1->start();
    else if(n_con==2){
        con1->start();
        con2->start();
    }
}

void MainWindow::on_pushButton_clicked()
{
    prod1->start();
    int n_con=ui->cant_con->value();
    if(n_con==1) con1->start();
    else if(n_con==2){
        con1->start();
        con2->start();
    }
}

void MainWindow::on_stoppr_clicked()
{
    prod1->terminate();
}

void MainWindow::on_stopcon_clicked()
{
    int n_con=ui->cant_con->value();
    if(n_con==1) con1->terminate();
    else if(n_con==2){
        con1->terminate();
        con2->terminate();
    }
}

void MainWindow::on_pushButton_2_clicked()
{
    prod1->terminate();
    int n_con=ui->cant_con->value();
    if(n_con==1) con1->terminate();
    else if(n_con==2){
        con1->terminate();
        con2->terminate();
    }
}

void MainWindow::on_radioButton_4_clicked()
{
    int numelem=int(ui->box->value());
    ui->progressBar->setMinimum(0);
    ui->progressBar->setMaximum(numelem);
    for(int i=0;i<numelem;i++) stock.push_back(0);
}

void MainWindow::on_infinito_clicked()
{
    int numelem=0;
    ui->progressBar->setMinimum(0);
    ui->progressBar->setMaximum(10000);
}
