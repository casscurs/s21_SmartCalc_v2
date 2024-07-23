#include "secondwindow.h"

#include <QMessageBox>

#include "ui_secondwindow.h"

SecondWindow::SecondWindow(QWidget* parent)
    : QMainWindow(parent),
      ui(new Ui::SecondWindow),
      m_doubleValidator(-1000000, 1000000, 2, this) {
  ui->setupUi(this);

  m_doubleValidator.setNotation(QDoubleValidator::StandardNotation);
  ui->lineEdit_Xmax->setValidator(&m_doubleValidator);
  ui->lineEdit_Xmin->setValidator(&m_doubleValidator);
  ui->lineEdit_Yrange->setValidator(&m_doubleValidator);
  ui->lineEdit_Xrange->setValidator(&m_doubleValidator);

  m_regexValidator.setRegularExpression(
      QRegularExpression("^[.1234567890+\\-x*/\\(\\)^cosintaqrlgomd\\s]*$"));
  ui->lineEdit_formula->setValidator(&m_regexValidator);
}

SecondWindow::~SecondWindow() { delete ui; }

void SecondWindow::on_pushButton_plot_clicked() {
  s21::CalcController calcController(&calcModel);

  QString inputFunc = ui->lineEdit_formula->text();
  QString inputXmin = ui->lineEdit_Xmin->text();
  QString inputXmax = ui->lineEdit_Xmax->text();
  QString inputYrange = ui->lineEdit_Yrange->text();
  QString inputXrange = ui->lineEdit_Xrange->text();

  QByteArray byteArrayFunc = inputFunc.toLocal8Bit();
  QByteArray byteArrayXmin = inputXmin.toLocal8Bit();
  QByteArray byteArrayXmax = inputXmax.toLocal8Bit();
  QByteArray byteArrayYrange = inputYrange.toLocal8Bit();
  QByteArray byteArrayXrange = inputXrange.toLocal8Bit();

  char* charArrayFunc = byteArrayFunc.data();
  char* charArrayXmin = byteArrayXmin.data();
  char* charArrayXmax = byteArrayXmax.data();
  char* charArrayYrange = byteArrayYrange.data();
  char* charArrayXrange = byteArrayXrange.data();

  charArrayFunc[byteArrayFunc.size()] = '\0';
  charArrayXmin[byteArrayXmin.size()] = '\0';
  charArrayXmax[byteArrayXmax.size()] = '\0';
  charArrayYrange[byteArrayYrange.size()] = '\0';
  charArrayXrange[byteArrayXrange.size()] = '\0';

  double res = 0;
  double Xmin = 0, Xmax = 0, Yrange = 0, Xrange = 0;
  int answer = 1;

  if (!calcController.readX(charArrayXmin, &Xmin)) answer = 0;
  if (!calcController.readX(charArrayXmax, &Xmax)) answer = 0;
  if (!calcController.readX(charArrayXrange, &Xrange)) answer = 0;
  if (!calcController.readX(charArrayYrange, &Yrange)) answer = 0;

  if (answer && Xmax > Xmin) {
    step = 0.1;
    xBegin = Xmin;
    xEnd = Xmax;
    ui->widget->xAxis->setRange(-1 * Xrange, Xrange);
    ui->widget->yAxis->setRange(-1 * Yrange, Yrange);

    calcController.graphCalc(xBegin, xEnd, x, y, charArrayFunc);

    QVector<double> Qx(x.begin(), x.end());
    QVector<double> Qy(y.begin(), y.end());

    if (ui->radioButton_points->isChecked()) {
      /* Точки */
      ui->widget->clearGraphs();
      ui->widget->addGraph();
      ui->widget->graph(0)->setPen(QColor(50, 50, 50, 255));
      ui->widget->graph(0)->setLineStyle(QCPGraph::lsNone);
      ui->widget->graph(0)->setScatterStyle(
          QCPScatterStyle(QCPScatterStyle::ssCircle, 4));
      ui->widget->graph(0)->addData(Qx, Qy);
      ui->widget->replot();
    }
    if (ui->radioButton_line->isChecked()) {
      /* Линии */
      ui->widget->clearGraphs();
      ui->widget->addGraph();
      ui->widget->graph(0)->addData(Qx, Qy);
      ui->widget->replot();
    }
    // зум и сдвиг
    ui->widget->setInteraction(QCP::iRangeZoom, true);
    ui->widget->setInteraction(QCP::iRangeDrag, true);
    x.clear();
    y.clear();
  } else {
    QMessageBox::warning(this, "Ошибка", "Invalid input.");
  }
}
