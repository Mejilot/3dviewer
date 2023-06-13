#include <QApplication>

#include "mainwindow.h"

int main(int argc, char *argv[]) {
  QApplication a(argc, argv);
  msp::Model model;
  msp::Controller controller(&model);
  msp::MainWindow w;
  w.SetController(&controller);
  w.show();
  model.addView(&w);
  model.addWidget(w.GetWidget());
  return a.exec();
}
