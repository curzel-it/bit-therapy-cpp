#pragma once 

#include <QGraphicsPixmapItem>
#include <QGraphicsScene>
#include <QLabel>
#include <QWidget>

#include <map>

#include "../game/game.h"

#include "game_pixmap_item.h"

class GameWindow : public QWidget {    
    Q_OBJECT

private:
    QGraphicsScene* scene;
    Game* game;
    QGraphicsTextItem* gameStateText;
    double uiFps;
    std::string screenName;
    Rect frame;
    bool debugEnabled;
    std::map<uint32_t, GamePixmapItem*> itemsById;

    void setupTimer();
    void buildUi();
    
    void removeItemsNotInList(std::vector<uint32_t> ids);
    void removeItemsWithId(uint32_t id);
    
    void createNewItems(std::vector<uint32_t> ids);
    void createNewItem(uint32_t id);

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
