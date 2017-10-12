#ifndef MAPWIDGET_H
#define MAPWIDGET_H

#include <QWidget>

namespace Ui {
class MapWidget;
}

class MapWidget : public QWidget
{
    Q_OBJECT

public:
    explicit MapWidget(QWidget *parent = 0);
    ~MapWidget();

protected:
    void paintEvent(QPaintEvent *e);

private:
    //Ui::MapWidget *ui;
    QGridLayout *mainGrid;


};

#endif // MAPWIDGET_H
