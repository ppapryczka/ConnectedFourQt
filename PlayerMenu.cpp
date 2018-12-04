#include "PlayerMenu.hpp"
#include "ui_PlayerMenu.h"

PlayerMenu::PlayerMenu(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::PlayerMenu)
{
    ui->setupUi(this);


    ui->player1Label->setText("Player 1");
    ui->player1NameLabel->setText("Name:");
    ui->player1Name->setText("Jake");
    ui->player1ColorLabel->setText("Color:");
    player1Pixmap_ = QPixmap(pixMapWidth, pixMapHeight);
    player1Pixmap_.fill(QColor("red"));
    player1Color_ = QColor("red");
    ui->player1Color->setPixmap(player1Pixmap_);

    ui->player2Label->setText("Player 2");
    ui->player2NameLabel->setText("Name:");
    ui->player2Name->setText("Elwood");
    ui->player2ColorLabel->setText("Color:");
    player2Pixmap_ = QPixmap(pixMapWidth, pixMapHeight);
    player2Pixmap_.fill(QColor("yellow"));
    player2Color_ = QColor("yellow");
    ui->player2Color->setPixmap(player2Pixmap_);

}

QColor PlayerMenu::getPlayer1Color(){
    return player1Color_;
}

QColor PlayerMenu::getPlayer2Color(){
    return player2Color_;
}

QString PlayerMenu::getPlayer1Name(){
    return ui->player1Name->text();
}

QString PlayerMenu::getPlayer2Name(){
    return ui->player2Name->text() ;
}


PlayerMenu::~PlayerMenu()
{
    delete ui;
}

void PlayerMenu::on_player2Color_clicked()
{
    QColorDialog qColorDialog_;
    qColorDialog_.setModal(true);
    qColorDialog_.exec();

    if(qColorDialog_.result() == QDialog::Accepted){
        QColor selectedColor = qColorDialog_.selectedColor();

        if(selectedColor != player1Color_ && selectedColor != QColor("blue")){
                player2Color_ = selectedColor;
                player2Pixmap_.fill(player2Color_);
                ui->player2Color->setPixmap(player2Pixmap_);
        }
    }
}

void PlayerMenu::on_player1Color_clicked()
{
    QColorDialog qColorDialog_;
    qColorDialog_.setModal(true);
    qColorDialog_.exec();

    if(qColorDialog_.result() == QDialog::Accepted){
        QColor selectedColor = qColorDialog_.selectedColor();

        if(selectedColor != player2Color_ && selectedColor != QColor("blue")){
            player1Color_ = selectedColor;
            player1Pixmap_.fill(player1Color_);
            ui->player1Color->setPixmap(player1Pixmap_);
        }
    }
}
