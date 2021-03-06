#ifndef MAPWIDGET_H
#define MAPWIDGET_H

#include <QWidget>
#include <QGridLayout>

#include "GameData\ZorkUL.h"

namespace Ui {
class MapWidget;
}

class MapWidget : public QWidget
{
    Q_OBJECT

public:
    explicit MapWidget(ZorkUL *zork, int VisibilityRange = 1, QWidget *parent = 0 );
    ~MapWidget();
    void changeRooms(ZorkUL *zork, int visibilityRange);

protected:
    void paintEvent(QPaintEvent *e);
private:
    QGridLayout *mainGrid;
    vector<vector<Room*>> rooms;
    int visibilityRange;
};

#endif // MAPWIDGET_H
