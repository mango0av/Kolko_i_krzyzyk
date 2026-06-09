#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QFile>
#include <QTextStream>
#include <vector>
#include <algorithm>

//filtr nicków
bool czyCenzurowac(QString tekst) {
    QStringList zakazane = {"kurw", "chuj", "jeb", "pizd", "pierdol", "dziwk", "szmat", "gówn", "srak"};

    for (const QString &slowo : zakazane) {
        if (tekst.contains(slowo, Qt::CaseInsensitive)) {
            return true;
        }
    }
    return false;
}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->tableLeaderboard->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->stackedWidget->setCurrentIndex(0); //wymuszenie 1 eranu

    for(int i = 0; i < 3; i++)
    {
        for(int j = 0; j < 3; j++)
        {
            QString nazwaGuzika = "btn_" + QString::number(i) + "_" + QString::number(j);
            QPushButton *guzik = this->findChild<QPushButton*>(nazwaGuzika);

            if(guzik != nullptr)
            {
                connect(guzik, &QPushButton::clicked, this, [=]()
                        {
                    char stanPrzed[3][3];
                    for(int r=0; r<3; r++)
                    {
                        for(int c=0; c<3; c++)
                        {
                            stanPrzed[r][c] = silnikGry.pobierzZnakZPlanszy(r, c);
                        }
                    }


                    silnikGry.obsluzKlikniecie(i, j);


                    ostRuchX_Czlowiek = i;
                    ostRuchY_Czlowiek = j;


                    for(int r=0; r<3; r++)
                    {
                        for(int c=0; c<3; c++)
                        {
                            char znakPo = silnikGry.pobierzZnakZPlanszy(r, c);

                            if (stanPrzed[r][c] != 'X' && stanPrzed[r][c] != 'O' &&
                                (znakPo == 'X' || znakPo == 'O') && !(r == i && c == j))
                            {
                                ostRuchX_Bot = r;
                                ostRuchY_Bot = c;
                            }
                        }
                    }

                    if (silnikGry.czyGraTrwa() == false)
                    {
                        odswiezPanel();

                        QString zwyciezca = QString::fromStdString(silnikGry.pobierzNickAktualnego());

                        zapiszWygranaDoPliku(zwyciezca);
                        odswiezTabeleRankingu();

                        QMessageBox msgBox(this);
                        msgBox.setWindowTitle("Koniec Gry");
                        msgBox.setText("Wygrywa: " + zwyciezca + "!");

                        msgBox.setStyleSheet(
                            "QMessageBox { "
                            "   background-color: #729fcf; "
                            "   border: 5px solid #ad7fa8; "
                            "} "
                            "QLabel { "
                            "   color: #fce94f; "
                            "   font-size: 32px; "
                            "   font-weight: bold; "
                            "} "
                            "QPushButton { "
                            "   background-color: #ad7fa8; "
                            "   color: black; "
                            "   font-weight: bold; "
                            "   font-size: 20px; "
                            "   border: 2px solid black; "
                            "   border-radius: 10px; "
                            "   min-width: 120px; "
                            "   min-height: 40px; "
                            "} "
                            "QPushButton:hover { "
                            "   background-color: #fce94f; "
                            "}"
                            );

                        msgBox.exec();

                    }
                    else
                    {
                        odswiezPanel();
                    }


                    odswiezPanel();
                });
            }
        }
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::odswiezPanel()
{
    //aktualizacja label
    QString aktualnyNick = QString::fromStdString(silnikGry.pobierzNickAktualnego());
    ui->lbl_tura->setText("Turn: " + aktualnyNick);

    QString stylDomyslny = "QPushButton { background-color: #f5f6fa; border: 3px solid #2f3640; border-radius: 15px; font-size: 60px; font-weight: bold; color: #2f3640; } QPushButton:hover { background-color: #dcdde1; border: 3px solid #e1b12c; }";
    QString stylCzlowiek = "QPushButton { background-color: #7bed9f; border: 3px solid #2ed573; border-radius: 15px; font-size: 60px; font-weight: bold; color: #2f3640; }";
    QString stylBot =      "QPushButton { background-color: #ff7979; border: 3px solid #eb4d4b; border-radius: 15px; font-size: 60px; font-weight: bold; color: #2f3640; }";
    QString stylZnikajacy = "QPushButton { background-color: #a29bfe; border: 4px dashed #6c5ce7; border-radius: 15px; font-size: 60px; font-weight: bold; color: #2f3640; }";

    std::pair<int, int> doUsuniecia = silnikGry.pobierzZnikajacePole();

    for(int i = 0; i < 3; i++) {
        for(int j = 0; j < 3; j++) {
            QString nazwaGuzika = "btn_" + QString::number(i) + "_" + QString::number(j);
            QPushButton *guzik = this->findChild<QPushButton*>(nazwaGuzika);

            if(guzik != nullptr) {

                char znak = silnikGry.pobierzZnakZPlanszy(i, j);
                if(znak == 'X' || znak == 'O')
                {
                    guzik->setText(QString(znak));
                }
                else
                {
                    guzik->setText("");
                }

                if (i == doUsuniecia.first && j == doUsuniecia.second)
                {
                    guzik->setStyleSheet(stylZnikajacy);
                }
                else if (i == ostRuchX_Czlowiek && j == ostRuchY_Czlowiek)
                {
                    guzik->setStyleSheet(stylCzlowiek);
                }
                else if (i == ostRuchX_Bot && j == ostRuchY_Bot)
                {
                    guzik->setStyleSheet(stylBot);
                }
                else
                {
                    guzik->setStyleSheet(stylDomyslny);
                }
            }
        }
    }
}

void MainWindow::on_btnPvP_clicked()
{
    QString nick1 = ui->inputNick1->text().trimmed();
    QString nick2 = ui->inputNick2->text().trimmed();

    if (nick1.isEmpty() || czyCenzurowac(nick1) || nick1.contains("pisz imie", Qt::CaseInsensitive) || nick1.contains("pisz nick", Qt::CaseInsensitive)) {
        nick1 = "Gracz 1";
    }
    if (nick2.isEmpty() || czyCenzurowac(nick2) || nick2.contains("pisz imie", Qt::CaseInsensitive) || nick2.contains("pisz nick", Qt::CaseInsensitive)) {
        nick2 = "Gracz 2";
    }

    silnikGry.uruchomPvP(nick1.toStdString(), nick2.toStdString());
    ui->stackedWidget->setCurrentIndex(1);
    odswiezPanel();
}

void MainWindow::on_btnPvE_clicked()
{
    QString nick1 = ui->inputNick1->text().trimmed();

    if (nick1.isEmpty() || czyCenzurowac(nick1) || nick1.contains("pisz imie", Qt::CaseInsensitive) || nick1.contains("pisz nick", Qt::CaseInsensitive)) {
        nick1 = "Gracz 1";
    }

    silnikGry.uruchomPvE(nick1.toStdString());
    ui->stackedWidget->setCurrentIndex(1);
    odswiezPanel();
}

void MainWindow::on_btnReset_clicked()
{
    silnikGry.zrestartujGre();

    // Zdejmujemy podświetlenia
    ostRuchX_Czlowiek = -1; ostRuchY_Czlowiek = -1;
    ostRuchX_Bot = -1; ostRuchY_Bot = -1;

    odswiezPanel();
}

void MainWindow::on_btnStart_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
    ostRuchX_Czlowiek = -1; ostRuchY_Czlowiek = -1;
    ostRuchX_Bot = -1; ostRuchY_Bot = -1;
}

void MainWindow::zapiszWygranaDoPliku(QString zwyciezca)
{
    QFile plik("ranking.txt");
    std::vector<std::pair<QString, int>> lista;

    if (plik.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QTextStream in(&plik);
        while (!in.atEnd())
        {
            QString linia = in.readLine();
            QStringList czesci = linia.split(";");
            if (czesci.size() == 2)
            {
                lista.push_back({czesci[0], czesci[1].toInt()});
            }
        }
        plik.close();
    }

    bool znaleziono = false;
    for (int i = 0; i < lista.size(); i++)
    {
        if (lista[i].first == zwyciezca)
        {
            lista[i].second += 1;
            znaleziono = true;
            break;
        }
    }
    if (!znaleziono)
    {
        lista.push_back({zwyciezca, 1});
    }

    std::sort(lista.begin(), lista.end(), [](const std::pair<QString, int>& a, const std::pair<QString, int>& b) {
        return a.second > b.second;
    });

    if (plik.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        QTextStream out(&plik);
        for (int i = 0; i < lista.size(); i++)
        {
            out << lista[i].first << ";" << lista[i].second << "\n";
        }
        plik.close();
    }
}

void MainWindow::odswiezTabeleRankingu()
{
    QFile plik("ranking.txt");
    ui->tableLeaderboard->setRowCount(0);

    if (plik.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QTextStream in(&plik);
        int wiersz = 0;

        while (!in.atEnd() && wiersz < 10)
        {
            QString linia = in.readLine();
            QStringList czesci = linia.split(";");
            if (czesci.size() == 2) {
                ui->tableLeaderboard->insertRow(wiersz);
                ui->tableLeaderboard->setItem(wiersz, 0, new QTableWidgetItem(czesci[0]));
                ui->tableLeaderboard->setItem(wiersz, 1, new QTableWidgetItem(czesci[1]));
                wiersz++;
            }
        }
        plik.close();
    }
}
