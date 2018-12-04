#include "MainWindow.hpp"
#include "ui_MainWindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow), gameStarted_(false), gameFinished_(true)
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
    for(unsigned int i = 0; i<gameBoardWidth; ++i ){
        for(unsigned int j = 0; j<gameBoardHeight; ++j){
           delete gameSquare[i][j];
        }
    }

    delete scene_;
    delete ui;
}

void MainWindow::initGameField()
{
    scene_ = new QGraphicsScene();

    for(unsigned int i = 0; i<gameBoardWidth; ++i ){
        for(unsigned int j = 0; j<gameBoardHeight; ++j){
            gameField[i][j] = Empty;
            gameSquare[i][j] = new GameSquare(i*gameSquareSideLength,
                                              j*gameSquareSideLength,
                                              gameSquareSideLength,
                                              gameSquareellipseProcent);
           scene_->addItem(gameSquare[i][j]);
        }
    }


    ui->graphicsView->setScene(scene_);
}


void MainWindow::resetGameField()
{
    for(unsigned int i = 0; i<gameBoardWidth; ++i ){
        for(unsigned int j = 0; j<gameBoardHeight; ++j){
           delete gameSquare[i][j];
        }
    }

    delete scene_;

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

        startGame();
    }
}

void MainWindow::startGame()
{
    resetGameField();

    int tmp = qrand()%2;

    if(tmp == 0){
        player1Turn_ = true;
    }
    else {
        player1Turn_ = false;
    }

    player1Pixmap_ = QPixmap(pixMapWidth, pixMapHeight);
    player1Pixmap_.fill(player1Color_);
    player2Pixmap_ = QPixmap(pixMapWidth, pixMapHeight);
    player2Pixmap_.fill(player2Color_);
    setPlayerLabels();

    gameStarted_ = true;
    gameFinished_ = false;
}

void MainWindow::makeMove(int x)
{
    int column = x/gameSquareSideLength;
    std::cout<<x<<" ";
    std::cout<<column<<std::endl;

    if(gameField[column][gameBoardHeight-1] == Empty){
        int emptyY = 0;
        std::cout<<emptyY<<std::endl;
        for(int y = 0; y<gameBoardHeight; ++y){
            if(gameField[column][y] == Empty){
                emptyY = y;
                break;
            }
            std::cout<<y<<std::endl;
        }

        std::cout<<emptyY<<std::endl;

        QBrush brush(player1Color_);
        //QRectF recEllipse(x*gameSquareSideLength + gameSquareellipseProcent*0.5*gameSquareSideLength,
        //                  emptyY*gameSquareSideLength + gameSquareellipseProcent*0.5*gameSquareSideLength,
        //                  gameSquareSideLength -gameSquareellipseProcent*gameSquareSideLength,
        //                  gameSquareSideLength-gameSquareellipseProcent*gameSquareSideLength);

        QGraphicsEllipseItem *ellipse = new QGraphicsEllipseItem(10, 10, 100, 100);
        ellipse->setBrush(brush);
        ellipse->setZValue(-1);

        ellipses_.push_back(ellipse);
        scene_->addItem(ellipse);

        gameFinished_ = isGameFinished();

        if(gameFinished_){

        }
        else{
            changePlayerTurn();
        }
    }
}

void MainWindow::changePlayerTurn()
{
    if(player1Turn_){
        player1Turn_ = false;
    }
    else {
        player1Turn_ = true;
    }

    setPlayerLabels();
}

void MainWindow::setPlayerLabels()
{
    if(player1Turn_){
        ui->message->setText(player1Name_ +" turn");
        ui->colorMessage->setPixmap(player1Pixmap_);
    }
    else{
        ui->message->setText(player2Name_ +" turn");
        ui->colorMessage->setPixmap(player2Pixmap_);
    }
}


bool MainWindow::isGameFinished()
{
    return false;
}

void MainWindow::checkWhoWins()
{

}

void MainWindow::on_actionGameHelp_triggered()
{
    QString help =
            "Connect Four is a two-player connection game\n"
            "in which the players first choose a color and then\n"
            "take turns dropping one colored disc from the top\n"
            "into a seven-column, six-row vertically suspended grid.\n"
            "The pieces fall straight down, occupying the lowest available\n"
            "space within the column. The objective of the game\n"
            "is to be the first to form a horizontal, vertical, or diagonal\n"
            "line of four of one's own discs.\n\n"
            "Source - Wikipedia\n(https://en.wikipedia.org/wiki/Connect_Four)";


    QMessageBox::information(this, "Game Help", help);
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
    if(!gameStarted_ && gameFinished_){
        on_actionNewGame_triggered();
    }
    else if(!gameFinished_){
        makeMove(x);
    }
}

