#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QString>
#include <iostream>
#include <random>
#include <algorithm>
#include <time.h>
#include "point.h"
#include "curve.h"
#include "circle.h"
#include "ellipse.h"
#include "spiral.h"

using namespace std;

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;

    void fill_first_container(vector<Curve*> &curves);
    void clear_table();
    void value_output(vector<Curve*> &curves);
    void fill_second_container_circles(vector<Curve*> &curves, vector<Curve*> &circle_curves);
    void circle_sort(vector<Curve*> &circle_curves);
    void find_sum_radii(vector<Curve*> &circle_curves);

private slots:
    void clicked_button_start();
};
#endif // MAINWINDOW_H
