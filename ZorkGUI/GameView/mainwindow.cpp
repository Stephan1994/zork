#include "mainwindow.h"
#include "GameData\Command.h"
#include "ui_mainwindow.h"
#include <QImage>
#include <QPixmap>
#include <QString>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //connect(temp, SIGNAL(outputChanged(QString)), ui->outputLabel, SLOT(setText(QString)));
    //ui->outputLabel->setText(QString::fromStdString(temp.guiOutput));
    zork = new ZorkUL(50,50);
    zork->play();
    updateOutputLabel(zork->guiOutput);
    //add Map
    map = new MapWidget(zork, 1);
    map->setMinimumSize(250,250);
    ui->gridLayout->addWidget(map, 1, 2, 2, 2);

    //add ItemWidget
    items = new ItemWidget(zork->player, this);
    items->setMinimumSize(150,150);
    ui->gridLayout->addWidget(items,0,3);

    //add ActionWidget
    actions = new ActionsWidget(zork);
    ui->gridLayout->addWidget(actions, 1, 0, 1, 2);
    roomChanged();

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::resizeEvent(QResizeEvent *event)
{
    if(this)
    {
        updateOutputLabel(zork->guiOutput);
    }
}

void MainWindow::updateOutputLabel(string out)
{
    ui->storyText->setText(QString::fromStdString(out));
    QImage *roomPic;
    if (!zork->currentRoom->enemies.empty())
    {
        roomPic = new QImage(QString::fromStdString(zork->currentRoom->enemies.front().getPicture()));
    }
    else if (!zork->currentRoom->itemsInRoom.empty())
    {
        roomPic = new QImage(QString::fromStdString(zork->currentRoom->itemsInRoom.front().getPicturePath()));
    }
    else
    {
        roomPic = new QImage(QString::fromStdString("GameView\\pictures\\room.jpg"));
    }

    ui->storyPic->setPixmap(QPixmap::fromImage(*roomPic).scaled(ui->storyPic->width(), ui->storyPic->height(), Qt::KeepAspectRatio));
    //ui->storyPic->setMaximumSize(250,250);
}

void MainWindow::roomChanged()
{
    if (zork->guiOutput.compare("underdefined input\n") != 0)
        updateOutputLabel(zork->guiOutput);
    map->changeRooms(zork, 1);
    actions->changeActions();
    /*if(!zork->currentRoom->itemsInRoom.empty())
    {
        ui->takeItemButton->show();
    }
    else
    {
        ui->takeItemButton->hide();
    }*/
}

void MainWindow::playerChanged()
{
    if (zork->player->carriedItems.size() == 6)
    {
        actions->enableTakeItem(false, "You cannot carry more than six items.\nYou can throw items away by rightclicking on them.");
        //ui->takeItemButton->setEnabled(false);
        //ui->takeItemButton->setToolTip(QString("You cannot carry more than six items.\nYou can throw items away by rightclicking on them."));
    }
    else
    {
        actions->enableTakeItem(true, "Pick up item.");
        //ui->takeItemButton->setEnabled(true);
        //ui->takeItemButton->setToolTip(QString(""));
    }
}

void MainWindow::on_teleportButton_clicked()
{
    Command* command = new Command("teleport", "rand");
    zork->teleport(*command);
    roomChanged();
    delete command;
}

void MainWindow::on_northButton_clicked()
{
    Command* command = new Command("go", "north");
    zork->goRoom(*command);
    roomChanged();
    delete command;
}

void MainWindow::on_eastButton_clicked()
{
    Command* command = new Command("go", "east");
    zork->goRoom(*command);
    roomChanged();
    delete command;
}

void MainWindow::on_southButton_clicked()
{
    Command* command = new Command("go", "south");
    zork->goRoom(*command);
    roomChanged();
    delete command;
}

void MainWindow::on_westButton_clicked()
{
    Command* command = new Command("go", "west");
    zork->goRoom(*command);
    roomChanged();
    delete command;
}

void MainWindow::takeItemButton_clicked()
{
    roomChanged();
    playerChanged();
    items->update();
}
