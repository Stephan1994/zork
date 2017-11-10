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
    if (game->currentRoom->getNumberofItems() == 0)
        ui->takeItemButton->hide();
    else
        ui->takeItemButton->show();

    //enable or disable itemButton if already 6 items are carried
    if (game->player->numberOfCarriedItems() != 6)
        enableTakeItem(true, "Add item to Inventory.");
    else
        enableTakeItem(false, "You cannot carry more than six items.\nYou can throw items away by rightclicking on them.");

    //no enemy in room -> hide attackGroup
    if (!game->currentRoom->enemyAvailable())
    {
        //hide fight groupbox
        ui->fightGroup->hide();
    }
    else
    {
        //show fight groupbox
        ui->fightGroup->show();

        //set health
        ui->enemyName->setText(QString::fromStdString(game->currentRoom->getEnemy()->getDescription()));
        if (ui->enemyHealth->maximum() > 100)
            ui->enemyHealth->setMaximum(game->currentRoom->getEnemy()->getHealth());
        ui->enemyHealth->setValue(game->currentRoom->getEnemy()->getHealth());

        //set Answers
        if(game->player->numberOfCarriedItems() != 0 && (int)radioButtons.size() < game->player->numberOfCarriedItems())
        {
            int buttonID = 2;
            for (int i=0; i < game->player->numberOfCarriedItems(); i++)
            {
                if (game->player->getItemByIndex(i)->isUsable())
                {
                    float effectiveness = (game->player->getItemByIndex(i)->getName() == game->currentRoom->getEnemy()->getWeakness()) ? 3 : 1;
                    effectiveness = (game->player->getItemByIndex(i)->getName() == game->currentRoom->getEnemy()->getImmunity()) ? 0.1 : 1;
                    QString actionText = QString(QString::fromStdString("Use your " + game->player->getItemByIndex(i)->getName() + " (Dmg: " + to_string((int)(game->player->getItemByIndex(i)->getDamage() * effectiveness)) + ")"));
                    QRadioButton *addedAction = new QRadioButton(actionText);
                    ui->attacksGroup->layout()->addWidget(addedAction);
                    ui->buttonGroup->addButton(addedAction, buttonID);
                    radioButtons[addedAction] = game->player->getItemByIndex(i);
                    buttonID++;
                }
            }
        }

        //set time
        if (game->currentRoom->getEnemy()->hasTimeLimit())
        {
            if (!answerTimer->isActive())
            {
                ui->timeBar->show();
                ui->timeLabel->show();
                secondCounter = game->currentRoom->getEnemy()->getTimeLimit();
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
    //add first item in room to player inventory (only one item possible at the moment)
    Item* itInRoom = game->currentRoom->getItemByIndex(0);
    if (itInRoom->isQuestItem())
        game->player->addItem(itInRoom);
    else if (game->player->numberOfCarriedItems() <= 6)
        game->player->addItem(itInRoom);

    //remove item from room
    game->currentRoom->removeItem(itInRoom->getName());

    //update views
    static_cast<MainWindow*>(this->parent()->parent())->takeItemButton_clicked();
}

//attackButton slot
void ActionsWidget::on_attackButton_clicked()
{
    map<QRadioButton*, Item*>::iterator item = radioButtons.find((QRadioButton*)ui->buttonGroup->checkedButton());
    //check if chosen anser needs an item
    if( item != radioButtons.end())
    {
        game->currentRoom->getEnemy()->setHealth(game->currentRoom->getEnemy()->getHealth() - item->second->getDamage());
    }
    else
    {
        if (ui->buttonGroup->checkedButton()->text() == "Use your fists (Dmg: 5)")
            game->currentRoom->getEnemy()->setHealth(game->currentRoom->getEnemy()->getHealth() - 5);
        else
        {//run away
            if (rand() % 20 ==0)
            {
                string directions[4] = {"north", "south", "west", "east"};
                for (int i = 0; i < 4; i++)
                {
                    if (game->currentRoom->hasExit(directions[i]))
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

    if(game->currentRoom->getEnemy()->getHealth() <= 0)
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
        QMessageBox::warning(this, QString::fromStdString("Defeted"), QString::fromStdString("You have been defeated by the " + game->currentRoom->getEnemy()->getName() + "!\nThe " + game->currentRoom->getEnemy()->getName() + " disappeared after this epic win and you will lose some health. Watch out the next time."),
                                        QMessageBox::Ok);
        cleanUp();
    }
}

void ActionsWidget::cleanUp()
{
    ui->enemyHealth->setMaximum(105);
    game->currentRoom->enemyDefeated();
    for(std::map<QRadioButton*, Item*>::iterator itr = radioButtons.begin(); itr != radioButtons.end(); itr++)
    {
        ui->attacksGroup->layout()->removeWidget(itr->first);
        ui->buttonGroup->removeButton(itr->first);
        delete itr->first;
        radioButtons.erase(itr);
    }
    static_cast<MainWindow*>(this->parent()->parent())->roomChanged();
}
