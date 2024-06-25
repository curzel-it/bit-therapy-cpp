#include "entity_pixmap_item.h"

#include <iostream>

GamePixmapItem::GamePixmapItem(
    const RenderedItem& item, 
    QGraphicsItem* parent
) : QGraphicsPixmapItem(parent) {
    auto path = QString::fromStdString(item.spritePath);
    QPixmap pixmap(path);

    if (item.isFlipped) {
        QTransform transform;
        transform.scale(-1, 1);
        pixmap = pixmap.transformed(transform, Qt::SmoothTransformation);
    }

    QPixmap scaledPixmap = pixmap.scaled(
        item.frame.w,
        item.frame.h,
        Qt::KeepAspectRatio,
        Qt::SmoothTransformation
    );

    setPixmap(scaledPixmap);
    setPos(item.frame.x, item.frame.y);
}

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