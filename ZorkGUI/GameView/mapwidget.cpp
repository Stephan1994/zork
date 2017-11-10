#include "MapWidget.h"

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
    int rowStart = current->getRoomRow() - visibilityRange;
    while(rowStart < 0){rowStart++;};
    int rowEnd = current->getRoomRow() + visibilityRange;
    while(rowEnd > (zork->maxRoomsRow - 1)){rowEnd--;};
    int colStart = current->getRoomCol() - visibilityRange;
    while(colStart < 0){colStart++;};
    int colEnd = current->getRoomCol() + visibilityRange;
    while(colEnd > zork->maxRoomsCol - 1){colEnd--;};

    //add rooms to widgets rooms vector
    for (int i=rowStart; i <= rowEnd; i++)
    {
        for(int j = colStart; j <= colEnd; j++)
        {
            rooms[i - (current->getRoomRow() - visibilityRange)][j - (current->getRoomCol() - visibilityRange)] = zork->rooms[i][j];
        }
    }
    this->update();
}

MapWidget::~MapWidget()
{
}

void MapWidget::paintEvent(QPaintEvent *e)
{
    //ignore unused variable
    (void)e;

    QPainter painter( this );
    painter.setRenderHint( QPainter::Antialiasing, true );
    painter.setPen( QPen( Qt::black, 2 ) );

    int squareSize = rect().width() < rect().height() ? rect().width() : rect().height();
    QRect backgroundRect = QRect(0,0,squareSize,squareSize);
    painter.drawImage(backgroundRect, QImage(":/GameView\\pictures\\scroll.png"));
    //number of rooms in width and height, that should be printed by map
    int nrOfRooms = 2 * visibilityRange + 1;

    int rowOffset, colOffset;
    int roomLength = (squareSize - ((squareSize / 9) * 2))/nrOfRooms;
    for (int row = 0; row < nrOfRooms; row++)
    {
        rowOffset = (roomLength * row) + (squareSize / 9);
        for (int col = 0; col < nrOfRooms; col++)
        {
            if (rooms[row][col] != NULL)
            {
                colOffset = roomLength * col + (squareSize / 9);
                QPoint p[4] = {
                    QPoint(0 + colOffset, 0 + rowOffset), //northwest
                    QPoint(roomLength + colOffset, 0 + rowOffset), //northeast
                    QPoint(roomLength + colOffset, roomLength + rowOffset), //southeast
                    QPoint(0 + colOffset, roomLength + rowOffset) //southwest
                };

                //draw items
                if (rooms[row][col]->getNumberofItems() != 0)
                {
                    for( int i = 0; i < rooms[row][col]->getNumberofItems(); i++) //std::vector<Item>::iterator it = rooms[row][col]->itemsInRoom.begin(); it != rooms[row][col]->itemsInRoom.end(); ++it)
                    {
                        Item *it = rooms[row][col]->getItemByIndex(i);
                        int playerPosX = p[0].x() + (roomLength / 2) - (roomLength / 12);
                        int playerPosY = p[0].y() + (roomLength / 2) - (roomLength / 12);

                        //calculate random upper left corner of item in room
                        //ten possible slots in width and height
                        int posX = p[0].x() + it->getXPosition() * (roomLength/10) - (it->getXPosition() / 9 * (roomLength/6));
                        int posY = p[0].y() + it->getYPosition() * (roomLength/10) - (it->getYPosition() / 9 * (roomLength/6));
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
                }

                int doorPos;
                //draw northern wall and door if necessary
                if (rooms[row][col]->hasExit("north"))
                {
                    doorPos = p[0].x() + rooms[row][col]->getDoorPosition("north") * (roomLength / 6);

                    QPoint leftDoor = QPoint(doorPos, 0 + rowOffset);
                    QPoint rightDoor = QPoint(doorPos + (roomLength / 6), 0 + rowOffset);
                    painter.drawLine( p[0], leftDoor );
                    painter.drawLine( rightDoor, p[1] );
                }
                else
                    painter.drawLine( p[0], p[1] );

                //draw southern wall and door if necessary
                if (rooms[row][col]->hasExit("south"))
                {
                    doorPos = p[3].x() + rooms[row][col]->getDoorPosition("south") * (roomLength / 6);
                    QPoint leftDoor = QPoint(doorPos, roomLength + rowOffset);
                    QPoint rightDoor = QPoint(doorPos + (roomLength / 6), roomLength + rowOffset);
                    painter.drawLine( p[3], leftDoor );
                    painter.drawLine( rightDoor, p[2] );
                }
                else
                    painter.drawLine( p[2], p[3] );

                //draw western wall and door if necessary
                if (rooms[row][col]->hasExit("west"))
                {
                    doorPos = p[0].y() + rooms[row][col]->getDoorPosition("west") * (roomLength / 6);
                    QPoint highDoor = QPoint(0 + colOffset, doorPos);
                    QPoint downDoor = QPoint(0 + colOffset, doorPos + (roomLength / 6));
                    painter.drawLine( p[0], highDoor );
                    painter.drawLine( downDoor, p[3] );
                }
                else
                    painter.drawLine( p[0], p[3] );

                //draw eastern wall and door if necessary
                if (rooms[row][col]->hasExit("east"))
                {
                    doorPos = p[1].y() + rooms[row][col]->getDoorPosition("east") * (roomLength / 6);
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

