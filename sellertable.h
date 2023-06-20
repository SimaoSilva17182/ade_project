#ifndef SELLERTABLE_H
#define SELLERTABLE_H

#include <QMainWindow>
#include <QTableView>
#include <QLineEdit>
#include <QLabel>
#include <QPushButton>
namespace Ui {
class SellerTable;
}

class SellerTable : public QMainWindow
{
    Q_OBJECT

public:
    explicit SellerTable(QWidget *parent = nullptr);
    ~SellerTable();

public:
    QTableView* tableView_Seller;
    QLabel* label_id,label_picture;
    QLineEdit* lineEdit_id,lineEdit_name,lineEdit_phone,lineEdit_email,lineEdit_address;
    QPushButton* upload_seller_pic,update_seller_pic,update_seller_data,delete_seller_data,home_page;

private slots:
    void on_tableView_Seller_clicked(const QModelIndex &index);

    void on_upload_seller_pic_clicked();

    void on_update_seller_pic_clicked();

    void on_update_seller_data_clicked();

    void on_delete_seller_data_clicked();

    void on_home_page_clicked();

private:
    Ui::SellerTable *ui;
};

#endif // SELLERTABLE_H
