#include "roompainter.h"
#include "ui_roompainter.h"

#include <QPainter>
#include <QPoint>
#include <QPen>

RoomPainter::RoomPainter(QWidget *parent, Room *roomToPaint) :
    QWidget(parent)
{
    //ui->setupUi(this);
    room = roomToPaint;
}

void RoomPainter::paintEvent(QPaintEvent *e)
{
    QPainter painter( this );
    painter.setRenderHint( QPainter::Antialiasing, true );
    painter.setPen( QPen( Qt::black, 10 ) );
    QPoint p[4] = {
        QPoint(5, 5), //northwest
        QPoint(this->width() - 5, 5), //northeast
        QPoint(this->width() - 5, this->height() - 5), //southeast
        QPoint(5, this->height() - 5) //southwest
    };

    //draw northern wall and door if necessary
    if (room->exits.find("north") != room->exits.end())
    {
        int doorPos = rand() % this->width();
        QPoint leftDoor = QPoint(doorPos, 5);
        QPoint rightDoor = QPoint(doorPos + this->width()/6, 5);
        painter.drawLine( p[0], leftDoor );
        painter.drawLine( rightDoor, p[1] );
    }
    else
        painter.drawLine( p[0], p[1] );

    //draw southern wall and door if necessary
    if (room->exits.find("south") != room->exits.end())
    {
        int doorPos = rand() % this->width();
        QPoint leftDoor = QPoint(doorPos, this->height() - 5);
        QPoint rightDoor = QPoint(doorPos + this->width()/6, this->height() - 5);
        painter.drawLine( p[3], leftDoor );
        painter.drawLine( rightDoor, p[2] );
    }
    else
        painter.drawLine( p[2], p[3] );

    //draw western wall and door if necessary
    if (room->exits.find("west") != room->exits.end())
    {
        int doorPos = rand() % this->height();
        QPoint highDoor = QPoint(5, doorPos);
        QPoint downDoor = QPoint(5, doorPos + this->height()/6);
        painter.drawLine( p[0], highDoor );
        painter.drawLine( downDoor, p[3] );
    }
    else
        painter.drawLine( p[0], p[3] );

    //draw eastern wall and door if necessary
    if (room->exits.find("east") != room->exits.end())
    {
        int doorPos = rand() % this->height();
        QPoint highDoor = QPoint(this->width() - 5, doorPos);
        QPoint downDoor = QPoint(this->width() - 5, doorPos + this->height()/6);
        painter.drawLine( p[1], highDoor );
        painter.drawLine( downDoor, p[2] );
    }
    else
        painter.drawLine( p[1], p[2] );
}

RoomPainter::~RoomPainter()
{
    //delete ui;
}
