#include "itemwidget.h"

#include <QPainter>
#include <QPoint>
#include <QPen>

#include <QEvent>
#include <QHelpEvent>
#include <QMessageBox>
#include "mainwindow.h"

ItemWidget::ItemWidget(Player *character, QWidget *parent) :
    QWidget(parent)
{
    player = character;
}

void ItemWidget::paintEvent(QPaintEvent *e)
{
    QPainter painter( this );
    painter.setRenderHint( QPainter::Antialiasing, true );
    painter.setPen( QPen( Qt::black, 2 ) );

    //draw main bag
    squareSize = rect().width() < rect().height() ? rect().width() : rect().height();
    QRect backgroundRect = QRect(0,0,squareSize,squareSize);
    painter.drawImage(backgroundRect, QImage("GameView\\pictures\\money-bag-changed.png"));

    startX = squareSize / 5 + squareSize / 5 / 6;
    startY = squareSize / 5 * 2 + squareSize / 6;

    int itemSquareSize = squareSize / 7;

    //draw coin for coin counter
    QRect coinRect = QRect(startX + itemSquareSize, startY - (itemSquareSize + itemSquareSize / 3), itemSquareSize, itemSquareSize);
    painter.drawImage(coinRect, QImage("GameView\\pictures\\coin.png"));

    //draw counter text

    QString counterText = QString::fromStdString("x" + to_string(player->carriedQuestItems.size()));
    float factor = itemSquareSize / painter.fontMetrics().height();
    if ((factor < 1) || (factor > 1.25))
    {
      QFont f = painter.font();
      f.setPointSizeF(f.pointSizeF()*factor);
      painter.setFont(f);
    }
    QRect coinCounterRect = QRect(coinRect.topLeft().x() + itemSquareSize + itemSquareSize / 5, coinRect.topLeft().y() + (itemSquareSize - painter.fontMetrics().height()) / 2, itemSquareSize, itemSquareSize);
    painter.drawText(coinCounterRect, counterText);

    int rectX = startX;
    int rectY = startY;
    for (unsigned int i = 0; i < 6; i++)
    {
        //draw background
        QRect iconBackgroundRect = QRect(rectX, rectY, itemSquareSize, itemSquareSize);
        painter.drawImage(iconBackgroundRect, QImage("GameView\\pictures\\item-embedded.png"));

        //draw items
        if (player->carriedItems.size() > i)
        {
            QRect itemRect = QRect(rectX + itemSquareSize / 7, rectY + itemSquareSize / 7, itemSquareSize - itemSquareSize / 3.5, itemSquareSize - itemSquareSize / 3.5);
            painter.drawImage(itemRect, QImage(QString::fromStdString(player->carriedItems[i].getPicturePath())));
        }
        rectX += itemSquareSize + itemSquareSize / 2;
        if (i == 2)
        {
            rectY += itemSquareSize + itemSquareSize / 5;
            rectX = startX;
        }
    }
}

bool ItemWidget::event( QEvent *event )
{
  if( event->type() == QEvent::ToolTip )
  {
    QHelpEvent *helpEvent = static_cast<QHelpEvent*>( event );

    int itemSquareSize = squareSize / 7;
    int rectX = startX;
    int rectY = startY;
    string tooltip = "";
    for (unsigned int i = 0; i < player->carriedItems.size(); i++)
    {
        QRect iconBackgroundRect = QRect(rectX, rectY, itemSquareSize, itemSquareSize);
        if(iconBackgroundRect.contains(helpEvent->pos()))
        {
            tooltip = player->carriedItems[i].getLongDescription();
            break;
        }

        rectX += itemSquareSize + itemSquareSize / 2;
        if (i == 2)
        {
            rectY += itemSquareSize + itemSquareSize / 5;
            rectX = startX;
        }
    }
    setToolTip(QString::fromStdString(tooltip));
  }
  else if (event->type() == QEvent::MouseButtonRelease)
  {
      QMouseEvent *mouseEvent = static_cast<QMouseEvent*>( event );
      if (mouseEvent->button() == Qt::MouseButton::RightButton)
      {
          int itemSquareSize = squareSize / 7;
          int rectX = startX;
          int rectY = startY;
          string tooltip = "";
          for (unsigned int i = 0; i < player->carriedItems.size(); i++)
          {
              QRect iconBackgroundRect = QRect(rectX, rectY, itemSquareSize, itemSquareSize);
              if(iconBackgroundRect.contains(mouseEvent->pos()))
              {
                  QMessageBox::StandardButton reply;
                  reply = QMessageBox::warning(this, QString::fromStdString("Delete item"), QString::fromStdString("Do you really want to delete this " + player->carriedItems[i].getShortDescription() + "?\nYou will lose it in the dark."),
                                                  QMessageBox::Yes|QMessageBox::No);
                  if (reply == QMessageBox::Yes)
                  {
                      vector<Item>::iterator itemToDeleted = player->carriedItems.begin() + i;
                      player->carriedItems.erase(itemToDeleted);
                      static_cast<MainWindow*>(this->parent()->parent()->parent())->playerChanged();
                  }
                  break;
              }

              rectX += itemSquareSize + itemSquareSize / 2;
              if (i == 2)
              {
                  rectY += itemSquareSize + itemSquareSize / 5;
                  rectX = startX;
              }
          }
      }

  }

  return QWidget::event( event );
}

ItemWidget::~ItemWidget()
{

}
