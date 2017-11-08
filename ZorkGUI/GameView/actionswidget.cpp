#include "actionswidget.h"
#include "ui_actionswidget.h"
#include "mainwindow.h"

ActionsWidget::ActionsWidget(ZorkUL *zork, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ActionsWidget)
{
    ui->setupUi(this);

    game = zork;
    changeActions();
}

void ActionsWidget::changeActions()
{
    //show or hide itembutton
    if (game->currentRoom->itemsInRoom.empty())
        ui->takeItemButton->hide();
    else
        ui->takeItemButton->show();

    //enable or disable itemButton if already 6 items are carried
    if (game->player->carriedItems.size() != 6)
        enableTakeItem(true, "Add item to Inventory.");
    else
        enableTakeItem(false, "You cannot carry more than six items.\nYou can throw items away by rightclicking on them.");

    //no enemy in room -> hide attackGroup
    if (game->currentRoom->enemies.empty())
    {
        //hide fight groupbox
        ui->fightGroup->hide();
    }
    else
    {
        //show fight groupbox
        ui->fightGroup->show();

        //set health
        ui->enemyName->setText(QString::fromStdString(game->currentRoom->enemies.front().getDescription()));
        ui->enemyHealth->setMaximum(game->currentRoom->enemies.front().health);
        ui->enemyHealth->setValue(game->currentRoom->enemies.front().health);

        //set Answers
        if(!game->player->carriedItems.empty())
        {
            for (int i=0; i < game->player->carriedItems.size(); i++)
            {
                if (game->player->carriedItems[i].isUsable)
                {
                    float effectiveness = (game->player->carriedItems[i].getShortDescription() == game->currentRoom->enemies.front().getWeakness()) ? 3 : 1;
                    effectiveness = (game->player->carriedItems[i].getShortDescription() == game->currentRoom->enemies.front().getImmunity()) ? 0.1 : 1;
                    QString actionText = QString(QString::fromStdString("Use your " + game->player->carriedItems[i].getShortDescription() + "(Dmg:" + to_string(game->player->carriedItems[i].getDamage() * effectiveness) + ")"));
                    ui->attacksGroup->layout()->addWidget(new QRadioButton(actionText));
                }
            }
        }

        //setTime

    }
}

void ActionsWidget::enableTakeItem(bool en, string tooltip)
{
    ui->takeItemButton->setEnabled(en);
    ui->takeItemButton->setToolTip(QString::fromStdString(tooltip));
}
ActionsWidget::~ActionsWidget()
{
    delete ui;
}

void ActionsWidget::on_takeItemButton_clicked()
{
    vector<Item>::iterator itInRoom = game->currentRoom->itemsInRoom.begin();
    if (itInRoom->questItem)
    {
        game->player->addQuestItem(*itInRoom);
        game->currentRoom->itemsInRoom.erase(itInRoom);
    }
    else if (game->player->carriedItems.size() <= 6)
    {
        game->player->addItem(*itInRoom);
        game->currentRoom->itemsInRoom.erase(itInRoom);
    }
    static_cast<MainWindow*>(this->parent()->parent())->takeItemButton_clicked();
}
