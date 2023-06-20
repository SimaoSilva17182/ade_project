#ifndef ADDNEWSELLER_H
#define ADDNEWSELLER_H

#include <QMainWindow>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>

namespace Ui {
class AddNewSeller;
}

class AddNewSeller : public QMainWindow
{
    Q_OBJECT

public:
    explicit AddNewSeller(QWidget *parent = nullptr);
    ~AddNewSeller();

public:
    QLabel* label_picture;
    QLineEdit* lineEdit_name,lineEdit_phone,lineEdit_email,lineEdit_address;
    QPushButton* Upload_seller_pic,save,home_page;

private slots:
    void on_Upload_seller_pic_clicked();

    void on_save_clicked();

    void on_home_page_clicked();

private:
    Ui::AddNewSeller *ui;
};

#endif // ADDNEWSELLER_H
