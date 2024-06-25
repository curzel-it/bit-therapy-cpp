#pragma once 

#include <QGraphicsPixmapitem>
#include <QString>
#include <QPixmap>
#include <QTransform>

#include "../game/game.h"

class GamePixmapItem : public QGraphicsPixmapItem {

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent* event) override;
    void mouseMoveEvent(QGraphicsSceneMouseEvent* event) override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent* event) override;
    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent* event) override;

public:
    GamePixmapItem(const RenderedItem& item, QGraphicsItem* parent = nullptr);
};