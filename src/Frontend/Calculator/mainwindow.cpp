#include "mainwindow.h"

#include "./ui_mainwindow.h"
#include "secondwindow.h"

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent),
      ui(new Ui::MainWindow),
      creditSum_doubleValidator(0, 1000000000000000, 2, this),
      creditPeriod_doubleValidator(1, 600, 2, this),
      creditPercent_doubleValidator(0, 999, 2, this) {
  ui->setupUi(this);
  /* Блок валидатора */

  /* На кредитный */
  creditSum_doubleValidator.setNotation(QDoubleValidator::StandardNotation);
  creditPeriod_doubleValidator.setNotation(QDoubleValidator::StandardNotation);
  creditPercent_doubleValidator.setNotation(QDoubleValidator::StandardNotation);
  ui->lineEdit_sum->setValidator(&creditSum_doubleValidator);
  ui->lineEdit_period->setValidator(&creditPeriod_doubleValidator);
  ui->lineEdit_percent->setValidator(&creditPercent_doubleValidator);

  /* На депозитный */
  ui->lineEdit_depPercent->setValidator(&creditPercent_doubleValidator);
  ui->lineEdit_depPeriod->setValidator(&creditPeriod_doubleValidator);
  ui->lineEdit_depSum->setValidator(&creditSum_doubleValidator);
  ui->lineEdit_WithSum->setValidator(&creditSum_doubleValidator);
  ui->lineEdit_WithMonth->setValidator(&creditPeriod_doubleValidator);
  ui->lineEdit_AddSum->setValidator(&creditSum_doubleValidator);
  ui->lineEdit_AddMonth->setValidator(&creditPeriod_doubleValidator);

  /* На основной калькулятор */
  m_doubleValidator.setNotation(QDoubleValidator::StandardNotation);
  ui->lineEdit_X->setValidator(&m_doubleValidator);

  m_regexValidator.setRegularExpression(
      QRegularExpression("^[.1234567890+\\-x*/\\(\\)^cosintaqrlgomd\\s]*$"));
  ui->lineEdit_input->setValidator(&m_regexValidator);

  x_regexValidator.setRegularExpression(QRegularExpression("^[0-9.\\-+]*$"));
  ui->lineEdit_X->setValidator(&x_regexValidator);

  /* Блок сигналов от кнопок */
  connect(ui->pushButton_0, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->pushButton_1, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->pushButton_2, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->pushButton_3, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->pushButton_4, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->pushButton_5, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->pushButton_6, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->pushButton_7, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->pushButton_8, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->pushButton_9, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->pushButton_X, SIGNAL(clicked()), this, SLOT(digits_numbers()));

  connect(ui->pushButton_acos, SIGNAL(clicked()), this, SLOT(functions()));
  connect(ui->pushButton_asin, SIGNAL(clicked()), this, SLOT(functions()));
  connect(ui->pushButton_atan, SIGNAL(clicked()), this, SLOT(functions()));
  connect(ui->pushButton_sin, SIGNAL(clicked()), this, SLOT(functions()));
  connect(ui->pushButton_cos, SIGNAL(clicked()), this, SLOT(functions()));
  connect(ui->pushButton_tan, SIGNAL(clicked()), this, SLOT(functions()));
  connect(ui->pushButton_ln, SIGNAL(clicked()), this, SLOT(functions()));
  connect(ui->pushButton_log, SIGNAL(clicked()), this, SLOT(functions()));
  connect(ui->pushButton_sqrt, SIGNAL(clicked()), this, SLOT(functions()));

  connect(ui->pushButton_mod, SIGNAL(clicked()), this, SLOT(digits_numbers()));

  connect(ui->pushButton_bracketC, SIGNAL(clicked()), this,
          SLOT(digits_numbers()));
  connect(ui->pushButton_bracketO, SIGNAL(clicked()), this,
          SLOT(digits_numbers()));

  connect(ui->pushButton_div, SIGNAL(clicked()), this, SLOT(operations()));
  connect(ui->pushButton_dot, SIGNAL(clicked()), this, SLOT(operations()));
  connect(ui->pushButton_minus, SIGNAL(clicked()), this, SLOT(operations()));
  connect(ui->pushButton_plus, SIGNAL(clicked()), this, SLOT(operations()));
  connect(ui->pushButton_mult, SIGNAL(clicked()), this, SLOT(operations()));
  connect(ui->pushButton_pow, SIGNAL(clicked()), this, SLOT(operations()));
  /* Сигналы на депозитный */
  connect(ui->pushButton_Add, SIGNAL(clicked()), this, SLOT(pushToStackAdd()));
  connect(ui->pushButton_With, SIGNAL(clicked()), this,
          SLOT(pushToStackWith()));
}

MainWindow::~MainWindow() { delete ui; }

void MainWindow::digits_numbers() {
  /* Переменная, котоая хранит метод sender - возвращает нажатую кнопку*/
  QPushButton* button = (QPushButton*)sender();
  QString new_str = (ui->lineEdit_input->text() + button->text());
  /*setText - установка текста*/
  ui->lineEdit_input->setText(new_str);
}

void MainWindow::on_pushButton_ac_clicked() { ui->lineEdit_input->setText(""); }

void MainWindow::operations() {
  QPushButton* button = (QPushButton*)sender();
  QString new_str;
  new_str = ui->lineEdit_input->text();

  if (button->text() == "/" && !(ui->lineEdit_input->text().endsWith("/"))) {
    new_str += "/";
  } else if (button->text() == "*" &&
             !(ui->lineEdit_input->text().endsWith("*"))) {
    new_str += "*";
  } else if (button->text() == "+" &&
             !(ui->lineEdit_input->text().endsWith("+"))) {
    new_str += "+";
  } else if (button->text() == "-" &&
             !(ui->lineEdit_input->text().endsWith("-"))) {
    new_str += "-";
  } else if (button->text() == "pow" &&
             !(ui->lineEdit_input->text().endsWith("pow"))) {
    new_str += "^";
  } else if (button->text() == "sqrt" &&
             !(ui->lineEdit_input->text().endsWith("sqrt"))) {
    new_str += "sqrt(";
  } else if (button->text() == "mod" &&
             !(ui->lineEdit_input->text().endsWith("mod"))) {
    new_str += "mod";
  } else if (button->text() == "." &&
             !(ui->lineEdit_input->text().endsWith("."))) {
    new_str += ".";
  } else if (button->text() == "x" &&
             !(ui->lineEdit_input->text().endsWith("x"))) {
    new_str += "x";
  } else if (button->text() == "^" &&
             !(ui->lineEdit_input->text().endsWith("^"))) {
    new_str += "^";
  }
  ui->lineEdit_input->setText(new_str);
}

void MainWindow::functions() {
  QPushButton* button = (QPushButton*)sender();
  QString new_str;
  new_str = ui->lineEdit_input->text() + button->text() + "(";
  ui->lineEdit_input->setText(new_str);
}

void MainWindow::on_pushButton_res_clicked() {
  s21::CalcController calcController(&calcModel);

  QString inputText = ui->lineEdit_input->text();
  QString inputX = ui->lineEdit_X->text();

  QByteArray byteArray = inputText.toLocal8Bit();
  QByteArray byteArrayX = inputX.toLocal8Bit();

  char* charArray = byteArray.data();
  char* charArrayX = byteArrayX.data();

  charArray[byteArray.size()] = '\0';
  charArrayX[byteArrayX.size()] = '\0';

  if (calcController.calc(charArray, charArrayX)) {
    ui->lineEdit_input->setText(QString::number(calcController.getCalcData()));
  } else {
    ui->lineEdit_input->setText("Invalid input");
  }
}

void MainWindow::on_pushButton_graph_clicked() {
  SecondWindow* window =
      new SecondWindow();  // Создание указателя на новый виджет
  window->setAttribute(
      Qt::WA_DeleteOnClose);  // Указываем Qt удалять объект после закрытия
  window->show();
}

void MainWindow::on_pushButton_calc_clicked() {
  QString inputSum = ui->lineEdit_sum->text();
  QString inputPeriod = ui->lineEdit_period->text();
  QString inputPercent = ui->lineEdit_percent->text();

  QByteArray byteArraySum = inputSum.toLocal8Bit();
  QByteArray byteArrayPeriod = inputPeriod.toLocal8Bit();
  QByteArray byteArrayPercent = inputPercent.toLocal8Bit();

  char* charArraySum = byteArraySum.data();
  char* charArrayPeriod = byteArrayPeriod.data();
  char* charArrayPercent = byteArrayPercent.data();

  charArraySum[byteArraySum.size()] = '\0';
  charArrayPeriod[byteArrayPeriod.size()] = '\0';
  charArrayPercent[byteArrayPercent.size()] = '\0';

  if (ui->radioButton_anny->isChecked()) {
    s21::CreditController creditController(&creditModel);
    int type = creditController.ANNUITY;
    if (creditController.credit(charArraySum, charArrayPeriod, charArrayPercent,
                                type)) {
      ui->plainTextEdit_output->clear();
      ui->plainTextEdit_output->appendPlainText(
          "Ежемесячный платеж: " +
          QString::number(creditController.getCreditData().monthly, 'f', 2));
      ui->plainTextEdit_output->appendPlainText(
          "Переплата: " +
          QString::number(creditController.getCreditData().overpay, 'f', 2));
      ui->plainTextEdit_output->appendPlainText(
          "Общая сумма: " +
          QString::number(creditController.getCreditData().total, 'f', 2));
    } else
      ui->plainTextEdit_output->setPlainText("Invalid input");
  }

  if (ui->radioButton_diff->isChecked()) {
    s21::CreditController creditController(&creditModel);
    s21::CalcController calcController(&calcModel);

    int type = creditController.DIFFERENTIATED;
    double period = 0;

    if (calcController.readX(charArrayPeriod, &period) &&
        creditController.credit(charArraySum, charArrayPeriod, charArrayPercent,
                                type)) {
      ui->plainTextEdit_output->clear();
      for (int i = 0; i < (int)period; ++i) {
        ui->plainTextEdit_output->appendPlainText(
            "Месяц " + QString::number(i + 1) + ": " +
            QString::number(creditController.getCreditData().valArr[i], 'f',
                            2));
      }
      ui->plainTextEdit_output->appendPlainText(
          "Переплата: " +
          QString::number(creditController.getCreditData().overpay, 'f', 2));
      ui->plainTextEdit_output->appendPlainText(
          "Общая сумма: " +
          QString::number(creditController.getCreditData().total, 'f', 2));
    } else
      ui->plainTextEdit_output->setPlainText("Invalid input");
  }
}

void MainWindow::on_pushButton_depCalc_clicked() {
  s21::DepositController depositController(&depositModel);

  s21::DepositModel::output depOut = {};
  s21::DepositModel::inputStr str = {};

  QString inputSum = ui->lineEdit_depSum->text();
  QString inputPeriod = ui->lineEdit_depPeriod->text();
  QString inputPercent = ui->lineEdit_depPercent->text();

  QByteArray byteArraySum = inputSum.toLocal8Bit();
  QByteArray byteArrayPeriod = inputPeriod.toLocal8Bit();
  QByteArray byteArrayPercent = inputPercent.toLocal8Bit();

  char* charArraySum = byteArraySum.data();
  char* charArrayPeriod = byteArrayPeriod.data();
  char* charArrayPercent = byteArrayPercent.data();

  charArraySum[byteArraySum.size()] = '\0';
  charArrayPeriod[byteArrayPeriod.size()] = '\0';
  charArrayPercent[byteArrayPercent.size()] = '\0';

  if (ui->checkBox_cap->isChecked()) str.capital = 1;
  if (ui->radioButton_yearly->isChecked()) str.regularity = depositModel.YEARLY;
  str.depositSumStr = charArraySum;
  str.percentStr = charArrayPercent;
  str.periodStr = charArrayPeriod;

  depositController.sortStackByPriority(&add);
  depositController.sortStackByPriority(&with);

  depositController.operationsInMonth(&add);
  depositController.operationsInMonth(&with);

  if (depositController.deposit(str, &add, &with)) {
    ui->plainTextEdit_dep->clear();
    ui->plainTextEdit_dep->appendPlainText(
        "Начисленные проценты: " +
        QString::number(depositController.getDepositData().percentAward, 'f',
                        2));
    ui->plainTextEdit_dep->appendPlainText(
        "Сумма налога: " +
        QString::number(depositController.getDepositData().taxAmount, 'f', 2));
    ui->plainTextEdit_dep->appendPlainText(
        "Сумма на вкладе к концу срока: " +
        QString::number(depositController.getDepositData().totalAward, 'f', 2));
  } else
    ui->plainTextEdit_dep->setPlainText("Invalid input");
  popAndClearStackAdd();
  popAndClearStackWith();
}

void MainWindow::pushToStackAdd() {
  s21::CalcController calcController(&calcModel);
  s21::DepositController depositController(&depositModel);

  QString inputAddSum = ui->lineEdit_AddSum->text();
  QByteArray byteArrayAddSum = inputAddSum.toLocal8Bit();
  char* charArrayAddSum = byteArrayAddSum.data();
  charArrayAddSum[byteArrayAddSum.size()] = '\0';

  QString inputAddMonth = ui->lineEdit_AddMonth->text();
  QByteArray byteArrayAddMonth = inputAddMonth.toLocal8Bit();
  char* charArrayAddMonth = byteArrayAddMonth.data();
  charArrayAddMonth[byteArrayAddMonth.size()] = '\0';

  double addsum = 0, addmonth = 0;

  if (!calcController.readX(charArrayAddSum, &addsum) ||
      !calcController.readX(charArrayAddMonth, &addmonth) ||
      (addmonth < 1 || addmonth - (int)addmonth > 0)) {
    ui->plainTextEdit_dep->setPlainText("Invalid input");
  } else {
    add = depositController.pushStackNode(add);
    add->priority = addmonth;
    add->what = depositController.ADDITION;
    add->value = addsum;
  }
}
void MainWindow::pushToStackWith() {
  s21::CalcController calcController(&calcModel);
  s21::DepositController depositController(&depositModel);

  QString inputWithSum = ui->lineEdit_WithSum->text();
  QByteArray byteArrayWithSum = inputWithSum.toLocal8Bit();
  char* charArrayWithSum = byteArrayWithSum.data();
  charArrayWithSum[byteArrayWithSum.size()] = '\0';

  QString inputWithMonth = ui->lineEdit_WithMonth->text();
  QByteArray byteArrayWithMonth = inputWithMonth.toLocal8Bit();
  char* charArrayWithMonth = byteArrayWithMonth.data();
  charArrayWithMonth[byteArrayWithMonth.size()] = '\0';

  double withsum = 0, withmonth = 0;

  if (!calcController.readX(charArrayWithSum, &withsum) ||
      !calcController.readX(charArrayWithMonth, &withmonth) ||
      (withmonth < 1 || withmonth - (int)withmonth > 0)) {
    ui->plainTextEdit_dep->setPlainText("Invalid input");
  } else {
    with = depositController.pushStackNode(with);
    with->priority = withmonth;
    with->what = depositController.WITHRAWAL;
    with->value = withsum;
  }
}

void MainWindow::popAndClearStackWith() {
  s21::DepositController depositController(&depositModel);
  depositController.freeStack(with);
  with = nullptr;
}
void MainWindow::popAndClearStackAdd() {
  s21::DepositController depositController(&depositModel);
  depositController.freeStack(add);
  add = nullptr;
}
