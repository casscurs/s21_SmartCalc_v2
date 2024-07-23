#ifndef SECONDWINDOW_H
#define SECONDWINDOW_H

#include <QMainWindow>
#include "qcustomplot.h"
#include <vector>
#include <QVector>
#include "../../Backend/controller/s21_calc_controller.h"

namespace Ui {
class SecondWindow;
}

class SecondWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit SecondWindow(QWidget *parent = nullptr);
    ~SecondWindow();

private slots:
    void on_pushButton_plot_clicked();

private:
    Ui::SecondWindow *ui;
    QDoubleValidator m_doubleValidator;
    QRegularExpressionValidator m_regexValidator;
    s21::CalcModel calcModel;
    double xBegin, xEnd, step, X;
    int quantity;
    std::vector<double> x,y;

};

#endif // SECONDWINDOW_H
