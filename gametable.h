#ifndef GAMETABLE_H
#define GAMETABLE_H

#include <QMainWindow>
#include <QTableView>
#include <QLineEdit>
#include <QLabel>
#include <QPushButton>
namespace Ui {
class GameTable;
}

class GameTable : public QMainWindow
{
    Q_OBJECT

public:
    explicit GameTable(QWidget *parent = nullptr);
    ~GameTable();

public:
    QTableView* tableView_Game;
    QLabel* label_id,label_picture;
    QLineEdit* lineEdit_id,lineEdit_name,lineEdit_dev,lineEdit_genre,lineEdit_copies,lineEdit_price,lineEdit_available;
    QPushButton* upload_game_pic,update_game_pic,update_game_data,delete_game_data,home_page;

private slots:
    void on_tableView_Game_clicked(const QModelIndex &index);

    void on_upload_game_pic_clicked();

    void on_update_game_pic_clicked();

    void on_update_game_data_clicked();

    void on_delete_game_data_clicked();

    void on_home_page_clicked();

private:
    Ui::GameTable *ui;
};

#endif // GAMETABLE_H
