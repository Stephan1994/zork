#ifndef ITEMWIDGET_H
#define ITEMWIDGET_H

#include <QWidget>
#include "GameData/player.h"

namespace Ui {
class ItemWidget;
}

class ItemWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ItemWidget(Player *character, QWidget *parent = 0);
    ~ItemWidget();

protected:
    void paintEvent(QPaintEvent *e);
    bool event( QEvent* event);
private:
    Player *player;
    int squareSize;
    int startX;
    int startY;
};

#endif // ITEMWIDGET_H
