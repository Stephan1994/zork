#ifndef ROOMPAINTER_H
#define ROOMPAINTER_H

#include <QWidget>
#include "Room.h"

namespace Ui {
class RoomPainter;
}

class RoomPainter : public QWidget
{
    Q_OBJECT

public:
    RoomPainter(QWidget *parent, Room *roomToPaint);
    RoomPainter(QWidget *parent = 0);
    ~RoomPainter();

protected:
    void paintEvent(QPaintEvent *e);
private:
    //Ui::RoomPainter *ui;
    Room *room;
};

#endif // ROOMPAINTER_H
