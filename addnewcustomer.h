#ifndef ADDNEWCUSTOMER_H
#define ADDNEWCUSTOMER_H

#include <QMainWindow>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>

namespace Ui {
class AddNewCustomer;
}

class AddNewCustomer : public QMainWindow
{
    Q_OBJECT

public:
    explicit AddNewCustomer(QWidget *parent = nullptr);
    ~AddNewCustomer();

public:
    QLabel* label_picture;
    QLineEdit* lineEdit_name,lineEdit_phone,lineEdit_email,lineEdit_address;
    QPushButton* Upload_customer_pic,save,home_page;

private slots:
    void on_Upload_customer_pic_clicked();

    void on_save_clicked();

    void on_home_page_clicked();

private:
    Ui::AddNewCustomer *ui;
};

#endif // ADDNEWCUSTOMER_H
