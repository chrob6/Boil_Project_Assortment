#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->startTest->setText("Test");
    ui->pushButton->setText("Close");

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::set(){ //po ustwieniu spinBox_2?
    int goods = ui->spinBox->value();
    int material = ui->spinBox_2->value();
    ui->tableWidget->setRowCount(material); //tabela 1 do wczytania nakładów jednostkowych
    ui->tableWidget->setColumnCount(goods);
}

void MainWindow::on_startTest_clicked()
{
    //Narazie bardzo dummy rozwiazanie ale dziala rozwiazanie z zajęć i póki co bez wczytywania z UI
    int goods = ui->spinBox->value(); // Zad 1 i 2
    //int goods = 4; // Zad 2.
    int material = ui->spinBox_2->value();
    int* limit_goods = new int[goods];
    int* limit_goods_unit = new int[goods];
    float **main_table = new float *[goods];
    for (int i =0; i< goods; ++i) {
        main_table[i] = new float [material];
    }



    //Zad1
    main_table[0][0] = 16;//ui->tableWidget->item(0,0)->text().toFloat();
    main_table[0][1] = 24;//ui->tableWidget->item(0,1)->text().toFloat();
    main_table[1][0] = 16;//ui->tableWidget->item(1,0)->text().toFloat();
    main_table[1][1] = 10;//ui->tableWidget->item(1,1)->text().toFloat();
    limit_goods_unit[0] = 3000;
    limit_goods_unit[1] = 4000;
    limit_goods[0] = 96000;
    limit_goods[1] = 80000;

    //Zad2
    main_table[0][0] = 6;
    main_table[0][1] = 6;
    main_table[1][0] = 10;
    main_table[1][1] = 5;
    limit_goods_unit[0] = 1000000; // nie ma ograniczenia ale jak da sie zero to petla nie rusza .. może trzeba dać coś większego
    limit_goods_unit[1] = 4000;
    limit_goods[0] = 36000;
    limit_goods[1] = 50000;

    //Zad3
//    main_table[0][0] = 1;
//    main_table[0][1] = 2;
//    main_table[0][2] = 1.5;
//    main_table[0][3] = 6;

//    main_table[1][0] = 2;
//    main_table[1][1] = 2;
//    main_table[1][2] = 1.5;
//    main_table[1][3] = 4;

//    limit_goods_unit[0] = 1000; // nie ma ograniczenia ale jak da sie zero to petla nie rusza .. może trzeba dać coś większego
//    limit_goods_unit[1] = 1000;
//    limit_goods_unit[2] = 1000; // nie ma ograniczenia ale jak da sie zero to petla nie rusza .. może trzeba dać coś większego
//    limit_goods_unit[3] = 1000;

//    limit_goods[0] = 90000;
//    limit_goods[1] = 120000;



    float current_result=0;
    float result =0;

    int x1, x2;
    //x3, x4;

    for(x1 = 1;x1 <= limit_goods_unit[0]; x1 ++) {

        for(x2 = 1; x2 <= limit_goods_unit[1]; x2++ ) {



                    //tu można dać checkboxa czy chcemy proporcje czy nie
                    //Zad1
        //            if(!(x1/x2 == 3/2)) {
                    // tu trzeba uważać na dzielenie przez 0
        //                continue;
        //            }

                    //Zad1 Zad2
                    if(!(main_table[0][0]*x1 + main_table[0][1]*x2 <= limit_goods[0])){
                        continue;
                    }

                    if(!(main_table[1][0]*x1 + main_table[1][1]*x2 <= limit_goods[1])){
                        continue;
                    }



                   //current_result = 30*x1 + 40*x2; //Zad1
                    current_result = x1 + x2; //Zad2
                   // current_result = 4*x1 + 6*x2 + 3*x3 + 12*x4; //Zad3
                    if(current_result > result) {
                        result = current_result;
                    }


        }
    }



    //float res = 170000;
    QString disp_res = QString::number(result);
    ui->result->setText(disp_res);
    qInfo() <<  x1;
    qInfo() <<  x2;


    delete[] limit_goods;
    delete [] limit_goods_unit;
    for ( int i(0); i < goods; ++i )  delete [] main_table[i];
    delete [] main_table;
}

