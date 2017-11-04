#include "itemwidget.h"
#include "ui_itemwidget.h"

#include <QPainter>
#include <QPoint>
#include <QPen>

ItemWidget::ItemWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ItemWidget)
{
    //ui->setupUi(this);
}

void ItemWidget::paintEvent(QPaintEvent *e)
{
    QPainter painter( this );
    painter.setRenderHint( QPainter::Antialiasing, true );
    painter.setPen( QPen( Qt::black, 2 ) );

    //draw main bag
    int squareSize = rect().width() < rect().height() ? rect().width() : rect().height();
    QRect backgroundRect = QRect(0,0,squareSize,squareSize);
    painter.drawImage(backgroundRect, QImage("GameView\\pictures\\money-bag-changed.png"));

    int startX = squareSize / 5 + squareSize / 5 / 6;
    int startY = squareSize / 5 * 2 + squareSize / 7;

    int itemSquareSize = squareSize / 7;
    int rectX = startX;
    int rectY = startY;
    for (int i = 0; i < 6; i++)
    {
        painter.drawRect(rectX, rectY, itemSquareSize, itemSquareSize);

        rectX += itemSquareSize + itemSquareSize / 2;
        if (i == 2)
        {
            rectY += itemSquareSize + itemSquareSize / 2;
            rectX = startX;
        }
    }

}

ItemWidget::~ItemWidget()
{
    delete ui;
}
