#ifndef COMMON_HPP
#define COMMON_HPP

// qt
#include <QString>
#include <QColor>
#include <QBrush>

const unsigned int GAME_BOARD_WIDTH = 7;
const unsigned int GAME_BOARD_HEIGHT= 6;
const double GAME_SQUARE_SIDE_LENGTH= 100.0;
const double GAME_SQUARE_ELLIPSE_PERCENT= 0.2;
const unsigned int PLAYER_COLOR_LABEL_WIDTH = 20;
const unsigned int PLAYER_COLOR_LABEL_HEIGHT = 20;
const unsigned int INIT_WINDOW_WIDTH= GAME_BOARD_WIDTH*static_cast<unsigned int>(GAME_SQUARE_SIDE_LENGTH);
const unsigned int INIT_WINDOW_HEIGHT= GAME_BOARD_HEIGHT*static_cast<unsigned int>(GAME_SQUARE_SIDE_LENGTH);

const QColor DEFAULT_PLAYER_1_COLOR = QColor("red");
const QColor DEFAULT_PLAYER_2_COLOR = QColor("yellow");
const QString DEFAULT_PLAYER_1_NAME = "Jake";
const QString DEFAULT_PLAYER_2_NAME = "Elwood";


const QBrush SQUARE_COLOR = QBrush("blue");
const QBrush BACKGROUND_BRUSH = QBrush("lightGray");

const QString ABOUT_MSG =
    "Game made for \"PAIN\" at Warsaw University Of Technology.\n\n"
     "Programing: Patryk Pankiewicz & Szymon Kałuski\n"
     "Icons authors:\n"
     "-Zurb\n(https://www.flaticon.com/authors/zurb)\n"
     "-Eleonor Wang\n(https://www.flaticon.com/authors/eleonor-wang)\n"
     "both from Flaticon(https://www.flaticon.com/)\nis licensed by Creative Commons BY 3.0.\n"
     "Thanks!\n\n"
     "\n\nWe are on a mission from God!\n"
     "~ Blues Brothers";

const QString CONTACT_MSG =
    "Patryk Pankiewicz:\n"
    "patryk.pankiewicz369@gmail.com";

const QString GAME_HELP_MSG =
    "Connect Four is a two-player connection game\n"
    "in which the players first choose a color and then\n"
    "take turns dropping one colored disc from the top\n"
    "into a seven-column, six-row vertically suspended grid.\n"
    "The pieces fall straight down, occupying the lowest available\n"
    "space within the column. The objective of the game\n"
    "is to be the first to form a horizontal, vertical, or diagonal\n"
    "line of four of one's own discs.\n\n"
    "Source - Wikipedia\n(https://en.wikipedia.org/wiki/Connect_Four)";

const QString START_GAME_MSG =
    "Click on board to start new game!";

#endif // COMMON_HPP

