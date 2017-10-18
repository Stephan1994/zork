#include "mapwidget.h"
#include "ui_mapwidget.h"

MapWidget::MapWidget(ZorkUL *zork, QWidget *parent) :
    QWidget(parent)
{
    //ui->setupUi(this);
    mainGrid = new QGridLayout();

    Room *current = zork->currentRoom;
    Room *rooms[9] = {NULL};
    int c = 0;
    int rowStart = (current->posRow - 1 < 0) ? current->posRow : current->posRow - 1;
    int rowEnd = (current->posRow + 1 > 49) ? current->posRow : current->posRow + 1;
    int colStart = (current->posCol - 1 < 0) ? current->posCol : current->posCol - 1;
    int colEnd = (current->posCol + 1 > 49) ? current->posCol : current->posCol + 1;
    for (int i=rowStart; i<rowEnd; i++)
    {
        for(int j = colStart; j < colEnd; j++)
        {
            rooms[c] = zork->rooms[i][j];
            c++;
        }

    }
    RoomPainter paintedRooms[9] = createRooms(rooms);


    c = 0;
    for (int row = 0; row < 3; row++)
    {
        for (int col = 0; col < 3; col++)
        {
            mainGrid->addWidget(paintedRooms[c], row, col, 1, 1);
            c++;
        }
    }
}

MapWidget::~MapWidget()
{
    //delete ui;
    delete mainGrid;
}

RoomPainter* MapWidget::createRooms(Room rooms[9])
{
    RoomPainter paintedRooms[9] = {NULL};
    for (int i = 0; i < 9; i++)
    {
        if (rooms[i] != NULL)
            paintedRooms[i] = RoomPainter(this, rooms[i])
    }
    return paintedRooms;
}
