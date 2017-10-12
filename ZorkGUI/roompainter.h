#ifndef ROOMPAINTER_H
#define ROOMPAINTER_H

#include <QWidget>

namespace Ui {
class RoomPainter;
}

class RoomPainter : public QWidget
{
    Q_OBJECT

public:
    explicit RoomPainter(QWidget *parent = 0);
    ~RoomPainter();

protected:
    void paintEvent(QPaintEvent *e);
private:
    //Ui::RoomPainter *ui;
};

#endif // ROOMPAINTER_H
