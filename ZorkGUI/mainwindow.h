#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "ZorkUL.h"

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

private:
    Ui::MainWindow *ui;
    ZorkUL zork;
    void updateOutputLabel(string out);
};

#endif // MAINWINDOW_H
