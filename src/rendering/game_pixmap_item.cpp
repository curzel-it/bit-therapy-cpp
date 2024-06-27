#include "game_pixmap_item.h"

#include <iostream>
#include <math.h>

#include "../game/game.h"

GamePixmapItem::GamePixmapItem(Yage::Game* game, uint32_t targetId) : QGraphicsPixmapItem(nullptr) {
    this->targetId = targetId;
    this->game = game;
    this->isMouseDown = false;
}

void GamePixmapItem::setup(const Yage::RenderedItem& item, const Yage::Rect& bounds) {
    auto path = QString::fromStdString(item.spritePath);
    QTransform transform;

    if (item.isFlipped) {
        transform.scale(-1, 1);
    }
    if (item.zRotation) {
        transform.rotateRadians(item.zRotation);
    }

    QPixmap pixmap(path);
    pixmap = pixmap.transformed(transform, Qt::FastTransformation);

    QPixmap scaledPixmap = pixmap.scaled(
        item.frame.w,
        item.frame.h,
        Qt::KeepAspectRatio,
        Qt::FastTransformation
    );

    setPixmap(scaledPixmap);

    setPos(
        bounds.x + item.frame.x + dragDelta.x, 
        bounds.y + item.frame.y + dragDelta.y
    );
}

void GamePixmapItem::mousePressEvent(QGraphicsSceneMouseEvent* event) {
    isMouseDown = true;
    mouseDownPosition = event->screenPos();
    game->mouseDragStarted(targetId);
}

void GamePixmapItem::mouseMoveEvent(QGraphicsSceneMouseEvent* event) {
    auto currentPosition = event->screenPos();
    dragDelta.x = currentPosition.x() - mouseDownPosition.x();
    dragDelta.y = currentPosition.y() - mouseDownPosition.y();
}

void GamePixmapItem::mouseReleaseEvent(QGraphicsSceneMouseEvent* event) {
    game->mouseDragEnded(targetId, dragDelta);
    isMouseDown = false;
    dragDelta.x = 0.0;
    dragDelta.y = 0.0;
}