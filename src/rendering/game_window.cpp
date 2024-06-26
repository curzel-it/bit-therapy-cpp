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

#include <algorithm>
#include <format>

#include "../game/game.h"
#include "../sprites/sprites.h"
#include "../utils/utils.h"

#include "game_pixmap_item.h"
#include "game_window.h"

GameWindow::GameWindow(
    double uiFps,
    Game* game, 
    bool debugEnabled, 
    std::string screenName, 
    Rect frame
) : QWidget(nullptr) {
    this->itemsById = std::map<uint32_t, GamePixmapItem*>({});
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

    gameStateText = scene->addText(QString::fromStdString("Loading..."));
    gameStateText->setDefaultTextColor(Qt::green);
    gameStateText->setFont(QFont("Courier New", 15, QFont::Medium));
    gameStateText->setPos(frame.x + 10, frame.y + 30);

    QGraphicsDropShadowEffect* shadowEffect = new QGraphicsDropShadowEffect();
    shadowEffect->setBlurRadius(8);
    shadowEffect->setColor(Qt::black);
    shadowEffect->setOffset(1.0, 1.0);
    gameStateText->setGraphicsEffect(shadowEffect);        

    QGraphicsView* sceneView = new QGraphicsView(scene);
    sceneView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    sceneView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    sceneView->setStyleSheet("background: transparent");
    
    QVBoxLayout* layout = new QVBoxLayout();
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
    auto items = game->render();
    auto ids = map<RenderedItem, uint32_t>(items, [](const RenderedItem& item) { 
        return item.id;
    });

    removeItemsNotInList(ids);
    createNewItems(ids);
    
    for (const auto& item : items) {
        itemsById[item.id]->setup(item, frame);
    }

    if (debugEnabled) {
        QString description = QString::fromStdString(game->description());
        gameStateText->setPlainText(description);
    }
}

void GameWindow::createNewItems(std::vector<uint32_t> ids) {
    for (const auto& id: ids) {
        if (!itemsById.contains(id)) {
            createNewItem(id);
        }
    }
}

void GameWindow::createNewItem(uint32_t id) {
    auto newItem = new GamePixmapItem(game, id);
    itemsById.emplace(id, newItem);
    scene->addItem(newItem);
}

void GameWindow::removeItemsNotInList(std::vector<uint32_t> ids) {
    for (const auto& existingId : std::views::keys(itemsById)) {
        if(std::find(ids.begin(), ids.end(), existingId) == ids.end()) {
            removeItemsWithId(existingId);
        }
    } 
}

void GameWindow::removeItemsWithId(uint32_t id) {
    auto item = itemsById[id];
    scene->removeItem(item);
    itemsById.erase(id);
    delete item;
}