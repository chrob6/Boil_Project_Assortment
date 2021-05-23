#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "Simplex.cpp"
#include <QDebug>
#include <stdio.h>
#include <stdlib.h>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->startTest->setText("Calculate");
    ui->pushButton->setText("Close");
    ui->get_variables->setText("Insert Variables");
    ui->result_text->setText("Optimal Result");
    ui->result_calculation->setText(" ");
    ui->result_variables->setText(" ");

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::set(){ //po ustwieniu spinBox_2?
   // int goods = ui->spinBox->value();
   // int material = ui->spinBox_2->value();
    //ui->tableWidget->setRowCount(material); //tabela 1 do wczytania nakładów jednostkowych
    //ui->tableWidget->setColumnCount(goods);
}



void MainWindow::on_startTest_clicked()
{

     // int material = ui->spinBox_2->value();
      int meaningVariables = ui->spinBox_3->value();
      int colSizeA = meaningVariables;
      int rowSizeA =ui->table_limits->rowCount();
      int howManyEquality = 0;
      int indexToPutSlackVar = 0;

      vector<float> _a;
      vector<float> _c;
      vector<float> _b;


      // ui->table_limits->item(1,1);
      cout << "Function: ";
      for(int i = 0; i < ui->table_max_function->columnCount(); i++) {
           QString number_string =  ui->table_max_function->item(0,i)->text();
           float number = number_string.toFloat();
          // cout << number<< " ";
           _c.push_back( (-1) *number);
      }

      for(int i = 0; i < ui->table_limits->rowCount(); i++) {

          for(int j = 0; j < ui->table_limits->columnCount(); j++) {

           QString item_string = ui->table_limits->item(i,j)->text();

              if( item_string == "<=" || item_string == ">=" ) {
                colSizeA++;
              }
              else if( item_string == "=") {
                colSizeA++;
                howManyEquality++;
              }
          }

      }

      for(int i = 0;i < howManyEquality; i++) {
          _c.push_back(100000);
      }


      //equality first -> idk why, due to algorithm
      for(int i = 0; i < ui->table_limits->rowCount(); i++) {

          vector<float> temp;
          for(int j = 0; j < ui->table_limits->columnCount(); j++) {

               if(howManyEquality > 0) {

               QString item_string = ui->table_limits->item(i,j)->text();

                  float number = item_string.toFloat();
                  if( item_string == "=") {
                    howManyEquality--;

                    for(auto c : temp) {
                        _a.push_back(c);
                    }

                    bool oneTimeAccess = true;
                    for(int i = 0; i < colSizeA - meaningVariables; i++) {


                        if(oneTimeAccess && indexToPutSlackVar == i) {
                            _a.push_back(1);
                            indexToPutSlackVar++;
                            oneTimeAccess = false;
                        }
                        else {
                            _a.push_back(0);
                        }

                    }

                    QString item_string = ui->table_limits->item(i,j+1)->text();
                     float limit = item_string.toFloat();
                    _b.push_back(limit);
                    break;

                  }
                  temp.push_back(number);
              }
          }

      }

      //rest later
      bool multiply_minus = false;
      for(int i = 0; i < ui->table_limits->rowCount(); i++) {
          vector<float> temp;
          for(int j = 0; j < ui->table_limits->columnCount(); j++) {


                 QString item_string = ui->table_limits->item(i,j)->text();

                  float number = item_string.toFloat();
                  if( item_string == "<=" || item_string == ">=" ) {
                     if( item_string == ">=") {
                         multiply_minus = true;
                     }

                     for(auto c : temp) {
                         if(multiply_minus) {
                             c = c * -1;
                         }
                         _a.push_back(c);
                     }

                    bool oneTimeAccess = true;
                    for(int i = 0; i < colSizeA - meaningVariables; i++) {

                        if(oneTimeAccess && indexToPutSlackVar == i) {
                            _a.push_back(1);
                            indexToPutSlackVar++;
                            oneTimeAccess = false;
                        }
                        else {
                            _a.push_back(0);
                        }

                    }

                    QString item_string = ui->table_limits->item(i,j+1)->text();
                     float limit = item_string.toFloat();
                     if(multiply_minus) {
                         limit = limit * -1;
                         multiply_minus = false;
                     }
                    _b.push_back(limit);
                    break;

                  }
                  temp.push_back(number);

          }

      }

      while((int)_c.size() != colSizeA) {
          _c.push_back(0);
      }
//      for(int i =0; i < (int)(colSizeA - _c.size()); i++) {
//            _c.push_back(0);
//      }


       float *C = new float[colSizeA];
       float *B = new float[rowSizeA];
       float **a = new float*[rowSizeA];
       for ( int i = 0; i < rowSizeA; ++i )
        {
             a[i] = new float [colSizeA]; //alokacja pamieci
        }

      cout<< endl << endl << "A" << _a.size() << endl;

      for(auto i : _a) {
          cout << i << " ,";
      }


      int k = 0;
      for(int i = 0; i < rowSizeA; i++) {
          for(int j = 0; j < colSizeA; j++) {
              a[i][j] = _a[k];
              k++;
          }
      }

      cout<< endl << endl << "B" << endl;

      int it = 0;
      for(auto i : _b) {
          cout << i << " ,";
          B[it] = i;
          it++;
      }
      cout<< endl << endl << "C" << endl;
      it = 0;
      for(auto i : _c) {
          cout << i << " ,";
          C[it] = i;
          it++;
      }

      cout << endl << endl;
      for(int i = 0; i < rowSizeA; i++) {
          for(int j = 0; j < colSizeA; j++) {
              cout << a[i][j]  << " ";
          }
          cout << endl;
      }
      cout << endl << endl;

     // int colSizeA= 8;  //should initialise columns size in A
     // int rowSizeA = 5;  //should initialise columns row in A[][] vector

     // float C[]= {-6,-5,-4,0,0,0};  //should initialis the c arry here

     // float C[]= {-1800,-2400,-3000,10000,100000,0,0,0};
     // float B[]={3600,4800,200,120,60};  // should initialis the b array here

     // float B[]={120,60,200,3600,4800};







//      float a[5][8] = {    //should intialis the A[][] array here
//                     { 0,  1, 0, 1, 0, 0, 0, 0},
//                     { 0,  0, 1, 0, 1, 0, 0, 0},
//                     { 1,  0, 0, 0, 0, 1, 0, 0},
//                     { 5,  3, 1, 0, 0, 0, 1, 0},
//                     { 1,  2, 4, 0, 0, 0, 0, 1}

//               };


          std::vector <std::vector<float> > vec2D(rowSizeA, std::vector<float>(colSizeA, 0));

          std::vector<float> b(rowSizeA,0);
          std::vector<float> c(colSizeA,0);




         for(int i=0;i<rowSizeA;i++){         //make a vector from given array
              for(int j=0; j<colSizeA;j++){
                  vec2D[i][j] = a[i][j];
              }
         }





         for(int i=0;i<rowSizeA;i++){
              b[i] = B[i];
         }

          for(int i=0;i<colSizeA;i++){
              c[i] = C[i];
         }


        // hear the make the class parameters with A[m][n] vector b[] vector and c[] vector
        Simplex simplex(vec2D,b,c);
        vector<string> display = simplex.CalculateSimplex(meaningVariables);

        QString qDisplayVar = QString::fromStdString(display[0]);
        QString qDisplayMax = QString::fromStdString(display[1]);

         ui->result_calculation->setText(qDisplayMax);
         ui->result_variables->setText(qDisplayVar);




}


void MainWindow::on_get_variables_clicked()
{
     int meaningVariables = ui->spinBox_3->value();
     ui->table_max_function->setColumnCount(meaningVariables);
     ui->table_max_function->setRowCount(1);
     QStringList labelColumnList;
     QStringList labelRowList;

     for (int i = 0; i < meaningVariables; i++) {
         QString x = "x";
         int second_char_x = i+1;
         QString s = QString::number(second_char_x);
         x = x + s;
        labelColumnList.append(x);
     }

     ui->table_max_function->setHorizontalHeaderLabels(labelColumnList);

     QString coef = "coef.";
     labelRowList.append(coef);
     ui->table_max_function->setVerticalHeaderLabels(labelRowList);
}


void MainWindow::on_add_limit_clicked()
{
     int meaningVariables = ui->spinBox_3->value();
     ui->table_limits->setColumnCount(meaningVariables+2);

     QStringList labelColumnList;
     for (int i = 0; i < meaningVariables; i++) {
         QString x = "x";
         int second_char_x = i+1;
         QString s = QString::number(second_char_x);
         x = x + s;
        labelColumnList.append(x);
     }
     labelColumnList.append("symbol");
     labelColumnList.append("limit");
     ui->table_limits->setHorizontalHeaderLabels(labelColumnList);
    // ui->table_limits->insertRow(1);
     ui->table_limits->setRowCount(ui->table_limits->rowCount() + 1);
}


void MainWindow::on_reset_limits_clicked()
{
    ui->table_limits->setRowCount(0);
    ui->table_limits->setColumnCount(0);
}

