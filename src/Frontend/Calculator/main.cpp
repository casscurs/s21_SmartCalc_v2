#include <QApplication>

#include "mainwindow.h"

int main(int argc, char *argv[]) {
  QApplication a(argc, argv);
  QLocale::setDefault(QLocale(QLocale::English, QLocale::UnitedStates));
  MainWindow w;
  w.show();
  return a.exec();
}
