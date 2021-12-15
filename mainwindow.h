#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSqlQuery>
#include <QCheckBox>
#include <QList>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_pushButtonAjouter_clicked();

    void on_tableWidget_cellClicked(int row, int column);

    void on_pushButtonModifier_clicked();

    void on_pushButtonSupprimer_clicked();

private:
    Ui::MainWindow *ui;
    int i=0;
    int noMax;
    void afficherTable();
    QList <QCheckBox *> liste;
};

#endif // MAINWINDOW_H
