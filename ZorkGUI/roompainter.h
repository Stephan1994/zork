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
    RoomPainter(Room *roomToPaint, double zoom, QWidget *parent = 0);
    RoomPainter(QWidget *parent = 0);
    ~RoomPainter();

protected:
    void paintEvent(QPaintEvent *e);
private:
    //Ui::RoomPainter *ui;
    Room *room;
    double scale;
};

#endif // ROOMPAINTER_H
