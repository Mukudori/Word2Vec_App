#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "W2VLib/wordlist.h"


#include <QString>
#include <QStandardItemModel>
#include <QStandardItem>
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

QString MainWindow::vecToQString(Vec<int> &v)
{
    QString wName;
    for (int i=0; i<v.Size(); i++)
        wName.append(v[i]);
    return wName;
}

QString MainWindow::vecToQString(Vec<Sentence> &vs)
{
    QString wName;

    return wName;
}

QString MainWindow::vecToNumberQString(Vec<int> &v)
{
    QString wName;
    for (int i=0; i<v.Size(); i++)
        wName.append(QString::number(v[i]));
    return wName;
}

void MainWindow::writeCode(){
    ui->teInput->setText(QString::number(ui->teInput->toPlainText()[0].unicode()));
}

void MainWindow::writeVocab(Vec<Word> &w)
{
    QStandardItemModel *model = new QStandardItemModel(w.Size(),3, ui->tvVocab);
    ui->tvVocab->setModel(model);

    model->setHorizontalHeaderLabels({QString("id"), QString("Слово"), QString("Вхождения")});

    for(int row=0; row!=model->rowCount(); ++row){

            QStandardItem *id = new QStandardItem(QString::number(row));
            model->setItem(row, 0, id);
            Vec<int> vWord = w[row].get();
            QStandardItem *word = new QStandardItem(vecToQString(vWord));
            model->setItem(row, 1, word);
            QStandardItem *inst = new QStandardItem(QString::number(w[row].getInstance()));
            model->setItem(row, 2, inst);

        }


}


void MainWindow::writeSentences(Vec<Sentence> &s){
    QStandardItemModel *model = new QStandardItemModel(s.Size(),3, ui->tvVocab);
    ui->tvSenten->setModel(model);

    model->setHorizontalHeaderLabels({QString("id"), QString("Кодированное предложение"), QString("Предложение")});

    for(int row=0; row!=model->rowCount(); ++row){

            QStandardItem *id = new QStandardItem(QString::number(row));
            model->setItem(row, 0, id);
            //Vec<int> is =  s[row].
    }


}

void MainWindow::textProcessing(){
   Vec<int> input = getTextVec();
   WordList wl(input, 10);
  // Vec<int> output = wl.GetWord(0).get();
   Vec<Word> w = wl.getVocab();

   writeVocab(w);

}
