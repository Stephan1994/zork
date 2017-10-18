#include "mapwidget.h"
#include "ui_mapwidget.h"
#include "roompainter.h"

MapWidget::MapWidget(ZorkUL *zork, QWidget *parent) :
    QWidget(parent)
{
    //ui->setupUi(this);
    mainGrid = new QGridLayout();


    //RoomPainter roomSouth = new RoomPainter(this,)

}

MapWidget::~MapWidget()
{
    //delete ui;
    delete mainGrid;
}

void MapWidget::createRooms(Room rooms[9])
{
    for (int i = 0; i < 9; i++)
    {
        //paintedRooms[i] = RoomPainter(this, )
    }
}
