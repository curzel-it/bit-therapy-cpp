#include <QGraphicsDropShadowEffect>
#include <QGraphicsPixmapitem>
#include <QGraphicsView>
#include <QImage>
#include <QLabel>
#include <QMouseEvent>
#include <QPainter>
#include <QScrollArea>
#include <QString>
#include <QTimer>
#include <QTime>
#include <QVBoxLayout>
#include <QWidget>

#include <format>

#include "../game/game.h"
#include "../sprites/sprites.h"
#include "../utils/utils.h"

#include "entity_pixmap_item.h"
#include "game_window.h"

GameWindow::GameWindow(
    double uiFps,
    Game* game, 
    bool debugEnabled, 
    std::string screenName, 
    Rect frame
) : QWidget(nullptr) {
    this->uiFps = uiFps;
    this->debugEnabled = debugEnabled;
    this->game = game;
    this->screenName = screenName;
    this->frame = frame;
    buildUi();
    setupTimer();
}

void GameWindow::setupTimer() {
    QTimer *timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &GameWindow::updateUi);
    timer->start(1000 / uiFps);
}

void GameWindow::buildUi() {
    scene = new QGraphicsScene();
    scene->setSceneRect(frame.x, frame.y, frame.w, frame.h);
    QGraphicsView *sceneView = new QGraphicsView(scene);
    sceneView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    sceneView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    sceneView->setStyleSheet("background: transparent");
    
    QVBoxLayout *layout = new QVBoxLayout();
    layout->setSpacing(0);
    layout->setContentsMargins(0, 0, 0, 0);
    layout->addWidget(sceneView);
    setLayout(layout);

    setGeometry(frame.x, frame.y, frame.w, frame.h);
    setWindowFlags(Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint);
    setAttribute(Qt::WA_TranslucentBackground);
    setWindowTitle("Game Window");
}

void GameWindow::updateUi() {
    scene->clear();

    for (const auto& item : game->render()) {
        GamePixmapItem* pixmapItem = new GamePixmapItem(item);
        scene->addItem(pixmapItem);
    }

    if (debugEnabled) {
        QString description = QString::fromStdString(game->description());
        QGraphicsTextItem *gameStateText = scene->addText(description);
        gameStateText->setDefaultTextColor(Qt::green);
        gameStateText->setFont(QFont("Courier New", 15, QFont::Medium));
        gameStateText->setPos(frame.x + 10, frame.y + 30);

        QGraphicsDropShadowEffect* shadowEffect = new QGraphicsDropShadowEffect();
        shadowEffect->setBlurRadius(8);
        shadowEffect->setColor(Qt::black);
        shadowEffect->setOffset(1.0, 1.0);
        gameStateText->setGraphicsEffect(shadowEffect);
    }
}
