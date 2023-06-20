#include "addnewseller.h"
#include "ui_addnewseller.h"
#include <QPixmap>
#include <QFile>
#include <QFileDialog>
#include <QDebug>
#include <QMessageBox>
#include <QSqlQuery>
#include "mainwindow.h"
#include "sellertable.h"

QString path_seller_pic;

AddNewSeller::AddNewSeller(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::AddNewSeller)
{
    ui->setupUi(this);
    ui->label_picture->setPixmap(QPixmap(":picure/images/new-arrival.png"));
}

AddNewSeller::~AddNewSeller()
{
    delete ui;
}

void AddNewSeller::on_Upload_seller_pic_clicked()
{
    path_seller_pic = QFileDialog::getOpenFileName(this,"Upload Seller picture",QDir::currentPath(),"Pictures files(*.png *.jpg)");
    qDebug()<<path_seller_pic;

    QPixmap targetPixmap = QPixmap(path_seller_pic);
    qDebug()<<targetPixmap;
    ui->label_picture->setPixmap(targetPixmap.scaledToHeight(300).scaledToWidth(300));

}


void AddNewSeller::on_save_clicked()
{
    QByteArray byte;
    QFile file(path_seller_pic);

    if(file.open(QIODevice::ReadOnly)){
        byte = file.readAll();

        file.close();
    }

    QString name = ui->lineEdit_name->text();
    QString phone = ui->lineEdit_phone->text();
    QString email = ui->lineEdit_email->text();
    QString address = ui->lineEdit_address->text();


    if(name==""||phone==""||email==""||address==""){
        QMessageBox::critical(this,"Input Error","input or selection fields can not be empty ");
        return;
    }else{
        QSqlQuery query;

        query.prepare("INSERT INTO Seller(name,phone,email,address,picture)VALUES(?,?,?,?,?)");
        query.addBindValue(name);
        query.addBindValue(phone);
        query.addBindValue(email);
        query.addBindValue(address);
        query.addBindValue(byte);

        if(query.exec()){
            QMessageBox::information(this,"Success","File has been inserted");

            //TODO
            this->close();
            SellerTable *ST = new SellerTable();
            ST->show();


        }else{
            QMessageBox::critical(this,"Error","File has not been inserted");
        }
    }
}


void AddNewSeller::on_home_page_clicked()
{
    this->close();

    MainWindow *MW = new MainWindow();
    MW->show();
}

