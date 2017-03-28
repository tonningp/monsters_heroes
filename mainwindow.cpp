#include "ui_mainwindow.h"

#include "mainwindow.h"
#include "sprite.h"
#include <QDebug>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    scene = new CTileScene(this);
    scene->setItemIndexMethod(QGraphicsScene::NoIndex);
    ui->graphicsView->setScene(scene);
    // create objects for the label and progress bar
    statusLabel = new QLabel(this);

    // set text for the label
    statusLabel->setText("Status Label");

    // add the two controls to the status bar
    ui->statusBar->addPermanentWidget(statusLabel);
    drawScene();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::drawScene() {
    /*
    QPixmap pxm = QPixmap(":/images/background_01.png");
    QGraphicsPixmapItem *pm =  scene->addPixmap(pxm);
    pm->setPos(-1*scene->sceneRect().height()/2-175,-1*scene->sceneRect().height()/2);
    */
}

void MainWindow::addHero() {
    addSprite(new Sprite(0,4,3),"hero"); // 0 is a Hero
}

void MainWindow::addMonster() {
    addSprite(new Sprite(1,4,3),"monster"); // 1 is a Monster
}

void MainWindow::addVillager() {
    addSprite(new Sprite(2,4,3),"villager"); // 2 is a Villager
}

void MainWindow::addScheusal() {
    addSprite(new Sprite(3,4,3),"scheusal"); // 3 is a Scheusal
}

void MainWindow::spriteDown() {
    moveSprite(Sprite_Direction::DOWN);
}

void MainWindow::spriteLeft() {
    moveSprite(Sprite_Direction::LEFT);
}

void MainWindow::spriteRight() {
    moveSprite(Sprite_Direction::RIGHT);
}


void MainWindow::spriteUp() {
    moveSprite(Sprite_Direction::UP);
}

void MainWindow::spriteSpeedFast() {
    current_sprite != NULL ? current_sprite->increaseSpeed(50):(void)NULL;
}

void MainWindow::spriteSpeedSlow() {
    current_sprite!=NULL ? current_sprite->decreaseSpeed(50):(void)NULL;
}

void MainWindow::spriteStop() {
    current_sprite != NULL?current_sprite->stop():(void)NULL;
}

void MainWindow::spriteSelected(Sprite *sprite) {
   current_sprite = sprite;
}

void MainWindow::addSprite(Sprite *sprite,const QString &name) {
    sprite->name(name);
    connect(sprite,&Sprite::spriteClick,this,&MainWindow::spriteSelected);
    connect(sprite,&Sprite::spriteTick,this,&MainWindow::updateSpritePosition);
    scene->addItem(sprite,"Sprite");
    current_sprite = sprite;
}

void MainWindow::updateSpritePosition(Sprite *sprite) {
    //qDebug() << "update sprite:" << sprite->pos();
}

void MainWindow::moveSprite(Sprite_Direction direction) {
    current_sprite != NULL ? current_sprite->direction(direction):(void)NULL;
}
