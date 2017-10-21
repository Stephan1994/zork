#include "roompainter.h"
#include "ui_roompainter.h"

#include <QPainter>
#include <QPoint>
#include <QPen>

RoomPainter::RoomPainter(QWidget *parent):
    QWidget(parent)
{

}
RoomPainter::RoomPainter(Room *roomToPaint, double zoom, QWidget *parent) :
    QWidget(parent)
{
    //ui->setupUi(this);
    room = roomToPaint;
    scale = zoom;
}

void RoomPainter::paintEvent(QPaintEvent *e)
{
    QPainter painter( this );
    painter.setRenderHint( QPainter::Antialiasing, true );
    painter.setPen( QPen( Qt::black, 2*scale ) );
    QPoint p[4] = {
        QPoint(5*scale, 5*scale), //northwest
        QPoint((100 - 5)*scale, 5*scale), //northeast
        QPoint((100 - 5)*scale, (100 - 5)*scale), //southeast
        QPoint(5*scale, (100 - 5)*scale) //southwest
    };

    //draw northern wall and door if necessary
    if (room->exits.find("north") != room->exits.end())
    {
        int doorPos = rand() % (int)(100*scale);
        QPoint leftDoor = QPoint(doorPos, 5*scale);
        QPoint rightDoor = QPoint(doorPos + (100/6)*scale, 5*scale);
        painter.drawLine( p[0], leftDoor );
        painter.drawLine( rightDoor, p[1] );
    }
    else
        painter.drawLine( p[0], p[1] );

    //draw southern wall and door if necessary
    if (room->exits.find("south") != room->exits.end())
    {
        int doorPos = rand() % (int)100*scale;
        QPoint leftDoor = QPoint(doorPos, (100 - 5)*scale);
        QPoint rightDoor = QPoint(doorPos + (100/6)*scale, (100 - 5)*scale);
        painter.drawLine( p[3], leftDoor );
        painter.drawLine( rightDoor, p[2] );
    }
    else
        painter.drawLine( p[2], p[3] );

    //draw western wall and door if necessary
    if (room->exits.find("west") != room->exits.end())
    {
        int doorPos = rand() % (int)100*scale;
        QPoint highDoor = QPoint(5*scale, doorPos);
        QPoint downDoor = QPoint(5*scale, doorPos + (100/6)*scale);
        painter.drawLine( p[0], highDoor );
        painter.drawLine( downDoor, p[3] );
    }
    else
        painter.drawLine( p[0], p[3] );

    //draw eastern wall and door if necessary
    if (room->exits.find("east") != room->exits.end())
    {
        int doorPos = rand() % (int)100*scale;
        QPoint highDoor = QPoint((100 - 5)*scale, doorPos);
        QPoint downDoor = QPoint((100 - 5)*scale, doorPos + (100/6)*scale);
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
