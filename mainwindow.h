#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "W2VLib/vec.h"
#include "W2VLib/wordlist.h"

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
    void writeCode();
    void writeVocab(Vec<Word> &w);
    void writeSentences(Vec<Sentence> &s);
    QString vecToQString(Vec<int> &v);
    QString vecToQString(Vec<Sentence> &vs);
    QString vecToNumberQString(Vec<int> &v);
    QString vecToNumberQString(Vec<Sentence> &vs);

};

#endif // MAINWINDOW_H
