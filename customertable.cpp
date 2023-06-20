#include "customertable.h"
#include "ui_customertable.h"
#include <QSqlQueryModel>
#include <QSqlQuery>
#include <QFileDialog>
#include <QFile>
#include <QMessageBox>
#include "mainwindow.h"

QString Customer_id,path_Update_Customer;

CustomerTable::CustomerTable(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::CustomerTable)
{
    ui->setupUi(this);

    QSqlQueryModel *tableModel = new QSqlQueryModel();

    tableModel->setQuery("SELECT id,name,phone,email,address FROM Customer");

    tableModel->setHeaderData(0,Qt::Horizontal,"ID");
    tableModel->setHeaderData(1,Qt::Horizontal,"NAME");
    tableModel->setHeaderData(2,Qt::Horizontal,"PHONE");
    tableModel->setHeaderData(3,Qt::Horizontal,"EMAIL");
    tableModel->setHeaderData(4,Qt::Horizontal,"ADDRESS");


    QFont font("Arial",12,QFont::Bold);
    ui->tableView_Customer->horizontalHeader()->setFont(font);
    ui->tableView_Customer->setModel(tableModel);
}

CustomerTable::~CustomerTable()
{
    delete ui;
}


void CustomerTable::on_tableView_Customer_clicked(const QModelIndex &index)
{
    Customer_id = ui->tableView_Customer->model()->index(index.row(),0).data().toString();
    ui->label_id->setText("Selected Customer id: " + Customer_id);

    QSqlQuery query;

    query.prepare("SELECT * FROM Customer WHERE id =  '" + Customer_id + "'");

    if(query.exec()){

        while(query.next()){

            ui->lineEdit_id->setText(query.value(0).toString());
            ui->lineEdit_name->setText(query.value(1).toString());
            ui->lineEdit_phone->setText(query.value(2).toString());
            ui->lineEdit_email->setText(query.value(3).toString());
            ui->lineEdit_address->setText(query.value(4).toString());

            QByteArray byte = query.value(5).toByteArray();

            QPixmap pix = QPixmap();

            pix.loadFromData(byte);

            ui->label_picture->setPixmap(pix.scaledToHeight(400).scaledToWidth(150));
        }
    }
}

void CustomerTable::on_upload_customer_pic_clicked()
{
    path_Update_Customer = QFileDialog::getOpenFileName(this,"Upload Customer picture",QDir::currentPath(),"Pictures files(*.png *.jpg)");
    qDebug()<<path_Update_Customer;

    QPixmap targetPixmap = QPixmap(path_Update_Customer);
    qDebug()<<targetPixmap;
    ui->label_picture->setPixmap(targetPixmap.scaledToHeight(300).scaledToWidth(150));
}


void CustomerTable::on_update_customer_pic_clicked()
{
    QByteArray byte;
    QFile file(path_Update_Customer);

    if(file.open(QIODevice::ReadOnly)){
        byte = file.readAll();

        file.close();
    }

    QSqlQuery query;

    query.prepare("UPDATE Customer SET picture =? WHERE id = '" + Customer_id + "'");
    query.addBindValue(byte);

    if(query.exec()){

        QMessageBox::information(this,"Success","Customer picture has been updated");

    }else{

        QMessageBox::critical(this,"Error","Customer picture has not been updated");
    }
}


void CustomerTable::on_update_customer_data_clicked()
{
    QString name = ui->lineEdit_name->text();
    QString phone = ui->lineEdit_phone->text();
    QString email = ui->lineEdit_email->text();
    QString address = ui->lineEdit_address->text();

    QSqlQuery query;

    query.prepare("UPDATE Customer SET name=?,phone=?,email=?,address=? WHERE id= '" + Customer_id + "'");
    query.addBindValue(name);
    query.addBindValue(phone);
    query.addBindValue(email);
    query.addBindValue(address);

    if(query.exec()){

        QMessageBox::information(this,"Success","Customer data has been updated");
        this->close();
        MainWindow *MW = new MainWindow();
        MW->show();

    }else{
        QMessageBox::critical(this,"Error","Customer data has not been updated");
    }
}


void CustomerTable::on_delete_customer_data_clicked()
{
    QMessageBox *msBox = new QMessageBox();

    msBox->setWindowTitle("Question");
    msBox->setIcon(QMessageBox::Question);
    msBox->setWindowIcon(QIcon(":picture/images/add-user.png"));
    msBox->setText("Are you sure? Do you really want to delete this Customer: ");

    QPushButton *button_yes, *button_no;
    button_yes = msBox->addButton(QMessageBox::Yes);
    button_no = msBox->addButton(QMessageBox::No);

    msBox->exec();

    if(msBox->clickedButton()==button_no){
        return;
    }if(msBox->clickedButton()==button_yes){
        QSqlQuery query;
        query.prepare("DELETE FROM Customer WHERE id = '" + Customer_id + "'");

        if(query.exec()){

            QMessageBox::information(this,"Success","Customer data has been delected");
            this->close();
            MainWindow *MW = new MainWindow();
            MW->show();

        }else{
            QMessageBox::critical(this,"Error","Customer data has not been delected");
        }

    }
}


void CustomerTable::on_home_page_clicked()
{
    this->close();

    MainWindow *MW = new MainWindow();
    MW->show();
}



