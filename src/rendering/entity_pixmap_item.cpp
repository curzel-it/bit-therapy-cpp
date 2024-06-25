#include "entity_pixmap_item.h"

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