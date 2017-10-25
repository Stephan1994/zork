#include "MapWidget.h"
#include "ui_mapwidget.h"

#include <QPainter>
#include <QPoint>
#include <QPen>

MapWidget::MapWidget(ZorkUL *zork, int visRange, QWidget *parent) :
    QWidget(parent)
{

    changeRooms(zork, visRange);
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

    int squareSize = rect().width() < rect().height() ? rect().width() : rect().height();
    QRect backgroundRect = QRect(0,0,squareSize,squareSize);
    painter.drawImage(backgroundRect, QImage("scroll.png"));
    //number of rooms in width and height, that should be printed by map
    int nrOfRooms = 2 * visibilityRange + 1;

    int rowOffset, colOffset;
    int roomLength = (squareSize - (((squareSize/nrOfRooms) / 3) * 2))/nrOfRooms;
    for (int row = 0; row < nrOfRooms; row++)
    {
        rowOffset = (roomLength * row) + ((squareSize/nrOfRooms) / 3);
        for (int col = 0; col < nrOfRooms; col++)
        {
            if (rooms[row][col] != NULL)
            {
                colOffset = roomLength * col + ((squareSize/nrOfRooms) / 3);
                QPoint p[4] = {
                    QPoint(0 + colOffset, 0 + rowOffset), //northwest
                    QPoint(roomLength + colOffset, 0 + rowOffset), //northeast
                    QPoint(roomLength + colOffset, roomLength + rowOffset), //southeast
                    QPoint(0 + colOffset, roomLength + rowOffset) //southwest
                };

                //draw items
                if (!rooms[row][col]->itemsInRoom.empty())
                {
                    for(std::vector<Item>::iterator it = rooms[row][col]->itemsInRoom.begin(); it != rooms[row][col]->itemsInRoom.end(); ++it)
                    {
                        int playerPosX = p[0].x() + (roomLength / 2) - (roomLength / 12);
                        int playerPosY = p[0].y() + (roomLength / 2) - (roomLength / 12);

                        int posX = p[0].x() + it->randPositionX % (roomLength - roomLength/6);
                        int posY = p[0].y() + it->randPositionY % (roomLength - roomLength/6);
                        if(posX > playerPosX - roomLength/6 && posX < playerPosX + roomLength/6 && posY > playerPosY - roomLength/6 && posY < playerPosY + roomLength/6)
                        {
                            posX += roomLength/3;
                            posY += roomLength/3;
                        }

                        QRect itemRect = QRect(posX, posY, roomLength /6, roomLength /6);
                        QImage itemImg = QImage(QString::fromStdString(it->getPicturePath()));
                        painter.drawImage(itemRect, itemImg);
                    }
                }
                //draw player
                if (row == visibilityRange && col == visibilityRange)
                {
                    int playerPosX = p[0].x() + (roomLength / 2) - (roomLength / 12);
                    int playerPosY = p[0].y() + (roomLength / 2) - (roomLength / 12);
                    QRect playerRect = QRect(playerPosX, playerPosY, roomLength / 6, roomLength / 6);

                    painter.setBrush( QBrush( Qt::red ) );
                    painter.setPen( Qt::NoPen );
                    painter.drawEllipse(playerRect);
                    painter.setBrush( Qt::NoBrush );
                    painter.setPen( QPen( Qt::black, 2 ) );
                    //QImage playerImg = QImage("player.png");
                    //painter.drawImage(playerRect, playerImg);
                }

                int doorPos;
                //draw northern wall and door if necessary
                if (rooms[row][col]->exits.find("north") != rooms[row][col]->exits.end())
                {
                    doorPos = p[0].x() + get<1>(rooms[row][col]->exits.find("north")->second) % (roomLength - (roomLength / 6));//(roomLength / 2) - (roomLength / 12) ;

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
                    doorPos = p[3].x() + get<1>(rooms[row][col]->exits.find("south")->second) % (roomLength - (roomLength / 6));
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
                    doorPos = p[0].y() + get<1>(rooms[row][col]->exits.find("west")->second) % (roomLength - (roomLength / 6));
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
                    doorPos = p[1].y() + get<1>(rooms[row][col]->exits.find("east")->second) % (roomLength - (roomLength / 6));
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

