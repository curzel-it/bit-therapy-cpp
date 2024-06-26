#pragma once 

#include <QGraphicsPixmapitem>
#include <QGraphicsSceneMouseEvent>
#include <QPointF>
#include <QPixmap>
#include <QString>
#include <QTransform>

#include "../game/game.h"

// TODO: Move from constructor to setup

class GamePixmapItem : public QGraphicsPixmapItem {
private:
    Game* game;
    uint32_t targetId;
    bool isMouseDown;
    Vector2d dragDelta;
    QPointF mouseDownPosition;

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent* event) override;
    void mouseMoveEvent(QGraphicsSceneMouseEvent* event) override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent* event) override;

public:
    GamePixmapItem(Game* game, uint32_t targetId);

    void setup(const RenderedItem& item, const Rect& bounds);
};