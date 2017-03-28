#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QGraphicsEllipseItem>
#include <QLabel>
#include <QMainWindow>
#include "ctilescene.h"
#include "sprite.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

    CTileScene *scene;
    QGraphicsRectItem *rectangle;
    QGraphicsEllipseItem *ellipse;
    QGraphicsTextItem *text;
    Sprite *current_sprite;
    QLabel *statusLabel;

    void moveSprite(Sprite_Direction);

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:
    void drawScene();
    void addVillager();
    void addHero();
    void addMonster();
    void addScheusal();
    void spriteDown();
    void spriteLeft();
    void spriteRight();
    void spriteSpeedFast();
    void spriteSpeedSlow();
    void spriteUp();
    void spriteStop();
    void spriteSelected(Sprite*);
    void addSprite(Sprite*,const QString &name);
    void updateSpritePosition(Sprite*);

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
