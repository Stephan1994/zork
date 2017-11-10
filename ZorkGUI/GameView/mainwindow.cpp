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

    //start game
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
    delete actions;
    delete items;
    delete map;
    delete zork;
}

void MainWindow::resizeEvent(QResizeEvent *event)
{
    (void)event;
    if(this)
    {
        updateOutputLabel(zork->guiOutput);
    }
}

void MainWindow::updateOutputLabel(string out)
{
    ui->storyText->setText(QString::fromStdString(out));
    QImage roomPic;
    if (zork->currentRoom->enemyAvailable())
    {
        roomPic = QImage(QString::fromStdString(zork->currentRoom->getEnemy()->getPicture()));
    }
    else if (zork->currentRoom->getNumberofItems() > 0)
    {
        roomPic = QImage(QString::fromStdString(zork->currentRoom->getItemByIndex(0)->getPicturePath()));
    }
    else
    {
        roomPic = QImage(QString::fromStdString(":/GameView\\pictures\\room.jpg"));
    }

    ui->storyPic->setPixmap(QPixmap::fromImage(roomPic).scaled(ui->storyPic->width(), ui->storyPic->height(), Qt::KeepAspectRatio));
}

void MainWindow::roomChanged()
{
    if (zork->guiOutput.compare("underdefined input\n") != 0)
        updateOutputLabel(zork->guiOutput);
    map->changeRooms(zork, 1);
    actions->changeActions();

    //set movement buttons enabled or disabled
    if (zork->currentRoom->enemyAvailable())
    {
        ui->northButton->setEnabled(false);
        ui->northButton->setToolTip(QString::fromStdString("You can't move while attacked."));
        ui->southButton->setEnabled(false);
        ui->southButton->setToolTip(QString::fromStdString("You can't move while attacked."));
        ui->westButton->setEnabled(false);
        ui->westButton->setToolTip(QString::fromStdString("You can't move while attacked."));
        ui->eastButton->setEnabled(false);
        ui->eastButton->setToolTip(QString::fromStdString("You can't move while attacked."));
        ui->teleportButton->setEnabled(false);
        ui->teleportButton->setToolTip(QString::fromStdString("You can't move while attacked."));
    }
    else
    {
        //north
        if (zork->currentRoom->exits.find("north")!= zork->currentRoom->exits.end())
        {
            ui->northButton->setEnabled(true);
            ui->northButton->setToolTip(QString::fromStdString("You will go to the next room in this direction."));
        }
        else
        {
            ui->northButton->setEnabled(false);
            ui->northButton->setToolTip(QString::fromStdString("There is no door in this direction."));
        }

        //south
        if (zork->currentRoom->exits.find("south")!= zork->currentRoom->exits.end())
        {
            ui->southButton->setEnabled(true);
            ui->southButton->setToolTip(QString::fromStdString("You will go to the next room in this direction."));
        }
        else
        {
            ui->southButton->setEnabled(false);
            ui->southButton->setToolTip(QString::fromStdString("There is no door in this direction."));
        }

        //west
        if (zork->currentRoom->exits.find("west")!= zork->currentRoom->exits.end())
        {
            ui->westButton->setEnabled(true);
            ui->westButton->setToolTip(QString::fromStdString("You will go to the next room in this direction."));
        }
        else
        {
            ui->westButton->setEnabled(false);
            ui->westButton->setToolTip(QString::fromStdString("There is no door in this direction."));
        }

        //east
        if (zork->currentRoom->exits.find("east")!= zork->currentRoom->exits.end())
        {
            ui->eastButton->setEnabled(true);
            ui->eastButton->setToolTip(QString::fromStdString("You will go to the next room in this direction."));
        }
        else
        {
            ui->eastButton->setEnabled(false);
            ui->eastButton->setToolTip(QString::fromStdString("There is no door in this direction."));
        }

        //teleport
        if (zork->currentRoom->getNumberofItems() != 0 && zork->currentRoom->getItemByIndex(0)->getName() == "Teleporter")
        {
            ui->teleportButton->setEnabled(true);
            ui->teleportButton->setToolTip(QString::fromStdString("Teleport to a random room."));
        }
        else
        {
            ui->teleportButton->setEnabled(false);
            ui->teleportButton->setToolTip(QString::fromStdString("You can only teleport with a teleporter. Go find a room with a teleporter in it!"));
        }
    }
}

void MainWindow::playerChanged()
{
    if (zork->player->numberOfCarriedItems() == 6)
        actions->enableTakeItem(false, "You cannot carry more than six items.\nYou can throw items away by rightclicking on them.");
    else
        actions->enableTakeItem(true, "Pick up item.");
}

void MainWindow::on_teleportButton_clicked()
{
    Command command = Command("teleport", "rand");
    zork->teleport(command);
    roomChanged();
}

void MainWindow::on_northButton_clicked()
{
    Command command = Command("go", "north");
    zork->goRoom(command);
    roomChanged();
}

void MainWindow::on_eastButton_clicked()
{
    Command command = Command("go", "east");
    zork->goRoom(command);
    roomChanged();
}

void MainWindow::on_southButton_clicked()
{
    Command command = Command("go", "south");
    zork->goRoom(command);
    roomChanged();
}

void MainWindow::on_westButton_clicked()
{
    Command command = Command("go", "west");
    zork->goRoom(command);
    roomChanged();
}

void MainWindow::takeItemButton_clicked()
{
    roomChanged();
    playerChanged();
    items->update();
}
