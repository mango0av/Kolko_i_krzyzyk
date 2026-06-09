#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "gra.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_btnPvP_clicked();
    void on_btnPvE_clicked();
    void on_btnStart_clicked();
    void on_btnReset_clicked();

private:
    Ui::MainWindow *ui;

    Gra silnikGry;       //tu silnik wazne
    void odswiezPanel();
    void zapiszWygranaDoPliku(QString zwyciezca);
    void odswiezTabeleRankingu();
    int ostRuchX_Czlowiek = -1;
    int ostRuchY_Czlowiek = -1;
    int ostRuchX_Bot = -1;
    int ostRuchY_Bot = -1;
};
#endif // MAINWINDOW_H
