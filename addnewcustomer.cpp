#include "addnewcustomer.h"
#include "ui_addnewcustomer.h"
#include <QPixmap>
#include <QFile>
#include <QFileDialog>
#include <QDebug>
#include <QMessageBox>
#include <QSqlQuery>
#include "mainwindow.h"
#include "customertable.h"

QString path_customer_pic;

AddNewCustomer::AddNewCustomer(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::AddNewCustomer)
{
    ui->setupUi(this);
    ui->label_picture->setPixmap(QPixmap(":picure/images/new-arrival.png"));
}

AddNewCustomer::~AddNewCustomer()
{
    delete ui;
}

void AddNewCustomer::on_Upload_customer_pic_clicked()
{
    path_customer_pic = QFileDialog::getOpenFileName(this,"Upload Customer picture",QDir::currentPath(),"Pictures files(*.png *.jpg)");
    qDebug()<<path_customer_pic;

    QPixmap targetPixmap = QPixmap(path_customer_pic);
    qDebug()<<targetPixmap;
    ui->label_picture->setPixmap(targetPixmap.scaledToHeight(300).scaledToWidth(300));
}


void AddNewCustomer::on_save_clicked()
{
    QByteArray byte;
    QFile file(path_customer_pic);

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

        query.prepare("INSERT INTO Customer(name,phone,email,address,picture)VALUES(?,?,?,?,?)");
        query.addBindValue(name);
        query.addBindValue(phone);
        query.addBindValue(email);
        query.addBindValue(address);
        query.addBindValue(byte);

        if(query.exec()){
            QMessageBox::information(this,"Success","File has been inserted");

            //TODO
            this->close();
            CustomerTable *CT = new CustomerTable();
            CT->show();


        }else{
            QMessageBox::critical(this,"Error","File has not been inserted");
        }
    }
}


void AddNewCustomer::on_home_page_clicked()
{
    this->close();

    MainWindow *MW = new MainWindow();
    MW->show();
}

