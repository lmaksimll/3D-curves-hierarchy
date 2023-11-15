#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->table_point->verticalHeader()->setVisible(false);
    ui->table_derivative->verticalHeader()->setVisible(false);

    connect(ui->pushButton_start,SIGNAL(clicked()),this,SLOT(clicked_button_start()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::fill_first_container(vector<Curve*> &curves)
{
    int count_curves = ui->spinBox_count->value();

    //--------------randoms block----------
    random_device rd;                               // non-deterministic generator
    mt19937 gen(rd());                              // to seed mersenne twister.
    uniform_int_distribution<> dist_type(1,3);      // distribute results between 1 and 3 inclusive.
    uniform_int_distribution<> dist_point(1,1000);   // distribute results between 1 and 100 inclusive.
    //-------------------------------------

    for (int i = 0; i < count_curves; ++i)
    {
        int type_curves = dist_type(gen);

        switch (type_curves) {
        case 1:
            curves.push_back(new Circle(dist_point(gen)));
            break;

        case 2:
            curves.push_back(new Ellipse(dist_point(gen),dist_point(gen)));
            break;

        case 3:
            curves.push_back(new Spiral(dist_point(gen),dist_point(gen)));
            break;
        default:
            break;
        }
    }
}

void MainWindow::clear_table()
{
    int rowCount = ui->table_point->rowCount();
    int columnCount = ui->table_point->columnCount();

    for (int i = 0; i < rowCount; i++)
    {
        for (int j = 0; j < columnCount; j++)
        {
            QTableWidgetItem *item1 = ui->table_point->takeItem(i, j);
            QTableWidgetItem *item2 = ui->table_derivative->takeItem(i, j);
            delete item1;
            delete item2;
        }
    }
    ui->table_point->setRowCount(0);
    ui->table_derivative->setRowCount(0);

}

void MainWindow::value_output(vector<Curve*> &curves)
{
    for (auto curve : curves)
    {
            Point point_curve = curve->get_point(M_PI/4);
            Point derivative_curves = curve->get_derivative(M_PI/4);

            ui->table_point->insertRow(ui->table_point->rowCount());
            ui->table_derivative->insertRow(ui->table_derivative->rowCount());
            int newRow = ui->table_point->rowCount()-1;

            ui->table_point->setItem(newRow, 0, new QTableWidgetItem(QString::number(point_curve.get_coord_x())));
            ui->table_point->setItem(newRow, 1, new QTableWidgetItem(QString::number(point_curve.get_coord_y())));
            ui->table_point->setItem(newRow, 2, new QTableWidgetItem(QString::number(point_curve.get_coord_z())));

            ui->table_derivative->setItem(newRow, 0, new QTableWidgetItem(QString::number(derivative_curves.get_coord_x())));
            ui->table_derivative->setItem(newRow, 1, new QTableWidgetItem(QString::number(derivative_curves.get_coord_y())));
            ui->table_derivative->setItem(newRow, 2, new QTableWidgetItem(QString::number(derivative_curves.get_coord_z())));
    }
}

void MainWindow::fill_second_container_circles(vector<Curve *> &curves, vector<Curve *> &circle_curves)
{
    for (auto curve : curves)
    {
        if (dynamic_cast<Circle*>(curve))
        {
            circle_curves.push_back(static_cast<Circle*>(curve));
        }
    }
}

void MainWindow::circle_sort(vector<Curve *> &circle_curves)
{
    sort(circle_curves.begin(), circle_curves.end(), [](Curve* a, Curve* b) {
        return a->get_point(0).get_coord_x() < b->get_point(0).get_coord_x();
    });
}

void MainWindow::find_sum_radii(vector<Curve *> &circle_curves)
{
    clock_t tStart = clock();

    double sum_radii = 0;
    if(ui->radioButton_one_th->isChecked())
    {
        for (auto circle : circle_curves) {
            sum_radii += circle->get_point(0).get_coord_x();
        }
    }
    else
    {
        #pragma omp parallel for reduction(+:sum_radii)
        for (auto circle : circle_curves) {
            sum_radii += circle->get_point(0).get_coord_x();
        }
    }

    ui->spinBox_sum->setValue(sum_radii);
    QString time_str = QString::number((double)(clock() - tStart)/CLOCKS_PER_SEC) + "s";
    ui->lineEdit_time->setText(time_str);
}

void MainWindow::clicked_button_start()
{
    vector<Curve*> curves;

    fill_first_container(curves);       //fill the type container randomly

    clear_table();                      //clean the table before filling

    value_output(curves);               //print coordinates of points and derivatives at t=PI/4

    vector<Curve*> circle_curves;

    fill_second_container_circles(curves,circle_curves);    //create a second container and fill it with circles

    circle_sort(circle_curves);         //sorted container by radius

    find_sum_radii(circle_curves);      //multithreaded calculation of the sum of radii

    curves.clear();                     // Clean up memory
    circle_curves.clear();
}

