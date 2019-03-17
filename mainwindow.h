#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "W2VLib/vec.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public slots:
    void textProcessing();

private:
    Ui::MainWindow *ui;
    Vec<int> getTextVec();
    void writeVector(Vec<int> &v);

};

#endif // MAINWINDOW_H
