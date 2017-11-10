#include "actionswidget.h"
#include "ui_actionswidget.h"
#include "mainwindow.h"
#include <QMessageBox>

ActionsWidget::ActionsWidget(ZorkUL *zork, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ActionsWidget)
{
    //setup ui form
    ui->setupUi(this);
    //give ids to standard radiobuttons
    ui->buttonGroup->setId(ui->radioButton, 0);
    ui->buttonGroup->setId(ui->radioButton_2, 1);

    game = zork;

    //init timer for enemies
    answerTimer = new QTimer();
    answerTimer->setInterval(1000);
    connect(answerTimer, SIGNAL(timeout()), this, SLOT(timeout()));

    //start by creating first actionsview for the current room
    changeActions();
}

ActionsWidget::~ActionsWidget()
{
    delete ui;
    delete answerTimer;
    for(std::map<QRadioButton*, Item*>::iterator itr = radioButtons.begin(); itr != radioButtons.end(); itr++)
    {
        delete itr->first;
    }
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
        if (ui->enemyHealth->maximum() > 100)
            ui->enemyHealth->setMaximum(game->currentRoom->enemies.front().health);
        ui->enemyHealth->setValue(game->currentRoom->enemies.front().health);

        //set Answers
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

//enables/disables the takeItemButton and sets tooltip
void ActionsWidget::enableTakeItem(bool en, string tooltip)
{
    ui->takeItemButton->setEnabled(en);
    ui->takeItemButton->setToolTip(QString::fromStdString(tooltip));
}

//slot for ItemButton
void ActionsWidget::on_takeItemButton_clicked()
{
    //take first item in room (only one item possible at the moment)
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

//attackButton slot
void ActionsWidget::on_attackButton_clicked()
{
    map<QRadioButton*, Item*>::iterator item = radioButtons.find((QRadioButton*)ui->buttonGroup->checkedButton());
    //check if chosen anser needs an item
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
                string directions[4] = {"north", "south", "west", "east"};
                for (int i = 0; i < 4; i++)
                {
                    if (game->currentRoom->exits.find(directions[i]) != game->currentRoom->exits.end())
                    {
                        Command command = Command("go", directions[i]);
                        game->goRoom(command);
                        break;
                    }
                }

                static_cast<MainWindow*>(this->parent()->parent())->roomChanged();
                return;
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
