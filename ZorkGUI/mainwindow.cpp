#include "mainwindow.h"
#include "Command.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //connect(temp, SIGNAL(outputChanged(QString)), ui->outputLabel, SLOT(setText(QString)));
    //ui->outputLabel->setText(QString::fromStdString(temp.guiOutput));
    zork.play();
    updateOutputLabel(zork.guiOutput);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_teleportButton_clicked()
{
    Command* command = new Command("teleport", "rand");
    zork.teleport(*command);
    updateOutputLabel(zork.guiOutput);
    delete command;
}

void MainWindow::updateOutputLabel(string out)
{
    ui->outputLabel->setText(QString::fromStdString(out));
}

void MainWindow::on_northButton_clicked()
{
    Command* command = new Command("go", "north");
    zork.goRoom(*command);
    if (zork.guiOutput.compare("underdefined input\n") != 0)
        updateOutputLabel(zork.guiOutput);
    delete command;
}

void MainWindow::on_eastButton_clicked()
{
    Command* command = new Command("go", "east");
    zork.goRoom(*command);
    if (zork.guiOutput.compare("underdefined input\n") != 0)
        updateOutputLabel(zork.guiOutput);
    delete command;
}

void MainWindow::on_southButton_clicked()
{
    Command* command = new Command("go", "south");
    zork.goRoom(*command);
    if (zork.guiOutput.compare("underdefined input\n") != 0)
        updateOutputLabel(zork.guiOutput);
    delete command;
}

void MainWindow::on_westButton_clicked()
{
    Command* command = new Command("go", "west");
    zork.goRoom(*command);
    if (zork.guiOutput.compare("underdefined input\n") != 0)
        updateOutputLabel(zork.guiOutput);
    delete command;
}
