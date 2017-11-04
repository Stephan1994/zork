#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "GameData\ZorkUL.h"
#include "MapWidget.h"
#include "itemwidget.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_teleportButton_clicked();

    void on_northButton_clicked();

    void on_eastButton_clicked();

    void on_southButton_clicked();

    void on_westButton_clicked();

    void on_takeItemButton_clicked();

private:
    Ui::MainWindow *ui;
    ZorkUL *zork;
    MapWidget *map;
    ItemWidget *items;
    void updateOutputLabel(string out);
    void roomChanged();
};

#endif // MAINWINDOW_H
