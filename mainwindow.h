#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLabel>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public:
    QLabel* label_picture;

private slots:
    void on_actionGame_Table_triggered();

    void on_actionAdd_new_game_triggered();

    void on_actionAdd_new_seller_triggered();

    void on_actionSeller_Table_triggered();

    void on_actionAdd_new_customer_triggered();

    void on_actionCustomer_Table_triggered();

    void on_actionDo_business_triggered();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
