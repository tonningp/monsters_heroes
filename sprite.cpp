#include "sprite.h"
#include <QGraphicsScene>
#include <QDebug>

QPixmap *Sprite::spriteImage;

Sprite::Sprite(int number,int rows,int cols,QObject *parent) :
    QObject(parent), QGraphicsItem(),
    _number(number),_rows(rows),_cols(cols),
    sprite_size(32),sprite_image_left(-10),sprite_image_top(-10),
    _start_row(0),sprite_speed(300) {

    setFlag(QGraphicsItem::ItemIsMovable);
    setFlag(QGraphicsItem::ItemIsSelectable);
    buildCoordinates();
    direction(Sprite_Direction::DOWN);
    if(Sprite::spriteImage == NULL) {
       Sprite::spriteImage = new QPixmap(":/images/sprite_sheet_01.png"); // Load the sprite image QPixmap
    }
    //spriteImage = new QPixmap(":/images/qpixmap_sprite.png"); // Load the sprite image QPixmap
    //spriteImage = new QPixmap(":/images/sprite_sheet_monster_01.png"); // Load the sprite image QPixmap

    timer = new QTimer();   // Create a timer for sprite animation
    connect(timer, &QTimer::timeout, this, &Sprite::nextFrame);
    timer->start(sprite_speed);   // Run the sprite on the signal generation with the given frequency
    left_adjust=0;
    top_adjust=0;
    right_adjust = 0;
    bottom_adjust = 0;
}

Sprite_Direction Sprite::direction() {
    return currentDirection;
}

void Sprite::direction(Sprite_Direction d) {
    currentDirection = d;
}

void Sprite::increaseSpeed(int speed) {
    timer->start((timer->interval()-speed < 0)?0:timer->interval()-speed);
}

void Sprite::decreaseSpeed(int speed) {
    timer->start(timer->interval()+speed);
}

void Sprite::stop() {
    timer->stop();
}

void Sprite::name(const QString& name) {
    spritename = name;
}

QString Sprite::name() {
    return spritename;
}

void Sprite::mousePressEvent(QGraphicsSceneMouseEvent *event) {
    emit spriteClick(this);
}

QRectF Sprite::boundingRect() const
{
    return QRectF(sprite_image_top,sprite_image_left,sprite_size,sprite_size);
}

void Sprite::buildCoordinates() {
    currentFrame = 0;   // Sets the coordinates of the current frame of the sprite
    for(int row=0;row < _rows;row++) {
        Coordinates list;
        for(int col=0;col<_cols;col++) {
            list << SpriteCoordinate((_number*_cols*sprite_size)+sprite_size*col,
                                       (_start_row*sprite_size)+sprite_size*row);
        }
        sprite_frames << list;
        list.clear();
    }
}

void Sprite::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    /* In the graphic renderer we draw the sprite
     * The first two arguments - is the X and Y coordinates of where to put QPixmap
     * The third argument - a pointer to QPixmap which is the sprite sheet
     * 4 and 5 of the arguments - The coordinates in the image QPixmap, where the image is displayed
     * By setting the X coordinate with the variable currentFrame we are moving the camera
     * to the sprite frame in the sprite sheet
     * and the last two arguments - the width and height of the displayed area, that is, the frame
     * */
    SpriteCoordinate coord = sprite_frames[(int)currentDirection][currentFrame];
    painter->drawPixmap(sprite_image_top,sprite_image_left, *spriteImage,
                        coord.first, coord.second, sprite_size,sprite_size);
    // Q_UNUSED Indicates to the compiler that the parameter with the specified name
    // is not used in the body of a function. This can be used to suppress
    // compiler warnings while allowing functions to be defined with meaningful
    // parameter names in their signatures.
    Q_UNUSED(option);
    Q_UNUSED(widget);
}

void Sprite::checkIfOutOfBounds() {
    QRectF sceneRect = scene()->sceneRect();
    if (x() < sceneRect.left()+left_adjust) { // left
            //setPos(sceneRect.left()+left_adjust, y());
            direction(RIGHT);
    }
    else if (x() + boundingRect().right() > sceneRect.right()) {
            //setPos(sceneRect.right() - boundingRect().width()/2+right_adjust, y());
            direction(LEFT);
    }

    if (y() < sceneRect.top()+top_adjust) {
            //setPos(x(), sceneRect.top()+top_adjust);
            direction(DOWN);
    }
    else if ( y()+ boundingRect().bottom() > sceneRect.bottom()) {
            //setPos(x(), sceneRect.bottom() - boundingRect().height()/2+bottom_adjust);
            direction(UP);
    }
}

void Sprite::checkCollision() {
    ItemList list = scene()->collidingItems(this);
    for(auto item : list) {
      if(item->data(0) == "Sprite") { // we are colliding with a Sprite
       qDebug() << (dynamic_cast<Sprite*>(item))->name();
      }
    }
}

/**
 * @brief Sprite::nextFrame
 * Will set the frame as well as the position of the sprite in the scene
 */
void Sprite::nextFrame() {
    currentFrame++; // update the column frame
    if(currentFrame > _cols-1) currentFrame = 0;
    switch(currentDirection) {
        case DOWN:
            this->setPos(this->pos()+QPointF(0,5));
            break;
        case UP:
            this->setPos(this->pos()+QPointF(0,-5));
            break;
        case LEFT:
            this->setPos(this->pos()+QPointF(-5,0));
            break;
        case RIGHT:
            this->setPos(this->pos()+QPointF(5,0));
            break;
    }
    checkIfOutOfBounds();
    checkCollision();
    this->update(sprite_image_top,sprite_image_left,sprite_size,sprite_size);
    emit spriteTick(this);
}
