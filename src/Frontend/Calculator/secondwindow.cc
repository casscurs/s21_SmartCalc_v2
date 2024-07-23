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

  QString input_func = ui->lineEdit_formula->text();
  QString input_xmin = ui->lineEdit_Xmin->text();
  QString input_xmax = ui->lineEdit_Xmax->text();
  QString input_yrange = ui->lineEdit_Yrange->text();
  QString input_xrange = ui->lineEdit_Xrange->text();

  QByteArray byte_array_func = input_func.toLocal8Bit();
  QByteArray byte_array_xmin = input_xmin.toLocal8Bit();
  QByteArray byte_array_xmax = input_xmax.toLocal8Bit();
  QByteArray byte_array_yrange = input_yrange.toLocal8Bit();
  QByteArray byte_array_xrange = input_xrange.toLocal8Bit();

  char* char_array_func = byte_array_func.data();
  char* char_array_xmin = byte_array_xmin.data();
  char* char_array_xmax = byte_array_xmax.data();
  char* char_array_yrange = byte_array_yrange.data();
  char* char_array_xrange = byte_array_xrange.data();

  char_array_func[byte_array_func.size()] = '\0';
  char_array_xmin[byte_array_xmin.size()] = '\0';
  char_array_xmax[byte_array_xmax.size()] = '\0';
  char_array_yrange[byte_array_yrange.size()] = '\0';
  char_array_xrange[byte_array_xrange.size()] = '\0';

  double res = 0;
  double x_min = 0, x_max = 0, y_range = 0, x_range = 0;
  int answer = 1;

  if (!calcController.XReader(char_array_xmin, &x_min)) answer = 0;
  if (!calcController.XReader(char_array_xmax, &x_max)) answer = 0;
  if (!calcController.XReader(char_array_xrange, &x_range)) answer = 0;
  if (!calcController.XReader(char_array_yrange, &y_range)) answer = 0;

  if (answer && x_max > x_min) {
    step = 0.1;
    xBegin = x_min;
    xEnd = x_max;
    ui->widget->xAxis->setRange(-1 * x_range, x_range);
    ui->widget->yAxis->setRange(-1 * y_range, y_range);

    calcController.GraphCalc(xBegin, xEnd, x, y, char_array_func);

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
