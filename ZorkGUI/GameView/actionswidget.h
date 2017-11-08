#ifndef ACTIONSWIDGET_H
#define ACTIONSWIDGET_H

#include <QWidget>
#include "GameData/ZorkUL.h"

namespace Ui {
class ActionsWidget;
}

class ActionsWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ActionsWidget(ZorkUL *zork, QWidget *parent = 0);
    ~ActionsWidget();
    void enableTakeItem(bool en, string tooltip);
    void changeActions();

private slots:
    void on_takeItemButton_clicked();

private:
    Ui::ActionsWidget *ui;
    ZorkUL *game;
};

#endif // ACTIONSWIDGET_H
