#pragma once 

#include <QGraphicsPixmapitem>
#include <QString>
#include <QPixmap>
#include <QTransform>

#include "../game/game.h"

class GamePixmapItem : public QGraphicsPixmapItem {
public:
    GamePixmapItem(const RenderedItem& item, QGraphicsItem *parent = nullptr);
};