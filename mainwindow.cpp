#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QLineEdit>
#include <QSqlQuery>
#include <QString>
#include <QDebug>
#include <QCheckBox>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //initialisation tableau
    ui->tableWidget->setColumnCount(6);
    ui->tableWidget->setRowCount(0);
    //mise en place du header du tableau
    QStringList headers;
    headers << "n°" << "prénom" << "nom" << "tel" << "email" << "Sélection";
    ui->tableWidget->setHorizontalHeaderLabels(headers);
    //tableau responsif
    ui->tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    afficherTable();
}

//initialisation du tableau
void MainWindow::afficherTable(){
    QSqlQuery query;
    query.exec("SELECT no,prenom,nom,tel,email FROM contact");
    while(query.next())
    {
        ui->tableWidget->insertRow(i);
        ui->tableWidget->setItem(i,0,new QTableWidgetItem(query.value("no").toString()));
        ui->tableWidget->setItem(i,1,new QTableWidgetItem(query.value("prenom").toString()));
        ui->tableWidget->setItem(i,2,new QTableWidgetItem(query.value("nom").toString()));
        ui->tableWidget->setItem(i,3,new QTableWidgetItem(query.value("tel").toString()));
        ui->tableWidget->setItem(i,4,new QTableWidgetItem(query.value("email").toString()));
        QCheckBox* cocher = new QCheckBox();
        liste.append(cocher);
        ui->tableWidget->setCellWidget(i,5, cocher);
        i++;
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

//bouton ajouter
void MainWindow::on_pushButtonAjouter_clicked()
{
    QString prenom,nom,tel,email;

    prenom = ui->lineEditPrenom->text();
    nom = ui->lineEditNom->text();
    tel = ui->lineEditTel->text();
    email = ui->lineEditEmail->text();

    QString txtMax="SELECT MAX(no) FROM contact";
    QSqlQuery queryMax(txtMax);
    queryMax.next();
    noMax = queryMax.value(0).toInt();
    noMax++;
    QString txtReq="INSERT INTO contact (no,prenom,nom,tel,email) VALUES ('"+QString::number(noMax)+"','"+prenom+"','"+nom+"','"+tel+"','"+email+"')";
    QSqlQuery query(txtReq);
    //j'ajoute une ligne dans la tableWidget
    int noLigne=ui->tableWidget->rowCount();
    ui->tableWidget->insertRow(noLigne);
    ui->tableWidget->setItem(noLigne,0,new QTableWidgetItem(QString::number(noMax)));
    ui->tableWidget->setItem(noLigne,1,new QTableWidgetItem(prenom));
    ui->tableWidget->setItem(noLigne,2,new QTableWidgetItem(nom));
    ui->tableWidget->setItem(noLigne,3,new QTableWidgetItem(tel));
    ui->tableWidget->setItem(noLigne,4,new QTableWidgetItem(email));
    QCheckBox* cocher = new QCheckBox();
    liste.append(cocher);
    ui->tableWidget->setCellWidget(noLigne,5, cocher);

}

//selection on click
void MainWindow::on_tableWidget_cellClicked(int i, int column)
{
    //recuperation cellule
    ui->labelNo->setText(ui->tableWidget->item(i,0)->text());
    ui->lineEditPrenom->setText(ui->tableWidget->item(i,1)->text());
    ui->lineEditNom->setText(ui->tableWidget->item(i,2)->text());
    ui->lineEditTel->setText(ui->tableWidget->item(i,3)->text());
    ui->lineEditEmail->setText(ui->tableWidget->item(i,4)->text());
}

//bouton modifier
void MainWindow::on_pushButtonModifier_clicked()
{
    ui->tableWidget->item(ui->tableWidget->currentRow(),1)->setText(ui->lineEditPrenom->text());
    ui->tableWidget->item(ui->tableWidget->currentRow(),2)->setText(ui->lineEditNom->text());
    ui->tableWidget->item(ui->tableWidget->currentRow(),3)->setText(ui->lineEditTel->text());
    ui->tableWidget->item(ui->tableWidget->currentRow(),4)->setText(ui->lineEditEmail->text());
}

void MainWindow::on_pushButtonSupprimer_clicked()
{
    qDebug()<<"void MainWindow::on_pushButtonSupprimer_clicked()";
    //supprimer du tableau
    for(int noLigne=ui->tableWidget->rowCount()-1;noLigne>0;noLigne--)
    {
        if(((QCheckBox*)ui->tableWidget->cellWidget(noLigne,5))->isChecked())
        {
            QString txtSup="DELETE FROM contact WHERE no="+ui->tableWidget->item(noLigne,0)->text();
            qDebug()<<txtSup;
            QSqlQuery querySup(txtSup);
            ui->tableWidget->removeRow(noLigne);
        }
    }
}
