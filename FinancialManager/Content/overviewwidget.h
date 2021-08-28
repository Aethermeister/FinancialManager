#ifndef OVERVIEWWIDGET_H
#define OVERVIEWWIDGET_H

#include <QWidget>

namespace Ui {
class OverviewWidget;
}

namespace Content
{
    class OverviewWidget : public QWidget
    {
        Q_OBJECT

    public:
        explicit OverviewWidget(QWidget *parent = nullptr);
        ~OverviewWidget();

    private:
        Ui::OverviewWidget *ui;
    };
}

#endif // OVERVIEWWIDGET_H
