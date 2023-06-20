#include "addnewgame.h"
#include "ui_addnewgame.h"
#include <QPixmap>
#include <QFile>
#include <QFileDialog>
#include <QDebug>
#include <QMessageBox>
#include <QSqlQuery>
#include "mainwindow.h"
#include "gametable.h"
QString path;

addNewGame::addNewGame(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::addNewGame)
{
    ui->setupUi(this);
    ui->label_picture->setPixmap(QPixmap(":picture/images/ghost.png").scaledToHeight(600).scaledToWidth(600));

}

addNewGame::~addNewGame()
{
    delete ui;
}

void addNewGame::on_Upload_game_pic_clicked()
{
    path = QFileDialog::getOpenFileName(this,"Upload Game picture",QDir::currentPath(),"Pictures files(*.png *.jpg)");
    qDebug()<<path;

    QPixmap targetPixmap = QPixmap(path);
    qDebug()<<targetPixmap;
    ui->label_picture->setPixmap(targetPixmap.scaledToHeight(600).scaledToWidth(600));
}


void addNewGame::on_save_clicked()
{
    QByteArray byte;
    QFile file(path);

    if(file.open(QIODevice::ReadOnly)){
        byte = file.readAll();

        file.close();
    }

    QString name = ui->lineEdit_name->text();
    QString dev = ui->lineEdit_dev->text();
    QString genre = ui->lineEdit_genre->text();
    int copies = ui->lineEdit_nOc->text().toInt();
    double price = ui->lineEdit_price->text().toDouble();

    if(name==""||dev==""||genre==""||copies==0||price==0){
        QMessageBox::critical(this,"Input Error","input or selection fields can not be empty ");
        return;
    }else{
        QSqlQuery query;

        query.prepare("INSERT INTO Game(name,dev,genre,copies,price,picture)VALUES(?,?,?,?,?,?)");
        query.addBindValue(name);
        query.addBindValue(dev);
        query.addBindValue(genre);
        query.addBindValue(copies);
        query.addBindValue(price);
        query.addBindValue(byte);

        if(query.exec()){
            QMessageBox::information(this,"Success","File has been inserted");

            //TODO
            this->close();
            GameTable *GT = new GameTable();
            GT->show();

        }else{
            QMessageBox::critical(this,"Error","File has not been inserted");
        }
    }
}

void addNewGame::on_home_page_clicked()
{
    this->close();

    MainWindow *MW = new MainWindow();
    MW->show();
}

