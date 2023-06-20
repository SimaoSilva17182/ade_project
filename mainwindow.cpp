#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QSqlDatabase>
#include <QPixmap>
#include "addnewgame.h"
#include "gametable.h"
#include "addnewseller.h"
#include "sellertable.h"
#include "addnewcustomer.h"
#include "customertable.h"
#include "sales.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QPixmap pix(":picture/images/videogames-icon.png");
    ui->label_picture->setPixmap(pix.scaledToHeight(900).scaledToWidth(900));
    QSqlDatabase DBConnection = QSqlDatabase::addDatabase("QSQLITE");
    DBConnection.setDatabaseName("C:/ade_project/database.db");

    if(DBConnection.open()==false){
        qDebug()<<"DBConnection Error";
    }else{
        qDebug()<<"DBConnection Success";
    }

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionGame_Table_triggered()
{
    this->close();
    GameTable *GT = new GameTable();
    GT->show();
}

void MainWindow::on_actionAdd_new_game_triggered()
{
    this->close();
    addNewGame *ANG = new addNewGame();
    ANG->show();
}


void MainWindow::on_actionAdd_new_seller_triggered()
{
    this->close();
    AddNewSeller *ANS = new AddNewSeller();
    ANS->show();
}


void MainWindow::on_actionSeller_Table_triggered()
{
    this->close();
    SellerTable *SL = new SellerTable();
    SL->show();
}


void MainWindow::on_actionAdd_new_customer_triggered()
{
    this->close();
    AddNewCustomer *ANC = new AddNewCustomer();
    ANC->show();
}


void MainWindow::on_actionCustomer_Table_triggered()
{
    this->close();
    CustomerTable *SL = new CustomerTable();
    SL->show();
}


void MainWindow::on_actionDo_business_triggered()
{
    this->close();
    Sales *S = new Sales();
    S->show();
}

