#ifndef HISTORYFILTERWIDGET_H
#define HISTORYFILTERWIDGET_H

#include <QWidget>

namespace Ui {
class HistoryFilterWidget;
}

namespace Content::Component
{
    class HistoryFilterWidget : public QWidget
    {
        Q_OBJECT

    public:
        explicit HistoryFilterWidget(QWidget *parent = nullptr);
        ~HistoryFilterWidget();

    private:
        Ui::HistoryFilterWidget *ui;
    };
}

#endif // HISTORYFILTERWIDGET_H
