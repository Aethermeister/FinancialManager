#ifndef RECORDSHISTORYWIDGET_H
#define RECORDSHISTORYWIDGET_H
#include "user.h"
#include "Components/recordhistoryitemwidget.h"

#include <QWidget>

namespace Ui {
class RecordsHistoryWidget;
}

namespace Content
{
    class RecordsHistoryWidget : public QWidget
    {
        Q_OBJECT

    public:
        explicit RecordsHistoryWidget(std::shared_ptr<User> user, QWidget *parent = nullptr);
        ~RecordsHistoryWidget();

    private:
        Ui::RecordsHistoryWidget *ui;

        std::shared_ptr<User> m_user;
        Component::RecordHistoryItemWidget* m_activeRecordItemWidget = nullptr;
    };
}

#endif // RECORDSHISTORYWIDGET_H
