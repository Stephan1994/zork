#include "mapwidget.h"
#include "ui_mapwidget.h"

#include <QPainter>
#include <QPoint>
#include <QPen>

MapWidget::MapWidget(ZorkUL *zork, int visRange, QWidget *parent) :
    QWidget(parent)
{
    //ui->setupUi(this);
    //mainGrid = new QGridLayout();

    changeRooms(zork, visRange);

    //vector<RoomPainter*> paintedRooms = createRooms(rooms, paintedRooms);

    //mainGrid->addWidget(paintedRooms[0], 1,1);

 /*   c = 0;
    for (int row = rowStart; row < rowEnd; row++)
    {
        for (int col = colStart; col < colEnd; col++)
        {
            mainGrid->addWidget(paintedRooms[c], row, col);
            c++;
        }
    }*/
}

void MapWidget::changeRooms(ZorkUL *zork, int visRange)
{
    visibilityRange = visRange;
    rooms.clear();
    rooms.resize(visibilityRange * 2 + 1);
    for (int i=0; i<visibilityRange * 2 + 1; i++)
    {
        rooms[i].resize(visibilityRange * 2 + 1, NULL);
    }

    Room *current = zork->currentRoom;

    //get rooms depending on the visibilityRange around the current room
    int rowStart = current->posRow - visibilityRange;
    while(rowStart < 0){rowStart++;};
    int rowEnd = current->posRow + visibilityRange;
    while(rowEnd > (zork->maxRoomsRow - 1)){rowEnd--;};
    int colStart = current->posCol - visibilityRange;
    while(colStart < 0){colStart++;};
    int colEnd = current->posCol + visibilityRange;
    while(colEnd > zork->maxRoomsCol - 1){colEnd--;};

    //add rooms to widgets rooms vector
    for (int i=rowStart; i <= rowEnd; i++)
    {
        for(int j = colStart; j <= colEnd; j++)
        {
            rooms[i - (current->posRow - visibilityRange)][j - (current->posCol - visibilityRange)] = zork->rooms[i][j];
        }
    }
    this->update();
}

MapWidget::~MapWidget()
{
    //delete ui;
    //delete mainGrid;
}

void MapWidget::paintEvent(QPaintEvent *e)
{
    QPainter painter( this );
    painter.setRenderHint( QPainter::Antialiasing, true );
    painter.setPen( QPen( Qt::black, 2 ) );

    //number of rooms in width and height, that should be printed by map
    int nrOfRooms = 2 * visibilityRange + 1;

    int rowOffset, colOffset;
    int roomLength = rect().width()/nrOfRooms;
    for (int row = 0; row < nrOfRooms; row++)
    {
        rowOffset = roomLength * row;
        for (int col = 0; col < nrOfRooms; col++)
        {
            if (rooms[row][col] != NULL)
            {
                colOffset = roomLength * col;
                QPoint p[4] = {
                    QPoint(0 + colOffset, 0 + rowOffset), //northwest
                    QPoint(roomLength + colOffset, 0 + rowOffset), //northeast
                    QPoint(roomLength + colOffset, roomLength + rowOffset), //southeast
                    QPoint(0 + colOffset, roomLength + rowOffset) //southwest
                };

                if (row == visibilityRange && col == visibilityRange)
                {
                    int playerPosX = p[0].x() + (roomLength / 2) - (roomLength / 12);
                    int playerPosY = p[0].y() + (roomLength / 2) - (roomLength / 12);
                    QRect playerRect = QRect(playerPosX, playerPosY, roomLength / 6, roomLength / 6);
                    QImage playerImg = QImage("player.png");
                    painter.drawImage(playerRect, playerImg);
                }

                int doorPos;
                //draw northern wall and door if necessary
                if (rooms[row][col]->exits.find("north") != rooms[row][col]->exits.end())
                {
                    doorPos = p[0].x() + (roomLength / 2) - (roomLength / 12) ;

                    QPoint leftDoor = QPoint(doorPos, 0 + rowOffset);
                    QPoint rightDoor = QPoint(doorPos + (roomLength / 6), 0 + rowOffset);
                    painter.drawLine( p[0], leftDoor );
                    painter.drawLine( rightDoor, p[1] );
                }
                else
                    painter.drawLine( p[0], p[1] );

                //draw southern wall and door if necessary
                if (rooms[row][col]->exits.find("south") != rooms[row][col]->exits.end())
                {
                    doorPos = p[3].x() + (roomLength / 2) - (roomLength / 12) ;
                    QPoint leftDoor = QPoint(doorPos, roomLength + rowOffset);
                    QPoint rightDoor = QPoint(doorPos + (roomLength / 6), roomLength + rowOffset);
                    painter.drawLine( p[3], leftDoor );
                    painter.drawLine( rightDoor, p[2] );
                }
                else
                    painter.drawLine( p[2], p[3] );

                //draw western wall and door if necessary
                if (rooms[row][col]->exits.find("west") != rooms[row][col]->exits.end())
                {
                    doorPos = p[0].y() + (roomLength / 2) - (roomLength / 12) ;
                    QPoint highDoor = QPoint(0 + colOffset, doorPos);
                    QPoint downDoor = QPoint(0 + colOffset, doorPos + (roomLength / 6));
                    painter.drawLine( p[0], highDoor );
                    painter.drawLine( downDoor, p[3] );
                }
                else
                    painter.drawLine( p[0], p[3] );

                //draw eastern wall and door if necessary
                if (rooms[row][col]->exits.find("east") != rooms[row][col]->exits.end())
                {
                    doorPos = p[1].y() + (roomLength / 2) - (roomLength / 12) ;
                    QPoint highDoor = QPoint(roomLength + colOffset, doorPos);
                    QPoint downDoor = QPoint(roomLength + colOffset, doorPos + (roomLength / 6));
                    painter.drawLine( p[1], highDoor );
                    painter.drawLine( downDoor, p[2] );
                }
                else
                    painter.drawLine( p[1], p[2] );
            }
        }
    }
}
/*
void MapWidget::createRooms(Room *rooms[9], RoomPainter *paintedRooms[9])
{
    for (int i = 0; i < 9; i++)
    {
        if (rooms[i] != NULL)
        {
            double zoom = 0.5;
            paintedRooms[i] = new RoomPainter(rooms[i], zoom);
            paintedRooms[i]->setMinimumSize(110*zoom, 110*zoom);
        }
    }
}*/
