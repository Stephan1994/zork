#include "roompainter.h"
#include "ui_roompainter.h"

RoomPainter::RoomPainter(QWidget *parent) :
    QWidget(parent)
{
    //ui->setupUi(this);

}

void RoomPainter::paintEvent(QPaintEvent *e)
{
    QPainter painter( this );
    painter.setRenderHint( QPainter::Antialiasing, true );
    painter.setPen( QPen( Qt::black, 10 ) );

    painter.drawLine( p1, p2 );
}

RoomPainter::~RoomPainter()
{
    //delete ui;
}
