#include "MainWindow.hpp"
#include "ui_MainWindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow), gameStarted_(false), gameFinished_(true)
{
    ui->setupUi(this);
    ui->message->setText("Click to start new game!");
    ui->graphicsView->setRenderHint(QPainter::Antialiasing);
    ui->colorMessage->setText("");

    player1Color_ = QColor("red");
    player2Color_ = QColor("yellow");
    player1Name_ ="Jake";
    player2Name_ = "Elwood";

    this->setMinimumSize(initWindowWidth, initWindowHeight);
    initGameField();

    QObject::connect(ui->graphicsView, &SizeFitGraphicsView::graphicsViewClicked,
                     this, &MainWindow::gameFieldClickedPosition);
}

MainWindow::~MainWindow()
{
    for(unsigned int i = 0; i<timers_.size(); ++i){
        delete timers_[i];
    }

    timers_.clear();

    delete scene_;

    delete ui;
}

void MainWindow::initGameField()
{
    scene_ = new QGraphicsScene();

    for(unsigned int i = 0; i<gameBoardWidth; ++i ){
        for(unsigned int j = 0; j<gameBoardHeight; ++j){
            gameField[i][j] = Empty;
            GameSquare *tmp = new GameSquare(gameSquareSideLength);
            tmp->setPos(i*gameSquareSideLength, j*gameSquareSideLength);
            scene_->addItem(tmp);
        }
    }

    ui->graphicsView->setScene(scene_);
    ui->graphicsView->setBackgroundBrush(QBrush("lightGray"));
}


void MainWindow::resetGameField()
{

    for(unsigned int i = 0; i<timers_.size(); ++i){
        delete timers_[i];
    }

    timers_.clear();

    delete scene_;

    initGameField();
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

    if(gameField[column][gameBoardHeight-1] == Empty){
        int row = 0;
        for(unsigned int y = 0; y<gameBoardHeight; ++y){
            if(gameField[column][y] == Empty){
                row = y;
                break;
            }
        }

        QPointF begin(column*gameSquareSideLength + gameSquareEllipseProcent/2*gameSquareSideLength,
                      gameSquareEllipseProcent/2*gameSquareSideLength);
        QPointF end(column*gameSquareSideLength + gameSquareEllipseProcent/2*gameSquareSideLength,
                               (gameBoardHeight-1-row)*gameSquareSideLength);
        QSizeF size((1-gameSquareEllipseProcent)*gameSquareSideLength,
                            (1-gameSquareEllipseProcent)*gameSquareSideLength);
        QRectF recEllipse(begin, size);

        Disc *disc = new Disc();

        disc->setEnd(end);
        disc->setRect(recEllipse);
        disc->setZValue(-1);

        if(player1Turn_){
            disc->setBrush(player1Color_);
            gameField[column][row] = Player1;
        }
        else {
            disc->setBrush(player2Color_);
            gameField[column][row] = Player2;
        }

        disc->setZValue(-1);
        scene_->addItem(disc);

        QTimer *timer = new QTimer();
        QObject::connect(timer, &QTimer::timeout, disc, &Disc::moveDisc);
        QObject::connect(disc, &Disc::animationHaveFinish, this, &MainWindow::animationHaveFinish);
        timer->start(20);

        timers_.emplace_back(timer);

        gameFinished_ = isGameFinished();

        if(!isGameFinished()){
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
    int winner = checkWhoWins();

    if(winner != Nobody){
        return true;
    }

    for(unsigned int i = 0; i<gameBoardWidth; ++i){
        if(gameField[i][gameBoardHeight-1]==Empty){
            return false;
        }
    }

    return true;
}

int MainWindow::checkWhoWins()
{
    // check vertically
    for(unsigned int  j = 0; j<gameBoardWidth; ++j){
        for(unsigned int  i = 0; i<gameBoardHeight-3; ++i){
            if( gameField[j][i]!=Empty &&
                gameField[j][i] == gameField[j][i+1] &&
                gameField[j][i+1] == gameField[j][i+2] &&
                gameField[j][i+2] == gameField[j][i+3]){
                if(gameField[j][i] == Player1)
                    return Player1Wins;
                else
                    return Player2Wins;
            }
        }
    }

    // check horizonally
    for(unsigned int  j = 0; j<gameBoardWidth-3; ++j){
        for(unsigned int  i = 0; i<gameBoardHeight; ++i){
            if( gameField[j][i]!=Empty &&
                gameField[j][i] == gameField[j+1][i] &&
                gameField[j+1][i] == gameField[j+2][i] &&
                gameField[j+2][i] == gameField[j+3][i]){
                if(gameField[j][i] == Player1)
                    return Player1Wins;
                else
                    return Player2Wins;
            }
        }
    }

    // check diagonaly left bottom to right top
    for(unsigned int j = 0; j<gameBoardWidth-3; ++j){
        for(unsigned int  i = 0; i<gameBoardHeight-3; ++i){
            if( gameField[j][i]!=Empty &&
                gameField[j][i] == gameField[j+1][i+1] &&
                gameField[j+1][i+1] == gameField[j+2][i+2] &&
                gameField[j+2][i+2] == gameField[j+3][i+3]){
                if(gameField[j][i] == Player1)
                    return Player1Wins;
                else
                    return Player2Wins;
            }
        }
    }

    //check diagonaly left top to right button
    for(unsigned int  j = gameBoardWidth-1; j>=3; --j){
        for(unsigned int  i = 0; i<gameBoardHeight-3; ++i){
            if( gameField[j][i]!=Empty &&
                gameField[j][i] == gameField[j-1][i+1] &&
                gameField[j-1][i+1] == gameField[j-2][i+2] &&
                gameField[j-2][i+2] == gameField[j-3][i+3]){
                if(gameField[j][i] == Player1)
                    return Player1Wins;
                else
                    return Player2Wins;
            }
        }
    }

    return Nobody;
}

// slots

void MainWindow::on_actionNewGame_triggered()
{
    PlayerMenu playerMenu(player1Name_, player2Name_, player1Color_, player2Color_, this);
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
         "Proggraming: Patryk Pankiewicz & Szymon Kałuski\n"
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
    else if(!gameFinished_ && x<=gameSquareSideLength*gameBoardWidth){
        makeMove(x);
    }
}

void MainWindow::animationHaveFinish(){
    if(gameFinished_){
        gameStarted_ = false;

        QFont font;
        font.setPixelSize(50);
        font.setBold(false);
        font.setFamily("Calbri");

        int winner = checkWhoWins();

        if(winner == Player1Wins){
            QPainterPath *painterPath = new QPainterPath();
            painterPath->addText(gameSquareSideLength, gameSquareSideLength*2, font, player1Name_ + " wins!");
            scene_->addPath(*painterPath, QPen(QBrush(Qt::black), 2), QBrush(player1Color_));
            delete painterPath;
        }
        else if(winner == Player2Wins){
            QPainterPath *painterPath = new QPainterPath();
            painterPath->addText(gameSquareSideLength, gameSquareSideLength*2, font, player2Name_ + " wins!");
            scene_->addPath(*painterPath, QPen(QBrush(Qt::black), 2), QBrush(player2Color_));
            delete painterPath;

        } else{
            QPainterPath *painterPath = new QPainterPath();
            painterPath->addText(gameSquareSideLength, gameSquareSideLength*2, font, "Draw...");
            scene_->addPath(*painterPath, QPen(QBrush(Qt::black), 2), QBrush(Qt::black));
            delete painterPath;
        }

        ui->message->setText("Click to start new game!");
        ui->colorMessage->setPixmap(QPixmap(0,0));

    }
}

