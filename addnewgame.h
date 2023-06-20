#ifndef ADDNEWGAME_H
#define ADDNEWGAME_H

#include <QMainWindow>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>

namespace Ui {
class addNewGame;
}

class addNewGame : public QMainWindow
{
    Q_OBJECT

public:
    explicit addNewGame(QWidget *parent = nullptr);
    ~addNewGame();

public:
    QLabel* label_picture;
    QLineEdit* lineEdit_name,lineEdit_dev,lineEdit_genre,lineEdit_price,lineEdit_nOc;
    QPushButton* Upload_game_pic,save,home_page;

private slots:
    void on_Upload_game_pic_clicked();

    void on_save_clicked();

    void on_home_page_clicked();

private:
    Ui::addNewGame *ui;
};

#endif // ADDNEWGAME_H
