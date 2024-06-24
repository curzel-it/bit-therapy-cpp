#ifndef GAME_WINDOW_H
#define GAME_WINDOW_H

#include <QGraphicsScene>
#include <QLabel>
#include <QWidget>

#include "../game/game.h"

class GameWindow : public QWidget {    
    Q_OBJECT

private:
    QGraphicsScene* scene;
    Game* game;
    double uiFps;
    std::string screenName;
    Rect frame;
    bool debugEnabled;

    void setupTimer();
    void buildUi();

public:
    GameWindow(
        double uiFps, 
        Game* game, 
        bool debugEnabled, 
        std::string screenName, 
        Rect frame
    );
    
    void updateUi();
};

#endif
