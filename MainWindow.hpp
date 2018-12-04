#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

// qt
#include <QMainWindow>
#include <QMessageBox>
#include <QGraphicsView>

// connected four
#include "common.hpp"
#include "PlayerMenu.hpp"
#include "GameSquare.hpp"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
protected:
    enum FieldType {Player1, Player2, Empty};

    FieldType gameField[gameBoardWidth][gameBoardHeight];
    GameSquare* gameSquare[gameBoardWidth][gameBoardHeight];

    QString player1Name_;
    QString player2Name_;
    QColor player1Color_;
    QColor player2Color_;
    bool gameStarted_;
    bool player1Turn;
    QGraphicsScene *scene;

protected:
    void initGameField();
    void resetGameField();
    void changePlayerTurn();
    void setPlayerLabels();

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_actionNewGame_triggered();
    void on_actionGameHelp_triggered();
    void on_actionAbout_triggered();
    void on_actionContact_triggered();

    void gameFieldClickedPosition(int x);

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_HPP
