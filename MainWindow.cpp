#include "MainWindow.hpp"
#include "ui_MainWindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow), gameStarted_(false)
{
    ui->setupUi(this);
    ui->message->setText("Start new game!");
    ui->graphicsView->setRenderHint(QPainter::Antialiasing);

    this->setMinimumSize(initWindowWidth, initWindowHeight);
    initGameField();

    QObject::connect(ui->graphicsView, &SizeFitGraphicsView::graphicsViewClicked,
                     this, &MainWindow::gameFieldClickedPosition);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::initGameField()
{
    scene = new QGraphicsScene();

    for(unsigned int i = 0; i<gameBoardWidth; ++i ){
        for(unsigned int j = 0; j<gameBoardHeight; ++j){
            gameField[i][j] = Empty;
            gameSquare[i][j] = new GameSquare(i*gameSquareSideLength,
                                              j*gameSquareSideLength,
                                              gameSquareSideLength,
                                              gameSquareellipseProcent);
           scene->addItem(gameSquare[i][j]);
        }
    }


    ui->graphicsView->setScene(scene);
}


void MainWindow::resetGameField()
{
    for(unsigned int i = 0; i<gameBoardWidth; ++i ){
        for(unsigned int j = 0; j<gameBoardHeight; ++j){
           delete gameSquare[i][j];
        }
    }

    delete scene;

    initGameField();
}


void MainWindow::on_actionNewGame_triggered()
{
    PlayerMenu playerMenu(this);
    playerMenu.setModal(true);
    playerMenu.exec();

    if(playerMenu.result() == QDialog::Accepted){
        player1Name_ = playerMenu.getPlayer1Name();
        player1Color_ = playerMenu.getPlayer1Color();
        player2Name_ = playerMenu.getPlayer2Name();
        player2Color_ = playerMenu.getPlayer2Color();
        gameStarted_ = false;
        resetGameField();
    }
}

void MainWindow::changePlayerTurn()
{

}

void

void MainWindow::on_actionGameHelp_triggered()
{
    QMessageBox::information(this, "Game Help", "Ok");
}

void MainWindow::on_actionAbout_triggered()
{
    QString message =
        "Game made for \"PAIN\" at Warsaw University Of Technology.\n\n"
         "Proggraming: Patryk Pankiewicz\n"
         "Icons authors:\n"
         "-Zurb\n(https://www.flaticon.com/authors/zurb)\n"
         "-Eleonor Wang\n(https://www.flaticon.com/authors/eleonor-wang)\n"
         "both from Flaticon(https://www.flaticon.com/)\nis licensed by Creative Commons BY 3.0.\n"
         "Thanks!\n\n"
         "\n\nWe are on a mission from God!\n"
         "~ Blues Brothers";

    QMessageBox::information(this, "About", message);
}

void MainWindow::on_actionContact_triggered()
{
    QString contact =
        "Patryk Pankiewicz:\n"
        "patryk.pankiewicz369@gmail.com";
    QMessageBox::information(this, "Contact", contact);
}

void MainWindow::gameFieldClickedPosition(int x){
    if(!gameStarted_){
        on_actionNewGame_triggered();
    }
    else {

    }
}

