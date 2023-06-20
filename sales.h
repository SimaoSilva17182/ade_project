#ifndef SALES_H
#define SALES_H

#include <QMainWindow>
#include <QLabel>
#include <QLineEdit>
#include <QComboBox>
#include <QPushButton>

namespace Ui {
class Sales;
}

class Sales : public QMainWindow
{
    Q_OBJECT

public:
    explicit Sales(QWidget *parent = nullptr);
    ~Sales();

public:
    QLineEdit* lineEdit_date_year;
    QComboBox* comboBox_game_name,comboBox_customer_name,comboBox_seller_name,comboBox_nOg,comboBox_date_day,comboBox_date_month;
    QPushButton* Submit,Confirm,Home_page;
    QLabel* label_game_name,label_customer_name,label_seller_name,label_nOg,label__sale_date,label_total_sales,label_picture,label_picture_2;

private slots:
    void on_comboBox_game_name_currentIndexChanged(int index);

    void on_Submit_clicked();

    void on_Confirm_clicked();

    void on_Home_page_clicked();

private:
    Ui::Sales *ui;
};

#endif // SALES_H
