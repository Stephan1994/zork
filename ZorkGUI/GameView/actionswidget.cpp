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
    if (game->getCurrentRoom()->getNumberofItems() == 0)
        ui->takeItemButton->hide();
    else
        ui->takeItemButton->show();

    //enable or disable itemButton if already 6 items are carried
    if (game->getPlayer()->numberOfCarriedItems() != 6)
        enableTakeItem(true, "Add item to Inventory.");
    else
        enableTakeItem(false, "You cannot carry more than six items.\nYou can throw items away by rightclicking on them.");

    //no enemy in room -> hide attackGroup
    if (!game->getCurrentRoom()->enemyAvailable())
    {
        //hide fight groupbox
        ui->fightGroup->hide();
    }
    else
    {
        //show fight groupbox
        ui->fightGroup->show();

        //set health
        ui->enemyName->setText(QString::fromStdString(game->getCurrentRoom()->getEnemy()->getDescription()));
        if (ui->enemyHealth->maximum() > 100)
            ui->enemyHealth->setMaximum(game->getCurrentRoom()->getEnemy()->getHealth());
        ui->enemyHealth->setValue(game->getCurrentRoom()->getEnemy()->getHealth());

        //set Answers
        if(game->getPlayer()->numberOfCarriedItems() != 0 && (int)radioButtons.size() < game->getPlayer()->numberOfCarriedItems())
        {
            int buttonID = 2;
            for (int i=0; i < game->getPlayer()->numberOfCarriedItems(); i++)
            {
                if (game->getPlayer()->getItemByIndex(i)->isUsable())
                {
                    float effectiveness = (game->getPlayer()->getItemByIndex(i)->getName() == game->getCurrentRoom()->getEnemy()->getWeakness()) ? 3 : 1;
                    effectiveness = (game->getPlayer()->getItemByIndex(i)->getName() == game->getCurrentRoom()->getEnemy()->getImmunity()) ? 0.1 : 1;
                    QString actionText = QString(QString::fromStdString("Use your " + game->getPlayer()->getItemByIndex(i)->getName() + " (Dmg: " + to_string((int)(game->getPlayer()->getItemByIndex(i)->getDamage() * effectiveness)) + ")"));
                    QRadioButton *addedAction = new QRadioButton(actionText);
                    ui->attacksGroup->layout()->addWidget(addedAction);
                    ui->buttonGroup->addButton(addedAction, buttonID);
                    radioButtons[addedAction] = game->getPlayer()->getItemByIndex(i);
                    buttonID++;
                }
            }
        }

        //set time
        if (game->getCurrentRoom()->getEnemy()->hasTimeLimit())
        {
            if (!answerTimer->isActive())
            {
                ui->timeBar->show();
                ui->timeLabel->show();
                secondCounter = game->getCurrentRoom()->getEnemy()->getTimeLimit();
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
    Item* itInRoom = game->getCurrentRoom()->getItemByIndex(0);
    if (itInRoom->isQuestItem())
        game->getPlayer()->addItem(itInRoom);
    else if (game->getPlayer()->numberOfCarriedItems() <= 6)
        game->getPlayer()->addItem(itInRoom);

    //remove item from room
    game->getCurrentRoom()->removeItem(itInRoom->getName());

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
        game->getCurrentRoom()->getEnemy()->setHealth(game->getCurrentRoom()->getEnemy()->getHealth() - item->second->getDamage());
    }
    else
    {
        if (ui->buttonGroup->checkedButton()->text() == "Use your fists (Dmg: 5)")
            game->getCurrentRoom()->getEnemy()->setHealth(game->getCurrentRoom()->getEnemy()->getHealth() - 5);
        else
        {//run away
            if (rand() % 20 ==0)
            {
                string directions[4] = {"north", "south", "west", "east"};
                for (int i = 0; i < 4; i++)
                {
                    if (game->getCurrentRoom()->hasExit(directions[i]))
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

    if(game->getCurrentRoom()->getEnemy()->getHealth() <= 0)
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
        QMessageBox::warning(this, QString::fromStdString("Defeted"), QString::fromStdString("You have been defeated by the " + game->getCurrentRoom()->getEnemy()->getName() + "!\nThe " + game->getCurrentRoom()->getEnemy()->getName() + " disappeared after this epic win and you will lose some health. Watch out the next time."),
                                        QMessageBox::Ok);
        cleanUp();
    }
}

void ActionsWidget::cleanUp()
{
    ui->enemyHealth->setMaximum(105);
    game->getCurrentRoom()->enemyDefeated();
    for(std::map<QRadioButton*, Item*>::iterator itr = radioButtons.begin(); itr != radioButtons.end(); itr++)
    {
        ui->attacksGroup->layout()->removeWidget(itr->first);
        ui->buttonGroup->removeButton(itr->first);
        delete itr->first;
        radioButtons.erase(itr);
    }
    static_cast<MainWindow*>(this->parent()->parent())->roomChanged();
}
