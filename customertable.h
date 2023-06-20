#ifndef CUSTOMERTABLE_H
#define CUSTOMERTABLE_H

#include <QMainWindow>
#include <QTableView>
#include <QLineEdit>
#include <QLabel>
#include <QPushButton>
namespace Ui {
class CustomerTable;
}

class CustomerTable : public QMainWindow
{
    Q_OBJECT

public:
    explicit CustomerTable(QWidget *parent = nullptr);
    ~CustomerTable();

public:
    QTableView* tableView_Customer;
    QLabel* label_id,label_picture;
    QLineEdit* lineEdit_id,lineEdit_name,lineEdit_phone,lineEdit_email,lineEdit_address;
    QPushButton* upload_customer_pic,update_customer_pic,update_customer_data,delete_customer_data,home_page;

private slots:
    void on_tableView_Customer_clicked(const QModelIndex &index);

    void on_upload_customer_pic_clicked();

    void on_update_customer_pic_clicked();

    void on_update_customer_data_clicked();

    void on_delete_customer_data_clicked();

    void on_home_page_clicked();


private:
    Ui::CustomerTable *ui;
};

#endif // CUSTOMERTABLE_H
