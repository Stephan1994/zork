#ifndef ITEMWIDGET_H
#define ITEMWIDGET_H

#include <QWidget>

namespace Ui {
class ItemWidget;
}

class ItemWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ItemWidget(QWidget *parent = 0);
    ~ItemWidget();

protected:
    void paintEvent(QPaintEvent *e);
private:
    Ui::ItemWidget *ui;
};

#endif // ITEMWIDGET_H
