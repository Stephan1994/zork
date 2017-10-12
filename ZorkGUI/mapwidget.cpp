#include "mapwidget.h"
#include "ui_mapwidget.h"
#include <QGridLayout>

MapWidget::MapWidget(QWidget *parent) :
    QWidget(parent)
{
    //ui->setupUi(this);
    mainGrid = new QGridLayout;


}

MapWidget::paintEvent(QPaintEvent *e)
{

}
MapWidget::~MapWidget()
{
    //delete ui;
}
