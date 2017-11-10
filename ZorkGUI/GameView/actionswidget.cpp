#include "actionswidget.h"
#include "ui_actionswidget.h"
#include "mainwindow.h"
#include <QMessageBox>

ActionsWidget::ActionsWidget(ZorkUL *zork, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ActionsWidget)
{
    ui->setupUi(this);
    ui->buttonGroup->setId(ui->radioButton, 0);
    ui->buttonGroup->setId(ui->radioButton_2, 1);
    game = zork;
    answerTimer = new QTimer();
    answerTimer->setInterval(1000);
    connect(answerTimer, SIGNAL(timeout()), this, SLOT(timeout()));
    changeActions();
}

ActionsWidget::~ActionsWidget()
{
    delete ui;
    delete answerTimer;
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
        if (ui->enemyHealth->maximum() == 105)
            ui->enemyHealth->setMaximum(game->currentRoom->enemies.front().health);
        ui->enemyHealth->setValue(game->currentRoom->enemies.front().health);

        //set Answers
        int radioSize = radioButtons.size();
        int itemSize = game->player->carriedItems.size();
        if(!game->player->carriedItems.empty() && radioButtons.size() < game->player->carriedItems.size())
        {
            int buttonID = 2;
            for (int i=0; i < game->player->carriedItems.size(); i++)
            {
                if (game->player->carriedItems[i].isUsable)
                {
                    float effectiveness = (game->player->carriedItems[i].getShortDescription() == game->currentRoom->enemies.front().getWeakness()) ? 3 : 1;
                    effectiveness = (game->player->carriedItems[i].getShortDescription() == game->currentRoom->enemies.front().getImmunity()) ? 0.1 : 1;
                    QString actionText = QString(QString::fromStdString("Use your " + game->player->carriedItems[i].getShortDescription() + " (Dmg:" + to_string((int)(game->player->carriedItems[i].getDamage() * effectiveness)) + ")"));
                    QRadioButton *addedAction = new QRadioButton(actionText);
                    ui->attacksGroup->layout()->addWidget(addedAction);
                    ui->buttonGroup->addButton(addedAction, buttonID);
                    radioButtons[addedAction] = &(game->player->carriedItems[i]);
                    buttonID++;
                }
            }
        }

        //set time
        if (game->currentRoom->enemies.front().time)
        {
            if (!answerTimer->isActive())
            {
                ui->timeBar->show();
                ui->timeLabel->show();
                secondCounter = game->currentRoom->enemies.front().getTimeLimit();
                ui->timeBar->setMaximum(secondCounter);
                ui->timeBar->setValue(secondCounter);
                answerTimer->start();
            }
        }
        else
        {
            ui->timeBar->hide();
            ui->timeLabel->hide();
        }
    }
}

void ActionsWidget::enableTakeItem(bool en, string tooltip)
{
    ui->takeItemButton->setEnabled(en);
    ui->takeItemButton->setToolTip(QString::fromStdString(tooltip));
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

void ActionsWidget::on_attackButton_clicked()
{
    map<QRadioButton*, Item*>::iterator item = radioButtons.find((QRadioButton*)ui->buttonGroup->checkedButton());
    if( item != radioButtons.end())
    {
        game->currentRoom->enemies.front().health -= item->second->getDamage();
    }
    else
    {
        if (ui->buttonGroup->checkedButton()->text() == "Use your fists (Dmg: 5)")
            game->currentRoom->enemies.front().health -= 5;
        else
        {//run away
            if (rand() % 20 ==0)
            {
                if (game->currentRoom->exits.find("north") != game->currentRoom->exits.end())
                    game->go("north");
                else if (game->currentRoom->exits.find("south") != game->currentRoom->exits.end())
                    game->go("south");
                else if (game->currentRoom->exits.find("west") != game->currentRoom->exits.end())
                    game->go("west");
                else if (game->currentRoom->exits.find("east") != game->currentRoom->exits.end())
                    game->go("east");

                static_cast<MainWindow*>(this->parent()->parent())->roomChanged();
            }
        }

    }

    if(game->currentRoom->enemies.front().health <= 0)
    {
        answerTimer->stop();
        cleanUp();
    }
    else
        changeActions();
}

void ActionsWidget::timeout()
{
    if (secondCounter > 1)
    {
        secondCounter--;
        ui->timeBar->setValue(secondCounter);
        //answerTimer->start(1000);
    }
    else
    {
        ui->timeBar->setValue(0);
        answerTimer->stop();
        QMessageBox::warning(this, QString::fromStdString("Defeted"), QString::fromStdString("You have been defeated by the " + game->currentRoom->enemies.front().getName() + "!\nThe " + game->currentRoom->enemies.front().getName() + "disappeared after this epic win and you will lose some health. Watch out the next time."),
                                        QMessageBox::Ok);
        cleanUp();
    }
}

void ActionsWidget::cleanUp()
{
    ui->enemyHealth->setMaximum(105);
    game->currentRoom->enemies.erase(game->currentRoom->enemies.begin());
    for(std::map<QRadioButton*, Item*>::iterator itr = radioButtons.begin(); itr != radioButtons.end(); itr++)
    {
        ui->attacksGroup->layout()->removeWidget(itr->first);
        ui->buttonGroup->removeButton(itr->first);
        delete itr->first;
        radioButtons.erase(itr);
    }
    static_cast<MainWindow*>(this->parent()->parent())->roomChanged();
}
