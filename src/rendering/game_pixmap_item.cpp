#include "game_pixmap_item.h"

#include <iostream>

#include "../game/game.h"

GamePixmapItem::GamePixmapItem() : QGraphicsPixmapItem(nullptr) {}

void GamePixmapItem::setup(const RenderedItem& item, const Rect& bounds) {
    auto path = QString::fromStdString(item.spritePath);
    QPixmap pixmap(path);

    if (item.isFlipped) {
        QTransform transform;
        transform.scale(-1, 1);
        pixmap = pixmap.transformed(transform, Qt::FastTransformation);
    }

    QPixmap scaledPixmap = pixmap.scaled(
        item.frame.w,
        item.frame.h,
        Qt::KeepAspectRatio,
        Qt::FastTransformation
    );

    setPixmap(scaledPixmap);
    setPos(bounds.x + item.frame.x, bounds.y + item.frame.y);
}

// TODO: Send mouse events to a bus for processing on next frame

void GamePixmapItem::mousePressEvent(QGraphicsSceneMouseEvent* event) {
    std::cout << "Mouse mousePressEvent " << event << std::endl;
}

void GamePixmapItem::mouseMoveEvent(QGraphicsSceneMouseEvent* event) {
    std::cout << "Mouse mouseMoveEvent " << event << std::endl;
}

void GamePixmapItem::mouseReleaseEvent(QGraphicsSceneMouseEvent* event) {
    std::cout << "Mouse mouseReleaseEvent " << event << std::endl;
}

void GamePixmapItem::mouseDoubleClickEvent(QGraphicsSceneMouseEvent* event) {
    std::cout << "Mouse mouseDoubleClickEvent " << event << std::endl;
}