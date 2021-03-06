#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>


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
    void on_startTest_clicked();
    void set();
    void on_get_variables_clicked();

    void on_add_limit_clicked();

    void on_reset_limits_clicked();

private:
    Ui::MainWindow *ui;

};
#endif // MAINWINDOW_H
