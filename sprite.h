#ifndef SPRITE_H
#define SPRITE_H

#include <QObject>
#include <QGraphicsItem>
#include <QTimer>
#include <QPixmap>
#include <QPainter>
#include <QList>
#include <QPair>

typedef QList<QGraphicsItem*> ItemList;
typedef QPair<int,int> SpriteCoordinate;
typedef QVector<SpriteCoordinate> Coordinates;
typedef QVector<Coordinates> CoordinatesVector;

enum Sprite_Direction {DOWN,LEFT,RIGHT,UP};

class Sprite : public QObject, public QGraphicsItem
{
    Q_OBJECT
public:
    explicit Sprite(int number, int rows,int cols,QObject *parent = 0);

    Sprite_Direction direction();
    void direction(Sprite_Direction d);
    void increaseSpeed(int speed);
    void decreaseSpeed(int speed);
    void stop();
    QString name();
    void name(const QString &name);

signals:
    void spriteClick(Sprite *);
    void spriteTick(Sprite *);

public slots:
    void mousePressEvent(QGraphicsSceneMouseEvent *event);

private slots:
    void nextFrame();   // Slot for turning images into QPixmap

private:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    void checkIfOutOfBounds();
    void checkCollision();
    QRectF boundingRect() const;

private:
    /* In this QPixmap, put the sprite sheet.
     Make it static for efficiency */
    static QPixmap *spriteImage;
    QString spritename;
    int sprite_size;
    int sprite_speed;
    int left_adjust,top_adjust,right_adjust,bottom_adjust;
    int _number; // sprite number
    int sprite_image_top,sprite_image_left;
    int _start_row,_start_col,_rows,_cols;
    Sprite_Direction currentDirection;
    QTimer *timer;      // Timer for turning images into QPixmap
    int currentFrame;   // Coordinates X, which starts the next frame of the sprite
    CoordinatesVector sprite_frames;
    void buildCoordinates();
};

#endif // SPRITE_H
