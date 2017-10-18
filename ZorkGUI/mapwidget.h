#ifndef MAPWIDGET_H
#define MAPWIDGET_H

#include <QWidget>
#include <QGridLayout>

#include "ZorkUL.h"
#include "roompainter.h"

namespace Ui {
class MapWidget;
}

class MapWidget : public QWidget
{
    Q_OBJECT

public:
    explicit MapWidget(ZorkUL *zork, QWidget *parent = 0 );
    ~MapWidget();

private:
    //Ui::MapWidget *ui;
    QGridLayout *mainGrid;
    //RoomPainter paintedRooms[9];
    RoomPainter* createRooms(Room rooms[9]);


};

#endif // MAPWIDGET_H
