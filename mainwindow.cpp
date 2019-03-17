#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "W2VLib/wordlist.h"

#include <QString>
#include <iostream>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->actVocab, SIGNAL(triggered()), this, SLOT(textProcessing()));

}

MainWindow::~MainWindow()
{
    delete ui;
}


Vec<int> MainWindow::getTextVec(){
    QString input = ui->teInput->toPlainText();
    Vec<int> in;
    for(int i=0; i<input.length(); i++)
        in.push_back(input[i].unicode());
    return in;
}

void MainWindow::writeVector(Vec<int> &v)
{
    QString out;
    for (int i=0; i<v.Size(); i++)
        out.append(QString::number(v[i]) + ", ");
    ui->teInput->setText(out);
}

void MainWindow::textProcessing(){
   Vec<int> input = getTextVec();
   WordList wl(input, '\n');
  // Vec<int> output = wl.GetWord(0).get();
   Vec<int> count;
   count.push_back(wl.SizeVocab());
   writeVector(count);


}
