#include "sellertable.h"
#include "ui_sellertable.h"
#include <QSqlQueryModel>
#include <QSqlQuery>
#include <QFileDialog>
#include <QFile>
#include <QMessageBox>
#include "mainwindow.h"

QString Seller_id,path_Update_Seller;

SellerTable::SellerTable(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::SellerTable)
{
    ui->setupUi(this);

    QSqlQueryModel *tableModel = new QSqlQueryModel();

    tableModel->setQuery("SELECT id,name,phone,email,address FROM Seller");

    tableModel->setHeaderData(0,Qt::Horizontal,"ID");
    tableModel->setHeaderData(1,Qt::Horizontal,"NAME");
    tableModel->setHeaderData(2,Qt::Horizontal,"PHONE");
    tableModel->setHeaderData(3,Qt::Horizontal,"EMAIL");
    tableModel->setHeaderData(4,Qt::Horizontal,"ADDRESS");


    QFont font("Arial",12,QFont::Bold);
    ui->tableView_Seller->horizontalHeader()->setFont(font);
    ui->tableView_Seller->setModel(tableModel);
}

SellerTable::~SellerTable()
{
    delete ui;
}

void SellerTable::on_tableView_Seller_clicked(const QModelIndex &index)
{
    Seller_id = ui->tableView_Seller->model()->index(index.row(),0).data().toString();
    ui->label_id->setText("Selected Seller id: " + Seller_id);

    QSqlQuery query;

    query.prepare("SELECT * FROM Seller WHERE id =  '" + Seller_id + "'");

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


void SellerTable::on_upload_seller_pic_clicked()
{
    path_Update_Seller = QFileDialog::getOpenFileName(this,"Upload Seller picture",QDir::currentPath(),"Pictures files(*.png *.jpg)");
    qDebug()<<path_Update_Seller;

    QPixmap targetPixmap = QPixmap(path_Update_Seller);
    qDebug()<<targetPixmap;
    ui->label_picture->setPixmap(targetPixmap.scaledToHeight(300).scaledToWidth(150));
}


void SellerTable::on_update_seller_pic_clicked()
{
    QByteArray byte;
    QFile file(path_Update_Seller);

    if(file.open(QIODevice::ReadOnly)){
        byte = file.readAll();

        file.close();
    }

    QSqlQuery query;

    query.prepare("UPDATE Seller SET picture =? WHERE id = '" + Seller_id + "'");
    query.addBindValue(byte);

    if(query.exec()){

        QMessageBox::information(this,"Success","Seller picture has been updated");

    }else{

        QMessageBox::critical(this,"Error","Seller picture has not been updated");
    }
}


void SellerTable::on_update_seller_data_clicked()
{
    QString name = ui->lineEdit_name->text();
    QString phone = ui->lineEdit_phone->text();
    QString email = ui->lineEdit_email->text();
    QString address = ui->lineEdit_address->text();

    QSqlQuery query;

    query.prepare("UPDATE Seller SET name=?,phone=?,email=?,address=? WHERE id= '" + Seller_id + "'");
    query.addBindValue(name);
    query.addBindValue(phone);
    query.addBindValue(email);
    query.addBindValue(address);

    if(query.exec()){

        QMessageBox::information(this,"Success","Seller data has been updated");
        this->close();
        MainWindow *MW = new MainWindow();
        MW->show();

    }else{
        QMessageBox::critical(this,"Error","Seller data has not been updated");
    }
}


void SellerTable::on_delete_seller_data_clicked()
{
    QMessageBox *msBox = new QMessageBox();

    msBox->setWindowTitle("Question");
    msBox->setIcon(QMessageBox::Question);
    msBox->setWindowIcon(QIcon(":picture/images/new-arrival.png"));
    msBox->setText("Are you sure? Do you really want to delete this Seller: ");

    QPushButton *button_yes, *button_no;
    button_yes = msBox->addButton(QMessageBox::Yes);
    button_no = msBox->addButton(QMessageBox::No);

    msBox->exec();

    if(msBox->clickedButton()==button_no){
        return;
    }if(msBox->clickedButton()==button_yes){
        QSqlQuery query;
        query.prepare("DELETE FROM Seller WHERE id = '" + Seller_id + "'");

        if(query.exec()){

            QMessageBox::information(this,"Success","Seller data has been delected");
            this->close();
            MainWindow *MW = new MainWindow();
            MW->show();

        }else{
            QMessageBox::critical(this,"Error","Seller data has not been delected");
        }

    }
}


void SellerTable::on_home_page_clicked()
{
    this->close();

    MainWindow *MW = new MainWindow();
    MW->show();
}

