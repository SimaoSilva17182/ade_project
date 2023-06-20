#include "sales.h"
#include "ui_sales.h"
#include <QPixmap>
#include <QDebug>
#include <QSqlQuery>
#include <QMessageBox>

#include "mainwindow.h"

QString game_name_sale,game_id_sale,customer_name_sale,customer_id_sale,
    seller_name_sale,seller_id_sale,selected_game_name,hidden_game_id,
    selected_customer_name,hidden_customer_id,selected_seller_name,hidden_seller_id,
    selected_date_day,selected_date_month,inputed_date_year;

int i,selected_game_copies,selected_number_of_copies_sold,new_game_copies;
double price,total_price;
Sales::Sales(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Sales)
{
    ui->setupUi(this);
    ui->label_picture->setPixmap(QPixmap(":picture/images/buy.png").scaledToHeight(150).scaledToWidth(150));
    ui->label_picture_2->setPixmap(QPixmap(":picture/images/buy.png").scaledToHeight(150).scaledToWidth(150));

    QSqlQuery query_game;
    query_game.prepare("SELECT id,name FROM Game WHERE available = 'available'");

    if(query_game.exec()){

        while(query_game.next()){
            game_id_sale = query_game.value(0).toString();
            game_name_sale = query_game.value(1).toString();

            ui->comboBox_game_name->addItem(game_name_sale,game_id_sale);
        }
    }

    QSqlQuery query_customer;
    query_customer.prepare("SELECT id,name FROM Customer");

    if(query_customer.exec()){

        while(query_customer.next()){
            seller_id_sale = query_customer.value(0).toString();
            seller_name_sale = query_customer.value(1).toString();

            ui->comboBox_customer_name->addItem(seller_name_sale,seller_id_sale);
        }
    }

    QSqlQuery query_seller;
    query_seller.prepare("SELECT id,name FROM Seller");

    if(query_seller.exec()){

        while(query_seller.next()){
            seller_id_sale = query_seller.value(0).toString();
            seller_name_sale = query_seller.value(1).toString();

            ui->comboBox_seller_name->addItem(seller_name_sale,seller_id_sale);
        }
    }


}

Sales::~Sales()
{
    delete ui;
}

void Sales::on_comboBox_game_name_currentIndexChanged(int /*index*/)
{
    ui->comboBox_nOg->clear();

    selected_game_name = ui->comboBox_game_name->currentText();
    hidden_game_id = ui->comboBox_game_name->currentData().toString();

    QSqlQuery query;

    query.prepare("SELECT copies FROM Game WHERE id = '" + hidden_game_id + "'");

    if(query.exec()){

        while(query.next()){
            selected_game_copies = query.value(0).toInt();
        }
    }

    for(i=1; i<=selected_game_copies;i++){
        ui->comboBox_nOg->addItem(QString::number(i));
    }

}


void Sales::on_Submit_clicked()
{
    selected_customer_name = ui->comboBox_customer_name->currentText();
    hidden_customer_id = ui->comboBox_customer_name->currentData().toString();

    selected_seller_name = ui->comboBox_seller_name->currentText();
    hidden_seller_id = ui->comboBox_seller_name->currentData().toString();

    selected_number_of_copies_sold = ui->comboBox_nOg->currentText().toInt();

    selected_date_day = ui->comboBox_date_day->currentText();
    selected_date_month = ui->comboBox_date_month->currentText();
    inputed_date_year = ui->lineEdit_date_year->text();

    QSqlQuery query;
    query.prepare("Select price FROM Game WHERE id= '" + hidden_game_id + "'");

    if(query.exec()){

        while(query.next()){

            price = query.value(0).toDouble();
        }
    }

    if(inputed_date_year==""){

        QMessageBox::critical(this,"Input Error","Inputed fields can not be empty!");
        return;
    }else{

        total_price = selected_number_of_copies_sold * price;

        ui->label_game_name->setText(selected_game_name);
        ui->label_customer_name->setText(selected_customer_name);
        ui->label_seller_name->setText(selected_seller_name);
        ui->label_nOg->setText(QString::number(selected_number_of_copies_sold));
        ui->label__sale_date->setText(selected_date_day + '.' + selected_date_month + '.' + inputed_date_year);
        ui->label_total_sales->setText(QString::number(total_price, 'f', 2));
    }
}


void Sales::on_Confirm_clicked()
{
    QString game_name = ui->label_game_name->text();
    QString customer_name = ui->label_customer_name->text();
    QString seller_name = ui->label_seller_name->text();
    QString number_of_copies = ui->label_nOg->text();
    QString date = ui->label__sale_date->text();
    QString total_sales = ui->label_total_sales->text();

    if(game_name==""||customer_name==""||seller_name==""||number_of_copies==""||date==""||total_sales==""){

        QMessageBox::critical(this, "Error", "There is no data available :");
        return;
    }else{

        if(selected_number_of_copies_sold < selected_game_copies){

            new_game_copies = selected_game_copies - selected_number_of_copies_sold;

            QSqlQuery query;

            query.prepare("UPDATE Game SET copies=? WHERE id = '" + hidden_game_id + "'");
            query.addBindValue(new_game_copies);
            query.exec();
        }

        if(selected_number_of_copies_sold == selected_game_copies){

            new_game_copies = selected_game_copies - selected_number_of_copies_sold;

            QSqlQuery query;

            query.prepare("UPDATE Game SET copies=?,available='not available' WHERE id = '" + hidden_game_id + "'");
            query.addBindValue(new_game_copies);
            query.exec();
        }
    }

    this->close();

    Sales *SA = new Sales();
    SA->show();
}


void Sales::on_Home_page_clicked()
{
    this->close();

    MainWindow *MW = new MainWindow();
    MW->show();
}

