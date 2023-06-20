#include "gametable.h"
#include "ui_gametable.h"
#include <QSqlQueryModel>
#include <QSqlQuery>
#include <QFileDialog>
#include <QFile>
#include <QMessageBox>
#include "mainwindow.h"

QString Game_id,path_Update_Game;

GameTable::GameTable(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::GameTable)
{
    ui->setupUi(this);

    QSqlQueryModel *tableModel = new QSqlQueryModel();

    tableModel->setQuery("SELECT id,name,dev,genre,copies,price,available FROM Game");

    tableModel->setHeaderData(0,Qt::Horizontal,"ID");
    tableModel->setHeaderData(1,Qt::Horizontal,"NAME");
    tableModel->setHeaderData(2,Qt::Horizontal,"DEV");
    tableModel->setHeaderData(3,Qt::Horizontal,"GENRE");
    tableModel->setHeaderData(4,Qt::Horizontal,"COPIES");
    tableModel->setHeaderData(5,Qt::Horizontal,"PRICE");
    tableModel->setHeaderData(6,Qt::Horizontal,"AVAILABLE");

    QFont font("Arial",12,QFont::Bold);
    ui->tableView_Game->horizontalHeader()->setFont(font);
    ui->tableView_Game->setModel(tableModel);
}

GameTable::~GameTable()
{
    delete ui;
}

void GameTable::on_tableView_Game_clicked(const QModelIndex &index)
{
    Game_id = ui->tableView_Game->model()->index(index.row(),0).data().toString();
    ui->label_id->setText("Selected Game id: " + Game_id);

    QSqlQuery query;

    query.prepare("SELECT * FROM Game WHERE id =  '" + Game_id + "'");

    if(query.exec()){

        while(query.next()){

            ui->lineEdit_id->setText(query.value(0).toString());
            ui->lineEdit_name->setText(query.value(1).toString());
            ui->lineEdit_dev->setText(query.value(2).toString());
            ui->lineEdit_genre->setText(query.value(3).toString());
            ui->lineEdit_copies->setText(query.value(4).toString());
            double price = query.value(5).toDouble();
            ui->lineEdit_price->setText(QString::number(price,'f',2));
            ui->lineEdit_available->setText(query.value(6).toString());

            QByteArray byte = query.value(7).toByteArray();

            QPixmap pix = QPixmap();

            pix.loadFromData(byte);

            ui->label_picture->setPixmap(pix.scaledToHeight(600).scaledToWidth(600));
        }
    }

}


void GameTable::on_upload_game_pic_clicked()
{
    path_Update_Game = QFileDialog::getOpenFileName(this,"Upload Game picture",QDir::currentPath(),"Pictures files(*.png *.jpg)");
    qDebug()<<path_Update_Game;

    QPixmap targetPixmap = QPixmap(path_Update_Game);
    qDebug()<<targetPixmap;
    ui->label_picture->setPixmap(targetPixmap.scaledToHeight(600).scaledToWidth(600));

}


void GameTable::on_update_game_pic_clicked()
{
    QByteArray byte;
    QFile file(path_Update_Game);

    if(file.open(QIODevice::ReadOnly)){
        byte = file.readAll();

        file.close();
    }

    QSqlQuery query;

    query.prepare("UPDATE Game SET picture =? WHERE id = '" + Game_id + "'");
    query.addBindValue(byte);

    if(query.exec()){

        QMessageBox::information(this,"Success","Game picture has been updated");

    }else{

        QMessageBox::critical(this,"Error","Game picture has not been updated");
    }
}


void GameTable::on_update_game_data_clicked()
{
    QString name = ui->lineEdit_name->text();
    QString dev = ui->lineEdit_dev->text();
    QString genre = ui->lineEdit_genre->text();
    int copies = ui->lineEdit_copies->text().toInt();
    double price = ui->lineEdit_price->text().toDouble();
    QString available = ui->lineEdit_available->text();

    QSqlQuery query;

    query.prepare("UPDATE Game SET name=?,dev=?,genre=?,copies=?,price=?,available=? WHERE id= '" + Game_id + "'");
    query.addBindValue(name);
    query.addBindValue(dev);
    query.addBindValue(genre);
    query.addBindValue(copies);
    query.addBindValue(price);
    query.addBindValue(available);

    if(query.exec()){

        QMessageBox::information(this,"Success","Game data has been updated");
        this->close();
        MainWindow *MW = new MainWindow();
        MW->show();

    }else{
        QMessageBox::critical(this,"Error","Game data has not been updated");
    }

}


void GameTable::on_delete_game_data_clicked()
{
    QMessageBox *msBox = new QMessageBox();

    msBox->setWindowTitle("Question");
    msBox->setIcon(QMessageBox::Question);
    msBox->setWindowIcon(QIcon(":picture/images/ghost.png"));
    msBox->setText("Are you sure? Do you really want to delete this Game: ");

    QPushButton *button_yes, *button_no;
    button_yes = msBox->addButton(QMessageBox::Yes);
    button_no = msBox->addButton(QMessageBox::No);

    msBox->exec();

    if(msBox->clickedButton()==button_no){
        return;
    }if(msBox->clickedButton()==button_yes){
        QSqlQuery query;
        query.prepare("DELETE FROM Game WHERE id = '" + Game_id + "'");

        if(query.exec()){

            QMessageBox::information(this,"Success","Game data has been delected");
            this->close();
            MainWindow *MW = new MainWindow();
            MW->show();

        }else{
            QMessageBox::critical(this,"Error","Game data has not been delected");
        }

    }

}


void GameTable::on_home_page_clicked()
{
    this->close();

    MainWindow *MW = new MainWindow();
    MW->show();
}

