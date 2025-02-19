#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QValidator>

#include "../../Backend/controller/s21_calc_controller.h"
#include "../../Backend/controller/s21_credit_controller.h"
#include "../../Backend/controller/s21_deposit_controller.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public:
s21::DepositController depositController;

private:
    Ui::MainWindow *ui;
    QDoubleValidator m_doubleValidator;
    QDoubleValidator creditSum_doubleValidator;
    QDoubleValidator creditPeriod_doubleValidator;
    QDoubleValidator creditPercent_doubleValidator;
    QRegularExpressionValidator m_regexValidator;
    QRegularExpressionValidator x_regexValidator;
    s21::CalcModel calcModel;
    s21::CreditModel creditModel;
    s21::DepositModel depositModel;

private slots:
    void digits_numbers();
    void on_pushButton_ac_clicked();
    void operations();
    void functions();
    void on_pushButton_res_clicked();
    void on_pushButton_graph_clicked();
    void on_pushButton_calc_clicked();
    void on_pushButton_depCalc_clicked();
    void pushToStackAdd();
    void pushToStackWith();

};

#endif // MAINWINDOW_H
