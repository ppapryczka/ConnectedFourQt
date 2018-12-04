#ifndef PLAYERMENU_HPP
#define PLAYERMENU_HPP

// qt
#include <QDialog>
#include <QPixmap>
#include <QMessageBox>
#include <QColorDialog>

// connected four
#include "common.hpp"

namespace Ui {
class PlayerMenu;
}

class PlayerMenu : public QDialog
{
    Q_OBJECT
protected:
    QPixmap player1Pixmap_;
    QPixmap player2Pixmap_;
    QColor player1Color_;
    QColor player2Color_;

public:
    explicit PlayerMenu(QWidget *parent = 0);
    QColor getPlayer1Color();
    QColor getPlayer2Color();
    QString getPlayer1Name();
    QString getPlayer2Name();
    ~PlayerMenu();

private slots:
    void on_player2Color_clicked();

    void on_player1Color_clicked();

private:
    Ui::PlayerMenu *ui;
};

#endif // PLAYERMENU_HPP
