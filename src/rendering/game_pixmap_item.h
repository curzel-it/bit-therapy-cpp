#pragma once 

#include <QGraphicsPixmapitem>
#include <QString>
#include <QPixmap>
#include <QTransform>

#include "../game/game.h"

// TODO: Move from constructor to setup

class GamePixmapItem : public QGraphicsPixmapItem {

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent* event) override;
    void mouseMoveEvent(QGraphicsSceneMouseEvent* event) override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent* event) override;
    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent* event) override;

public:
    GamePixmapItem();

    void setup(const RenderedItem& item, const Rect& bounds);
};